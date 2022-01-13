PROG := ctest

all: $(PROG)

ctest: ctest.cpp
	$(CXX) -Wall -Wextra -o $@ $<
	
.PHONY: clean	
clean:
	rm -rf $(PROG) temp.dat
