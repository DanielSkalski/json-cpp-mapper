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

#define MAPPER_GET_VALUE(T, RET)      [](const T& x) -> string  { return x.RET; }
#define MAPPER_GET_VALUE_BOOL(T, RET) [](const T& x) -> bool    { return x.RET; }
#define MAPPER_GET_VALUE_INT(T, RET)  (function<int (const T&)>)  ([](const T& x) -> int    { return x.RET; })
#define MAPPER_GET_VALUE_FLOAT(T, RET)(function<float (const T&)>)([](const T& x) -> float    { return x.RET; })
#define MAPPER_GET_VALUE_(T, RET)     [](const T& x) -> string  { return to_string(x.RET); }

#define MAPPER_ARRAY_GET_COUNT(T, RET)[](const T& x) -> int { return x.RET; }



int main()
{
    SerializerFactory serializerFactory;

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

    auto bookSerializer = serializerFactory.getObjectSerializer<Book>(bookMapping);

    cout << bookSerializer->serialize(book);

    Mapping<A> aMapping;
    aMapping.map("name")->asString(MAPPER_GET_VALUE(A, name));
    aMapping.map("title")->asString(MAPPER_GET_VALUE(A, title));
    aMapping.map("number")->asNumber(MAPPER_GET_VALUE_INT(A, number));
    aMapping.map("book")->asObject<Book>([](const A& x) -> Book { return x.book; })
                        ->mappedWith(bookMapping);

    auto aSerializer = serializerFactory.getObjectSerializer<A>(aMapping);

    cout << aSerializer->serialize(a);

    Mapping<Shelf> shelfMapping;
    shelfMapping.map("name", MAPPER_GET_VALUE(Shelf, name));
//    shelfMapping.map<int>("number", MAPPER_GET_VALUE_INT(Shelf, number));
//    shelfMapping.mapArrayOf<Book>("books",
//                                     [](const Shelf& x) -> int { return x.books.size(); },
//                                     [](const Shelf& x, int index) -> Book { return x.books[index]; },
//                                     bookMapping);

    auto shelfSerializer = serializerFactory.getObjectSerializer<Shelf>(shelfMapping);

    cout << shelfSerializer->serialize(shelf);

    NumbersCollection numbers { "Liczby", new int[5] { 1, 3, 4, 5, 6 }, 5 };
    Mapping<NumbersCollection> numbersMapping;
    numbersMapping.map("name")->asString(MAPPER_GET_VALUE(NumbersCollection, name));
    numbersMapping.map("values")->asArray()->ofNumbers(
                                    [](const NumbersCollection& x) -> int { return x.count; },
                                    (function<int (const NumbersCollection&, int)>)
                                    [](const NumbersCollection& x, int index) -> int { return x.numbers[index]; });

    auto numbersSerializer = serializerFactory.getObjectSerializer<NumbersCollection>(numbersMapping);

    cout << numbersSerializer->serialize(numbers);

    StringsCollection strings {
        "Napisy",
        new string[3] { "Ala", "ma", "kota" },
        new bool[3] { true, false, true },
        3
    };

    Mapping<StringsCollection> stringsMapping;
    stringsMapping.map("name")->asString(MAPPER_GET_VALUE(StringsCollection, name));
    stringsMapping.map("values")->asArray()->ofStrings(
                                     [](const StringsCollection& x) -> int { return x.count; },
                                     [](const StringsCollection& x, int index) -> string { return x.values[index]; });
    stringsMapping.map("booleans")->asArray()->ofBooleans(
                                     [](const StringsCollection& x) -> int { return x.count; },
                                     [](const StringsCollection& x, int index) -> bool { return x.booleans[index]; });

    auto stringsSerializer = serializerFactory.getObjectSerializer<StringsCollection>(stringsMapping);

    cout << stringsSerializer->serialize(strings);


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
