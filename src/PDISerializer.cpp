/*
 * File: PDISerializer.cpp
 * Project: src
 * File Created: Wednesday, 21st July 2021 11:54:17 am
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Thursday, 22nd July 2021 12:57:43 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 NinjaTech
 */

#include "PDISerializer.hpp"

void DescribeStruct(std::ostringstream &ostream,
                    const PDI::StructAttr &structIdentifier,
                    const PDI::StructMap &structIdentifiers,
                    const std::size_t extraSpaces)
{
  ostream << duplicateChar(' ', extraSpaces) << "type: record\n";
  ostream << duplicateChar(' ', extraSpaces) << "name: " << structIdentifier.name << "\n";
  if (!structIdentifier.alias.empty())
  {
    ostream << duplicateChar(' ', extraSpaces) << "alias: [";
    std::copy(structIdentifier.alias.cbegin(), structIdentifier.alias.cend() - 1,
              std::ostream_iterator<std::string>(ostream, ", "));
    ostream << structIdentifier.alias.back() << "]\n";
  }
  ostream << duplicateChar(' ', extraSpaces) << "fieldsize: " << structIdentifier.fieldSize << "\n";
  ostream << duplicateChar(' ', extraSpaces) << "buffersize: " << structIdentifier.size.getQuantity() << "\n";
  ostream << duplicateChar(' ', extraSpaces) << "packed: " << structIdentifier.packed << "\n";
  ostream << duplicateChar(' ', extraSpaces) << "members:\n";
  DescribeTypes(ostream,
                structIdentifier.fields,
                structIdentifiers,
                extraSpaces + 1);
}

void DescribeStructs(std::ostringstream &ostream,
                     const PDI::StructMap &structIdentifiers,
                     const std::size_t extraSpaces)
{
  for (const auto &[structID, structIdentifier] : structIdentifiers)
  {
    ostream << duplicateChar(' ', extraSpaces) << structIdentifier.name << ":\n";
    DescribeStruct(ostream,
                   structIdentifier,
                   structIdentifiers,
                   extraSpaces + 1);
  }
}

void DescribeTypes(std::ostringstream &ostream,
                   const PDI::TypeMap &typeIdentifiers,
                   const PDI::StructMap &structIdentifiers,
                   const std::size_t extraSpaces)
{
  std::string typeRepr;
  for (const auto &[typeIdentifierName, typeIdentifier] : typeIdentifiers)
  {
    pushCharsIn(ostream, ' ', extraSpaces);
    ostream << typeIdentifier.name << ':';
    typeRepr = typeIdentifier.type;
    if (typeIdentifier.offset)
    {
      ostream << "\n";
      pushCharsIn(ostream, ' ', extraSpaces + 1);
      ostream << "offset: " << typeIdentifier.offset;
    }
    if (typeIdentifier.pragma.isNotEmpty())
    {
      if (!typeIdentifier.pragma.type.empty())
        typeRepr = typeIdentifier.pragma.type;
      if (!typeIdentifier.pragma.arraySizes.empty())
        PDI::describePragmaArray(typeIdentifier, typeRepr);
      if (typeIdentifier.starsNbr)
        PDI::describePointer(typeIdentifier, typeRepr);
      if (typeRepr == typeIdentifier.pragma.type)
        typeRepr = "\n" +
                   duplicateChar(' ', extraSpaces + 1) + "type: " + typeRepr;
      ostream << typeRepr;
    }
    else
    {
      if (typeIdentifier.starsNbr)
        PDI::describePointer(typeIdentifier, typeRepr);
      if (!typeIdentifier.arraySizes.empty())
        PDI::describeArray(typeIdentifier.arraySizes, typeRepr);
      if (typeIdentifier.structId)
      {
        ostream << "\n";
        DescribeStruct(ostream,
                       wrapMap(structIdentifiers).get(typeIdentifier.structId, PDI::StructAttr()),
                       structIdentifiers,
                       extraSpaces + 1);
        typeRepr.clear();
      }
      else if (typeIdentifier.type == typeRepr)
      {
        pushCharsIn(ostream, ' ', extraSpaces);
        typeRepr = "\n" +
                   duplicateChar(' ', extraSpaces + 1) + "type: " + typeRepr;
      }
      ostream << typeRepr;
    }
    ostream << "\n";
    typeRepr.clear();
  }
}