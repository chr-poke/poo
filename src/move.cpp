#include "move.h"
#include "pokemon.h"
#include <utility>

move::move() {
    this->type = noneType;
    this->name = "None";
    this->power = 0;
}

move::move(const pokeType& type_, const int power_, std::string name_) 
    : type{type_}, name{std::move(name_)}, power{power_} {}

std::ostream& operator<<(std::ostream& os, const move& obj) {
    os << obj.name << " is a " << obj.type.getName()
       << " Type move and it has " << obj.power << " power.\n";
    return os;
}

void physicalMove::execute(pokemon& attacker, pokemon& defender) {
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(false, power, defender.getDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    defender.takeDamage(dmg);
}

void specialMove::execute(pokemon& attacker, pokemon& defender) {
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    const int dmg = attacker.damage(true, power, defender.getSpDefense(),
                              type.getAttack(defender.getType1().getID()),
                              type.getAttack(defender.getType2().getID()));
    defender.takeDamage(dmg);
    // de modificat
}

void statusMove::execute(pokemon& attacker, pokemon& defender) {
    std::cout << "--- " << attacker.getName() << " used " << name << "! ---\n";
    // de modificat
}