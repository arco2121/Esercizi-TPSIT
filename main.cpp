#include <iostream>
#include <cstring>
using namespace std;

class Prodotto {
private:
    char* nome;
    int quantita;
    double prezzo;

public:
    Prodotto(const char* n, int q, double p) : quantita(q), prezzo(p) {
        nome = new char[strlen(n) + 1];
        strcpy(nome, n);
    }

    Prodotto(const Prodotto& other) : quantita(other.quantita), prezzo(other.prezzo) {
        nome = new char[strlen(other.nome) + 1];
        strcpy(nome, other.nome);
    }

    Prodotto& operator=(const Prodotto& other) {
        if (this != &other) {
            delete[] nome;
            nome = new char[strlen(other.nome) + 1];
            strcpy(nome, other.nome);
            quantita = other.quantita;
            prezzo = other.prezzo;
        }
        return *this;
    }

    ~Prodotto() {
        delete[] nome;
    }

    void stampa() const {
        cout << "Nome: " << nome << ", Quantita: " << quantita << ", Prezzo: " << prezzo << " EUR" << endl;
    }

    const char* getNome() const {
        return nome;
    }
};

class Magazzino {
private:
    Prodotto* prodotti;
    int capacita;
    int numeroProdotti;

public:
    Magazzino(int cap) : capacita(cap), numeroProdotti(0) {
        prodotti = new Prodotto[capacita];
    }

    Magazzino(const Magazzino& other) : capacita(other.capacita), numeroProdotti(other.numeroProdotti) {
        prodotti = new Prodotto[capacita];
        for (int i = 0; i < numeroProdotti; i++) {
            prodotti[i] = other.prodotti[i];
        }
    }

    Magazzino& operator=(const Magazzino& other) {
        if (this != &other) {
            delete[] prodotti;
            capacita = other.capacita;
            numeroProdotti = other.numeroProdotti;
            prodotti = new Prodotto[capacita];
            for (int i = 0; i < numeroProdotti; i++) {
                prodotti[i] = other.prodotti[i];
            }
        }
        return *this;
    }

    ~Magazzino() {
        delete[] prodotti;
    }

    void aggiungiProdotto(const Prodotto& p) {
        if (numeroProdotti < capacita) {
            prodotti[numeroProdotti++] = p;
        } else {
            cout << "Magazzino pieno! Impossibile aggiungere altri prodotti." << endl;
        }
    }

    void rimuoviProdotto(const char* nome) {
        for (int i = 0; i < numeroProdotti; i++) {
            if (strcmp(prodotti[i].getNome(), nome) == 0) {
                for (int j = i; j < numeroProdotti - 1; j++) {
                    prodotti[j] = prodotti[j + 1];
                }
                numeroProdotti--;
                return;
            }
        }
        cout << "Prodotto non trovato." << endl;
    }

    void stampaInventario() const {
        if (numeroProdotti == 0) {
            cout << "Il magazzino è vuoto." << endl;
        } else {
            for (int i = 0; i < numeroProdotti; i++) {
                prodotti[i].stampa();
            }
        }
    }
};

int main() {
    Magazzino magazzino(5);
    
    magazzino.aggiungiProdotto(Prodotto("Laptop", 10, 999.99));
    magazzino.aggiungiProdotto(Prodotto("Mouse", 50, 19.99));
    magazzino.aggiungiProdotto(Prodotto("Tastiera", 30, 49.99));
    
    cout << "Inventario iniziale:" << endl;
    magazzino.stampaInventario();
    
    magazzino.rimuoviProdotto("Mouse");
    cout << "\nInventario dopo la rimozione del Mouse:" << endl;
    magazzino.stampaInventario();
    
    return 0;
}