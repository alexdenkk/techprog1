#include "Bird.h"

Bird::Bird() : food("Не указано"), habitat("Не указано") {
    std::cout << "[Bird] Вызван конструктор без параметров (" << getBreed() << ")" << std::endl;
}

Bird::Bird(const std::string& breed, const std::string& color,
           const std::string& food, const std::string& habitat)
    : Base(breed, color) {
    setFood(food);
    setHabitat(habitat);
    std::cout << "[Bird] Вызван конструктор с параметрами (" << getBreed() << ")" << std::endl;
}

Bird::Bird(const Bird& other) : Base(other), food(other.food), habitat(other.habitat) {
    std::cout << "[Bird] Вызван конструктор копирования (" << getBreed() << ")" << std::endl;
}

Bird::~Bird() {
    std::cout << "[Bird] Вызван деструктор (" << getBreed() << ")" << std::endl;
}

Bird& Bird::operator=(const Bird& other) {
    if (this != &other) {
        Base::operator=(other);
        food = other.food;
        habitat = other.habitat;
    }
    return *this;
}

bool Bird::operator==(const Bird& other) const {
    return getBreed() == other.getBreed() && getColor() == other.getColor() &&
           food == other.food && habitat == other.habitat;
}

std::string Bird::getFood() const { return food; }
std::string Bird::getHabitat() const { return habitat; }

void Bird::setFood(const std::string& food) {
    checkNotEmpty(food, "Чем питается");
    this->food = food;
}

void Bird::setHabitat(const std::string& habitat) {
    checkNotEmpty(habitat, "Где обитает");
    this->habitat = habitat;
}

std::string Bird::getTypeName() const { return "Птица"; }
std::string Bird::getTypeTag() const { return "BIRD"; }

void Bird::print(std::ostream& out) const {
    out << "Птица: " << getBreed() << "\n"
        << "    Окрас: " << getColor() << "\n"
        << "    Чем питается: " << food << "\n"
        << "    Где обитает: " << habitat;
}

Base* Bird::clone() const {
    return new Bird(*this);
}

void Bird::save(std::ostream& out) const {
    out << getBreed() << "\n" << getColor() << "\n" << food << "\n" << habitat << "\n";
}

void Bird::load(std::istream& in) {
    setBreed(readField(in));
    setColor(readField(in));
    setFood(readField(in));
    setHabitat(readField(in));
}
