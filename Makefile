CXX=g++
CCLINK=$(CXX) 
CXXFLAGS=-g -Wall -std=c++11
OBJS= main.o libfirewall.so libinput.so ip.o field.o port.o string.o
EXEC=firewall.exe
RM=rm -rf

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

libfirewall.so: string.o port.o ip.o field.o 
	$(CCLINK) $(CXXFLAGS) -shared string.o port.o ip.o field.o -o libfirewall.so

main.o: main.cpp input.h string.h port.h field.h ip.h
	$(CCLINK) $(CXXFLAGS) -c main.cpp

ip.o: ip.h ip.cpp field.h
	$(CCLINK) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.h port.cpp field.h string.h
	$(CCLINK) $(CXXFLAGS) -c -fpic port.cpp

string.o: string.h string.cpp
	$(CCLINK) $(CXXFLAGS) -c -fpic string.cpp

field.o: field.h field.cpp ip.h port.h
	$(CCLINK) $(CXXFLAGS) -c -fpic field.cpp

clean:
	$(RM) *.o *.exe 