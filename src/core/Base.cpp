#include "Base.h"
#include "../exceptions/AnimalException.h"

Base::Base() : breed("Не указана"), color("Не указан") {
    std::cout << "[Base] Вызван конструктор без параметров (" << breed << ")" << std::endl;
}

Base::Base(const std::string& breed, const std::string& color) {
    setBreed(breed);
    setColor(color);
    std::cout << "[Base] Вызван конструктор с параметрами (" << breed << ")" << std::endl;
}

Base::Base(const Base& other) : breed(other.breed), color(other.color) {
    std::cout << "[Base] Вызван конструктор копирования (" << breed << ")" << std::endl;
}

Base::~Base() {
    std::cout << "[Base] Вызван деструктор (" << breed << ")" << std::endl;
}

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        breed = other.breed;
        color = other.color;
    }
    return *this;
}

std::string Base::getBreed() const { return breed; }
std::string Base::getColor() const { return color; }

void Base::setBreed(const std::string& breed) {
    checkNotEmpty(breed, "Порода");
    this->breed = breed;
}

void Base::setColor(const std::string& color) {
    checkNotEmpty(color, "Окрас");
    this->color = color;
}

std::string Base::readField(std::istream& in) {
    std::string line;
    if (!std::getline(in, line)) {
        throw AnimalException("Ошибка чтения файла: данные животного обрываются");
    }
    // Поддерживаем файлы с окончаниями строк Windows (\r\n)
    if (!line.empty() && line[line.size() - 1] == '\r') {
        line.erase(line.size() - 1);
    }
    return line;
}

void Base::checkNotEmpty(const std::string& value, const std::string& fieldName) {
    if (value.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw AnimalException("Поле \"" + fieldName + "\" не может быть пустым");
    }
    // В файле каждому полю соответствует ровно одна строка
    if (value.find_first_of("\r\n") != std::string::npos) {
        throw AnimalException("Поле \"" + fieldName + "\" не должно содержать переводов строки");
    }
}

std::ostream& operator<<(std::ostream& out, const Base& obj) {
    obj.print(out);
    return out;
}
