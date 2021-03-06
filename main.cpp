#include <iostream>
#include <string>
#include <vector>

#include "JsonSerializer.h"

using namespace std;
using namespace mapper;

class Book
{
public:
    string title;
    string author;
    float something;
    bool is_new;
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
    bool* booleans;
    int count;
};

struct StringsMultiArray
{
    string** values;
};

int main()
{
    Book book {"Czarodziciel", "Terry Pratchett", 20.5, true};
    Book book2 {"Kolor magii", "Terry Pratchett", 23.5, false};
    Book book3 {"Miecz przeznaczenia", "Andrzej Sapkowski", 33.0f, true};
    A a {"nazwa", "tytuł", 2, book};
    vector<Book> books { book, book2, book3 };
    Shelf shelf {"Fantastyka", 23, books};

    Mapping<Book> bookMapping;
    bookMapping.map("Title")->asString(MAPPER_GET_VALUE(Book, title));
    bookMapping.map("Author")->asString(MAPPER_GET_VALUE(Book, author));
    bookMapping.map("Price")->asNumber(MAPPER_GET_VALUE_FLOAT(Book, something));
    bookMapping.map("is_new")->asBoolean(MAPPER_GET_VALUE_BOOL(Book, is_new));

    auto bookSerializer = JsonSerializer<Book>(bookMapping);

    cout << bookSerializer.serialize(book);

    Mapping<A> aMapping;
    aMapping.map("name")->asString(MAPPER_GET_VALUE(A, name));
    aMapping.map("title")->asString(MAPPER_GET_VALUE(A, title));
    aMapping.map("book")->asObject<Book>(MAPPER_GET_VALUE_OBJ(A, Book, book))
                        ->mappedWith(bookMapping);
    aMapping.map("number")->asNumber(MAPPER_GET_VALUE_INT(A, number));

    auto aSerializer = JsonSerializer<A>(aMapping);

    cout << aSerializer.serialize(a);

    Mapping<Shelf> shelfMapping;
    shelfMapping.map("name")->asString(MAPPER_GET_VALUE(Shelf, name));
    shelfMapping.map("number")->asNumber(MAPPER_GET_VALUE_INT(Shelf, number));
    shelfMapping.map("books")->asArray()->ofObjects<Book>(
                                     MAPPER_ARRAY_GET_COUNT(Shelf, books.size()),
                                     MAPPER_GET_INDEXED_VALUE_OBJ(Shelf, Book, books),
                                     bookMapping);

    auto shelfSerializer = JsonSerializer<Shelf>(shelfMapping);

    cout << shelfSerializer.serialize(shelf);

    NumbersCollection numbers { "Liczby", new int[5] { 1, 3, 4, 5, 6 }, 5 };
    Mapping<NumbersCollection> numbersMapping;
    numbersMapping.map("name")->asString(MAPPER_GET_VALUE(NumbersCollection, name));
    numbersMapping.map("values")->asArray()->ofNumbers(
                                    MAPPER_ARRAY_GET_COUNT(NumbersCollection, count),
                                    MAPPER_GET_INDEXED_VALUE_INT(NumbersCollection, numbers));

    auto numbersSerializer = JsonSerializer<NumbersCollection>(numbersMapping);

    cout << numbersSerializer.serialize(numbers);

    StringsCollection strings {
        "Napisy",
        new string[3] { "Ala", "ma", "kota" },
        new bool[3] { true, false, true },
        3
    };

    Mapping<StringsCollection> stringsMapping;
    stringsMapping.map("name")->asString(MAPPER_GET_VALUE(StringsCollection, name));
    stringsMapping.map("values")->asArray()->ofStrings(
                                     MAPPER_ARRAY_GET_COUNT(StringsCollection, count),
                                     MAPPER_GET_INDEXED_VALUE(StringsCollection, values));
    stringsMapping.map("booleans")->asArray()->ofBooleans(
                                     MAPPER_ARRAY_GET_COUNT(StringsCollection, count),
                                     MAPPER_GET_INDEXED_VALUE_BOOL(StringsCollection, booleans));

    auto stringsSerializer = JsonSerializer<StringsCollection>(stringsMapping);

    cout << stringsSerializer.serialize(strings);

//    StringsMultiArray multiStrings
//    {
//        new string* [3]
//        {
//            new string[3] {"Ala", "ma", "kota"},
//            new string[3] {"Kota", "ma", "Ala"},
//            new string[3] {"Ola", "posiada", "psa"},
//        }
//    };

//    Mapping<StringsMultiArray> multiStringsMapping;
//    multiStringsMapping.mapArrayOfStringArrays("values",
//                                   [](const StringsMultiArray&) -> int { return 3; },
//                                   [](const StringsMultiArray& x, int index) -> string* { return x.values[index]; },
//                                   [](const string*) -> int { return 3; },
//                                   [](const string* x, int index) -> string { return x[index]; });


//    auto multiStringsSerializer = serializerFactory.getObjectSerializer<StringsMultiArray>(multiStringsMapping);
//    cout << multiStringsSerializer->serialize(multiStrings);

    return 0;
}
