#ifndef INPUT_H
#define INPUT_H

#include <string>

// Ввод с клавиатуры с проверкой корректности.
// При закрытии входного потока (Ctrl+Z / Ctrl+D) бросает AnimalException.
namespace Input {
    std::string readString(const std::string& prompt);
    int readInt(const std::string& prompt, int min, int max);
}

#endif
