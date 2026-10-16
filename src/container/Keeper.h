#ifndef KEEPER_H
#define KEEPER_H

#include "../core/Base.h"

// Контейнер животных: динамический массив указателей на Base.
// Keeper владеет переданными ему объектами и сам освобождает память.
class Keeper {
private:
    std::string name;
    Base** items;
    int count;
    int capacity;

    void grow();
    void checkIndex(int index) const;
    void swapWith(Keeper& other);
    static Base* createByTag(const std::string& tag);

public:
    Keeper();
    explicit Keeper(const std::string& name);
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);
    Keeper& operator+=(Base* obj);
    Base& operator[](int index);
    const Base& operator[](int index) const;

    std::string getName() const;
    void setName(const std::string& name);
    int getCount() const;
    bool isEmpty() const;

    // Принимает владение новым объектом, в том числе при ошибке расширения
    void add(Base* obj);
    void remove(int index);
    void clear();
    void print(std::ostream& out) const;

    void saveToFile(const std::string& fileName) const;
    void loadFromFile(const std::string& fileName);
};

std::ostream& operator<<(std::ostream& out, const Keeper& keeper);

#endif
