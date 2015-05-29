#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <sstream>

using namespace std;

template<class T>
class Serializer;

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


enum class PropertyKind
{
    String,
    Value,
    Array,
    Object
};

template<class T>
class PropertyDefinition
{
public:
    string propertyName;
    function<string (const T&)> mapping;
    PropertyKind propertyKind;

    virtual string serializeValue(const T& obj) const
    {
        stringstream out;

        if (propertyKind == PropertyKind::String)
        {
            out << "\"" << mapping(obj) << "\"";
        }
        else if (propertyKind == PropertyKind::Value)
        {
            out << mapping(obj);
        }
        else if (propertyKind == PropertyKind::Object)
        {
            out << "tutaj lol";
        }

        return out.str();
    }

    virtual ~PropertyDefinition() { }
};

template<class T, class OT>
class ObjectPropertyDefinition : public PropertyDefinition<T>
{
public:

    Serializer<OT> serializer;
    function<OT (const T&)> mappingObject;

    virtual string serializeValue(const T &obj) const override
    {
        stringstream out;

        OT value = mappingObject(obj);

        string serializedValue = serializer.serialize(value);

        if (serializedValue.empty())
        {
            serializedValue = "null";
        }

        out << serializedValue;

        return out.str();
    }

    virtual ~ObjectPropertyDefinition() { }
};

template<class T>
class PropertyDefinitionFactory
{
public:
    PropertyDefinition<T>* createPropertyDefinition(string propertyName,
                                                   function<string (const T&)> valueFunction,
                                                   PropertyKind propertyKind = PropertyKind::String) const
    {
        PropertyDefinition<T>* propertyDefinition = new PropertyDefinition<T>;
        propertyDefinition->propertyName = propertyName;
        propertyDefinition->mapping = valueFunction;
        propertyDefinition->propertyKind = propertyKind;

        return propertyDefinition;
    }

    template<class IT>
    PropertyDefinition<T>* createPropertyDefinition(string propertyName,
                                                   function<IT (const T&)> valueFunction,
                                                   const Serializer<IT>& objectSerializer) const
    {
        ObjectPropertyDefinition<T, IT>* propertyDefinition = new ObjectPropertyDefinition<T, IT>;
        propertyDefinition->propertyName = propertyName;
        propertyDefinition->mappingObject = valueFunction;
        propertyDefinition->propertyKind = PropertyKind::Object;
        propertyDefinition->serializer = objectSerializer;

        return propertyDefinition;
    }
};

template<class T>
class Serializer
{
    list< PropertyDefinition<T>* > m_properties;
    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;

public:

    void map(const string& propertyName,
             function<string (const T&)> valueFunction,
             PropertyKind propertyKind = PropertyKind::String)
    {
        auto propertyDefinition = m_propertyDefinitionFactory
                                    .createPropertyDefinition(propertyName, valueFunction, propertyKind);

        m_properties.push_back(propertyDefinition);
    }

    template<class IT>
    void map(const string &propertyName,
             function<IT (const T &)> valueFunction,
             const Serializer<IT>& objectSerializer)
    {
        auto propertyDefinition = m_propertyDefinitionFactory
                                    .createPropertyDefinition(propertyName, valueFunction, objectSerializer);

        m_properties.push_back(propertyDefinition);
    }

    string serialize(const T& obj) const
    {
        stringstream out;

        out << "{" << endl;

        for (PropertyDefinition<T>* prop : m_properties)
        {
            string value = prop->serializeValue(obj);

            out << "\"" << prop->propertyName << "\" : " << value << "," << endl;
        }

        // Remove last ',' sign.
        if (m_properties.size() > 0)
        {
            out.seekp(-2, out.cur);
        }

        out << endl << "}" << endl;

        return out.str();
    }

    virtual ~Serializer()
    {
        for (PropertyDefinition<T>* prop : m_properties)
        {
            delete prop;
        }
    }
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
    bookSerializer.map("Something", JSON_VALUE_FUNC_(Book, something), PropertyKind::Value);

    Serializer<A> s;
    s.map("name", JSON_VALUE_FUNC(A, name));
    s.map("title", JSON_VALUE_FUNC(A, title));
    s.map("number", JSON_VALUE_FUNC_(A, number), PropertyKind::Value);
    s.map<Book>("book", [](const A& x) -> Book { return x.book; }, bookSerializer);

    cout << s.serialize(a);

    return 0;
}
