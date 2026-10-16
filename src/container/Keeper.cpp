#include "Keeper.h"
#include "../entities/Fish.h"
#include "../entities/Bird.h"
#include "../entities/Cat.h"
#include "../exceptions/AnimalException.h"

#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <utility>

static const char* FILE_HEADER = "ANIMAL_KEEPER";
static const int INITIAL_CAPACITY = 4;

Keeper::Keeper()
    : name("Животные"), items(new Base*[INITIAL_CAPACITY]), count(0), capacity(INITIAL_CAPACITY) {
    std::cout << "[Keeper] Вызван конструктор без параметров (" << name << ")" << std::endl;
}

Keeper::Keeper(const std::string& name)
    : name("Животные"), items(new Base*[INITIAL_CAPACITY]), count(0), capacity(INITIAL_CAPACITY) {
    try {
        setName(name);
    } catch (...) {
        delete[] items;
        throw;
    }
    std::cout << "[Keeper] Вызван конструктор с параметрами (" << this->name << ")" << std::endl;
}

Keeper::Keeper(const Keeper& other)
    : name(other.name), items(new Base*[other.capacity]), count(0), capacity(other.capacity) {
    // Глубокое копирование: контейнеры не разделяют одни и те же объекты
    try {
        for (int i = 0; i < other.count; i++) {
            items[i] = other.items[i]->clone();
            count++;
        }
    } catch (...) {
        clear();
        delete[] items;
        throw;
    }
    std::cout << "[Keeper] Вызван конструктор копирования (" << name << ")" << std::endl;
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Вызван деструктор (" << name << ")" << std::endl;
    clear();
    delete[] items;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        // Старые данные окажутся в copy и удалятся её деструктором
        swapWith(copy);
    }
    return *this;
}

Keeper& Keeper::operator+=(Base* obj) {
    add(obj);
    return *this;
}

Base& Keeper::operator[](int index) {
    checkIndex(index);
    return *items[index];
}

const Base& Keeper::operator[](int index) const {
    checkIndex(index);
    return *items[index];
}

void Keeper::swapWith(Keeper& other) {
    std::swap(name, other.name);
    std::swap(items, other.items);
    std::swap(count, other.count);
    std::swap(capacity, other.capacity);
}

std::string Keeper::getName() const { return name; }

void Keeper::setName(const std::string& name) {
    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw AnimalException("Название контейнера не может быть пустым");
    }
    if (name.find_first_of("\r\n") != std::string::npos) {
        throw AnimalException("Название контейнера не должно содержать переводов строки");
    }
    this->name = name;
}

int Keeper::getCount() const { return count; }
bool Keeper::isEmpty() const { return count == 0; }

void Keeper::grow() {
    if (capacity > std::numeric_limits<int>::max() / 2) {
        throw AnimalException("Достигнут предельный размер контейнера");
    }
    int newCapacity = capacity * 2;
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < count; i++) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

void Keeper::checkIndex(int index) const {
    if (index < 0 || index >= count) {
        throw AnimalException("Индекс " + std::to_string(index) +
                              " вне диапазона (всего животных: " + std::to_string(count) + ")");
    }
}

void Keeper::add(Base* obj) {
    if (obj == nullptr) {
        throw AnimalException("Нельзя добавить пустой объект");
    }
    try {
        if (count == capacity) {
            grow();
        }
    } catch (...) {
        delete obj;
        throw;
    }
    items[count++] = obj;
}

void Keeper::remove(int index) {
    checkIndex(index);
    delete items[index];
    for (int i = index; i < count - 1; i++) {
        items[i] = items[i + 1];
    }
    items[--count] = nullptr;
}

void Keeper::clear() {
    for (int i = 0; i < count; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    count = 0;
}

void Keeper::print(std::ostream& out) const {
    out << "=== " << name << " (животных: " << count << ") ===\n";
    if (count == 0) {
        out << "    Список пуст\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        out << i + 1 << ". " << *items[i] << "\n";
    }
}

Base* Keeper::createByTag(const std::string& tag) {
    if (tag == "FISH") return new Fish();
    if (tag == "BIRD") return new Bird();
    if (tag == "CAT") return new Cat();
    throw AnimalException("Ошибка чтения файла: неизвестный тип животного \"" + tag + "\"");
}

void Keeper::saveToFile(const std::string& fileName) const {
    std::ofstream out(fileName);
    if (!out.is_open() || !out) {
        throw AnimalException("Не удалось открыть файл \"" + fileName + "\" для записи");
    }
    out << FILE_HEADER << "\n" << name << "\n" << count << "\n";
    for (int i = 0; i < count; i++) {
        out << items[i]->getTypeTag() << "\n";
        items[i]->save(out);
    }
    out.close();
    if (!out) {
        throw AnimalException("Ошибка записи в файл \"" + fileName + "\"");
    }
}

// Чтение строки без завершающего '\r' (если файл правили в Windows)
static std::string readLine(std::istream& in) {
    std::string line;
    if (!std::getline(in, line)) {
        throw AnimalException("Ошибка чтения файла: файл обрывается");
    }
    if (!line.empty() && line[line.size() - 1] == '\r') {
        line.erase(line.size() - 1);
    }
    return line;
}

void Keeper::loadFromFile(const std::string& fileName) {
    std::ifstream in(fileName);
    if (!in.is_open() || !in) {
        throw AnimalException("Не удалось открыть файл \"" + fileName + "\" для чтения");
    }
    if (readLine(in) != FILE_HEADER) {
        throw AnimalException("Файл \"" + fileName + "\" не является файлом животных");
    }

    // Текущие данные заменяются только после успешного чтения всего файла
    Keeper loaded(readLine(in));
    std::string countLine = readLine(in);
    char* end = nullptr;
    errno = 0;
    long total = std::strtol(countLine.c_str(), &end, 10);
    if (countLine.empty() || end == countLine.c_str() || *end != '\0' ||
        errno == ERANGE || total < 0 || total > std::numeric_limits<int>::max()) {
        throw AnimalException("Ошибка чтения файла: неверное количество животных");
    }
    for (long i = 0; i < total; i++) {
        Base* obj = createByTag(readLine(in));
        try {
            obj->load(in);
        } catch (...) {
            delete obj;
            throw;
        }
        // add сам освобождает obj, если расширение массива не удалось
        loaded.add(obj);
    }
    std::string extra;
    while (std::getline(in, extra)) {
        if (extra.find_first_not_of(" \t\r") != std::string::npos) {
            throw AnimalException("Ошибка чтения файла: лишние данные после списка животных");
        }
    }
    if (in.bad()) {
        throw AnimalException("Ошибка чтения файла \"" + fileName + "\"");
    }
    swapWith(loaded);
}

std::ostream& operator<<(std::ostream& out, const Keeper& keeper) {
    keeper.print(out);
    return out;
}
