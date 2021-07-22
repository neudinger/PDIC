/*
 * File: PDITools.cpp
 * Project: src
 * File Created: Wednesday, 12th May 2021 3:23:04 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Thursday, 22nd July 2021 12:58:00 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 NinjaTech
 */

#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>

#include "PDITools.hpp"

#define BOOST_NO_EXCEPTIONS
void boost::throw_exception(std::exception const &e) {}

namespace PDI
{
    static inline bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
    // trim from start (in place)
    static inline std::string &ltrim(std::string &str)
    {
        str.erase(str.begin(),
                  std::find_if(
                      str.begin(), str.end(),
                      [](const uint8_t &ch) -> bool
                      {
                          return !std::isspace(ch);
                      }));
        return str;
    }

    // trim from end (in place)
    static inline std::string &rtrim(std::string &str)
    {
        str.erase(std::find_if(
                      str.rbegin(), str.rend(),
                      [](const uint8_t &ch) -> bool
                      {
                          return !std::isspace(ch);
                      })
                      .base(),
                  str.end());
        return str;
    }

    // trim from both ends (in place)
    static inline std::string &trim(std::string &str)
    {
        return rtrim(ltrim(str));
    }

    std::string &clean(std::string &str)
    {
        trim(str);
        std::string::iterator new_end(std::unique(str.begin(), str.end(), BothAreSpaces));
        str.erase(new_end, str.end());
        return str;
    }

    void split(const std::string &str,
               std::vector<std::string> &cont,
               const std::string delims)
    {
        boost::split(cont, str, boost::is_any_of(delims));
    }

    uint8_t charLen(const std::string &declstring, const char &elem)
    {
        if (declstring.find(elem) != std::string::npos)
            return (declstring.find_last_of(elem) - declstring.find_first_of(elem) + 1);
        return 0;
    }

    // Extract all values between [] and [][]...[] and add to container
    void extractBetweens(const std::string &str,
                         std::vector<std::string> &container,
                         const std::string delims)
    {
        assert(delims.length() == 2 ? true : false);
        std::size_t side_left, side_right = 0;
        while ((side_left = str.find(delims[0], side_right)) != std::string::npos)
        {
            side_right = str.find(delims[1], side_left);
            container.push_back(str.substr(side_left + 1, (side_right - (side_left + 1))));
        }
    }

    void describePointer(const TypeAttr &typeIdentifier,
                         uint8_t &starsNbr,
                         const std::string &typeRepr,
                         std::ostringstream &ostream)
    {
        ostream << " { type: pointer, subtype: ";
        if (--starsNbr)
            describePointer(typeIdentifier, starsNbr, typeRepr, ostream);
        else
            ostream << typeRepr;
        ostream << " }";
    }

    void describePointer(const TypeAttr &typeIdentifier,
                         std::string &typeRepr)
    {
        uint8_t starsNbr;
        std::ostringstream ostream;
        if (__builtin_sub_overflow(typeIdentifier.starsNbr, typeIdentifier.pragma.arraySizes.size(), &starsNbr))
        {
            llvm::errs() << "cannot describe Pointer of"
                         << typeIdentifier.type
                         << " " << typeIdentifier.name << " \n";
            return;
        }
        ostream << " { type: pointer, subtype: ";
        if (--starsNbr)
            describePointer(typeIdentifier, starsNbr, typeRepr, ostream);
        else
            ostream << typeRepr;
        ostream << " }";
        typeRepr = ostream.str();
    }

    void describeArray(const std::vector<std::string> &arrays,
                       std::string &typeRepr)
    {
        std::ostringstream ostream;
        const std::size_t arrayLengh = arrays.size();

        ostream << " { type: array, subtype: "
                << typeRepr
                << ", size: " << (arrayLengh > 1 ? "[" : "");

        std::copy(arrays.cbegin(), arrays.cend() - 1,
                  std::ostream_iterator<std::string>(ostream, ", "));
        ostream << arrays.back() << (arrayLengh > 1 ? "]" : "") << " }";

        typeRepr = ostream.str();
    }

    void describePragmaArray(const TypeAttr &typeIdentifier,
                             std::string &typeRepr)
    {
        describeArray(typeIdentifier.pragma.arraySizes, typeRepr);
    }

    std::map<std::string, std::string>
    stringToMap(const std::string &str)
    {
        std::map<std::string, std::string> pragmaParamsMap;
        std::vector<std::string> pragmaParamsList;
        std::vector<std::string> pragmaParamsVect;
        split(str, pragmaParamsList, ";");
        for (const auto &pragma : pragmaParamsList)
        {
            split(pragma, pragmaParamsVect, ":");
            if (pragmaParamsVect.size() == 2)
                pragmaParamsMap[pragmaParamsVect[0]] = pragmaParamsVect[1];
            pragmaParamsVect.clear();
        }
        return pragmaParamsMap;
    }

    void PragmaIdentifiers::load(const std::string &attributes)
    {
        auto annotAttr = stringToMap(attributes);
        this->type = wrapMap(annotAttr).get(/* key= */ "type",
                                            /* default_val= */ this->type);
        extractBetweens(annotAttr["size"], /* &container */ this->arraySizes);
    }

    const bool Switch::isRaised(const std::ostringstream &stringStream,
                                const clang::SourceLocation &sourceLocation)
    {
        if (stringStream.str() == "\"on")
        {
            this->isOffRaised = false;
            this->isOnRaised = true;
            this->pdiOnLoc = sourceLocation;
        }
        else if (stringStream.str() == "\"off")
        {
            this->isOffRaised = true;
            this->pdiOffLoc = sourceLocation;
        }
        else
            return false;
        return true;
    }

}