/*
 * File: PDIDecls.cpp
 * Project: PDIC
 * File Created: Monday, 10th May 2021 12:23:33 am
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Thursday, 22nd July 2021 12:57:01 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 neudinger
 */

// clang::ASTFrontendAction
#include "clang/AST/RecursiveASTVisitor.h"

// import clang::CompilerInstance
#include "clang/Frontend/CompilerInstance.h"

// import clang::tooling::ClangTool
#include "clang/Tooling/Tooling.h"

// import clang::tooling::CommonOptionsParser
// #include "clang/Tooling/CommonOptionsParser.h" $ only for pdi binary

// use of clang::ASTRecordLayout &typeLayout
#include "clang/AST/RecordLayout.h"

#include "PDIDecls.hpp"

namespace PDI
{
  // Usefull link
  // https://github.com/quarkslab/clang/commit/0163f52f70e4781ce99710575bb66943125357b2

  /// push the declaration of __attribute(annotate(char const*))) into the stream
  /// it is added before each call
  static void PragmaPDItoAnnotate(clang::Preprocessor &PP,
                                  clang::SmallVectorImpl<clang::Token> &TokenList,
                                  std::string AnnotateStr)
  {
    static char const _attrAnnotate[] = "annotate";
    clang::Token AttrNameTok;
    AttrNameTok.startToken();
    AttrNameTok.setKind(clang::tok::string_literal);
    AttrNameTok.setLength(AnnotateStr.size());
    AttrNameTok.setLiteralData(strdup(AnnotateStr.data()));

    clang::Token AttrTok;
    AttrTok.startToken();
    AttrTok.setKind(clang::tok::kw___attribute);

    clang::Token LParTok;
    LParTok.startToken();
    LParTok.setKind(clang::tok::l_paren);

    clang::Token RParTok;
    RParTok.startToken();
    RParTok.setKind(clang::tok::r_paren);

    clang::Token AnnotTok;
    AnnotTok.startToken();
    AnnotTok.setKind(clang::tok::identifier);
    AnnotTok.setIdentifierInfo(PP.getIdentifierInfo(_attrAnnotate));

    TokenList.push_back(AttrTok);
    TokenList.push_back(LParTok);
    TokenList.push_back(LParTok);
    TokenList.push_back(AnnotTok);
    TokenList.push_back(LParTok);
    TokenList.push_back(AttrNameTok);
    TokenList.push_back(RParTok);
    TokenList.push_back(RParTok);
    TokenList.push_back(RParTok);
  }
  void PragmaHandler::HandlePragma(clang::Preprocessor &PP,
                                   clang::PragmaIntroducer Introducer,
                                   clang::Token &PragmaTok)
  {
    clang::Token Tok;
    clang::SmallVector<clang::Token, 10> TokenList;
    std::ostringstream PDIDirectiveStream;

    PDIDirectiveStream << "\"";

    while ((PP.Lex(Tok), true) && Tok.isNot(clang::tok::eod))
      PDIDirectiveStream << PP.getSpelling(Tok);
    if (pdiSwitch.isRaised(/* stringStream= */ PDIDirectiveStream,
                           /* sourceLocation= */ Tok.getLocation()))
      return;

    PDIDirectiveStream << "\"";

    PragmaPDItoAnnotate(PP, TokenList, PDIDirectiveStream.str());
    clang::Token *TokenArray = new clang::Token[TokenList.size()];
    std::copy(TokenList.begin(), TokenList.end(), TokenArray);
    PP.EnterTokenStream(/* Toks= */ llvm::makeArrayRef(TokenArray, TokenList.size()),
                        /* DisableMacroExpansion= */ false,
                        /* IsReinject= */ true);
    // Do NOT delete TokenArray
    // It will remove AST information
  }
  const bool PDIDeclVisitor::VisitVarDecl(const clang::VarDecl *varDecl)
  {
    typeIdentifiers[varDecl->getNameAsString()] = EvalDecl(varDecl);
    return !PragmaError;
  }
  const bool PDIDeclVisitor::VisitRecordDecl(const clang::RecordDecl *recordDecl)
  {
    const clang::ASTRecordLayout &typeLayout(recordDecl->getASTContext().getASTRecordLayout(recordDecl));
    StructAttr curentStruct = StructAttr(/* name= */ recordDecl->getNameAsString(),
                                         /* size= */ typeLayout.getSize(),
                                         /* fieldCount= */ typeLayout.getFieldCount(),
                                         /* sourceLocation= */ recordDecl->getLocation());

    if (!recordDecl->isStruct())
      RAISE("Only struct allowed", recordDecl);

    if (recordDecl->getNameAsString().empty())
      WARN("Anonymous struct used : First alias Or generated ID will be used as StructName", recordDecl);

    // Check if
    // #pragma pack
    // #pragma pack(n)
    // https://docs.microsoft.com/en-us/cpp/preprocessor/pack?view=msvc-160
    // and __attribute__((packed))
    if (const auto *MFAA = recordDecl->getAttr<clang::MaxFieldAlignmentAttr>())
      curentStruct.packed = true;
    else if (recordDecl->getAttr<clang::PackedAttr>())
      curentStruct.packed = true;

    structIdentifiers[reinterpret_cast<uintptr_t>(recordDecl->getTypeForDecl())] = curentStruct;

    // return true if no PragmaError was raised
    // This method must return true if no error occurred
    // PragmaError must alway be false if no error occurred
    return !PragmaError;
  }
  const bool PDIDeclVisitor::VisitFieldDecl(const clang::FieldDecl *fieldDecl)
  {
    const auto recordAddr = reinterpret_cast<uintptr_t>(fieldDecl->getParent()->getTypeForDecl());
    auto &curentStruct = structIdentifiers[recordAddr];
    const clang::ASTRecordLayout &typeLayout = fieldDecl->getASTContext().getASTRecordLayout(fieldDecl->getParent());
    TypeAttr curentType = EvalDecl(fieldDecl);

    if (!fieldDecl->getParent()->isStruct())
      RAISE("Only struct type are suported", fieldDecl);

    if (wrapMap(structIdentifiers).hasNot(/* key= */ recordAddr))
      RAISE("Parent record type are not suported", fieldDecl);

    // Add offset on each field base on padding and packing struct memory alignement
    curentType.offset = typeLayout.getFieldOffset(fieldDecl->getFieldIndex()) / BYTE_SIZE;

    // Add Field description to current struct description
    curentStruct.fields[fieldDecl->getNameAsString()] = curentType;

    // return true if no PragmaError was raised
    // This must return true if no error occurred
    // PragmaError must alway be false if no error occurred
    return !PragmaError;
  }
  const bool PDIDeclVisitor::VisitTypedefDecl(const clang::TypedefDecl *typedefDecl)
  {
    // Retreive struct inserted during VisitRecordDecl process
    auto &curentStruct = structIdentifiers[reinterpret_cast<uintptr_t>(typedefDecl->getTypeSourceInfo()->getType()->getAs<clang::RecordType>())];
    // Define this alias as global name if struct is Anonymous
    if (curentStruct.name.empty())
      curentStruct.name = typedefDecl->getNameAsString();
    // Add typedef alias to this struct description
    curentStruct.alias.push_back(typedefDecl->getNameAsString());
    return true;
  }
  bool ASTConsumerDeclConsumer::HandleTopLevelDecl(clang::DeclGroupRef dg)
  {
    for (clang::Decl *decl : dg)
    {
      /// Create Custom annotation
      // decl->addAttr(clang::AnnotateAttr::CreateImplicit(decl->getASTContext(),
      // pragmaTypeIdentifiers.type));

      /// Check if the current declaration is between pragma on and off
      /// pragma pdi on
      /// (decl)
      /// pragma pdi off
      if (!(pdiSwitch.isOnRaised && IsBefore(/* LHS= */ pdiSwitch.pdiOnLoc,
                                             /* RHS= */ decl->getLocation())) ||
          (pdiSwitch.isOffRaised && IsBefore(/* LHS= */ pdiSwitch.pdiOffLoc,
                                             /* RHS= */ decl->getLocation())))
        break;
#ifdef DEBUG
      decl->dumpColor(); // <- Usefull for debug
#endif
      /// Stop if any error occurred
      if (!declNodeVisitor.TraverseDecl(decl) ||
          compilerInstance.getSourceManager().getDiagnostics().hasErrorOccurred())
        return false;
    }
    return true;
  }
}

