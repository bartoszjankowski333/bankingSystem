#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

/*struct Konto {
    int id;
    string pesel, name, lastname, numer_rozliczeniowy, typ_konta;
};
Konto sprawdzDaneKonta(sql::Connection* con, const string& pesel) {
    Konto konto;
    try {
        unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT id, pesel, name, lastname, numer_rozliczeniowy, typ_konta FROM bankregisterclient WHERE pesel = ?"));
        pstmt->setString(1, pesel);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            konto.id = res->getInt("id");
            konto.pesel = res->getString("pesel");
            konto.name = res->getString("name");
            konto.lastname = res->getString("lastname");
            konto.numer_rozliczeniowy = res->getString("numer_rozliczeniowy");
            konto.typ_konta = res->getString("typ_konta");
        }
        else {
            cerr << "Nie znaleziono konta z podanym peselem." << endl;
            konto.id = -1;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        cerr << "Error Code: " << e.getErrorCode() << endl;
        konto.id = -1;
    }
    catch (exception& e) {
        cerr << "Other Error: " << e.what() << endl;
        konto.id = -1;
    }
    return konto;
}

*/
class Konto {
private:
    int id;
    string pesel, name, lastname, numer_rozliczeniowy;
    char typ_konta;

public:
    Konto() : id(-1), typ_konta('N') {}  // Konstruktor domyślny, 'N' jako domyślny typ konta

    void ustawId(int id) {
        this->id = id;
    }

    void ustawPesel(const string& pesel) {
        this->pesel = pesel;
    }

    void ustawImie(const string& name) {
        this->name = name;
    }

    void ustawNazwisko(const string& lastname) {
        this->lastname = lastname;
    }

    void ustawNumerRozliczeniowy(const string& numer_rozliczeniowy) {
        this->numer_rozliczeniowy = numer_rozliczeniowy;
    }

    void ustawTypKonta(char typ_konta) {
        this->typ_konta = typ_konta;
    }

    int pobierzId() const {
        return id;
    }

    string pobierzPesel() const {
        return pesel;
    }

    string pobierzImie() const {
        return name;
    }

    string pobierzNazwisko() const {
        return lastname;
    }

    string pobierzNumerRozliczeniowy() const {
        return numer_rozliczeniowy;
    }

    char pobierzTypKonta() const {
        return typ_konta;
    }
};


