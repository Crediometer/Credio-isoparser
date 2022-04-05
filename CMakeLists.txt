cmake_minimum_required(VERSION 3.19)
project(ISO8583PARSER)

set(CMAKE_CXX_STANDARD 14)

add_library(ISO8583PARSER SHARED
        main.cpp
        "src/Isomessage.cpp"
        headers/utils.h src/utils.cpp
        "src/data.cpp"
        src/DataElementsConfig.cpp
        headers/DataElementsConfig.h
        src/PayAttitude.cpp headers/PayAttitude.h
        src/Iso8583UnpackingFromCards.cpp
        headers/Iso8583UnpackingFromCards.h
        )
