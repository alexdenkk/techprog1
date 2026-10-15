#include "Cat.h"

Cat::Cat() : ownerFullName("Не указано"), nickname("Не указана") {
    std::cout << "[Cat] Вызван конструктор без параметров (" << nickname << ")" << std::endl;
}

Cat::Cat(const std::string& breed, const std::string& color,
         const std::string& ownerFullName, const std::string& nickname)
    : Base(breed, color) {
    setOwnerFullName(ownerFullName);
    setNickname(nickname);
    std::cout << "[Cat] Вызван конструктор с параметрами (" << nickname << ")" << std::endl;
}

Cat::Cat(const Cat& other)
    : Base(other), ownerFullName(other.ownerFullName), nickname(other.nickname) {
    std::cout << "[Cat] Вызван конструктор копирования (" << nickname << ")" << std::endl;
}

Cat::~Cat() {
    std::cout << "[Cat] Вызван деструктор (" << nickname << ")" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        Base::operator=(other);
        ownerFullName = other.ownerFullName;
        nickname = other.nickname;
    }
    return *this;
}

bool Cat::operator==(const Cat& other) const {
    return getBreed() == other.getBreed() && getColor() == other.getColor() &&
           ownerFullName == other.ownerFullName && nickname == other.nickname;
}

std::string Cat::getOwnerFullName() const { return ownerFullName; }
std::string Cat::getNickname() const { return nickname; }

void Cat::setOwnerFullName(const std::string& ownerFullName) {
    checkNotEmpty(ownerFullName, "ФИО владельца");
    this->ownerFullName = ownerFullName;
}

void Cat::setNickname(const std::string& nickname) {
    checkNotEmpty(nickname, "Кличка");
    this->nickname = nickname;
}

std::string Cat::getTypeName() const { return "Кошка"; }
std::string Cat::getTypeTag() const { return "CAT"; }

void Cat::print(std::ostream& out) const {
    out << "Кошка: " << nickname << "\n"
        << "    Порода: " << getBreed() << "\n"
        << "    Окрас: " << getColor() << "\n"
        << "    ФИО владельца: " << ownerFullName;
}

Base* Cat::clone() const {
    return new Cat(*this);
}

void Cat::save(std::ostream& out) const {
    out << getBreed() << "\n" << getColor() << "\n" << ownerFullName << "\n" << nickname << "\n";
}

void Cat::load(std::istream& in) {
    setBreed(readField(in));
    setColor(readField(in));
    setOwnerFullName(readField(in));
    setNickname(readField(in));
}
