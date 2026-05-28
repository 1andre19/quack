CXX      = g++
CXXFLAGS = -std=c++17

TARGET = quack

.PHONY: all clean regenerate

all: regenerate $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp driver.cc parser.cc lex.yy.cc Scopes.cpp SemanticCube.cpp

parser.cc parser.hh: parser.yy
	bison -d -o parser.cc $

lex.yy.cc: scanner.l parser.hh
	flex -o $@ $

regenerate: parser.yy lex.yy.cc

clean:
	rm -f $(TARGET) parser.cc parser.hh location.hh lex.yy.cc
