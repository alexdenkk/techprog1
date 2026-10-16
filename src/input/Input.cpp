#include "Input.h"
#include "../exceptions/AnimalException.h"

#include <cerrno>
#include <cstdlib>
#include <iostream>

namespace Input {

std::string readString(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        throw AnimalException("Входной поток закрыт");
    }
    if (!line.empty() && line[line.size() - 1] == '\r') {
        line.erase(line.size() - 1);
    }
    return line;
}

int readInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::string line = readString(prompt);
        char* end = nullptr;
        errno = 0;
        long value = std::strtol(line.c_str(), &end, 10);
        if (line.empty() || end == line.c_str() || *end != '\0' || errno == ERANGE) {
            std::cout << "Ошибка: введите целое число" << std::endl;
        } else if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть от " << min << " до " << max << std::endl;
        } else {
            return static_cast<int>(value);
        }
    }
}

}
