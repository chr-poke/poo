#pragma once
#include <memory>
#include <string>
#include <utility>
#include "pokeType.h"

class pokemon;

class move {
protected:
    pokeType type;
    std::string name;
    int power;

public:
    move();
    move(const pokeType& type_, int power_, std::string name_);

    virtual ~move() = default;
    [[nodiscard]] virtual std::shared_ptr<move> clone() const = 0;
    virtual void execute(pokemon& attacker, pokemon& defender) = 0;

    friend std::ostream& operator<<(std::ostream& os, const move& obj);
    [[nodiscard]] const std::string& getName() const { return name; }
};

class physicalMove : public move {
public:
    physicalMove(const pokeType& type_, int power_, std::string name_)
        : move(type_, power_, std::move(name_)) {}

    [[nodiscard]] std::shared_ptr<move> clone() const override {
        return std::make_shared<physicalMove>(*this);
    }
    void execute(pokemon &attacker, pokemon &defender) override;
};

class specialMove : public move {
public:
    specialMove(const pokeType& type_, int power_, std::string name_)
        : move(type_, power_, std::move(name_)) {}

    [[nodiscard]] std::shared_ptr<move> clone() const override {
        return std::make_shared<specialMove>(*this);
    }
    void execute(pokemon& attacker, pokemon& defender) override;
};

class statusMove : public move {
private:
    std::vector<int> effects;

public:
    statusMove(const pokeType& type_, int power_, std::string name_, const std::vector<int>& effects_)
        : move(type_, power_, std::move(name_)), effects(effects_) {}

    [[nodiscard]] std::shared_ptr<move> clone() const override {
        return std::make_shared<statusMove>(*this);
    }
    void execute(pokemon& attacker, pokemon& defender) override;
};

extern std::shared_ptr<move> leerMove;
extern std::shared_ptr<move> poundMove;
extern std::shared_ptr<move> absorbMove;
extern std::shared_ptr<move> quick_attackMove;
extern std::shared_ptr<move> growlMove;
extern std::shared_ptr<move> scratchMove;
extern std::shared_ptr<move> focus_energyMove;
extern std::shared_ptr<move> emberMove;
extern std::shared_ptr<move> tackleMove;
extern std::shared_ptr<move> mud_slapMove;
extern std::shared_ptr<move> water_gunMove;
extern std::shared_ptr<move> howlMove;
extern std::shared_ptr<move> sand_attackMove;
extern std::shared_ptr<move> biteMove;