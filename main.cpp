#include <iostream>
#include <string>
#include <vector>

#include "Mapping.hpp"
#include "Serializer/ObjectSerializer.hpp"


using namespace std;
using namespace mapper;

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

class NumbersCollection
{
public:
    string name;
    int* numbers;
    int count;
};

class StringsCollection
{
public:
    string name;
    string* values;
    int count;
};

struct StringsMultiArray
{
    string** values;
};

#define JSON_VALUE_FUNC(T, RET)     [](const T& x) -> string { return x.RET; }
#define JSON_VALUE_FUNC_INT(T, RET) [](const T& x) -> int    { return x.RET; }
#define JSON_VALUE_FUNC_FLOAT(T, RET) [](const T& x) -> float    { return x.RET; }

#define JSON_VALUE_FUNC_(T, RET)    [](const T& x) -> string { return to_string(x.RET); }


int main()
{
    SerializerFactory serializerFactory;

    Book book {"Czarodziciel", "Terry Pratchett", 20.5};
    Book book2 {"Kolor magii", "Terry Pratchett", 23.5};
    Book book3 {"Miecz przeznaczenia", "Andrzej Sapkowski", 33.0f};
    A a {"nazwa", "tytuł", 2, book};
    vector<Book> books { book, book2, book3 };
    Shelf shelf {"Fantastyka", 23, books};

    Mapping<Book> bookMapping;
    bookMapping.map("Title", JSON_VALUE_FUNC(Book, title));
    bookMapping.map("Author", JSON_VALUE_FUNC(Book, author));
    bookMapping.map<float>("Price", JSON_VALUE_FUNC_FLOAT(Book, something));

    auto bookSerializer = serializerFactory.getObjectSerializer<Book>(bookMapping);

    cout << bookSerializer->serialize(book);

    Mapping<A> aMapping;
    aMapping.map("name", JSON_VALUE_FUNC(A, name));
    aMapping.map("title", JSON_VALUE_FUNC(A, title));
    aMapping.map<int>("number", JSON_VALUE_FUNC_INT(A, number));
    aMapping.map<Book>("book", [](const A& x) -> Book { return x.book; }, bookMapping);

    auto aSerializer = serializerFactory.getObjectSerializer<A>(aMapping);

    cout << aSerializer->serialize(a);

    Mapping<Shelf> shelfMapping;
    shelfMapping.map("name", JSON_VALUE_FUNC(Shelf, name));
    shelfMapping.map<int>("number", JSON_VALUE_FUNC_INT(Shelf, number));
    shelfMapping.mapArrayOf<Book>("books",
                                     [](const Shelf& x) -> int { return x.books.size(); },
                                     [](const Shelf& x, int index) -> Book { return x.books[index]; },
                                     bookMapping);

    auto shelfSerializer = serializerFactory.getObjectSerializer<Shelf>(shelfMapping);

    cout << shelfSerializer->serialize(shelf);

    NumbersCollection numbers { "Liczby", new int[5] { 1, 3, 4, 5, 6 }, 5 };
    Mapping<NumbersCollection> numbersMapping;
    numbersMapping.map("name", JSON_VALUE_FUNC(NumbersCollection, name));
    numbersMapping.mapArrayOfNumbers<int>
                                   ("values",
                                    [](const NumbersCollection& x) -> int { return x.count; },
                                    [](const NumbersCollection& x, int index) -> int { return x.numbers[index]; });

    auto numbersSerializer = serializerFactory.getObjectSerializer<NumbersCollection>(numbersMapping);

    cout << numbersSerializer->serialize(numbers);

    StringsCollection strings { "Napisy", new string[3] { "Ala", "ma", "kota" }, 3 };
    Mapping<StringsCollection> stringsMapping;
    stringsMapping.map("name", JSON_VALUE_FUNC(StringsCollection, name));
    stringsMapping.mapArrayOfStrings("values",
                                     [](const StringsCollection& x) -> int { return x.count; },
                                     [](const StringsCollection& x, int index) -> string { return x.values[index]; });

    auto stringsSerializer = serializerFactory.getObjectSerializer<StringsCollection>(stringsMapping);

    cout << stringsSerializer->serialize(strings);


    StringsMultiArray multiStrings
    {
        new string* [3]
        {
            new string[3] {"Ala", "ma", "kota"},
            new string[3] {"Kota", "ma", "Ala"},
            new string[3] {"Ola", "posiada", "psa"},
        }
    };

    Mapping<StringsMultiArray> multiStringsMapping;
    multiStringsMapping.mapArrayOfStringArrays("values",
                                   [](const StringsMultiArray&) -> int { return 3; },
                                   [](const StringsMultiArray& x, int index) -> string* { return x.values[index]; },
                                   [](const string*) -> int { return 3; },
                                   [](const string* x, int index) -> string { return x[index]; });


    auto multiStringsSerializer = serializerFactory.getObjectSerializer<StringsMultiArray>(multiStringsMapping);
    cout << multiStringsSerializer->serialize(multiStrings);

    return 0;
}
