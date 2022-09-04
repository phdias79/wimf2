CPP = g++
CPP_FLIAGS = -Wall

#all:  test_dynamic_table test_catalog
all:  test_compare_string #testfast_compare_string testclang_compare_string

testclang_%: test_%.cpp
	clang++ ${CPP_FLAGS} -O3  -o testclang_$* test_$*.cpp

testfast_%: test_%.cpp
	${CPP} ${CPP_FLAGS} -O3 -march=native -o testfast_$* test_$*.cpp

test_%: test_%.cpp
	${CPP} ${CPP_FLAGS} -g -O3 -o test_$* test_$*.cpp

%.o: %.cpp
	${CPP} ${CPP_FLAGS} -c $*.cpp