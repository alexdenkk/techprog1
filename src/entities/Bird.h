#ifndef BIRD_H
#define BIRD_H

#include "../core/Base.h"

// Птица: порода, окрас, чем питается, где обитает.
class Bird : public Base {
private:
    std::string food;
    std::string habitat;

public:
    Bird();
    Bird(const std::string& breed, const std::string& color,
         const std::string& food, const std::string& habitat);
    Bird(const Bird& other);
    ~Bird() override;

    Bird& operator=(const Bird& other);
    bool operator==(const Bird& other) const;

    std::string getFood() const;
    std::string getHabitat() const;
    void setFood(const std::string& food);
    void setHabitat(const std::string& habitat);

    std::string getTypeName() const override;
    std::string getTypeTag() const override;
    void print(std::ostream& out) const override;
    Base* clone() const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif
