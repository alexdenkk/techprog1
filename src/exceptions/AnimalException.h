#ifndef ANIMAL_EXCEPTION_H
#define ANIMAL_EXCEPTION_H

#include <exception>
#include <string>

// Исключение программы «Животные». Хранит текст с пояснением ошибки.
class AnimalException : public std::exception {
private:
    std::string message;

public:
    AnimalException();
    explicit AnimalException(const std::string& message);
    AnimalException(const AnimalException& other);
    ~AnimalException() noexcept override;

    AnimalException& operator=(const AnimalException& other);
    std::string getMessage() const;
    void setMessage(const std::string& message);
    const char* what() const noexcept override;
};

#endif
