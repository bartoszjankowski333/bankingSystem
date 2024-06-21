// bank.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <stdlib.h>
#include <iostream>
#include <memory>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "classes.h"

using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1";
const string username = "root";
const string password = "";

// Funkcja logowania
bool login(sql::Connection* con, const string& pesel, const string& password) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT password FROM bankregisterclient WHERE pesel = ?"));
        pstmt->setString(1, pesel);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            string storedPassword = res->getString("password");
            if (storedPassword == password) {
                return true;
            }
            else {
                cout << "Niepoprawne haslo." << endl;
                return false;
            }
        }
        else {
            cout << "Konto nie istnieje." << endl;
            return false;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
        return false;
    }
    catch (exception& e) {
        cerr << "Other Error: " << e.what() << endl;
        return false;
    }
}
bool czyPeselPoprawny(const string& pesel) {
    // Sprawdzenie długości PESEL
    if (pesel.length() != 11) {
        return false;
    }

    // Sprawdzenie czy każdy znak PESEL jest cyfrą
    for (char c : pesel) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Jeśli wszystkie warunki są spełnione, PESEL jest poprawny
    return true;
}


bool czyNumerPoprawny(const string& numer_rozliczeniowy) {
    // Sprawdzenie długości numeru rozliczeniowego 
    if (pesel.length() != 26) {
        return false;
    }

    // Sprawdzenie czy każdy znak numer jest cyfrą
    for (char c : pesel) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Jeśli wszystkie warunki są spełnione, numer jest poprawny
    return true;
}







int sprawdzStanKonta(sql::Connection* con, const string& pesel) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT stan_konta FROM bankregisterclient WHERE pesel = ?"));
        pstmt->setString(1, pesel);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            return res->getInt("stan_konta");
        }
        else {
            cerr << "Nie znaleziono konta z podanym peselem." << endl;
            return -1;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
        return -1;
    }
    catch (exception& e) {
        cerr << "Other Error: " << e.what() << endl;
        return -1;
    }
}

Konto sprawdzDaneKonta(sql::Connection* con, const string& pesel) {
    Konto konto;
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT id, pesel, name, lastname, numer_rozliczeniowy, typ_konta FROM bankregisterclient WHERE pesel = ?"));
        pstmt->setString(1, pesel);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            konto.ustawId(res->getInt("id"));
            konto.ustawPesel(res->getString("pesel"));
            konto.ustawImie(res->getString("name"));
            konto.ustawNazwisko(res->getString("lastname"));
            konto.ustawNumerRozliczeniowy(res->getString("numer_rozliczeniowy"));
            konto.ustawTypKonta(res->getString("typ_konta")[0]); // Pobranie pierwszego znaku
        }
        else {
            cerr << "Nie znaleziono konta z podanym peselem." << endl;
            konto.ustawId(-1);
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
        konto.ustawId(-1);
    }
    catch (exception& e) {
        cerr << "Other Error: " << e.what() << endl;
        konto.ustawId(-1);
    }
    return konto;
}

void wplata(sql::Connection* con, const string& pesel, double kwota) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("UPDATE bankregisterclient SET stan_konta = stan_konta + ? WHERE pesel = ?"));
        pstmt->setDouble(1, kwota);
        pstmt->setString(2, pesel);
        pstmt->executeUpdate();
        cout << "Wplata dokonana" << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
    }
    catch (exception& e) {
        cerr << "Other Error: " << e.what() << endl;
    }
}

