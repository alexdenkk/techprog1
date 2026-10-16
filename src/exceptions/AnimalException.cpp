#include "AnimalException.h"

#include <iostream>

AnimalException::AnimalException() : message("Неизвестная ошибка") {
    std::cout << "[AnimalException] Вызван конструктор без параметров (" << message << ")" << std::endl;
}

AnimalException::AnimalException(const std::string& message) : message(message) {
    std::cout << "[AnimalException] Вызван конструктор с параметрами (" << message << ")" << std::endl;
}

AnimalException::AnimalException(const AnimalException& other)
    : std::exception(other), message(other.message) {
    std::cout << "[AnimalException] Вызван конструктор копирования (" << message << ")" << std::endl;
}

AnimalException::~AnimalException() noexcept {
    std::cout << "[AnimalException] Вызван деструктор (" << message << ")" << std::endl;
}

AnimalException& AnimalException::operator=(const AnimalException& other) {
    if (this != &other) {
        std::exception::operator=(other);
        message = other.message;
    }
    return *this;
}

std::string AnimalException::getMessage() const { return message; }
void AnimalException::setMessage(const std::string& message) { this->message = message; }

const char* AnimalException::what() const noexcept {
    return message.c_str();
}
