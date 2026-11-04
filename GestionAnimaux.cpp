
#include <iostream>
#include <vector>
using namespace std;

class Animal {
public:
 
    virtual void crier() const = 0;

    void info() const {
        cout << "Je suis un animal." << endl;
    }

    virtual ~Animal() {}
};

class Chien : public Animal {
public:
    void crier() const override {
        cout << "Wouf !" << endl;
    }
};

class Chat : public Animal {
public:
    void crier() const override {
        cout << "Miaou !" << endl;
    }
};


class Vache : public Animal {
public:
    void crier() const override {
        cout << "Meuh !" << endl;
    }
};

int main() {
    vector<Animal*> animaux;
    animaux.push_back(new Chien());
    animaux.push_back(new Chat());
    animaux.push_back(new Vache());
    animaux.push_back(new Chien());
    cout << "Informations et cris des animaux " << endl;

    for (int i = 0; i < animaux.size(); i++) {

        cout << "Animal " << i + 1 << ":" << endl;
        animaux[i]->info();

      
        animaux[i]->crier();
    }

    for (int i = 0; i < animaux.size(); i++) {
        delete animaux[i];
    }

    return 0;
}
