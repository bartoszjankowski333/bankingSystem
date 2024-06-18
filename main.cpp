#include <iostream>
#include <string>
#include "klasy.h"

using namespace std;

int main()
{
    Pracownik p1(1, 333333333); //przykladowy pracownik
    Klient klient1(2, 123456789, "haslo123", "Jan", "Kowalski", "oszczednosciowe", 1234567890, 1000.0); // Przykładowy klient

    int inputPesel;
    string inputHaslo;

    do {
        // Panel logowania
        cout << "------ PANEL LOGOWANIA ------" << endl;
        cout << "Podaj login (PESEL): ";
        cin >> inputPesel;
        cout << "Podaj haslo: ";
        cin >> inputHaslo;

        // Sprawdzenie roli użytkownika
        if (inputPesel == p1.getPesel() && inputHaslo == p1.getHaslo()) {
            cout << "Pomyslnie zalogowano!" << endl;

            int choicePracownik;
            do {
                // Wyświetlanie menu pracownika
                cout << endl;
                cout << "------ PANEL ZARZADZANIA ------" << endl;
                cout << "1. Dodaj klienta" << endl;
                cout << "2. Modyfikacja konta" << endl;
                cout << "3. Wplata" << endl;
                cout << "4. Wyplata" << endl;
                cout << "5. Sprawdz saldo" << endl;
                cout << "6. Lista kont" << endl;
                cout << "7. Zamknij konto" << endl;
                cout << "8. Wyloguj" << endl;
                cout << "Wybierz opcję: ";
                cin >> choicePracownik;

                switch (choicePracownik) {
                    case 1: {
                        // Dodawanie nowego klienta
                        cout << "--- Dodawanie nowego klienta ---" << endl;
                        int id, pesel, numerKonta;
                        string imie, nazwisko, haslo, typKonta;
                        double saldo;

                        cout << "Podaj ID klienta: ";
                        cin >> id;
                        cout << "Podaj PESEL klienta: ";
                        cin >> pesel;
                        cout << "Podaj imię klienta: ";
                        cin >> imie;
                        cout << "Podaj nazwisko klienta: ";
                        cin >> nazwisko;
                        cout << "Podaj hasło klienta: ";
                        cin >> haslo;
                        cout << "Podaj typ konta klienta: ";
                        cin >> typKonta;
                        cout << "Podaj numer rachunku klienta: ";
                        cin >> numerKonta;
                        cout << "Podaj saldo klienta: ";
                        cin >> saldo;

                        // TUTAJ DODANIE DO BAZY DANYCH

                        cout << "Pomyslnie dodano nowego klienta!" << endl;
                        break;
                    }
                    case 2: {
                        int id, pesel, numerKonta;
                        string imie, nazwisko, haslo, typKonta;
                        double saldo;

                        cout << "--- Modyfikacja konta ---" << endl;
                        cout << "Podaj PESEL klienta: ";
                        cin >> pesel;
                        // TUTAJ SZUKAMY PESELU W BAZIE DANYCH I WYSWIETLAMY DANE

//                        cout << "ID: " << id << endl;
//                        cout << "Imie: " << imie << endl;
//                        cout << "Nazwisko " << nazwisko << endl;
//                        cout << "Haslo: " << haslo << endl;
//                        cout << "Typ konta: " << typKonta << endl;
//                        cout << "Numer konta: " << numerKonta << endl;

                        int choiceModyfikacja;
                        cout << endl << "Co chcesz zmienic?" << endl;
                        cout << "1. Imie" << endl;
                        cout << "2. Nazwisko" << endl;
                        cout << "3. Typ konta" << endl;
                        cout << "4. Wyjdz" << endl;
                        cout << "Wybierz opcję: ";
                        cin >> choiceModyfikacja;

                        switch (choiceModyfikacja) {
                            case 1: {
                                string noweImie;
                                cout << "Podaj nowe imie: ";
                                cin >> noweImie;
                                //klient.setImie(noweImie);
                                cout << "Zmieniono imie na: " << noweImie << endl;
                                break;
                            }
                            case 2: {
                                string noweNazwisko;
                                cout << "Podaj nowe nazwisko: ";
                                cin >> noweNazwisko;
                                //klient.setImie(noweImie);
                                cout << "Zmieniono nazwisko na: " << noweNazwisko << endl;
                                break;
                            }
                            case 3: {
                                string nowyTyp;
                                cout << "Podaj nowy typ konta ";
                                cin >> nowyTyp;
                                //klient.setImie(noweImie);
                                cout << "Zmieniono typ konta na: " << nowyTyp << endl;
                                break;
                            }
                            case 4: {
                                break;
                            }
                            default:
                                cout << "Niepoprawny wybór opcji." << endl;
                        }
                        break;
                    }
                    case 3:
                        cout << "--- Wplata ---" << endl;
                        // Implementacja...
                        break;
                    case 4:
                        cout << "--- Wyplata ---" << endl;
                        // Implementacja...
                        break;
                    case 5:
                        cout << "--- Sprawdz saldo ---" << endl;
                        // Implementacja...
                        break;
                    case 6:
                        cout << "--- Lista wszystkich kont ---" << endl;
                        break;
                    case 7:
                        cout << "--- Zamkniecie konta ---" << endl;
                        break;
                    case 8:
                        cout << "Wylogowano!" << endl << endl;
                        break;
                    default:
                        cout << "Niepoprawny wybór opcji." << endl;
                }
            } while (choicePracownik != 8); // Pętla pracownika

        } else if (inputPesel == klient1.getPesel() && inputHaslo == klient1.getHaslo()) {
            cout << "Pomyslnie zalogowano!" << endl;

            int choiceKlient;
            do {
                // Wyświetlanie menu klienta
                cout << endl;
                cout << "------ PANEL KLIENTA ------" << endl;
                cout << "1. Wplata" << endl;
                cout << "2. Wyplata" << endl;
                cout << "3. Sprawdz saldo" << endl;
                cout << "4. Wyloguj" << endl;
                cout << "Wybierz opcję: ";
                cin >> choiceKlient;

                switch (choiceKlient) {
                    case 1:
                        cout << "--- Wplata ---" << endl;
                        // Implementacja...
                        break;
                    case 2:
                        cout << "--- Wyplata ---" << endl;
                        // Implementacja...
                        break;
                    case 3:
                        cout << "--- Sprawdz saldo ---" << endl;
                        // Implementacja...
                        break;
                    case 4:
                        cout << "Wylogowano!" << endl << endl;
                        break;
                    default:
                        cout << "Niepoprawny wybór opcji." << endl;
                }
            } while (choiceKlient != 4); // Pętla klienta

        } else {
            cout << "Niepoprawny login lub haslo. Logowanie nieudane." << endl << endl;
        }

    } while (true); // Pętla logowania

    return 0;
}