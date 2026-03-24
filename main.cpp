#include <iostream>
#include <string>
#include <random>
#include <array>
#include <vector>
#include <cmath>
#include "include/Example.h"
// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"

class move {

};

class pokemon {
private:
    int pokedexNumber; // Hoenn Pokedex
    int level;
    int xp;
    int hp;
    int type1;
    int type2;
    std::string statusCondition;
    std::string name;
public:
    pokemon() {
        // wild encounter
    }

    pokemon(int pokedexNumber, int level) {
        this->pokedexNumber = pokedexNumber;
        this->level = level;
        this->xp = pow(level, 3);
        // hp din db
        // types din db
        this->statusCondition = "None";
        switch (pokedexNumber) {
            case 1:
                this->name = "Treecko";
                break;
            case 4:
                this->name = "Torchic";
                break;
            case 7:
                this->name = "Mudkip";
                break;
            default:
                this->name = "Unknown";
        }
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

    std::string getNume() {
        return this->name;
    }
};

int main() {
    /*
    std::cout << "Hello, world!\n";
    Example e1;
    e1.g();
    std::array<int, 100> v{};
    int nr;
    std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    return 0;
    */
    // *** STARTER SELECTION ***
    int selectedStarter = 0;
    bool starterWasChosen = false;
    std::cout << "Professor Birch is in trouble! Release a Pokemon and rescue him!\n"
                 "Type '1', '2' or '3' to show details about each Pokemon.\n";
    while (!starterWasChosen) {
        std::string input;
        std::cin >> input;
        if (input.size() == 1) {
            switch (input[0]) {
                case '1':
                    std::cout << "Wood Gecko Pokemon - Treecko\n";
                    selectedStarter = 1;
                    break;
                case '2':
                    std::cout << "Chick Pokemon - Torchic\n";
                    selectedStarter = 2;
                    break;
                case '3':
                    std::cout << "Mud Fish Pokemon - Mudkip\n";
                    selectedStarter = 3;
                    break;
                case 'Y':
                    starterWasChosen = true;
                    break;
                default:
                    std::cout << "Invalid input!\n";
            }
            if (input[0] >= '1' && input[0] <= '3')
                std::cout << "Type 'Y' to choose this Pokemon!\n";
        }
        else
            std::cout << "Invalid input!\n";
    }
    pokemon starter((selectedStarter - 1) * 3 + 1, 5);

    return 0;
}
