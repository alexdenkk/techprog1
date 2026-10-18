#!/bin/sh
# Сборка программы компилятором g++. Результат: build/animals
set -e
cd "$(dirname "$0")"
mkdir -p build
g++ -std=c++17 -Wall -Wextra \
    src/main.cpp src/core/Base.cpp \
    src/entities/Fish.cpp src/entities/Bird.cpp src/entities/Cat.cpp \
    src/container/Keeper.cpp src/exceptions/AnimalException.cpp src/input/Input.cpp \
    -o build/animals
printf 'Готово: build/animals\n'
