#include "pokemon.h"
#include "exceptions.h"
#include <random>
#include <cmath>

int pokemon::totalDefeated = 0;

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
    this->sp_attack = 0;
    this->sp_defense = 0;
    this->effects = {0, 0, 0, 0};
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
                 const int sp_attack_, const int sp_defense_,
                 const pokeType& type1_, const pokeType& type2_,
                 std::vector<std::shared_ptr<move>> moveset_, std::string  name_,
                 const int level_, const int status_) :
        pokedexNumber{pokedexNumber_}, full_hp{full_hp_},
        attack{attack_}, defense{defense_},
        sp_attack{sp_attack_}, sp_defense{sp_defense_},
        type1{type1_}, type2{type2_},
        moveset{std::move(moveset_)}, name{std::move(name_)},
        level{level_}, status{status_} {
    if (full_hp_ <= 0 || level_ <= 0) {
        throw statException("Pokémon must have at least 1 HP and level 1!");
    }

    this->hp = full_hp;
    this->xp = pow(level, 3);
    if (status == 0)
        std::cout << "Wild " << name << " appeared!\n";
    this->effects = {0, 0, 0, 0};
}

pokemon::pokemon(const pokemon& other) :
        pokedexNumber{other.pokedexNumber},
        full_hp{other.full_hp}, hp{other.hp},
        attack{other.attack}, defense{other.defense},
        sp_attack{other.sp_attack}, sp_defense{other.sp_defense},
        effects{other.effects},
        type1{other.type1}, type2{other.type2},
        name{other.name}, level{other.level},
        xp{other.xp}, status{other.status} {
    for (const auto& m : other.moveset)
        if (m)
            this->moveset.push_back(m->clone());
}

pokemon& pokemon::operator=(pokemon other) {
    swap(*this, other);
    return *this;
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

void swap(pokemon& x, pokemon& y) noexcept {
    std::swap(x.pokedexNumber, y.pokedexNumber);
    std::swap(x.full_hp, y.full_hp);
    std::swap(x.hp, y.hp);
    std::swap(x.attack, y.attack);
    std::swap(x.defense, y.defense);
    std::swap(x.sp_attack, y.sp_attack);
    std::swap(x.sp_defense, y.sp_defense);
    std::swap(x.effects, y.effects);
    std::swap(x.type1, y.type1);
    std::swap(x.type2, y.type2);
    std::swap(x.moveset, y.moveset);
    std::swap(x.name, y.name);
    std::swap(x.level, y.level);
    std::swap(x.xp, y.xp);
    std::swap(x.status, y.status);
}

void pokemon::changeStatus(const int newStatus) {
    status = newStatus;
    if (newStatus == 1)
        setNickname();
}

void pokemon::xpGain(const double b, const int l) {
    // b = xp of the defeated Pokemon
    // l = level of the defeated Pokemon
    const int gain = b * l / 7;
    std::cout << name << " gained " << gain << " XP.\n";
    xp += gain;
    if (xp >= pow(level + 1, 3)) {
        level++;
        attack++;
        defense++;
        sp_attack++;
        sp_defense++;
        full_hp += 2;
        std::cout << name << " grew to Level " << level << "!\n";
    }
    std::cout << std::endl;
}

// https://www.dragonflycave.com/mechanics/stat-stages/

[[nodiscard]] int pokemon::getAttack() const {
    if (effects[0] > 0)
        return std::floor(attack * (effects[0] + 2) / 2.0);
    if (effects[0] < 0)
        return std::floor(attack * 2.0 / (2 - effects[0]));
    return attack;
}

[[nodiscard]] int pokemon::getDefense() const {
    if (effects[1] > 0)
        return std::floor(defense * (effects[1] + 2) / 2.0);
    if (effects[1] < 0)
        return std::floor(defense * 2.0 / (2 - effects[1]));
    return defense;
}

[[nodiscard]] int pokemon::getSpAttack() const {
    if (effects[2] > 0)
        return std::floor(sp_attack * (effects[2] + 2) / 2.0);
    if (effects[2] < 0)
        return std::floor(sp_attack * 2.0 / (2 - effects[2]));
    return sp_attack;
}

[[nodiscard]] int pokemon::getSpDefense() const {
    if (effects[3] > 0)
        return std::floor(sp_defense * (effects[3] + 2) / 2.0);
    if (effects[3] < 0)
        return std::floor(sp_defense * 2.0 / (2 - effects[3]));
    return sp_defense;
}

void pokemon::setEffect(const int stat, const int change) {
    if (effects[stat] + change > 6)
        effects[stat] = 6;
    else if (effects[stat] + change < -6)
        effects[stat] = -6;
    else
        effects[stat] += change;
}

void pokemon::resetEffects() {
    for (int i = 0; i < 4; i++)
        effects[i] = 0;
}

void pokemon::heal(const int amount) {
    hp += amount;
    if (hp > full_hp)
        hp = full_hp;
}

void pokemon::takeDamage(const int amount) {
    hp -= amount;
    if (hp < 0)
        hp = 0;
}

[[nodiscard]] int pokemon::damage(const bool sp, const int p, const int d, const float t1, const float t2) const {
    // p = move power
    // d = defense/sp_defense of target
    // t1 = target's 1st type effectiveness
    // t2 = target's 2nd type effectiveness
    // sp = true if move is special, false otherwise
    // r = random number between 217/255 and 1
    // a = attack/sp_attack of user
    const float r = getRandom();
    int a;
    if (sp)
        a = getSpAttack();
    else
        a = getAttack();
    return std::floor(
        (static_cast<float>(((2 * level) / 5 + 2) * p * a) / static_cast<float>(d)) / 50.0 * t1 * t2 * r);
}

std::shared_ptr<move> pokemon::selMove() {
    std::string input;
    std::cout << "| ";
    for (unsigned long i = 0; i < moveset.size(); i++)
        std::cout << i + 1 << ". " << moveset[i]->getName() << " | ";
    std::cout << std::endl << std::endl;
    std::cout << "Use a move by typing '1'-'"
              << std::to_string(moveset.size()) << "'.\n";
    std::cout << "Type 'help' to learn more about " << name << "'s moves.\n";
    while (std::cin >> input) {
        if (input == "help")
            for (unsigned long i = 0; i < moveset.size(); i++)
                std::cout << i + 1 << ". " << *moveset[i];
        else if (stol(input) >= 1 && static_cast<unsigned long>(stol(input)) <= moveset.size())
            return moveset[stoi(input) - 1];
        else
            std::cout << "Invalid input!\n";
    }
    throw inputException("Input stream was closed unexpectedly during move selection!");
}