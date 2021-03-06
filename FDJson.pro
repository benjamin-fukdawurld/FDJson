#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:57:00
#
#-------------------------------------------------
TARGET = FDJson
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore

INCLUDEPATH += include \
    ../FDCore/include \
    ../FDSerialize/include \
    ../thirdparty/rapidjson/include

SOURCES += \
    src/Json_utils.cpp \
    src/JsonSerializer.cpp

HEADERS += \
    include/FDJson/FDJson.h \
    include/FDJson/Json_fwd.h \
    include/FDJson/JsonSerializer.h \
    include/FDJson/Json_primitive_fwd.h \
    include/FDJson/Json_primitive.h \
    include/FDJson/Json_array_fwd.h \
    include/FDJson/Json_array.h \
    include/FDJson/Json_list_fwd.h \
    include/FDJson/Json_list.h \
    include/FDJson/Json_set.h \
    include/FDJson/Json_set_fwd.h \
    include/FDJson/Json_map_fwd.h \
    include/FDJson/Json_map.h \
    include/FDJson/Json_tuple.h \
    include/FDJson/Json_tuple_fwd.h \
    include/FDJson/Json.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
