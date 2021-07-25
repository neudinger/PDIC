/*
 * File: PDIDecls.hpp
 * Project: PDIC
 * File Created: Wednesday, 21st July 2021 4:34:34 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Thursday, 22nd July 2021 12:57:37 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 NinjaTech
 */

#if !defined(PDI_DECLS)
#define PDI_DECLS
#include "PDITools.hpp"
#include "PDISerializer.hpp"

namespace PDI
{
    static bool PragmaError = false;
    static TypeMap typeIdentifiers;
    static StructMap structIdentifiers;
    static Switch pdiSwitch;

    class PragmaHandler : public clang::PragmaHandler
    {
    public:
        PragmaHandler() : clang::PragmaHandler() {}

        void HandlePragma(clang::Preprocessor &PP,
                          clang::PragmaIntroducer Introducer,
                          clang::Token &PragmaTok) override;
    };

    // RecursiveASTVisitor does a pre-order depth-first traversal of the
    // AST. We implement VisitFoo() methods for the types of nodes we are
    // interested in.
    class PDIDeclVisitor : public clang::RecursiveASTVisitor<PDIDeclVisitor>
    {
    private:
        const clang::SourceManager &sourceManager;
        template <typename DECL>
        TypeAttr EvalDecl(DECL nodeDecl)
        {

            TypeAttr curentId;
            std::vector<std::string> declTypes;
            const std::string declString(nodeDecl->getType().getAsString());
            const clang::TypeInfo typeInfo = nodeDecl->getASTContext().getTypeInfo(nodeDecl->getType());

            if (declString.find("struct (") != std::string::npos)
                RAISE("Anonymous struct without typedef not allowed", nodeDecl);

            if (nodeDecl->getType()->template getAs<clang::Type>()->isStructureType())
                curentId.structId = reinterpret_cast<uintptr_t>(nodeDecl->getType()->template getAs<clang::RecordType>());

            curentId.sourceLoc = nodeDecl->getLocation();
            curentId.name = nodeDecl->getNameAsString();
            split(declString, declTypes);
            curentId.type = (declTypes.size() > 1) ? *(--(--declTypes.cend())) : declTypes.back();
            curentId.starsNbr = charLen(declString, '*');
            extractBetweens(declTypes.back(), curentId.arraySizes);
            for (const auto &attr : nodeDecl->getAttrs())
                if (attr->getKind() == clang::Attr::Kind::AT_CFUnknownTransfer &&
                    attr->getSpelling() == "annotate")
                    curentId.pragma.load(/* attributes= */
                                         (static_cast<clang::AnnotateAttr *>(attr))->getAnnotation().str());
            if (curentId.starsNbr &&
                curentId.pragma.arraySizes.size() >= curentId.starsNbr)
                RAISE("Numbers of stars must be > in Pragma array", nodeDecl);

            curentId.buffersize = typeInfo.Width / BYTE_SIZE;

            return curentId;
        }

    public:
        explicit PDIDeclVisitor(const clang::SourceManager &SM) : sourceManager(SM) {}
        const bool VisitVarDecl(const clang::VarDecl *varDecl);
        // Struct handler
        const bool VisitRecordDecl(const clang::RecordDecl *recordDecl);
        const bool VisitFieldDecl(const clang::FieldDecl *fieldDecl);
        // This will add any alias to the existing structures
        const bool VisitTypedefDecl(const clang::TypedefDecl *typedefDecl);
    };

    // An ASTConsumer is a client object that receives callbacks as the AST is
    // built, and "consumes" it.
    class ASTConsumerDeclConsumer : public clang::ASTConsumer
    {
    private:
        PDIDeclVisitor declNodeVisitor;
        clang::CompilerInstance &compilerInstance;

        ///   Return true If LHS is located before RHS
        constexpr bool const IsBefore(const clang::SourceLocation &LHS,
                                      const clang::SourceLocation RHS)
        {
            return compilerInstance.getSourceManager().isBeforeInTranslationUnit(LHS, RHS);
        }

    public:
        explicit ASTConsumerDeclConsumer(clang::CompilerInstance &CI)
            : declNodeVisitor(PDIDeclVisitor(CI.getSourceManager())),
              compilerInstance(CI) {}

        // Called by the parser for each top-level declaration group.
        // Returns true to continue parsing, or false to abort parsing.
        virtual bool HandleTopLevelDecl(clang::DeclGroupRef dg) override;
    };
}
#endif // PDI_DECLS
