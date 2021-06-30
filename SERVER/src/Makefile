CC = g++
dependentCPP = $(wildcard *.cpp)
target = server

$(target): $(dependentCPP) ../include/Database.h ../include/Communication.h ../include/crud.h ../include/readfile.h ../include/server.h 
	$(CC) $(dependentCPP) -Wall -o $@ -I/usr/include/mysql -lmysqlclient

clean:
	rm -rf $(target)