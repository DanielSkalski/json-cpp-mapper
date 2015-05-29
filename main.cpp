#include <iostream>
#include <string>
#include <vector>

#include "Serializer.hpp"

using namespace std;

class Book
{
public:
    string title;
    string author;
    float something;
};

class A
{
public:
    string name;
    string title;
    int number;

    Book book;
};

class Shelf
{
public:
    string name;
    int number;
    vector<Book> books;
};


#define JSON_VALUE_FUNC(T, RET)     [](const T& x) -> string { return x.RET; }
#define JSON_VALUE_FUNC_INT(T, RET) [](const T& x) -> int    { return x.RET; }
#define JSON_VALUE_FUNC_(T, RET)    [](const T& x) -> string { return to_string(x.RET); }

int main()
{
    Book book {"Czarodziciel", "Terry Pratchett", 20.5};
    Book book2 {"Kolor magii", "Terry Pratchett", 23.5};
    Book book3 {"Miecz przeznaczenia", "Andrzej Sapkowski", 33.0f};
    A a {"nazwa", "tytuł", 2, book};
    vector<Book> books { book, book2, book3 };
    Shelf shelf {"Fantastyka", 23, books};

    Serializer<Book> bookSerializer;
    bookSerializer.map("Title", JSON_VALUE_FUNC(Book, title));
    bookSerializer.map("Author", JSON_VALUE_FUNC(Book, author));
    bookSerializer.map("Price", JSON_VALUE_FUNC_(Book, something), PropertyKind::Value);

    Serializer<A> s;
    s.map("name", JSON_VALUE_FUNC(A, name));
    s.map("title", JSON_VALUE_FUNC(A, title));
    s.map("number", JSON_VALUE_FUNC_(A, number), PropertyKind::Value);
    s.map<Book>("book", [](const A& x) -> Book { return x.book; }, bookSerializer);

    Serializer<Shelf> shelfSerializer;
    shelfSerializer.map("name", JSON_VALUE_FUNC(Shelf, name));
    shelfSerializer.map("number", JSON_VALUE_FUNC_(Shelf, number), PropertyKind::Value);
    shelfSerializer.mapArrayOf<Book>("books",
                                     [](const Shelf& x) -> int { return x.books.size(); },
                                     [](const Shelf& x, int index) -> Book { return x.books[index]; },
                                     bookSerializer);

    cout << shelfSerializer.serialize(shelf);

    return 0;
}
