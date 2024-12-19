module;
#include <iostream>
#include <fstream>
#include <sstream>

export module Book;

export class Book
{
private:
    std::string title;
    std::string author;
    int year;
public:
    Book() 
    {
        title = author = "";
        year = 0;
    }
    Book(std::string t, std::string a, int y) : title(t), author(a), year(y) {}
    friend std::ostream& operator<<(std::ostream& out, const Book& book) {
        out << book.title << ',' << book.author << ',' << book.year << '\n';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Book& book) {
        int y;
        std::string line;
        in.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        if (&in == &std::cin)
        {
            std::cout << "Enter title and author of the book separated by commas: ";
            if (std::getline(in, line)) {
                std::istringstream iss(line);
                std::getline(iss, book.title, ',');
                std::getline(iss, book.author);
                
            }
        }
        else if (std::getline(in, line)) {
            std::istringstream iss(line);
            std::getline(iss, book.title, ',');
            std::getline(iss, book.author, ',');
            iss >> book.year;
        }

        if (&in == &std::cin) {
            bool validInput = false; 
            do {
                std::cout << "Enter the year of the book's releaseò (0 <= year <= 2024): ";
                if (!(in >> y) || y < 0 || y > 2024)
                { 
                    in.clear();
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cout << "Input error! Please try again.\n";
                }
                else 
                    validInput = true; 
            } while (!validInput);
            book.year = y;
        }

        return in;
    }
    std::strong_ordering operator<=>(const Book& other) const
    {
        if (title < other.title) return std::strong_ordering::less;
        if (title > other.title) return std::strong_ordering::greater;

        if (author < other.author) return std::strong_ordering::less;
        if (author > other.author) return std::strong_ordering::greater;

        if (year < other.year) return std::strong_ordering::less;
        if (year > other.year) return std::strong_ordering::greater;

        return std::strong_ordering::equal;
    }
    bool operator==(Book& other);
    bool operator!=(Book& other);
    std::string get_title();
    std::string get_author();
    int get_year();
    void set_title(std::string t);
    void set_author(std::string a);
    void set_year(int y);
};

bool Book::operator==(Book& other)
{
    return title == other.title && author == other.author && year == other.year;
}

bool Book::operator!=(Book& other)
{
    return !(title == other.title && author == other.author && year == other.year);
}

std::string Book::get_title()
{
    return title;
}

std::string Book::get_author()
{
    return author;
}

int Book::get_year()
{
    return year;
}

void Book::set_title(std::string t)
{
    title = t;
}

void Book::set_author(std::string a)
{
    author = a;
}

void Book::set_year(int y)
{
    year = y;
}
