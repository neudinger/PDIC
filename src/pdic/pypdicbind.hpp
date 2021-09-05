/*
 * File: pypdicbind.hpp
 * Project: pdic
 * File Created: Wednesday, 4th August 2021 9:38:33 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Monday, 9th August 2021 3:25:37 pm
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 neudinger
 */

#if !defined(PY_PDIC_BIND)
#define PY_PDIC_BIND
// pip3 install --use-feature=in-tree-build . -v

#include <string>
#include <cstdio>

#include <pybind11/pybind11.h>

namespace python = pybind11;

const std::string getPDIRepFromStr(const char *str)
{
  std::ostringstream ostream;
  ostream << std::boolalpha;

  // serialize only runToolOnCode was successfull
  if (clang::tooling::runToolOnCode(std::make_unique<PDIPluginASTAction>(), str))
    serializeIn(ostream);
#ifdef DEBUG
  llvm::outs() << ostream.str() << "\n"; // <- Usefull for debug
#endif
  PDI::typeIdentifiers.clear();
  PDI::structIdentifiers.clear();
  return ostream.str();
}

const std::string getPDIRepFromFile(const char *filepath)
{
  std::ostringstream ostream;
  ostream << std::boolalpha;

  // serialize only runToolOnCode was successfull
  if (clang::tooling::runToolOnCode(std::make_unique<PDIPluginASTAction>(), get_file_contents(filepath)))
    serializeIn(ostream);
#ifdef DEBUG
  llvm::outs() << ostream.str() << "\n"; // <- Usefull for debug
#endif
  PDI::typeIdentifiers.clear();
  PDI::structIdentifiers.clear();
  return ostream.str();
}

const std::string getPDIRepFromFiles(const python::list filepaths)
{
  std::ostringstream ostream;
  ostream << std::boolalpha;
  // serialize only runToolOnCode was successfull
  for (const auto &item : filepaths)
    clang::tooling::runToolOnCode(std::make_unique<PDIPluginASTAction>(),
                                  get_file_contents(item.cast<std::string>().c_str()));
  serializeIn(ostream);
  PDI::typeIdentifiers.clear();
  PDI::structIdentifiers.clear();
  return ostream.str();
}

using namespace pybind11::literals;

PYBIND11_MODULE(pypdic, m)
{
  m.doc() = "pypdic From C/C++ to Yaml Description C++ pybind API";
  m.def("file_to_pdi", &getPDIRepFromFile,
        "file_to_pdi\n\
        Return yaml in (str)\n\
\n\
        Parameters\n\
        ----------\n\
        filepath : str\n\
            Path of source code\n\
\n\
        Returns\n\
        -------\n\
        str\n\
            Return pdi yaml representation of one file", "filepath"_a);
  m.def("str_to_pdi", &getPDIRepFromStr, 
        "file_to_pdi\n\
        Return yaml in (str)\n\
\n\
        Parameters\n\
        ----------\n\
        filepath : str\n\
            Source code\n\
\n\
        Returns\n\
        -------\n\
        str\n\
            Return pdi yaml representation", 
        "source_code_in_str"_a);
  m.def("files_to_pdi", &getPDIRepFromFiles, 
        "files_to_pdi\n\
        Return yaml in (str)\n\
\n\
        Parameters\n\
        ----------\n\
        filepath : List[str]\n\
            Path of source code\n\
\n\
        Returns\n\
        -------\n\
        str\n\
            Return pdi representation of all files in one yaml", 
        "source_code_in_list"_a);
}
#endif // !PY_PDIC_BIND