class PDIPluginASTAction : public clang::ASTFrontendAction
{
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &compilerInstance,
                    const llvm::StringRef fileName) override
  {
    clang::Preprocessor &PP = compilerInstance.getPreprocessor();
    PP.AddPragmaHandler(new PDI::PragmaHandler());
    return std::make_unique<PDI::ASTConsumerDeclConsumer>(compilerInstance);
  }
};

void serializeIn(std::ostringstream &ostream)
{
  if (!PDI::structIdentifiers.empty())
    ostream << "structs:\n";
  DescribeStructs(ostream, PDI::structIdentifiers);
  if (!PDI::typeIdentifiers.empty())
    ostream << "data:\n";
  DescribeTypes(ostream,
                PDI::typeIdentifiers,
                PDI::structIdentifiers);
}

void writeYML(const std::ostringstream &ostream,
              const std::string &firstSourceFile)
{
  std::string outputFileName(firstSourceFile);
  std::ofstream outputFile(outputFileName
                                   .substr(0, outputFileName.find_last_of('.')) +
                               ".yml",
                           std::ios::trunc | std::ios::out);
  outputFile << ostream.str();
  outputFile.close();
}

// clang::tooling::runToolOnCode(std::make_unique<FindNamedClassAction>(), "namespace n { namespace m { class C {}; } }");
// std::unique_ptr<ASTUnit> AST(tooling::buildASTFromCode("auto x = 1 + 1;"));
// TranslationUnitDecl *DC = AST->getASTContext().getTranslationUnitDecl();

#if defined(SKBUILD)
  #include "pypdicbind.hpp"
#elif defined(GOOGLE_TEST)
  #include "maintest.hpp"
#else
  #include "main.hpp"
#endif // SKBUILD