#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

// Абстрактный класс «Животное». Порода и окрас есть у всех наследников.
class Base {
private:
    std::string breed;
    std::string color;

public:
    Base();
    Base(const std::string& breed, const std::string& color);
    Base(const Base& other);
    virtual ~Base();

    Base& operator=(const Base& other);

    std::string getBreed() const;
    std::string getColor() const;
    void setBreed(const std::string& breed);
    void setColor(const std::string& color);

    // Название типа для пользователя и метка типа в файле
    virtual std::string getTypeName() const = 0;
    virtual std::string getTypeTag() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Копия того же производного типа для глубокого копирования Keeper
    virtual Base* clone() const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

protected:
    static std::string readField(std::istream& in);
    static void checkNotEmpty(const std::string& value, const std::string& fieldName);
};

std::ostream& operator<<(std::ostream& out, const Base& obj);

#endif
