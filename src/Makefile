CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp driver.cc parser.cc lex.yy.cc Scopes.cpp SemanticCube.cpp \
       FunctionDirectory.cpp ast.cpp astVisitor.cpp

# Generated files
GENERATED = parser.cc parser.hh lex.yy.cc

quack: $(SRCS)
	$(CXX) $(CXXFLAGS) -o quack $(SRCS)

# Bison rule: parser.yy → parser.cc + parser.hh
parser.cc parser.hh: parser.yy
	bison -d -o parser.cc parser.yy

# Flex rule: scanner.l → lex.yy.cc
# Depends on parser.hh so tokens are defined before scanning
lex.yy.cc: scanner.l parser.hh
	flex -o lex.yy.cc scanner.l

clean:
	rm -f quack $(GENERATED)
