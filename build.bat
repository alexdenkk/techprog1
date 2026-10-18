@echo off
rem Build with g++ (MinGW / MSYS2). Output: build\animals.exe
if not exist build mkdir build
g++ -std=c++17 -Wall -Wextra ^
    src\main.cpp ^
    src\core\Base.cpp ^
    src\entities\Fish.cpp src\entities\Bird.cpp src\entities\Cat.cpp ^
    src\container\Keeper.cpp ^
    src\exceptions\AnimalException.cpp ^
    src\input\Input.cpp ^
    -o build\animals.exe
if errorlevel 1 (
    echo Build failed
    exit /b 1
)
echo Done: build\animals.exe
