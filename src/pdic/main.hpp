/*
 * File: main.hpp
 * Project: pdic
 * File Created: Wednesday, 4th August 2021 9:43:26 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Wednesday, 9th August 2021 9:46:03 pm
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 neudinger
 */

#if !defined(MAIN)
#define MAIN
#include "clang/Tooling/CommonOptionsParser.h"

static llvm::cl::OptionCategory myToolCategory("pdi options");
// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
static llvm::cl::opt<std::string> outputFile("outputfilename");
static llvm::cl::opt<std::string> printout("stdout");
int main(int argc, const char **argv)
{
    std::ostringstream ostream;
    ostream << std::boolalpha;

    printout.setInitialValue("on");
    // Call ClangTool
    auto expectedParser = clang::tooling::CommonOptionsParser(argc, argv, myToolCategory);
    clang::tooling::ClangTool tool(expectedParser.getCompilations(),
                                   expectedParser.getSourcePathList());
    auto pdiPluging = tool.run(clang::tooling::newFrontendActionFactory<PDIPluginASTAction>().get());

    if (!pdiPluging)
    {
        serializeIn(ostream);
        if (printout.getValue() == "on")
            llvm::outs() << ostream.str() << "\n";
        if (!outputFile.empty())
            writeYML(ostream, outputFile.getValue());
    }
    PDI::typeIdentifiers.clear();
    PDI::structIdentifiers.clear();
    return pdiPluging;
}
#endif // !MAIN