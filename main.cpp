#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <vector>

using namespace std;

struct UserData{
    int id;
    string login;
    string password;
};
struct PersonalData {
    int id;
    int userId;
    string name;
    string surname;
    string email;
    string telephone;
    string adress;
};
string loadLine() {
    string line;
    cin.sync();
    getline(cin, line);
    return line;
}
int strToInt(string numberString) {
    stringstream ss;
    int number;

    ss << numberString;
    ss >> number;

    return number;
}
string intToStr(int number) {
    stringstream ss;
    string numberString;

    ss << number;
    ss >> numberString;

    return numberString;
}
bool isIdValid(vector<PersonalData> &personDataBase,int id) {
    bool isValid = false;
    for (int i = 0; i < (int)personDataBase.size(); i++) {
        if (id == personDataBase.at(i).id) isValid = true;
    }
    return isValid;
}
string personToString(PersonalData person) {
  return intToStr(person.id) + "|" + intToStr(person.userId) + "|" + person.name + "|" + person.surname + "|" + person.email + "|" + person.telephone + "|" + person.adress + "|";
}
string userToString(UserData user) {
    return intToStr(user.id) + "|" + user.login + "|" + user.password + "|";
}
void assignToCategory(PersonalData &person,vector<PersonalData> &personDataBase, int caseNumber, string text){
    switch(caseNumber) {
    case 1:
        person.id = strToInt(text);
        break;

    case 2:
        person.userId = strToInt(text);
        break;

    case 3:
        person.name = text;
        break;

    case 4:
        person.surname = text;
        break;

    case 5:
        person.email = text;
        break;

    case 6:
        person.telephone = text;
        break;

    case 7:
        person.adress = text;
        break;
    }
}
void assignToCategory(vector<UserData> &userDataBase, int caseNumber, string text) {
    int lastPos;
    if (userDataBase.empty()) lastPos = 0;
    else lastPos = userDataBase.size() - 1;

    switch(caseNumber) {
    case 1:
        userDataBase.at(lastPos).id = strToInt(text);
        break;

    case 2:
        userDataBase.at(lastPos).login = text;
        break;

    case 3:
        userDataBase.at(lastPos).password = text;
        break;
    }
}
void loadDataBase(vector<PersonalData> &personDataBase, int loggedUserId) {
    PersonalData person;
    string line, word = "";
    fstream file;
    file.open("baza.txt", ios::in);

    while(getline(file, line)) {
        int pos = 0, categoryNum = 0;
        word.clear();
        while( pos < (int)line.length()) {
            if (line[pos] == '|') {
                categoryNum++;
                assignToCategory(person, personDataBase, categoryNum, word);
                pos++;
                word.clear();
            }
            word += line[pos];
            pos++;
        }
        if(loggedUserId == person.userId) personDataBase.push_back(person);
    }
    file.close();
}
void printByPos(vector<PersonalData> &personDataBase, int personPos) {
    cout << "ID :" << personDataBase.at(personPos).id << endl;
    cout << "Imie :" << personDataBase.at(personPos).name <<endl;
    cout << "Nazwisko :" << personDataBase.at(personPos).surname <<endl;
    cout << "Email :" << personDataBase.at(personPos).email <<endl;
    cout << "Telefon :" << personDataBase.at(personPos).telephone <<endl;
    cout << "Adres :" << personDataBase.at(personPos).adress << endl;
    cout << endl <<endl;
}
void printEveryone(vector<PersonalData> &personDatabase) {
    system("cls");
    if (personDatabase.size() == 0) cout << "Ksiazka adresowa jest pusta!" << endl << endl;
    else {
        for (int i = 0; i < (int)personDatabase.size(); i++) {
            printByPos(personDatabase, i);
        }
    }
}
int checkLastID() {
    int id;
    string strId;
    string line;
    fstream file;

    file.open("baza.txt", ios::in);
    if (file.peek() == ifstream::traits_type::eof()) id = 0;
    else {
        while(getline(file, line)) {
            strId = line[0];
        }
        id = strToInt(strId);
    }
    file.close();
    return id;
}
int getPosByID(vector<PersonalData> &personDataBase, int id) {
    int pos = 0;
    for (int i = 0; i < (int)personDataBase.size(); i++ ) {
        if (personDataBase.at(i).id == id) pos = i;
    }
    return pos;
}
void savePersonToFile(PersonalData newPerson){
    fstream file;
    file.open("baza.txt", ios::app);
    file << personToString(newPerson);
    file << endl;
    file.close();
}
void makeTempEditedDataBase(vector<PersonalData> &personDataBase, int pos){
    fstream file, temp;
    int idOriginal;
    int idEdited = personDataBase.at(pos).id;
    string line;
    file.open("baza.txt", ios::in);
    temp.open("baza_temp.txt", ios::app);

    while(getline(file, line)) {
        idOriginal = line[0] - 48;
        if (idOriginal == idEdited ) {
            temp << personToString(personDataBase.at(pos));
            temp << endl;
        } else {
            temp << line;
            temp << endl;
        }
    }
    file.close();
    temp.close();
}

