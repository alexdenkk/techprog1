#include "Fish.h"

Fish::Fish() : foodType("Не указан") {
    std::cout << "[Fish] Вызван конструктор без параметров (" << getBreed() << ")" << std::endl;
}

Fish::Fish(const std::string& breed, const std::string& color, const std::string& foodType)
    : Base(breed, color) {
    setFoodType(foodType);
    std::cout << "[Fish] Вызван конструктор с параметрами (" << getBreed() << ")" << std::endl;
}

Fish::Fish(const Fish& other) : Base(other), foodType(other.foodType) {
    std::cout << "[Fish] Вызван конструктор копирования (" << getBreed() << ")" << std::endl;
}

Fish::~Fish() {
    std::cout << "[Fish] Вызван деструктор (" << getBreed() << ")" << std::endl;
}

Fish& Fish::operator=(const Fish& other) {
    if (this != &other) {
        Base::operator=(other);
        foodType = other.foodType;
    }
    return *this;
}

bool Fish::operator==(const Fish& other) const {
    return getBreed() == other.getBreed() && getColor() == other.getColor() &&
           foodType == other.foodType;
}

std::string Fish::getFoodType() const { return foodType; }

void Fish::setFoodType(const std::string& foodType) {
    checkNotEmpty(foodType, "Тип питания");
    this->foodType = foodType;
}

std::string Fish::getTypeName() const { return "Рыба"; }
std::string Fish::getTypeTag() const { return "FISH"; }

void Fish::print(std::ostream& out) const {
    out << "Рыба: " << getBreed() << "\n"
        << "    Окрас: " << getColor() << "\n"
        << "    Тип питания: " << foodType;
}

Base* Fish::clone() const {
    return new Fish(*this);
}

void Fish::save(std::ostream& out) const {
    out << getBreed() << "\n" << getColor() << "\n" << foodType << "\n";
}

void Fish::load(std::istream& in) {
    setBreed(readField(in));
    setColor(readField(in));
    setFoodType(readField(in));
}
