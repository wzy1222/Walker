obj = worker.o networkClient.o ../Common/my_unp.o ../Common/mylog.o ../Common/yaolog.o ../NetTransfer/NetTransfer.o
worker : $(obj)
	g++ $(obj) -lpthread -o worker


