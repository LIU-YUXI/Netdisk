CC = g++
dependentCPP = $(wildcard *.cpp)
target = main

$(target): $(dependentCPP) Database.h
	$(CC) $(dependentCPP) -Wall -o $@ -I/usr/include/mysql -lmysqlclient

clean:
	rm -rf $(target)