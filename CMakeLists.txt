cmake_minimum_required(VERSION 3.14)
project(Translator)

set(CMAKE_CXX_STANDARD 17)


add_executable(Projects
        Translator/Token/BaseElement.h
        Translator/Token/Digit.cpp
        Translator/Token/Digit.h
        Translator/Token/Error.cpp
        Translator/Token/Error.h
        Translator/Token/Identifier.cpp
        Translator/Token/Identifier.h
        Translator/LexicalAnalyzer.cpp
        Translator/LexicalAnalyzer.h
        Translator/main.cpp
        Translator/Token/WhiteSpace.cpp
        Translator/Token/WhiteSpace.h
        Translator/Context.cpp
        Translator/Context.h
        Translator/Common/TypesFmd.h
        Translator/Common/Utils.h
        Translator/Common/Utils.cpp
        Translator/Common/Constants.h
        Translator/Token/Comment.cpp
        Translator/Token/Comment.h
        Translator/Token/OneSymbolSeparator.cpp
        Translator/Token/OneSymbolSeparator.h)

