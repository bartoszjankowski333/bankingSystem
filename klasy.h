#ifndef BANKINGSYSTEM_KLASY_H
#define BANKINGSYSTEM_KLASY_H
#include <iostream>
#include <string>
using namespace std;

class Uzytkownik
{
protected:
    int id;
    int pesel;
    string haslo;

public:
    Uzytkownik(int id, const int pesel, const string& haslo) : id(id), pesel(pesel), haslo(haslo) {}
};

class Pracownik : public Uzytkownik
{
public:
    Pracownik(int id, const int& pesel) : Uzytkownik(id, pesel, haslo) {
        setPassword("admin");
    }

    // Metoda ustawiająca hasło
    void setPassword(const string& pass) {
        haslo = pass;
    }

    // Metoda do pobierania loginu
    int getPesel() const {
        return pesel;
    }

    // Metoda do pobierania hasła
    string getHaslo() const {
        return haslo;
    }
};


class Klient : public Uzytkownik
{
private:
    string imie;
    string nazwisko;
    string typKonta;
    int numerKonta;
    double saldo;

public:
    Klient(int id, const int& pesel, const string& haslo, const string& imie, const string& nazwisko, const string& typKonta, const int& numerKonta, double saldo)
            : Uzytkownik(id, pesel, haslo), imie(imie), nazwisko(nazwisko), typKonta(typKonta), numerKonta(numerKonta), saldo(saldo) {}


    // Metody do pobierania danych klienta
    int getId() const { return id; }
    int getPesel() const { return pesel; }
    string getImie() const { return imie; }
    string getNazwisko() const { return nazwisko; }
    string getHaslo() const { return haslo; }
    string getTypkonta() const { return typKonta; }
    int getNumerkonta() const { return numerKonta; }
    double getSaldo() const { return saldo; }
};



#endif //BANKINGSYSTEM_KLASY_H
