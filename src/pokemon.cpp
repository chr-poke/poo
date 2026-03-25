#include "pokemon.h"
#include <random>
#include <cmath>

float pokemon::getRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(217.0f / 255.0f, 1.0f);
    return dist(gen);
}

void pokemon::setNickname() {
    std::string input;
    bool dialog = true;
    while (dialog) {
        std::cout << "Give a nickname to the captured " + name + "? Y/N\n";
        std::cin >> input;
        if (input.size() == 1 && (input[0] == 'Y' || input[0] == 'N')) {
            dialog = false;
            if (input[0] == 'Y') {
                std::cout << "Type your nickname:\n";
                std::cin >> this->name;
            }
        }
    }
}

pokemon::pokemon() {
    this->pokedexNumber = 0;
    this->full_hp = 0;
    this->hp = 0;
    this->attack = 0;
    this->defense = 0;
    this->type1 = noneType;
    this->type2 = noneType;
    this->moveset = {};
    this->name = "Unknown";
    this->level = 0;
    this->xp = 0;
    this->status = 2;
}

pokemon::pokemon(const int pokedexNumber_, const int full_hp_,
                 const int attack_, const int defense_,
                 const pokeType& type1_, const pokeType& type2_,
                 const std::vector<move>& moveset_, std::string  name_,
                 const int level_, const int status_) :
        pokedexNumber{pokedexNumber_}, full_hp{full_hp_},
        attack{attack_}, defense{defense_},
        type1{type1_}, type2{type2_},
        moveset{moveset_}, name{std::move(name_)},
        level{level_}, status{status_} {
    this->hp = full_hp;
    this->xp = pow(level, 3);
    if (status == 0)
        std::cout << "Wild " << name << " appeared!\n";
}

pokemon::pokemon(const pokemon& other) {
    this->pokedexNumber = other.pokedexNumber;
    this->full_hp = other.full_hp;
    this->hp = other.full_hp;
    this->attack = other.attack;
    this->defense = other.defense;
    this->type1 = other.type1;
    this->type2 = other.type2;
    this->moveset = other.moveset;
    this->name = other.name;
    this->level = other.level;
    this->xp = pow(other.level, 3);
    this->status = other.status;
}

pokemon::~pokemon() {
    if (status == 1)
        std::cout << name + " was released.\n"
                  << "Bye-bye, " + name + "!\n";
}

std::ostream& operator<<(std::ostream& os, const pokemon& obj) {
    os << obj.name << " (Level " << obj.level << ")\n"
       << "HP: " << obj.hp << "/" << obj.full_hp << "\n";
    return os;
}

void pokemon::changeStatus(const int newStatus) {
    status = newStatus;
    if (newStatus == 1)
        setNickname();
}

int pokemon::xpGain(const double b, const int l) {
    // b = xp of the defeated Pokemon
    // l = level of the defeated Pokemon
    xp += b * l / 7;
    if (xp >= pow(level + 1, 3)) {
        level++;
        attack++;
        defense++;
        full_hp += 2;
    }
    return b * l / 7;
}

void pokemon::takeDamage(const int damage) {
    hp -= damage;
    if (hp < 0)
        hp = 0;
}

[[nodiscard]] int pokemon::damage(const int p, const int d, const float t1, const float t2) const {
    // p = move power
    // d = defense of target
    // t1 = target's 1st type effectiveness
    // t2 = target's 2nd type effectiveness
    // r = random number between 217/255 and 1
    const float r = getRandom();
    return std::floor(
        (static_cast<float>(((2 * level) / 5 + 2) * p * attack) / static_cast<float>(d)) / 50.0 * t1 * t2 * r);
}

move pokemon::selMove() {
    std::string input;
    std::cout << "| ";
    for (unsigned long i = 0; i < moveset.size(); i++)
        std::cout << i + 1 << ". " << moveset[i].getName() << " | ";
    std::cout << std::endl << std::endl;
    std::cout << "Use a move by typing '1'-'"
              << std::to_string(moveset.size()) << "'.\n";
    std::cout << "Type 'help' to learn more about " << name << "'s moves.\n";
    while (std::cin >> input) {
        if (input == "help")
            for (unsigned long i = 0; i < moveset.size(); i++)
                std::cout << i + 1 << ". " << moveset[i];
        else if (stol(input) >= 1 && static_cast<unsigned long>(stol(input)) <= moveset.size())
            return moveset[stoi(input) - 1];
        else
            std::cout << "Invalid input!\n";
    }
    move none;
    return none;
}