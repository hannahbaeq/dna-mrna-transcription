CXX = g++
CXXFLAGS = -Wall

proj3:  Sequencer.o Strand.o proj3.cpp
        $(CXX) $(CXXFLAGS) Sequencer.o Strand.o proj3.cpp -o proj3

Sequencer.o: Strand.o Sequencer.cpp Sequencer.h
        $(CXX) $(CXXFLAGS) -c Sequencer.cpp

Strand.o: Strand.h Strand.cpp
        $(CXX) $(CXXFLAGS) -c Strand.cpp

clean:
        rm *.o*
        rm *~

val:
        valgrind ./proj3
