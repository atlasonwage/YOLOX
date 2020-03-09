# By default, the makefile is for debugging.
# The Makefile_Release will have the release build.
CXX=clang++
CXXFLAGS=-Wall -g -fno-omit-frame-pointer -fsanitize=address,leak

.PHONY: clean
clean:
	-rm -f *.o *~ a.out