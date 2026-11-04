#include <iostream>
using namespace std;


class Paiement {
public:
    virtual void effectuerPaiement(double montant) = 0;

    virtual ~Paiement() {}
};


class PaiementCarte : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant
             << " DH par carte bancaire." << endl;
    }
};
class PaiementEspece : public Paiement {
public:
    void effectuerPaiement(double montant) override {
        cout << "Paiement de " << montant
             << " DH en especes." << endl;
    }
};

int main() {

    
    Paiement* paiements[4];

    
    paiements[0] = new PaiementCarte();
    paiements[1] = new PaiementEspece();
    paiements[2] = new PaiementCarte();
    paiements[3] = new PaiementEspece();

    
    double montants[4] = {200, 150, 500, 80};

    
    cout << "Simulation des paiements" << endl;

    for (int i = 0; i < 4; i++) {
        paiements[i]->effectuerPaiement(montants[i]);
    }


    for (int i = 0; i < 4; i++) {
        delete paiements[i];
    }

    return 0;
}
