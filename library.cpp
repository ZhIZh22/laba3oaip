#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Book {  // klas knigi
    string title;
    string author;
    int year;
};

void saveOutput(const string& result) { //zapis v KONEC output.txt
    ofstream outputFile("output.txt", ios::app); 
    if (outputFile.is_open()) {
        outputFile << result << endl;
        outputFile.close();
    }
}

void addBooks() { // dobav knigu v konec
    ofstream file("books.txt", ios::app);
    if (!file.is_open()) {
        cout << "Cant open file" << endl;
        return;
    }

    while (true) {
        string title, author;
        int year;

        cout << "Type title: ";
        getline(cin, title);
        if (title.empty()) break;

        cout << "Type author: ";
        getline(cin, author);

        cout << "Type year: ";
        cin >> year;
        cin.ignore(); // ochistka bufera

        file << title << "|" << author << "|" << year << endl;
        cout << "Book added." << endl;
    }

    file.close();
}

void searchBook() { //pois knigi po nazv
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "Cant open file" << endl;
        return;
    }

    string titleToFind;
    cout << "Type title to find: ";
    getline(cin, titleToFind);

    string line, result;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author;
        int year;
        getline(ss, title, '|');
        getline(ss, author, '|');
        ss >> year;

        if (title == titleToFind) {
            result = "Find book: " + title + ", Author: " + author + ", Year: " + to_string(year);
            cout << result << endl;
            saveOutput(result);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Cant find book." << endl;
        saveOutput("Book not found.");
    }

    file.close();
}

vector<Book> readBooks() { //knigi iz faila
    ifstream file("books.txt");
    vector<Book> books;

    if (!file.is_open()) {
        cout << "Cant open file" << endl;
        return books;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author;
        int year;

        getline(ss, title, '|');
        getline(ss, author, '|');
        ss >> year;

        books.push_back({title, author, year});
    }

    file.close();
    return books;
}

void sortBooks() { //sortirovka knig
    vector<Book> books = readBooks();
    if (books.empty()) return;

    int choice;
    cout << "Sort by author(1) or sort by year(2): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {return a.author < b.author;});
    } 
    
    else if (choice == 2) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {return a.year < b.year;});
    } 
    
    else {
        cout << "Wrong answer" << endl;
        return;
    }

    ofstream file("books.txt", ios::trunc); //perezapis v file
    for (const auto& book : books) {
        file << book.title << "|" << book.author << "|" << book.year << endl;
    }
    file.close();
    cout << "Books sorted and saved" << endl;
}

void booksBeforeYear() { //knigi do goda
    int year;
    cout << "Type year: ";
    cin >> year;
    cin.ignore();

    vector<Book> books = readBooks();
    if (books.empty()) return;

    string result = "Books, released before " + to_string(year) + ":\n";
    for (const auto& book : books) {
        if (book.year <= year) {
            result += book.title + " (" + book.author + ", " + to_string(book.year) + ")\n";
        }
    }

    cout << result << endl;
    saveOutput(result);
}

void menu() { //menu
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add books\n";
        cout << "2. Find book\n";
        cout << "3. Sort books\n";
        cout << "4. Books before year\n";
        cout << "5. Exit\n";
        cout << "Type command number: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addBooks();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                sortBooks();
                break;
            case 4:
                booksBeforeYear();
                break;
            case 5:
                cout << "Exiting." << endl;
                return;
            default:
                cout << "Wrong answer." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
