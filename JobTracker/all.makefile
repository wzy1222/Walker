obj = JobDaemon.o  network.o command.o ../Common/my_unp.o ../NetTransfer/NetTransfer.o ../Common/mylog.o ../Common/yaolog.o

JobDaemon : $(obj)
	g++ $(obj) -lpthread -o JobDaemon

JobDaemon.o : JobDaemon.cpp
	g++ -c JobDaemon.cpp

network.o : network.cpp
	g++ -c network.cpp 

command.o : command.cpp 
	g++ -c command.cpp

../my_unp.o : ../my_unp.c
	g++ -c ../my_unp.c
