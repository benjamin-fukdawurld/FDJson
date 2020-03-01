TARGET_NAME := FDJson

LLVM_BIN_PATH ?= ../thirdparty/llvm/build/bin

CC = $(LLVM_BIN_PATH)/clang
CXX = $(LLVM_BIN_PATH)/clang++
LINK_LIB = $(LLVM_BIN_PATH)/llvm-ar

include ../FDMakeUtils/utils.mk

#################################################################

# PROJECT CONFIG

#################################################################

PROJECT_CFLAGS := $(DEFAULT_CFLAGS)
PROJECT_CXXFLAGS := $(DEFAULT_CXXFLAGS) -fpic
PROJECT_LDFLAGS := $(DEFAULT_LDFLAGS) -pthread
PROJECT_DEFINES := $(DEFAULT_DEFINES)
PROJECT_INCLUDEPATH := $(DEFAULT_INCLUDEPATH)-I../thirdparty/rapidjson/include -I../FDSerialize/include -I../FDJson/include
PROJECT_LIBPATH := $(DEFAULT_LIBPATH)
PROJECT_LIBS := $(DEFAULT_LIBS)
PROJECT_WARNINGS := $(DEFAULT_WARNINGS)

CXX_COMPILE = $(CXX) -c $(CXXFLAGS) $(DEFINES) $(INCLUDEPATH)
CXX_LINK = $(CXX) $(LDFLAGS)
CXX_LINK_LIB = $(LINK_LIB) $(LDFLAGS)
#################################################################

# OUTPUT CONFIG

#################################################################

PWD = $(shell pwd)
BUILD_DIR = $(PWD)/../build/$(TARGET_NAME)
LIB_DIR = $(BUILD_DIR)/lib
OBJECTS_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
TEST_OBJECTS_DIR = $(BUILD_DIR)/obj/test

TEST_CXXFLAGS := -I../thirdparty/googletest/googletest/include -I.
TEST_LDFLAGS := $(LIB_DIR)/libFDJson.a ../thirdparty/googletest/build/lib/libgtest.a

$(TARGET_NAME): $(LIB_DIR)/lib$(TARGET_NAME).a

$(LIB_DIR)/lib$(TARGET_NAME).a: lib_dir $(OBJECTS_DIR)/Json_utils.o
	$(CXX_LINK_LIB) rc $(LIB_DIR)/lib$(TARGET_NAME).a $(OBJECTS_DIR)/Json_utils.o

$(OBJECTS_DIR)/Json_utils.o: obj_dir src/Json_utils.cpp $(LIB_DIR)/lib$(TARGET_NAME).a
	$(CXX_COMPILE) -o $(OBJECTS_DIR)/Json_utils.o src/Json_utils.cpp

tests: bin_dir $(OBJECTS_DIR)/test_main.o
	$(CXX_LINK) -o $(BIN_DIR)/FDJson_test $(OBJECTS_DIR)/test_main.o $(TEST_LDFLAGS)

$(OBJECTS_DIR)/test_main.o: test_obj_dir test/main.cpp
	$(CXX_COMPILE) $(TEST_CXXFLAGS) -o $(OBJECTS_DIR)/test_main.o test/main.cpp