void saveDataBase(vector<PersonalData> &personDataBase){
    fstream file;
    file.open("baza.txt", ios::out);

    for (int i = 0; i < (int)personDataBase.size(); i++) {
        file << personToString(personDataBase.at(i));
        file << endl;
    }
    file.close();
}
void editParameter(vector<PersonalData> &personDataBase, int pos, char parameterID) {
    switch(parameterID)
        {
        case '1':
            cout << endl << "Wprowadz nowe imie: ";
            personDataBase.at(pos).name = loadLine();
            break;

        case '2':
            cout << endl << "Wprowadz nowe nazwisko: ";
            personDataBase.at(pos).surname = loadLine();
            break;

       case '3':
            cout << endl << "Wprowadz nowy email: ";
            personDataBase.at(pos).email = loadLine();
            break;

        case '4':
            cout << endl << "Wprowadz nowy telefon: ";
            personDataBase.at(pos).telephone = loadLine();
            break;

        case '5':
            cout << endl << "Wprowadz nowy adres: ";
            personDataBase.at(pos).adress = loadLine();
            break;
        }
}
void editPerson(vector<PersonalData> &personDataBase) {
    int id;
    char choice;
    printEveryone(personDataBase);

    cout << endl << "Podaj ID osoby do edycji:";
    cin >> id;

    if(isIdValid(personDataBase, id)) {
        int pos = getPosByID(personDataBase, id);

        while(choice != '9') {
            system("cls");
            printByPos(personDataBase, pos);

            cout << "Wybierz opcje:" << endl;
            cout << "1. Edytuj imie" << endl;
            cout << "2. Edytuj nazwisko" << endl;
            cout << "3. Edytuj email" << endl;
            cout << "4. Edytuj telefon" << endl;
            cout << "5. Edytuj adres" << endl;
            cout << "9. Wroc do menu glownego" << endl;
            choice = getch();

            editParameter(personDataBase, pos, choice);
        }
        makeTempEditedDataBase(personDataBase, pos);
        remove("baza.txt");
        rename("baza_temp.txt","baza.txt");

    } else cout << "Brak takiego ID w bazie!" <<endl, system("pause");
}
void addPerson(vector<PersonalData> &personDataBase, int userId) {
    PersonalData newPerson;
    newPerson.id = checkLastID() + 1;
    newPerson.userId = userId;

    system("cls");

    cout << "Podaj imie     :";
    newPerson.name = loadLine();

    cout << "Podaj nazwisko :";
    newPerson.surname = loadLine();

    cout << "Podaj email    :";
    newPerson.email = loadLine();

    cout << "Podaj telefon  :";
    newPerson.telephone = loadLine();

    cout << "Podaj adres    :";
    newPerson.adress = loadLine();

    personDataBase.push_back(newPerson);
    savePersonToFile(newPerson);
}
void removePerson(vector<PersonalData> &personDataBase){
    int id;
    char choice;
    printEveryone(personDataBase);

    cout << endl << "Podaj ID osoby do usuniecia:";
    cin >> id;
    if(isIdValid(personDataBase, id)) {
        int pos = getPosByID(personDataBase, id);

        system("cls");
        printByPos(personDataBase, pos);
        cout << endl << "Wcisnij klawisz 't' by potwierdzic usuniecie lub inny aby anulowac:";
        choice = getch();

        if (choice == 't') {
            personDataBase.erase(personDataBase.begin()+ pos);
            saveDataBase(personDataBase);
        }
    } else cout << "Brak takiego ID w bazie!" <<endl, system("pause");
}
void printByName(vector<PersonalData> &personDataBase) {
    string name;
    int counter = 0;

    system("cls");
    cout << "Podaj szukane imie:";
    cin >> name;

    for (int i = 0; i < (int)personDataBase.size(); i++) {
        if (name == personDataBase.at(i).name) {
            printByPos(personDataBase, i);
            counter++;
        }
    }
    if (counter == 0)  cout << endl << "Brak osob o takim imieniu w bazie!" << endl;
}
void printBySurname(vector<PersonalData> &personDataBase) {
    string surname;
    int counter = 0;

    system("cls");
    cout << "Podaj szukane nazwisko:";
    cin >> surname;

    for (int i = 0; i < (int)personDataBase.size(); i++) {
        if (surname == personDataBase.at(i).surname) {
            printByPos(personDataBase, i);
            counter++;
        }
    }
    if (counter == 0)  cout << endl << "Brak osob o takim nazwisku w bazie!" << endl;
}
void loadUsers(vector<UserData> &userDataBase) {
    UserData user;
    string line, word = "";
    fstream file;
    file.open("uzytkownicy.txt", ios::in);

    while(getline(file, line)) {
        int pos = 0, categoryNum = 0;
        word.clear();
        userDataBase.push_back(user);

        while( pos < (int)line.length()) {

            if (line[pos] == '|') {
                categoryNum++;
                assignToCategory(userDataBase, categoryNum, word);
                pos++;
                word.clear();
            }
            word += line[pos];
            pos++;
        }
    }
    file.close();
}
string userNameByID(vector<UserData> &userDataBase, int id) {
    string name = "";
    for (int i = 0; i < (int)userDataBase.size(); i++) {
        if (userDataBase.at(i).id == id) name = userDataBase.at(i).login;
    }
    return name;
}
int signIn(vector<UserData> &userDataBase) {
    string login;
    string password;
    int pos = 0;
    int loggedUserID = 0;
    bool userFound = false;
    system("cls");

    cout << "Podaj login: ";
    login = loadLine();

    cout << "Podaj haslo: ";
    password = loadLine();

    while (pos < (int)userDataBase.size() && !userFound) {
        if (login == userDataBase.at(pos).login) {
            if (password == userDataBase.at(pos).password) {
                userFound = true;
                loggedUserID = userDataBase.at(pos).id;
            }
        }
        pos++;
    }
    if (pos >= (int)userDataBase.size() && !userFound ) {
        cout << endl << "Bledny login lub haslo" << endl;
        system("pause");
    }
    return loggedUserID;
}
void addUser(vector<UserData> &userDataBase) {
    fstream file;
    UserData newUser;
    file.open("uzytkownicy.txt", ios::app);
    system("cls");

    cout << "         REJESTRACJA UZYTKOWNIKA" << endl << endl;

    newUser.id = userDataBase.back().id + 1;
    cout << "Podaj login     :";
    newUser.login = loadLine();
    cout << "Podaj haslo     :";
    newUser.password = loadLine();

    userDataBase.push_back(newUser);
    file << userToString(newUser);
    file << endl;
    file.close();
}
void userMenu(vector<UserData> &userDataBase, int &loggedUserID) {
    while(loggedUserID == 0) {
        system("cls");

        cout << "         WITAJ W KSIAZCE ADRESOWEJ" << endl;
        cout << "              Wybierz opcje:" << endl << endl;

        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja uzytkownika" << endl;
        cout << "9. Zamknij program" << endl;

        char choice = getch();

        switch(choice) {

        case '1':
            loggedUserID = signIn(userDataBase);
            break;

        case '2':
            addUser(userDataBase);
            break;

        case '9':
            exit(1);
            break;
        }
        system("cls");
    }
}
void mainMenu(vector<UserData> &userDataBase, vector<PersonalData> &personDataBase, int &loggedUserID){
    while (loggedUserID != 0) {
        cout << "         WITAJ W KSIAZCE ADRESOWEJ" << endl;
        cout << "       Aktualny uzytkownik: " << userNameByID(userDataBase, loggedUserID) << endl << endl;
        cout << "              Wybierz opcje:" << endl << endl;


        cout << "1. Wyswietl zawartosc ksiazki adresowej" << endl;
        cout << "2. Dodaj pozycje do ksiazki adresowej" << endl;
        cout << "3. Edytuj pozycje w ksiazce adresowej" << endl;
        cout << "4. Usun pozycje z ksiazki adresowej" << endl;
        cout << "5. Szukaj w ksiazce adresowej po imieniu" << endl;
        cout << "6. Szukaj w ksiazce adresowej po nazwisku" << endl;
        cout << "7. Wyloguj uzytkownika" << endl;
        cout << "9. Zamknij program" << endl;

        char choice = getch();

        switch(choice) {
        case '1':
            printEveryone(personDataBase);
            system("pause");
            break;

        case '2':
            addPerson(personDataBase, loggedUserID);
            break;

        case '3':
            editPerson(personDataBase);
            break;

        case '4':
            removePerson(personDataBase);
            break;

        case '5':
            printByName(personDataBase);
            system("pause");
            break;

        case '6':
            printBySurname(personDataBase);
            system("pause");
            break;

        case '7':
            loggedUserID = 0;
            break;

        case '9':
            exit(1);
            break;
        }
        system("cls");
    }
}
int main()
{
    vector<PersonalData> personDataBase;
    vector<UserData> userDataBase;
    int loggedUserID = 0;
    loadUsers(userDataBase);

    while(true) {
        userMenu(userDataBase, loggedUserID);
        loadDataBase(personDataBase, loggedUserID);
        mainMenu(userDataBase, personDataBase, loggedUserID);
        personDataBase.clear();
    }
    return 0;
}
