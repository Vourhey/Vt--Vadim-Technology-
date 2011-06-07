TARGET  = mixexec
CXX     = g++ -g
INCPATH = -I../../../include/ -Iinclude/
LIB     = ../../../libVtLib.a

$(TARGET): main.cpp
	$(CXX) $(INCPATH) main.cpp $(LIB) -o $(TARGET)

clean:
	rm *.o
