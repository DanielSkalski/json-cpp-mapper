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
    Serializer.hpp \
    PropertyDefinition/ArrayPropertyDefinition.hpp

