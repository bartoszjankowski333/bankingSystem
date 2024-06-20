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
// Deklaracja funkcji, true w przypadku pozytywnego zalogowania, false w przeciwnym razie
// Funkcja przyjmuje wskaznik do obiektu sql ktory reprezentuje polaczenie z baza danych oraz dwa ciagi znakow, pesel i password
bool login(sql::Connection* con, const string& pesel, const string& password) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT password FROM bankregisterclient WHERE pesel = ?")); // Przygotowanie zapytania SQL. Zapytanie to wybiera hasło z tabeli bankregisterclient, gdzie PESEL jest równy podanemu PESEL.
        pstmt->setString(1, pesel); // Ustawia wartość pierwszego (i jedynego) parametru w przygotowanym zapytaniu na podany PESEL. Indeksy w zapytaniach przygotowanych zaczynają się od 1.
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery()); // Wykonuje zapytanie i przechowuje wynik w unikalnym wskaźniku do obiektu sql::ResultSet.
        if (res->next()) { // Sprawdza, czy wynik zapytania zawiera jakiekolwiek wiersze (czy użytkownik o podanym PESEL istnieje).
            string storedPassword = res->getString("password"); // Pobiera hasło z wyniku zapytania.
            if (storedPassword == password) { //Porównuje pobrane hasło z hasłem podanym przez użytkownika.
                return true; // Jeśli hasła są zgodne, funkcja zwraca true.
            }
            else {
                cout << "Niepoprawne haslo." << endl; // Jeśli hasła nie są zgodne, funkcja wyświetla komunikat "Niepoprawne haslo." i zwraca false.
                return false;
            }
        }
        else {
            cout << "Konto nie istnieje." << endl; // Jeśli wynik zapytania nie zawiera żadnych wierszy (czyli użytkownik o podanym PESEL nie istnieje), funkcja wyświetla komunikat "Konto nie istnieje." i zwraca false
            return false;
        }
    }
    catch (sql::SQLException& e) { // Blok catch dla wyjątków SQL
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
        return false;
    }
    catch (exception& e) { // Blok catch dla innych wyjątków
        cerr << "Other Error: " << e.what() << endl;
        return false;
    }
}





//Funckja sprawdzajaca stan konta
int sprawdzStanKonta(sql::Connection* con, const string& pesel) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT stan_konta FROM bankregisterclient WHERE pesel = ?")); // Przygotowanie zapytania SQL. Zapytanie to wybiera stan_konta z tabeli bankregisterclient, gdzie pesel jest równy podanemu pesel.
        pstmt->setString(1, pesel); // Ustawia wartość pierwszego (i jedynego) parametru w przygotowanym zapytaniu na podany PESEL. Indeksy w zapytaniach przygotowanych zaczynają się od 1.
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery()); // Wykonuje zapytanie i przechowuje wynik w unikalnym wskaźniku do obiektu sql::ResultSet.
        if (res->next()) { // Sprawdzenie, czy zapytanie zwrocilo wynik. Metoda next() w obiekcie ResultSet przesuwa kursor na następny wiersz wyniku. Tutaj sprawdzamy, czy istnieje co najmniej jeden wiersz.
            return res->getInt("stan_konta"); // res->getInt("stan_konta") pobiera wartość kolumny stan_konta z aktualnego wiersza wyniku i zwraca ją jako wartość funkcji, jeśli wiersz istnieje.
        }
        else { // Obsługa przypadku, gdy konto nie istnieje
            cerr << "Nie znaleziono konta z podanym peselem." << endl;
            return -1;
        }
    }
    catch (sql::SQLException& e) { // Blok catch dla wyjątków SQL
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
        return -1;
    }
    catch (exception& e) { // Blok catch dla innych wyjątków
        cerr << "Other Error: " << e.what() << endl;
        return -1;
    }
}




Konto sprawdzDaneKonta(sql::Connection* con, const string& pesel) {
    Konto konto;
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT id, pesel, name, lastname, numer_rozliczeniowy, typ_konta FROM bankregisterclient WHERE pesel = ?")); // Przygotowanie zapytania SQL, pobiera różne dane konta na podstawie pesel.
        pstmt->setString(1, pesel); // Ustawienie wartości parametru PESEL w zapytaniu
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery()); // Wykonanie zapytania i przechwycenie wyniku
        if (res->next()) { // Sprawdzenie, czy zapytanie zwróciło wynik // Jeśli wynik jest dostępny, ustawienie danych konta // Metoda next() w obiekcie ResultSet przesuwa kursor na następny wiersz wyniku.
            // if (res->next()) sprawdza, czy wynik zawiera co najmniej jeden wiersz. Jeśli tak, dane są pobierane z wyniku i ustawiane w obiekcie konto.
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
    return konto; // Zwraca obiekt konto, który może zawierać pobrane dane konta lub informacje o błędzie (w przypadku, gdy ID konta zostało ustawione na -1).
}                   // pozniej za pomoca tego obiektu wywolujemy metody pobierzImie itp. zeby wyswietlic dane






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
    if (wybor == 1) {

        cout << "Podaj pesel: ";
        cin >> pesel;
        cout << "Wpisz haslo: ";
        cin >> password;
        cout << "Podaj Imie: ";
        cin >> name;
        cout << "Podaj nazwisko: ";
        cin >> lastname;
        cout << "Podaj numer rozliczeniowy: ";
        cin >> numer_rozliczeniowy;
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

