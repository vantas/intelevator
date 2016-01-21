CPP=clang++
CXXFLAGS=-Wall -Werror -Wpedantic

all: intelevator

intelevator: main.o event.o client.o elevator.o eventtype.o floor.o
	$(CPP) $^ -o $@

main.o: main.cpp
	$(CPP) $(CXXFLAGS) -c main.cpp

client.o: client.cpp client.h
	$(CPP) $(CXXFLAGS) -c client.cpp

elevator.o: elevator.cpp elevator.h
	$(CPP) $(CXXFLAGS) -c elevator.cpp

event.o: event.cpp event.h
	$(CPP) $(CXXFLAGS) -c event.cpp

eventtype.o: eventtype.cpp eventtype.h
	$(CPP) $(CXXFLAGS) -c eventtype.cpp

floor.o: floor.cpp floor.h
	$(CPP) $(CXXFLAGS) -c floor.cpp

clean:
	rm -rf ./*.o intelevator
