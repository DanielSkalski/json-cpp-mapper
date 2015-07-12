#ifndef ITEMSFORARRAYPROPERTYCHOOSER_H
#define ITEMSFORARRAYPROPERTYCHOOSER_H

#include "PropertyKindChooser.hpp"
#include <functional>

namespace mapper {

template<class T>
class PropertyKindChooser;

template<class T>
class ItemsForArrayPropertyChooser
{
    PropertyKindChooser<T>* m_previousChooser;

public:
    explicit ItemsForArrayPropertyChooser(PropertyKindChooser<T>* previousChooser);

    ~ItemsForArrayPropertyChooser()
    {
        std::cout << "Destructor ItemsForArrayPropertyChooser" << std::endl;
    }

    void ofStrings(function<int (const T &)>     collectionSizeFunction,
                   function<string (const T &, int)> elementAccessFunction);

    void ofBooleans(function<int (const T &)>     collectionSizeFunction,
                    function<bool (const T &, int)> elementAccessFunction);

    void ofNumbers(function<int (const T &)>     collectionSizeFunction,
                   function<int (const T &, int)> elementAccessFunction);

    void ofNumbers(function<int (const T &)>     collectionSizeFunction,
                   function<float (const T &, int)> elementAccessFunction);

    template<class ELEM_T>
    void ofObjects(function<int (const T &)>     collectionSizeFunction,
                   function<ELEM_T (const T &, int)> elementAccessFunction,
                   Mapping<ELEM_T> mapping);
//    void ofArrays();
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
ItemsForArrayPropertyChooser<T>::ItemsForArrayPropertyChooser(
        PropertyKindChooser<T>* previousChooser)
    : m_previousChooser(previousChooser)
{

}

// ----- METHODS --------------------------------------------------------------

template<class T>
void ItemsForArrayPropertyChooser<T>::ofStrings(function<int (const T &)>     collectionSizeFunction,
                                                function<string (const T &, int)> elementAccessFunction)
{
    m_previousChooser->mapAsArrayOf(collectionSizeFunction, elementAccessFunction);
    delete this;
}

template<class T>
void ItemsForArrayPropertyChooser<T>::ofBooleans(function<int (const T &)>     collectionSizeFunction,
                                                function<bool (const T &, int)> elementAccessFunction)
{
    m_previousChooser->mapAsArrayOf(collectionSizeFunction, elementAccessFunction);
    delete this;
}

template<class T>
void ItemsForArrayPropertyChooser<T>::ofNumbers(function<int (const T &)>     collectionSizeFunction,
                                                function<int (const T &, int)> elementAccessFunction)
{
    m_previousChooser->mapAsArrayOf(collectionSizeFunction, elementAccessFunction);
    delete this;
}

template<class T>
void ItemsForArrayPropertyChooser<T>::ofNumbers(function<int (const T &)>     collectionSizeFunction,
                                                function<float (const T &, int)> elementAccessFunction)
{
    m_previousChooser->mapAsArrayOf(collectionSizeFunction, elementAccessFunction);
    delete this;
}

template<class T>
template<class ELEM_T>
void ItemsForArrayPropertyChooser<T>::ofObjects(function<int (const T &)>     collectionSizeFunction,
                                                function<ELEM_T (const T &, int)> elementAccessFunction,
                                                Mapping<ELEM_T> mapping)
{
    m_previousChooser->mapAsArrayOf(collectionSizeFunction, elementAccessFunction, mapping);
    delete this;
}

} // namespace mapper

#endif // ITEMSFORARRAYPROPERTYCHOOSER_H
