/*
 * File: PDITools.hpp
 * Project: src
 * File Created: Wednesday, 12th May 2021 3:23:04 pm
 * Author: kbarre (kevin.barre@epitech.eu)
 * -----
 * Last Modified: Thursday, 22nd July 2021 12:58:12 am
 * Modified By: kbarre (kevin.barre@epitech.eu>)
 * -----
 * Licenses: EUPL
 * -----
 * Copyright 2021 - 2021 NinjaTech
 */

#if !defined(PDI_TOOLS)
#define PDI_TOOLS

#include <string>
#include <map>
#include <iterator>
#include <vector>

#include <sstream> // stringstream
#include <fstream> // ofstream

#include "llvm/ADT/StringSwitch.h" //llvm::StringSwitch

// Import clang::TypeInfo
#include "clang/AST/ASTContext.h"

/// msg must be static const char[N] aka llvm::StringRef - Represent a constant reference to a string, i.e. a character
/// array and a length, which need not be null terminated.
#define RAISE(msg, node) (                                                                    \
    {                                                                                         \
        sourceManager.getDiagnostics().Report(node->getLocation(),                            \
                                              sourceManager.getDiagnostics().getCustomDiagID( \
                                                  clang::DiagnosticsEngine::Error,            \
                                                  msg));                                      \
        PragmaError = true;                                                                   \
    })

#define WARN(msg, node) (                                                                     \
    {                                                                                         \
        sourceManager.getDiagnostics().Report(node->getLocation(),                            \
                                              sourceManager.getDiagnostics().getCustomDiagID( \
                                                  clang::DiagnosticsEngine::Warning,          \
                                                  msg));                                      \
    })

// Number of Bits in one byte
#define BYTE_SIZE 8

namespace PDI
{
    static char const attrAnnotate[] = "annotate";
    typedef struct // Pragma_Identifiers
    {
        std::vector<std::string> arraySizes; // values of arrays length ex [32,45]
        std::string type;                    // variable type ex: int
        const bool isEmpty() const { return (arraySizes.empty() && type.empty()); };
        const bool isNotEmpty() const { return !(arraySizes.empty() && type.empty()); };
        void load(const std::string &attributes);
    } PragmaIdentifiers;
    typedef struct Type_Attr
    {
        PragmaIdentifiers pragma;
        std::string name; // variable name ex: foo
        std::string type; // variable type ex: int
        uintptr_t structId = 0;
        uint8_t starsNbr = 0;                          // number of pointer stars ex 2 if **
        clang::SourceLocation sourceLoc;               // Decl location in c/c++ file
        std::vector<std::string> arraySizes;           // values of arrays length ex [32,45]
        clang::CharUnits::QuantityType buffersize = 0; // size of current value in bytes

        // Struct Field attributes
        uint64_t offset = 0;

        Type_Attr() = default;
        Type_Attr(std::string typeName,
                  std::string typeType,
                  clang::SourceLocation sourceLocation) : name(typeName),
                                                          type(typeType),
                                                          sourceLoc(sourceLocation){};
    } TypeAttr;
    typedef struct // _Switch
    {
        bool isOnRaised = false;
        clang::SourceLocation pdiOnLoc; // On location in c/c++ file
        bool isOffRaised = false;
        clang::SourceLocation pdiOffLoc; // Off location in c/c++ file
        const bool isRaised(const std::ostringstream &StringStream, const clang::SourceLocation &Loc);
    } Switch;

    using TypeMap = std::map<const std::string, TypeAttr>;

    // Struct_Attr
    typedef struct Struct_Attr
    {
        std::string name;                // variable name ex: foo
        clang::SourceLocation sourceLoc; // Decl location in c/c++ file
        clang::CharUnits size;
        std::vector<std::string> alias;
        TypeMap fields;
        // if __attribute__((packed)) or #pragma pack() has been used
        bool packed = false;
        unsigned fieldSize = 0;

        Struct_Attr() = default;
        Struct_Attr(std::string name,
                    clang::CharUnits size,
                    unsigned fieldCount,
                    clang::SourceLocation sourceLocation) : name(name),
                                                            size(size),
                                                            fieldSize(fieldCount),
                                                            sourceLoc(sourceLocation){};
    } StructAttr;

    using StructMap = std::map<const uintptr_t, StructAttr>;

    template <typename MAP>
    struct mapWrapper
    {
        typedef typename MAP::key_type K;
        typedef typename MAP::mapped_type V;
        typedef typename MAP::const_iterator CIT;

        mapWrapper(const MAP &m) : m_map(m) {}

        const V &get(const K &key, const V &default_val) const
        {
            CIT it = m_map.find(key);
            if (it == m_map.end())
                return default_val;
            return it->second;
        }
        constexpr bool const has(const K &key)
        {
            return !(m_map.find(key) == m_map.end());
        }
        constexpr bool const hasNot(const K &key)
        {
            return (m_map.find(key) == m_map.end());
        }

    private:
        const MAP &m_map;
    };

    template <typename MAP>
    mapWrapper<MAP> wrapMap(const MAP &m)
    {
        return mapWrapper<MAP>(m);
    }

    std::string &clean(std::string &str);
    void split(const std::string &str, std::vector<std::string> &cont, const std::string delims = " ");
    uint8_t charLen(const std::string &declstring, const char &elem);
    void describeArray(const std::vector<std::string> &arrays, std::string &typeRepr);
    void extractBetweens(const std::string &str, std::vector<std::string> &container, const std::string delims = "[]");
    void describePointer(const TypeAttr &typeIdentifier, std::string &typeRepr);
    void describePragmaArray(const TypeAttr &typeIdentifier, std::string &typeRepr);

}
#endif // PDI_TOOLS
