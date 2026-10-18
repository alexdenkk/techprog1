cmake_minimum_required(VERSION 3.10)
project(Animals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(animals
    src/main.cpp
    src/core/Base.cpp
    src/entities/Fish.cpp
    src/entities/Bird.cpp
    src/entities/Cat.cpp
    src/container/Keeper.cpp
    src/exceptions/AnimalException.cpp
    src/input/Input.cpp
)

if(MSVC)
    # Исходники и строки программы используют UTF-8
    target_compile_options(animals PRIVATE /utf-8 /W4)
else()
    target_compile_options(animals PRIVATE -Wall -Wextra)
endif()
