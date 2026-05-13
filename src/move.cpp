#include "move.h"
#include "pokemon.h"
#include "exceptions.h"
#include <utility>

std::vector<std::string> statNames = {
    "Attack", "Defense", "Special Attack", "Special Defense",
    "Attack", "Defense", "Special Attack", "Special Defense"
};

move::move() {
    this->type = noneType;
    this->name = "None";
    this->power = 0;
}

move::move(const pokeType& type_, const int power_, std::string name_) 
    : type{type_}, name{std::move(name_)}, power{power_} {}

std::ostream& operator<<(std::ostream& os, const move& obj) {
    obj.print(os);
    return os;
}

void move::print(std::ostream& os) const {
    os << name << " [" << type.getName() << " Type]";
}

void physicalMove::execute(pokemon& attacker, pokemon& defender) {
    if (attacker.getHP() <= 0)
        throw battleException(attacker.getName() + " has fainted!");
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(false, power, defender.getDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    std::cout << attacker.getName() << " dealt " << dmg << "HP of damage!\n\n";
    defender.takeDamage(dmg);
}

void physicalMove::print(std::ostream& os) const {
    move::print(os);
    os << " - Physical Move (Power: " << power << ")\n";
}

void specialMove::execute(pokemon& attacker, pokemon& defender) {
    if (attacker.getHP() <= 0)
        throw battleException(attacker.getName() + " has fainted!");
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(true, power, defender.getSpDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    std::cout << attacker.getName() << " dealt " << dmg << "HP of damage!\n\n";
    defender.takeDamage(dmg);
}

void specialMove::print(std::ostream& os) const {
    move::print(os);
    os << " - Special Move (Power: " << power << ")\n";
}

void statusMove::execute(pokemon& attacker, pokemon& defender) {
    if (attacker.getHP() <= 0)
        throw battleException(attacker.getName() + " has fainted!");
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";

    for (int i = 0; i < 8; i++) {
        if (effects[i] == 0)
            continue;
        pokemon& target = (i < 4) ? defender : attacker;
        std::string action = (effects[i] < 0) ? "fell" : "rose";
        target.setEffect(i % 4, effects[i]);
        std::cout << target.getName() << "'s " << statNames[i] << " " << action << "!\n\n";
    }
}

void statusMove::print(std::ostream& os) const {
    move::print(os);
    os << " - Status Move (";
    for (int i = 0; i < 8; i++)
        if (effects[i]) {
            std::string target = (i < 4) ? "Foe's" : "Your";
            std::string plus = (effects[i] < 0) ? "" : "+";
            os << target << " " << statNames[i] << ": " << plus << effects[i];
        }
    os << ")\n";
}

bool statusMove::loweringStats() const {
    for (int i = 0; i < 4; i++)
        if (effects[i] < 0)
            return true;
    return false;
}

void healingMove::execute(pokemon& attacker, pokemon& defender) {
    if (attacker.getHP() <= 0)
        throw battleException(attacker.getName() + " has fainted!");
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(true, power, defender.getSpDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    std::cout << attacker.getName() << " dealt " << dmg << "HP of damage!\n";
    defender.takeDamage(dmg);

    int healAmount = dmg / 2;
    if (healAmount > 0) {
        attacker.heal(healAmount);
        std::cout << attacker.getName() << " healed " << healAmount << " HP!\n";
    }
    std::cout << std::endl;
}

void healingMove::print(std::ostream& os) const {
    move::print(os);
    os << " - Healing Move (Power: " << power << ", restores 50% of damage dealt)\n";
}