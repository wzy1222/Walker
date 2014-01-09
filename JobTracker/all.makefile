

JobDaemon : JobDaemon.o network.o command.o ../my_unp.o
	g++ JobDaemon.o network.o command.o ../my_unp.o -o JobDaemon

JobDaemon.o : JobDaemon.cpp
	g++ -c JobDaemon.cpp

network.o : network.cpp
	g++ -c network.cpp 

command.o : command.cpp 
	g++ -c command.cpp

../my_unp.o : ../my_unp.c
	g++ -c ../my_unp.c
