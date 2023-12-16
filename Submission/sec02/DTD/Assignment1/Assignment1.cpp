#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_BOOKS = 10; 

class Book {
private:
    string title;
    string author;
    int publicationYear;
    string ISBN;

public:
    // Default Constructor
    Book() : title(""), author(""), publicationYear(0), ISBN("") {}

    // Parameterized Constructor
    Book(const string& t, const string& a, int year, const string& isbn)
        : title(t), author(a), publicationYear(year), ISBN(isbn) {}

    // Accessors
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getPublicationYear() const { return publicationYear; }
    string getISBN() const { return ISBN; }

    // Display method
    void displayBook() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Year: " << publicationYear << ", ISBN: " << ISBN << endl;
    }
};

// Function to swap two books
void swapBooks(Book& a, Book& b) {
    Book temp = a;
    a = b;
    b = temp;
}

// Function to sort books based on user's choice using bubble sort
void sortBooks(Book books[], int size, int option) {
    switch (option) {
        case 1:
            for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {
                    if (books[j].getTitle() > books[j + 1].getTitle()) {
                        swapBooks(books[j], books[j + 1]);
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {
                    if (books[j].getAuthor() > books[j + 1].getAuthor()) {
                        swapBooks(books[j], books[j + 1]);
                    }
                }
            }
            break;
        case 3:
            for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {
                    if (books[j].getPublicationYear() > books[j + 1].getPublicationYear()) {
                        swapBooks(books[j], books[j + 1]);
                    }
                }
            }
            break;
        case 4:
            for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {
                    if (books[j].getISBN() > books[j + 1].getISBN()) {
                        swapBooks(books[j], books[j + 1]);
                    }
                }
            }
            break;
        default:
            cout << "Invalid option" << endl;
    }
}

// Function to print books in tabular format
void printBooks(const Book books[], int size) {
    cout << "<<< Sorted Books >>>" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(50) << left << "| Title"
         << setw(30) << left << "| Author"
         << setw(10) << left << "| Year"
         << setw(15) << left << "| ISBN" << " |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < size; ++i) {
        cout << setw(50) << left << "| " + books[i].getTitle()
             << setw(30) << left << "| " + books[i].getAuthor()
             << setw(10) << left << "| " + to_string(books[i].getPublicationYear())
             << setw(15) << left << "| " + books[i].getISBN() + "|" << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
}

// Function to search for a book based on user's choice
void searchBooks(const Book books[], int size, int option, const string& key) {
    switch (option) {
        case 1:
            // Search by title
            for (int i = 0; i < size; ++i) {
                if (books[i].getTitle() == key) {
                    books[i].displayBook();
                    return;
                }
            }
            cout << "Book with title '" << key << "' not found." << endl;
            break;
        case 2:
            // Implement search logic for other options  author)
            break;
        case 3:
            // Implement search logic for other options by publication year)
            break;
        case 4:
            // Implement search logic for other options by ISBN)
            break;

        default:
            cout << "Invalid option" << endl;
    }
}

int main() {
    // Read books from file
    ifstream inputFile("book.txt");
    Book books[MAX_BOOKS];
    int numBooks = 0;

    if (inputFile.is_open()) {
        string title, author, isbn;
        int year;

        while (getline(inputFile, title, ',') &&
               getline(inputFile >> ws, author, ',') &&
            (inputFile >> year, true) &&
               getline(inputFile >> ws, isbn)) {
            books[numBooks++] = Book(title, author, year, isbn);
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    // Calculate the actual number of books in the array
    numBooks = sizeof(books) / sizeof(books[0]);

    // Display menu for user to choose between sorting and searching
    int operationOption;
    cout << "<<< Library Management System >>>" << endl;
    cout << "[1] Sort Books" << endl;
    cout << "[2] Search Books" << endl;
    cout << "Option: ";
    cin >> operationOption;

    if (operationOption == 1) {
        // Display menu for sorting
        int sortingOption;
        cout << "<<< Sorting Process >>>" << endl;
        cout << "[1] By title" << endl;
        cout << "[2] By author" << endl;
        cout << "[3] By publication year" << endl;
        cout << "[4] By ISBN" << endl;
        cout << "Option: ";
        cin >> sortingOption;

        // Sort books based on user's choice
        sortBooks(books, numBooks, sortingOption);

        // Print the sorted books
        printBooks(books, numBooks);
    } else if (operationOption == 2) {
        // Display menu for searching
        int searchingOption;
        string searchKey;
        cout << "<<< Searching Process >>>" << endl;
        cout << "[1] By title" << endl;
        cout << "[2] By author" << endl;
        cout << "[3] By publication year" << endl;
        cout << "[4] By ISBN" << endl;
        cout << "Option: ";
        cin >> searchingOption;
        cout << "Enter search key: ";
        cin >> searchKey;

        // Search for a book based on user's choice
        searchBooks(books, numBooks, searchingOption, searchKey);
    } else {
        cout << "Invalid option" << endl;
    }

    return 0;
}
