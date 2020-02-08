#include "Utils.h"
#include "TypesFmd.h"
#include "Constants.h"
#include "../Context.h"

namespace utils
{

    SymbolsCategories CreateSymbolsCategories()
    {
        SymbolsCategories symbolsCategories
                {
                        /// Comment
                        {CharToInt('*'), Categories::StartComment},
                        /// White space
                        {CharToInt(' '), Categories::WhiteSpace},
                        {CharToInt('\n'), Categories::WhiteSpace},
                        {8, Categories ::WhiteSpace}, //backspace
                        {9, Categories ::WhiteSpace}, //Tab
                        /// Digits
                        {CharToInt('0'), Categories::StartConstant},
                        {CharToInt('1'), Categories::StartConstant},
                        {CharToInt('2'), Categories::StartConstant},
                        {CharToInt('3'), Categories::StartConstant},
                        {CharToInt('4'), Categories::StartConstant},
                        {CharToInt('5'), Categories::StartConstant},
                        {CharToInt('6'), Categories::StartConstant},
                        {CharToInt('7'), Categories::StartConstant},
                        {CharToInt('8'), Categories::StartConstant},
                        {CharToInt('9'), Categories::StartConstant},
                        /// Upper Letters
                        {CharToInt('A'), Categories::StartIdentifier},
                        {CharToInt('B'), Categories::StartIdentifier},
                        {CharToInt('C'), Categories::StartIdentifier},
                        {CharToInt('D'), Categories::StartIdentifier},
                        {CharToInt('E'), Categories::StartIdentifier},
                        {CharToInt('F'), Categories::StartIdentifier},
                        {CharToInt('G'), Categories::StartIdentifier},
                        {CharToInt('H'), Categories::StartIdentifier},
                        {CharToInt('I'), Categories::StartIdentifier},
                        {CharToInt('J'), Categories::StartIdentifier},
                        {CharToInt('K'), Categories::StartIdentifier},
                        {CharToInt('L'), Categories::StartIdentifier},
                        {CharToInt('M'), Categories::StartIdentifier},
                        {CharToInt('N'), Categories::StartIdentifier},
                        {CharToInt('O'), Categories::StartIdentifier},
                        {CharToInt('P'), Categories::StartIdentifier},
                        {CharToInt('R'), Categories::StartIdentifier},
                        {CharToInt('S'), Categories::StartIdentifier},
                        {CharToInt('T'), Categories::StartIdentifier},
                        {CharToInt('U'), Categories::StartIdentifier},
                        {CharToInt('V'), Categories::StartIdentifier},
                        {CharToInt('W'), Categories::StartIdentifier},
                        {CharToInt('X'), Categories::StartIdentifier},
                        {CharToInt('Y'), Categories::StartIdentifier},
                        {CharToInt('Z'), Categories::StartIdentifier},
                        /// Small Letters
                        {CharToInt('a'), Categories::StartIdentifier},
                        {CharToInt('b'), Categories::StartIdentifier},
                        {CharToInt('c'), Categories::StartIdentifier},
                        {CharToInt('d'), Categories::StartIdentifier},
                        {CharToInt('e'), Categories::StartIdentifier},
                        {CharToInt('f'), Categories::StartIdentifier},
                        {CharToInt('g'), Categories::StartIdentifier},
                        {CharToInt('h'), Categories::StartIdentifier},
                        {CharToInt('i'), Categories::StartIdentifier},
                        {CharToInt('j'), Categories::StartIdentifier},
                        {CharToInt('k'), Categories::StartIdentifier},
                        {CharToInt('l'), Categories::StartIdentifier},
                        {CharToInt('m'), Categories::StartIdentifier},
                        {CharToInt('n'), Categories::StartIdentifier},
                        {CharToInt('o'), Categories::StartIdentifier},
                        {CharToInt('p'), Categories::StartIdentifier},
                        {CharToInt('r'), Categories::StartIdentifier},
                        {CharToInt('s'), Categories::StartIdentifier},
                        {CharToInt('t'), Categories::StartIdentifier},
                        {CharToInt('u'), Categories::StartIdentifier},
                        {CharToInt('v'), Categories::StartIdentifier},
                        {CharToInt('w'), Categories::StartIdentifier},
                        {CharToInt('x'), Categories::StartIdentifier},
                        {CharToInt('y'), Categories::StartIdentifier},
                        {CharToInt('z'), Categories::StartIdentifier},
                        /// one symbol delimiter
                        {CharToInt('='),  Categories::OneSymbolSeparator},
                        {CharToInt(';'),  Categories::OneSymbolSeparator},
                        {CharToInt(','),  Categories::OneSymbolSeparator},
                        {CharToInt('\\'), Categories::OneSymbolSeparator},

                        {CharToInt('\r'), Categories::ScipSymbol},
                };
        return symbolsCategories;
    }



    TokenNameToCodeMap CreateKeywordsMap()
    {
        auto start = KeywordsNumberStart;
        TokenNameToCodeMap map
                {
                        {"program", ++start},
                        {"deffunc", ++start},
                        {"begin", ++start},
                        {"end", ++start}
                };
        return map;
    }

    Categories GetSymbolCategories(Symbol symbol, const Context& context)
    {
        const auto& symbolsCategories = context.GetSymbolsCategories();
        const auto it = symbolsCategories.find(CharToInt(symbol));
        if(it != symbolsCategories.end())
        {
            return it->second;
        }
        return Categories::ErrorSymbol;
    }

    TokenNumber AddNewIdentifier(TokenView name, TokenNameToCodeMap& identifiers)
    {
        static auto number = IdentifiersNumberStart;
        identifiers.insert({name.data(), ++number});
        return number;
    }

    TokenNumber AddNewConstant(TokenView name, TokenNameToCodeMap& constants)
    {
        static auto number = ConstantsNumberStart;
        constants.insert({name.data(), ++number});
        return number;
    }
}
