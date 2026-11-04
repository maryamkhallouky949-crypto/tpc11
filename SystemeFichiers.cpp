
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class NoeudFichier {
protected:
    string m_nom;

public:
    NoeudFichier(string n) {
        m_nom = n;
    }

    
    virtual string nom() const {
        return m_nom;
    }

    virtual int taille() const = 0;

 
    virtual ~NoeudFichier() {}
};

class Fichier : public NoeudFichier {
private:
    int m_taille;

public:
    Fichier(string n, int t) : NoeudFichier(n) {
        m_taille = t;
    }

    int taille() const override {
        return m_taille;
    }
};

class Dossier : public NoeudFichier {
private:
    vector<NoeudFichier*> enfants;

public:
    Dossier(string n) : NoeudFichier(n) {}

    void ajouter(NoeudFichier* element) {
        enfants.push_back(element);
    }
    int taille() const override {
        int total = 0;

        for (int i = 0; i < enfants.size(); i++) {
            total += enfants[i]->taille();
        }

        return total;
    }

 
    const vector<NoeudFichier*>& getEnfants() const {
        return enfants;
    }

    ~Dossier() {
        for (int i = 0; i < enfants.size(); i++) {
            delete enfants[i];
        }
    }
};

void remplirDossier(Dossier* dossier) {
    int choix;

    do {
        cout << "\n--- Dossier : " << dossier->nom() << " ---" << endl;
        cout << "1. Ajouter un fichier" << endl;
        cout << "2. Ajouter un sous-dossier" << endl;
        cout << "0. Terminer ce dossier" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choix == 1) {
            string nomFichier;
            int tailleFichier;

            cout << "Nom du fichier : ";
            getline(cin, nomFichier);

            cout << "Taille du fichier (Ko) : ";
            cin >> tailleFichier;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            dossier->ajouter(new Fichier(nomFichier, tailleFichier));

            cout << "Fichier ajoute avec succes !" << endl;
        }
        else if (choix == 2) {
            string nomDossier;

            cout << "Nom du sous-dossier : ";
            getline(cin, nomDossier);

            Dossier* sousDossier = new Dossier(nomDossier);

        
            remplirDossier(sousDossier);

            dossier->ajouter(sousDossier);

            cout << "Sous-dossier ajoute avec succes !" << endl;
        }
        else if (choix != 0) {
            cout << "Choix invalide !" << endl;
        }

    } while (choix != 0);
}


void afficherArborescence(Dossier* dossier, int niveau = 0) {

    for (int i = 0; i < niveau; i++) {
        cout << "   ";
    }

    cout << "[Dossier] " << dossier->nom()
         << " (" << dossier->taille() << " Ko)" << endl;

    const vector<NoeudFichier*>& enfants = dossier->getEnfants();

    for (int i = 0; i < enfants.size(); i++) {

        Dossier* sousDossier = dynamic_cast<Dossier*>(enfants[i]);

        if (sousDossier != nullptr) {
            afficherArborescence(sousDossier, niveau + 1);
        }
        else {
            for (int j = 0; j <= niveau; j++) {
                cout << "   ";
            }

            cout << "[Fichier] " << enfants[i]->nom()
                 << " (" << enfants[i]->taille() << " Ko)" << endl;
        }
    }
}


void collecterDossiers(Dossier* dossier, vector<Dossier*>& liste) {

    liste.push_back(dossier);

    const vector<NoeudFichier*>& enfants = dossier->getEnfants();

    for (int i = 0; i < enfants.size(); i++) {

        Dossier* sousDossier = dynamic_cast<Dossier*>(enfants[i]);

        if (sousDossier != nullptr) {
            collecterDossiers(sousDossier, liste);
        }
    }
}

int main() {

    string nomRacine;

    cout << "Nom du dossier principal : ";
    getline(cin, nomRacine);

    Dossier* racine = new Dossier(nomRacine);

    remplirDossier(racine);

    
    cout << "ARBORESCENCE DES FICHIERS" << endl;
    afficherArborescence(racine);
    vector<Dossier*> listeDossiers;
    collecterDossiers(racine, listeDossiers);
    cout << "CHOISIR UN DOSSIER" << endl;

    for (int i = 0; i < listeDossiers.size(); i++) {
        cout << i + 1 << ". " << listeDossiers[i]->nom() << endl;
    }

    int choix;
    cout << "Numero du dossier a selectionner : ";
    cin >> choix;

    if (choix >= 1 && choix <= listeDossiers.size()) {
        cout << "Taille totale du dossier "
             << listeDossiers[choix - 1]->nom()
             << " = "
             << listeDossiers[choix - 1]->taille()
             << " Ko" << endl;
    }
    else {
        cout << "Numero invalide !" << endl;
    }
    delete racine;

    return 0;
}