int main() {
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt = nullptr; // Inicjalizacja wskaźnika do nullptr

    try {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    // Please create database "bank" ahead of time
    con->setSchema("bank");

    string pesel, password, name, lastname, numer_rozliczeniowy;
    char typ_konta;
    int stan_konta;
    char wybor;
    cout << "Witaj w aplikacji bankowej." << " Wybierz opcje, ktora chcesz wykonac na swoim koncie." << endl << "1. Zaloz konto" << endl << "2. Zaloguj sie" << endl;
    cin >> wybor;
    if (wybor == '1') {

        cout << "Podaj pesel: ";
        cin >> pesel;
        if (!czyPeselPoprawny(pesel)) {
            cout << "Blad: PESEL powinien składac sie z dokladnie 11 cyfr." << endl;
            return 1; // Zakończenie programu z kodem błędu
        }
        cout << "Wpisz haslo: ";
        cin >> password;
        cout << "Podaj Imie: ";
        cin >> name;
        cout << "Podaj nazwisko: ";
        cin >> lastname;
        cout << "Podaj numer rozliczeniowy: ";
        cin >> numer_rozliczeniowy;
         if (!czyNumerPoprawny(numer_rozliczeniowy)) {
            cout << "Blad: Numer powinien składac sie z dokladnie 26 cyfr." << endl;
            return 1; // Zakończenie programu z kodem błędu
        }
        stan_konta = 0;  // Ustawienie stanu konta na 0
        cout << "Podaj typ konta (jeden znak): ";
        cin >> typ_konta;
        pstmt = con->prepareStatement("INSERT INTO bankregisterclient(pesel, password, name, lastname, numer_rozliczeniowy, stan_konta, typ_konta) VALUES(?,?,?,?,?,?,?)");
        pstmt->setString(1, pesel);
        pstmt->setString(2, password);
        pstmt->setString(3, name);
        pstmt->setString(4, lastname);
        pstmt->setString(5, numer_rozliczeniowy);
        pstmt->setInt(6, stan_konta);
        pstmt->setString(7, string(1, typ_konta)); // Konwersja char na string
        pstmt->execute();
        cout << "Twoje konto zostalo zalozone." << endl;
    }
    if (wybor == '2') {
        cout << "Podaj pesel: ";
        cin >> pesel;
        cout << "Podaj haslo: ";
        cin >> password;
        if (login(con, pesel, password)) {
            cout << "Pomyslnie zalogowano." << endl;
            while (true) {
                cout << "Wybierz opcje: " << endl;
                cout << "1. Sprawdz stan konta." << endl;
                cout << "2. Wyswietl dane o swoim koncie." << endl;
                cout << "3. Wplata." << endl;
                cout << "4. Wyplata." << endl;
                cout << "5. Wyloguj sie." << endl;
                cout << "6. Zamknij konto." << endl;
                cin >> wybor;
                int saldo = sprawdzStanKonta(con, pesel);
                Konto konto = sprawdzDaneKonta(con, pesel);
                switch (wybor) {
                case '1':
                    cout << "Twoj stan konta wynosi: " << saldo << endl;

                case '2':
                    cout << "Informacje o Twoim koncie: " << endl;
                    cout << "ID: " << konto.pobierzId() << endl;
                    cout << "Pesel: " << konto.pobierzPesel() << endl;
                    cout << "Imie: " << konto.pobierzImie() << endl;
                    cout << "Nazwisko: " << konto.pobierzNazwisko() << endl;
                    cout << "Numer rozliczeniowy: " << konto.pobierzNumerRozliczeniowy() << endl;
                    cout << "Typ konta: " << konto.pobierzTypKonta() << endl;
                case '3':
                    double kwota;
                    cout << "Podaj kwote do wplaty: ";
                    cin >> kwota;
                    wplata(con, pesel, kwota);
                    break;
                case '4':

                case '5':
                    cout << "Wylogowano z konta." << endl;
                    break;
                    return 0;
                case '6':
                    cout << "Na pewno chcesz zamknac swoje konto? Mamy niesamowite znizki dla naszych klientow." << endl << "Stracisz WSZYSTKIE promocje oraz proces usuwania konta jest nieodwracalny." << endl;
                    cin >> wybor;
                    if (wybor == 'tak') {
                        pstmt = con->prepareStatement("DELETE FROM bankregisterclient WHERE pesel = ?");
                        pstmt->setString(1, pesel);
                        pstmt->execute();
                        cout << "Twoje konto zostalo zamkniete." << endl;
                        break;
                    }
                }
            }
        } else cout << "Niepoprawne dane." << endl;
    
        
    } else cout << "Wybierz odpowiednia opcje" << endl;

    delete pstmt;
    delete con;

    return 0;
}

