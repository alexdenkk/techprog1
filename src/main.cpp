#include "entities/Fish.h"
#include "entities/Bird.h"
#include "entities/Cat.h"
#include "exceptions/AnimalException.h"
#include "input/Input.h"
#include "container/Keeper.h"

#include <iostream>
#include <new>

#ifdef _WIN32
#include <windows.h>
#endif

using Input::readInt;
using Input::readString;

static void addFish(Keeper& keeper) {
    std::cout << "--- Новая рыба ---" << std::endl;
    std::string breed = readString("Порода: ");
    std::string color = readString("Окрас: ");
    std::string foodType = readString("Тип питания: ");
    keeper += new Fish(breed, color, foodType);
    std::cout << "Рыба добавлена" << std::endl;
}

static void addBird(Keeper& keeper) {
    std::cout << "--- Новая птица ---" << std::endl;
    std::string breed = readString("Порода: ");
    std::string color = readString("Окрас: ");
    std::string food = readString("Чем питается: ");
    std::string habitat = readString("Где обитает: ");
    keeper += new Bird(breed, color, food, habitat);
    std::cout << "Птица добавлена" << std::endl;
}

static void addCat(Keeper& keeper) {
    std::cout << "--- Новая кошка ---" << std::endl;
    std::string breed = readString("Порода: ");
    std::string color = readString("Окрас: ");
    std::string ownerFullName = readString("ФИО владельца: ");
    std::string nickname = readString("Кличка: ");
    keeper += new Cat(breed, color, ownerFullName, nickname);
    std::cout << "Кошка добавлена" << std::endl;
}

// Нумерация для пользователя начинается с единицы, в массиве — с нуля
static int askIndex(const Keeper& keeper, const std::string& prompt) {
    if (keeper.isEmpty()) {
        throw AnimalException("В контейнере нет ни одного животного");
    }
    return readInt(prompt + " (1-" + std::to_string(keeper.getCount()) + "): ",
                   1, keeper.getCount()) - 1;
}

static void editFish(Fish& f) {
    std::cout << "1. Порода\n2. Окрас\n3. Тип питания\n0. Отмена" << std::endl;
    switch (readInt("Какое поле изменить: ", 0, 3)) {
        case 1: f.setBreed(readString("Новая порода: ")); break;
        case 2: f.setColor(readString("Новый окрас: ")); break;
        case 3: f.setFoodType(readString("Новый тип питания: ")); break;
        default: return;
    }
    std::cout << "Изменено:\n" << f << std::endl;
}

static void editBird(Bird& b) {
    std::cout << "1. Порода\n2. Окрас\n3. Чем питается\n4. Где обитает\n0. Отмена" << std::endl;
    switch (readInt("Какое поле изменить: ", 0, 4)) {
        case 1: b.setBreed(readString("Новая порода: ")); break;
        case 2: b.setColor(readString("Новый окрас: ")); break;
        case 3: b.setFood(readString("Чем питается: ")); break;
        case 4: b.setHabitat(readString("Где обитает: ")); break;
        default: return;
    }
    std::cout << "Изменено:\n" << b << std::endl;
}

static void editCat(Cat& c) {
    std::cout << "1. Порода\n2. Окрас\n3. ФИО владельца\n4. Кличка\n0. Отмена" << std::endl;
    switch (readInt("Какое поле изменить: ", 0, 4)) {
        case 1: c.setBreed(readString("Новая порода: ")); break;
        case 2: c.setColor(readString("Новый окрас: ")); break;
        case 3: c.setOwnerFullName(readString("Новое ФИО владельца: ")); break;
        case 4: c.setNickname(readString("Новая кличка: ")); break;
        default: return;
    }
    std::cout << "Изменено:\n" << c << std::endl;
}

static void editObject(Keeper& keeper) {
    Base& obj = keeper[askIndex(keeper, "Номер животного для изменения")];
    std::cout << obj << std::endl;
    if (Fish* f = dynamic_cast<Fish*>(&obj)) {
        editFish(*f);
    } else if (Bird* b = dynamic_cast<Bird*>(&obj)) {
        editBird(*b);
    } else if (Cat* c = dynamic_cast<Cat*>(&obj)) {
        editCat(*c);
    }
}

