CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp driver.cc parser.cc lex.yy.cc Scopes.cpp SemanticCube.cpp \
       FunctionDirectory.cpp ast.cpp astVisitor.cpp

quack: $(SRCS)
	$(CXX) $(CXXFLAGS) -o quack $(SRCS)

clean:
	rm -f quack
