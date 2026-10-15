#ifndef CAT_H
#define CAT_H

#include "../core/Base.h"

// Кошка: порода, окрас, ФИО владельца, кличка.
class Cat : public Base {
private:
    std::string ownerFullName;
    std::string nickname;

public:
    Cat();
    Cat(const std::string& breed, const std::string& color,
        const std::string& ownerFullName, const std::string& nickname);
    Cat(const Cat& other);
    ~Cat() override;

    Cat& operator=(const Cat& other);
    bool operator==(const Cat& other) const;

    std::string getOwnerFullName() const;
    std::string getNickname() const;
    void setOwnerFullName(const std::string& ownerFullName);
    void setNickname(const std::string& nickname);

    std::string getTypeName() const override;
    std::string getTypeTag() const override;
    void print(std::ostream& out) const override;
    Base* clone() const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif
