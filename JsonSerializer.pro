TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    Serializer/SerializerFactory.cpp

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
    Serializer/SerializerFactory.h \
    Serializer/StringSerializer.hpp \
    Serializer/ValueSerializer.hpp

