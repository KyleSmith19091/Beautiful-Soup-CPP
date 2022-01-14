SRC_FILES := $(wildcard src/*.cpp)
SRC_FILES := $(filter-out src/main.cpp, $(SRC_FILES))

run:
	g++ \
	 -I /Users/kylesmith/Development/Libraries/c++/tree-sitter/lib/include            \
	 -I ./include \
	/Users/kylesmith/Development/Libraries/c++/tree-sitter-html/src/parser.c         \
	/Users/kylesmith/Development/Libraries/c++/tree-sitter-html/src/scanner.cc         \
	/Users/kylesmith/Development/Libraries/c++/tree-sitter/libtree-sitter.a          \
	-lcurl \
	./src/*.cpp                    \
	-std=c++11\
  	-o ./build/main \
	-Wall 
	./build/main

gtest:
	g++ \
	 -I /Users/kylesmith/Development/Libraries/c++/tree-sitter/lib/include            \
	 -I ./include \
	/Users/kylesmith/Development/Libraries/c++/tree-sitter-html/src/parser.c         \
	/Users/kylesmith/Development/Libraries/c++/tree-sitter-html/src/scanner.cc         \
	/Users/kylesmith/Development/Libraries/c++/tree-sitter/libtree-sitter.a          \
	-lcurl \
	-lgtest \
	$(SRC_FILES) \
	./test/Test.cpp \
	-std=c++11\
  	-o ./build/test \
	-Wall 
	./build/test
