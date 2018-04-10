cmake_minimum_required(VERSION 3.5)

project(FF3)

set(CMAKE_CXX_STANDARD 11)
link_directories(/usr/local/lib)

file(GLOB SRC_NFC
        "nfc/src/*.cpp"
        "nfc/include/*.h"
        )

file(GLOB SRC_FOOD
        "food/src/*.cpp"
        "food/include/*.h"
        )

add_executable(main
        src/main.cpp
        ${SRC_NFC}
        ${SRC_FOOD}
        )
target_link_libraries (main nfc)
