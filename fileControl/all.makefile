test : test.o ../my_unp.o fileControl.o
	g++ test.o ../my_unp.o fileControl.o -o test

fileControl.o : fileControl.cpp
	g++ -c fileControl.cpp


