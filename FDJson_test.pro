TARGET = FDJson_test

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = build/bin
MAKEFILE = build/makefiles/$${TARGET}
OBJECTS_DIR = build/.obj/$${TARGET}

LIBS += \
    -pthread \
    -Lbuild/lib -lFDJson \
    -L../thirdparty/googletest/build/lib -lgtest

DEPENDPATH += \
    ../FDSerialize/include \
    ../FDJson/include \
    ../thirdparty/rapidjson/include \
    ../thirdparty/googletest/googletest/include \

INCLUDEPATH += \
    ../FDSerialize/include \
    ../FDJson/include \
    ../thirdparty/rapidjson/include \
    ../thirdparty/googletest/googletest/include \

SOURCES += \
    test/main.cpp

HEADERS += \
    test/test_custom.h \
    test/test_primitive.h \
    test/test_array.h \
    test/test_list.h \
    test/test_tuple.h \
    test/test_set.h \
    test/test_map.h
