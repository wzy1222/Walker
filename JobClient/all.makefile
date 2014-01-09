worker : worker.o networkClient.o ../my_unp.o
	g++ worker.o networkClient.o ../my_unp.o -o worker


