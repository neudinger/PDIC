/*
 * File: PDISerializer.hpp
 * Project: PDIC
 * File Created: Wednesday, 21st July 2021 11:55:12 am
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Thursday, 22nd July 2021 12:57:51 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 neudinger
 */

#if !defined(PDI_SERIALIZER)
#define PDI_SERIALIZER
#include "PDITools.hpp"

void DescribeStructs(std::ostringstream &ostream,
                     const PDI::StructMap &structIdentifiers,
                     const std::size_t extraSpaces = 1);

void DescribeStruct(std::ostringstream &ostream,
                    const PDI::StructAttr &structIdentifier,
                    const PDI::StructMap &structIdentifiers,
                    const std::size_t extraSpaces = 1);

void DescribeTypes(std::ostringstream &ostream,
                   const PDI::TypeMap &typeIdentifiers,
                   const PDI::StructMap &structIdentifiers,
                   const std::size_t extraSpaces = 1);

inline void pushCharsIn(std::ostringstream &ostream,
                        const char &c,
                        const std::size_t &nb = 1) noexcept
{
  for (size_t i = 0; i < nb; i++)
    ostream << c;
}

inline std::string duplicateChar(const char &c,
                                 const std::size_t &nb = 1) noexcept
{
  std::ostringstream stream;
  for (size_t i = 0; i < nb; i++)
    stream << c;
  return stream.str();
}

#endif // PDI_SERIALIZER
