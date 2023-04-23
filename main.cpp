#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <vector>

using namespace std;

struct PersonalData {
    int id;
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

    string personString = intToStr(person.id) + "|" + person.name + "|" + person.surname + "|" + person.email + "|" + person.telephone + "|" + person.adress + "|";
    return personString;
}

void assignToCategory(vector<PersonalData> &personDataBase, int caseNumber, string text){
    int lastPos;
    if (personDataBase.empty()) lastPos = 0;
    else lastPos = personDataBase.size() - 1;

    switch(caseNumber) {
    case 1:
        personDataBase.at(lastPos).id = strToInt(text);
        break;

    case 2:
        personDataBase.at(lastPos).name = text;
        break;

    case 3:
        personDataBase.at(lastPos).surname = text;
        break;

    case 4:
        personDataBase.at(lastPos).email = text;
        break;

    case 5:
        personDataBase.at(lastPos).telephone = text;
        break;

    case 6:
        personDataBase.at(lastPos).adress = text;
        break;
    }
}
void loadDataBase(vector<PersonalData> &personDataBase) {

    PersonalData person;
    string line, word = "";
    fstream file;
    file.open("baza.txt", ios::in);

    while(getline(file, line)) {
        int pos = 0, categoryNum = 0;
        word.clear();
        personDataBase.push_back(person);

        while( pos < (int)line.length()) {

            if (line[pos] == '|') {
                categoryNum++;
                assignToCategory(personDataBase, categoryNum, word);
                pos++;
                word.clear();
            }
            word += line[pos];
            pos++;
        }
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
int checkLastID(vector<PersonalData> &personDataBase) {
    int id;
    if (personDataBase.empty()) id = 1;
    else {
        id = personDataBase.at(0).id;
        for (int i = 1; i < (int)personDataBase.size(); i++) {
            if(id < personDataBase.at(i).id) id = personDataBase.at(i).id;
        }
    }
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
void saveDataBase(vector<PersonalData> &personDataBase){
    fstream file;
    file.open("baza.txt", ios::out);

    for (int i = 0; i < (int)personDataBase.size(); i++) {
        file << personToString(personDataBase.at(i));
        file << endl;
    }
    file.close();
}

void editParameter(vector<PersonalData> &personDataBase, int pos, char parameterID)
{
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
void editPerson(vector<PersonalData> &personDataBase){
    int id;
    char choice;
    printEveryone(personDataBase);

    cout << endl << "Podaj ID osoby do edycji:";
    cin >> id;

    if(isIdValid(personDataBase, id)) {
        int pos = getPosByID(personDataBase, id);

        while(choice != '9'){
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
            saveDataBase(personDataBase);
        }
    }
    else cout << "Brak takiego ID w bazie!" <<endl, system("pause");
    }

void addPerson(vector<PersonalData> &personDataBase) {
    PersonalData newPerson;
    if (personDataBase.empty()) newPerson.id = checkLastID(personDataBase);
    else newPerson.id = checkLastID(personDataBase) + 1;

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
int main()
{
    vector<PersonalData> personDataBase;
    loadDataBase(personDataBase);

    while (true)
    {
        cout << "         WITAJ W KSIAZCE ADRESOWEJ" << endl;
        cout << "              Wybierz opcje:" << endl << endl;

        cout << "1. Wyswietl zawartosc ksiazki adresowej" << endl;
        cout << "2. Dodaj pozycje do ksiazki adresowej" << endl;
        cout << "3. Edytuj pozycje w ksiazce adresowej" << endl;
        cout << "4. Usun pozycje z ksiazki adresowej" << endl;
        cout << "5. Szukaj w ksiazce adresowej po imieniu" << endl;
        cout << "6. Szukaj w ksiazce adresowej po nazwisku" << endl;
        cout << "9. Zamknij program" << endl;

        char choice = getch();

        switch(choice)
        {
        case '1':
            printEveryone(personDataBase);
            system("pause");
            break;

        case '2':
            addPerson(personDataBase);
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

        case '9':
            exit(1);
            break;
        }
    system("cls");
    }
    return 0;
}
