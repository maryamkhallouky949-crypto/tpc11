
#include <iostream>
#include <cmath>
using namespace std;


class Forme {
public:
    virtual double aire() const = 0;

    virtual ~Forme() {}
};


class Cercle : public Forme {
private:
    double rayon;

public:
    Cercle(double r) {
        rayon = r;
    }

    double aire() const override {
        return M_PI * rayon * rayon;
    }
};


class Rectangle : public Forme {
private:
    double longueur;
    double largeur;

public:
    Rectangle(double l, double L) {
        longueur = l;
        largeur = L;
    }

    double aire() const override {
        return longueur * largeur;
    }
};

int main() {
    const int N = 2;

  
    Forme* formes[N];

    double rayon, longueur, largeur;

    cout << "Cercle " << endl;
    cout << "Donner le rayon : ";
    cin >> rayon;

    formes[0] = new Cercle(rayon);


    cout << " Rectangle" << endl;
    cout << "Donner la longueur : ";
    cin >> longueur;

    cout << "Donner la largeur : ";
    cin >> largeur;

    formes[1] = new Rectangle(longueur, largeur);

   
    cout << "Aires des formes " << endl;

    for (int i = 0; i < N; i++) {
        cout << "Aire de la forme " << i + 1
             << " = " << formes[i]->aire() << endl;
    }

    for (int i = 0; i < N; i++) {
        delete formes[i];
    }

    return 0;
}
