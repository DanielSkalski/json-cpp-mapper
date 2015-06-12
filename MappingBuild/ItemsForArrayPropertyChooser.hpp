#ifndef ITEMSFORARRAYPROPERTYCHOOSER_H
#define ITEMSFORARRAYPROPERTYCHOOSER_H

#include "MappingPropertyKindChooser.hpp"
#include <functional>

namespace mapper {

template<class T>
class MappingPropertyKindChooser;

template<class T>
class ItemsForArrayPropertyChooser
{
    MappingPropertyKindChooser<T>* m_previousChooser;

public:
    explicit ItemsForArrayPropertyChooser(MappingPropertyKindChooser<T>* previousChooser);

    ~ItemsForArrayPropertyChooser()
    {
        std::cout << "Destructor ItemsForArrayPropertyChooser" << std::endl;
    }

    void ofStrings(function<int (const T &)>     collectionSizeFunction,
                   function<string (const T &, int)> elementAccessFunction);

    void ofBooleans(function<int (const T &)>     collectionSizeFunction,
                    function<bool (const T &, int)> elementAccessFunction);

//    void ofNumbers();
//    void ofObjects();
//    void ofArrays();
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
ItemsForArrayPropertyChooser<T>::ItemsForArrayPropertyChooser(
        MappingPropertyKindChooser<T>* previousChooser)
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

} // namespace mapper

#endif // ITEMSFORARRAYPROPERTYCHOOSER_H
