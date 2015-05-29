#include <iostream>
#include <string>

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


#define JSON_VALUE_FUNC(T, RET)     [](const T& x) -> string { return x.RET; }
#define JSON_VALUE_FUNC_INT(T, RET) [](const T& x) -> int    { return x.RET; }
#define JSON_VALUE_FUNC_(T, RET)    [](const T& x) -> string { return to_string(x.RET); }

int main()
{
    Book book {"Czarodziciel", "Terry Pratchett", 20.5};
    A a {"nazwa", "tytuł", 2, book};

    Serializer<Book> bookSerializer;
    bookSerializer.map("Title", JSON_VALUE_FUNC(Book, title));
    bookSerializer.map("Author", JSON_VALUE_FUNC(Book, author));
    bookSerializer.map("Price", JSON_VALUE_FUNC_(Book, something), PropertyKind::Value);

    Serializer<A> s;
    s.map("name", JSON_VALUE_FUNC(A, name));
    s.map("title", JSON_VALUE_FUNC(A, title));
    s.map("number", JSON_VALUE_FUNC_(A, number), PropertyKind::Value);
    s.map<Book>("book", [](const A& x) -> Book { return x.book; }, bookSerializer);

    cout << s.serialize(a);

    return 0;
}
