TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    PropertyDefinition/PropertyDefinitionBase.h \
    PropertyDefinition/PropertyKind.h \
    PropertyDefinition/PropertyDefinitionFactory.hpp \
    PropertyDefinition/PropertyDefinition.hpp \
    PropertyDefinition/ObjectPropertyDefinition.hpp \
    PropertyDefinition/ArrayPropertyDefinition.hpp \
    Serializer/ISerializer.h \
    Mapping.hpp \
    Serializer/ArraySerializer.hpp \
    Serializer/ObjectSerializer.hpp \
    Serializer/StringSerializer.hpp \
    Serializer/NumberSerializer.hpp \
    PropertyDefinition/PropertyDefinitionCommon.h \
    Serializer/SerializerFactory.hpp \
    Serializer/SerializerCommon.h \
    Serializer/BooleanSerializer.hpp \
    MappingBuild/MappingBuilder.hpp \
    MappingBuild/MappingPropertyKindChooser.hpp \
    MappingBuild/MappingForObjectPropertyChooser.hpp \
    MappingBuild/ItemsForArrayPropertyChooser.hpp

