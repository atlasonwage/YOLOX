# By default, the makefile is for debugging.
# The Makefile_Release will have the release build.
CXX=clang++
CXXFLAGS=-Wall -g -fno-omit-frame-pointer -fsanitize=address,leak

test.out: main.o testCases.o
	$(CXX) $(CXXFLAGS) main.o testCases.o

.PHONY: clean
clean:
	-rm -f *.o *~ a.out

main.o: main.cpp testCases.h
testCases.o: testCases.cpp testCases.h ASTDummy.h \
  ../ASTGenerator/ASTNode.h ../ASTGenerator/GeneralTools.h \
  ../ASTGenerator/ASTBlock.h