// Сравнение всех характеристик двух животных перегруженным оператором ==
static void compareObjects(const Keeper& keeper) {
    const Base& a = keeper[askIndex(keeper, "Номер первого животного")];
    const Base& b = keeper[askIndex(keeper, "Номер второго животного")];
    bool equal = false;
    if (a.getTypeTag() != b.getTypeTag()) {
        equal = false;
    } else if (const Fish* f = dynamic_cast<const Fish*>(&a)) {
        equal = *f == dynamic_cast<const Fish&>(b);
    } else if (const Bird* bird = dynamic_cast<const Bird*>(&a)) {
        equal = *bird == dynamic_cast<const Bird&>(b);
    } else if (const Cat* c = dynamic_cast<const Cat*>(&a)) {
        equal = *c == dynamic_cast<const Cat&>(b);
    }
    std::cout << (equal ? "Животные одинаковые" : "Животные различаются") << std::endl;
}

static void printMenu(const Keeper& keeper) {
    std::cout << "\n========== " << keeper.getName() << " ==========\n"
              << " 1. Добавить рыбу\n"
              << " 2. Добавить птицу\n"
              << " 3. Добавить кошку\n"
              << " 4. Показать всех животных\n"
              << " 5. Показать животное по номеру\n"
              << " 6. Изменить животное\n"
              << " 7. Удалить животное\n"
              << " 8. Дублировать животное\n"
              << " 9. Сравнить двух животных\n"
              << "10. Сохранить животных в файл\n"
              << "11. Загрузить животных из файла\n"
              << "12. Удалить всех животных\n"
              << "13. Переименовать контейнер\n"
              << "14. Создать резервную копию\n"
              << "15. Восстановить из резервной копии\n"
              << " 0. Выход\n";
}

static void runMenu() {
    Keeper keeper;
    Keeper* backup = nullptr;   // резервная копия создаётся по запросу пользователя
    bool running = true;

    try {
        while (running) {
            try {
                printMenu(keeper);
                switch (readInt("Выберите пункт: ", 0, 15)) {
                    case 1: addFish(keeper); break;
                    case 2: addBird(keeper); break;
                    case 3: addCat(keeper); break;
                    case 4: std::cout << keeper; break;
                    case 5: {
                        int index = askIndex(keeper, "Номер животного");
                        std::cout << index + 1 << ". " << keeper[index] << std::endl;
                        break;
                    }
                    case 6: editObject(keeper); break;
                    case 7:
                        keeper.remove(askIndex(keeper, "Номер животного для удаления"));
                        std::cout << "Животное удалено" << std::endl;
                        break;
                    case 8:
                        keeper += keeper[askIndex(keeper, "Номер животного для копирования")].clone();
                        std::cout << "Копия добавлена под номером " << keeper.getCount() << std::endl;
                        break;
                    case 9: compareObjects(keeper); break;
                    case 10: {
                        std::string fileName = readString("Имя файла для сохранения: ");
                        keeper.saveToFile(fileName);
                        std::cout << "Животные сохранены в файл \"" << fileName << "\"" << std::endl;
                        break;
                    }
                    case 11: {
                        std::string fileName = readString("Имя файла для загрузки: ");
                        keeper.loadFromFile(fileName);
                        std::cout << "Загружено животных: " << keeper.getCount() << std::endl;
                        break;
                    }
                    case 12:
                        keeper.clear();
                        std::cout << "Все животные удалены" << std::endl;
                        break;
                    case 13:
                        keeper.setName(readString("Новое название контейнера: "));
                        break;
                    case 14: {
                        Keeper* copy = new Keeper(keeper);
                        delete backup;
                        backup = copy;
                        std::cout << "Резервная копия создана" << std::endl;
                        break;
                    }
                    case 15:
                        if (backup == nullptr) {
                            throw AnimalException("Резервная копия ещё не создавалась");
                        }
                        keeper = *backup;
                        std::cout << "Контейнер восстановлен из резервной копии" << std::endl;
                        break;
                    case 0: running = false; break;
                }
            } catch (const AnimalException& e) {
                if (std::cin.eof()) {
                    running = false;
                } else if (std::cin.fail()) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                    running = false;
                } else {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
            } catch (const std::bad_alloc&) {
                std::cout << "Ошибка: недостаточно памяти" << std::endl;
            }
        }
    } catch (...) {
        delete backup;
        throw;
    }

    delete backup;
    std::cout << "Работа программы завершена" << std::endl;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    try {
        runMenu();
    } catch (const std::bad_alloc&) {
        std::cout << "Ошибка: недостаточно памяти для запуска программы" << std::endl;
        return 1;
    }
    return 0;
}
