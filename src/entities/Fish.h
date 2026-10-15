#ifndef FISH_H
#define FISH_H

#include "../core/Base.h"

// Рыба: порода, окрас, тип питания.
class Fish : public Base {
private:
    std::string foodType;

public:
    Fish();
    Fish(const std::string& breed, const std::string& color, const std::string& foodType);
    Fish(const Fish& other);
    ~Fish() override;

    Fish& operator=(const Fish& other);
    bool operator==(const Fish& other) const;

    std::string getFoodType() const;
    void setFoodType(const std::string& foodType);

    std::string getTypeName() const override;
    std::string getTypeTag() const override;
    void print(std::ostream& out) const override;
    Base* clone() const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif
