progname=programm
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++20 -g3

TEST_INPUTS:=$(wildcard test*.input)
TESTS:=$(patsubst %.input,%,$(TEST_INPUTS))

SOURCES:=$(wildcard *.cpp)
PREPROCS:=$(patsubst %.cpp,%.ii,$(SOURCES))
ASSEMBLES:=$(patsubst %.cpp,%.s,$(SOURCES))
OBJS:=$(patsubst %.cpp,%.o,$(SOURCES))

qa: $(TESTS)

test%: $(progname)
	 ./$< < $@.input > $@.output
	 diff $@.output $@.expected && echo PASSED || echo FAILED
  
$(progname): $(OBJS) | .gitignore
	 $(CXX) $(CXXFLAGS) $^ -o $@

%.ii: %.cpp
	 $(CXX) $(CXXFLAGS) -E $< -o $@

%.s: %.ii
	 $(CXX) $(CXXFLAGS) -S $< -o $@

%.o: %.s
	 $(CXX) $(CXXFLAGS) -c $< -o $@

.gitignore:
	 echo $(progname) > $@
 
clean:
	 rm -rf *.ii *.s *.o *.output $(progname) .gitignore

.PRECIOUS: $(PREPROCS) $(ASSEMBLES)
.SECONDARY: $(PREPROCS) $(ASSEMBLES)
