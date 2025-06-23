CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
OBJS = main.o Lexer.o ASTNode.o Parser.o SymbolTable.o SemanticAnalyzer.o TACGenerator.o Optimizer.o utils.o

all: compiler

compiler: $(OBJS)
	$(CXX) $(CXXFLAGS) -o compiler $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o compiler 