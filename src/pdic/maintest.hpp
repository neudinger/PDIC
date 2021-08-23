/*
 * File: fakemain.hpp
 * Project: pdic
 * File Created: Friday, 13th August 2021 12:12:51 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Friday, 13th August 2021 12:13:04 pm
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 neudinger
 */

#if !defined(MAIN_TEST)
#define MAIN_TEST

#include <string>
#include <cstdio>
#include <vector>

const std::string runToolOn(const std::string &filepath)
{
  std::ostringstream ostream;
  ostream << std::boolalpha;

  clang::tooling::runToolOnCode(std::make_unique<PDIPluginASTAction>(),
                                get_file_contents(filepath.c_str()));
  serializeIn(ostream);
  PDI::typeIdentifiers.clear();
  PDI::structIdentifiers.clear();
  return ostream.str();
}

const std::string mainTest(const std::vector<std::string> filepaths)
{
  std::ostringstream ostream;
  ostream << std::boolalpha;

  // serialize only runToolOnCode was successfull
  for (const auto &item : filepaths)
    clang::tooling::runToolOnCode(std::make_unique<PDIPluginASTAction>(),
                                  get_file_contents(item.c_str()));
  serializeIn(ostream);
  PDI::typeIdentifiers.clear();
  PDI::structIdentifiers.clear();
  return ostream.str();
}
#endif // !MAIN_TEST