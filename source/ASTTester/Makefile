# By default, the makefile is for debugging.
# The Makefile_Release will have the release build.
CXX=clang++
CXXFLAGS=-Wall -g -fno-omit-frame-pointer -fsanitize=address,leak --include-directory="../ASTGenerator"

AST_OBJECTS=../ASTGenerator/ASTBlock.o ../ASTGenerator/ASTBoolExpr.o ../ASTGenerator/ASTBoolVar.o \
	../ASTGenerator/ASTConditional.o ../ASTGenerator/ASTLoop.o ../ASTGenerator/ASTNode.o \
	../ASTGenerator/ASTOp.o ../ASTGenerator/ASTSubCall.o ../ASTGenerator/ASTVar.o \
	../ASTGenerator/GeneralTools.o ../ASTGenerator/SubroutineManager.o ../ASTGenerator/TypeService.o \
	../ASTGenerator/VarReferencer.o

test.out: main.o testCases.o
	$(CXX) $(CXXFLAGS) main.o testCases.o $(AST_OBJECTS)

.PHONY: clean
clean:
	-rm -f *.o *~ a.out

main.o: main.cpp testCases.h
testCases.o: testCases.cpp testCases.h ASTDummy.h \
  ../ASTGenerator/ASTNode.h ../ASTGenerator/GeneralTools.h \
  ../ASTGenerator/ASTBlock.h
