first: all

CXX = g++
CXXFLAGS = -g -Wall
INCPATH = -Iinclude/
TARGET  = libVtLib.a
OUT_DIR = .obj
OBJECTS = .obj/vpoint.o     \
	  .obj/vsize.o      \
	  .obj/vbytearray.o \
	  .obj/vline.o      \
	  .obj/vdatetime.o  \
	  .obj/vglobal.o    \
	  .obj/viodevice.o  \
	  .obj/vbuffer.o    \
	  .obj/vchar.o      \
	  .obj/vstring.o
SOURCES = src/vbytearray.cpp   \
	  src/vdatetime.cpp    \
	  src/vglobal.cpp      \
	  src/viterator.cpp    \
	  src/vline.cpp        \
	  src/vlinkedlist.cpp  \
	  src/vpair.cpp        \
	  src/vpoint.cpp       \
	  src/vsize.cpp        \
	  src/vstack.cpp       \
	  src/vlist.cpp        \
	  src/viodevice.cpp    \
	  src/vbuffer.cpp      \
	  src/vchar.cpp        \
	  src/vstring.cpp
HEADERS = include/valgorithms.h  \
	  include/vdatetime.h    \
	  include/viterator.h    \
	  include/vlinkedlist.h  \
	  include/vpair.h        \
	  include/vqueue.h       \
	  include/vstack.h       \
	  include/vbytearray.h   \
	  include/vglobal.h      \
	  include/vline.h        \
      	  include/vlist.h        \
   	  include/vpoint.h       \
	  include/vsize.h        \
	  include/vvector.h      \
	  include/viodevice.h    \
	  include/vbuffer.h      \
	  include/vchar.h        \
	  include/vstring.h

all: $(OBJECTS) $(SOURCES) $(HEADERS) $(TARGET)

$(TARGET): $(OBJECTS) $(SOURCES) $(HEADERS)
	ar cr libVtLib.a $(OBJECTS)

$(OUT_DIR)/vpoint.o: src/vpoint.cpp include/vpoint.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vpoint.cpp -o $(OUT_DIR)/vpoint.o

$(OUT_DIR)/vsize.o: src/vsize.cpp include/vsize.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vsize.cpp -o $(OUT_DIR)/vsize.o

$(OUT_DIR)/vbytearray.o: src/vbytearray.cpp include/vbytearray.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vbytearray.cpp -o $(OUT_DIR)/vbytearray.o

$(OUT_DIR)/vline.o: src/vline.cpp include/vline.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vline.cpp -o $(OUT_DIR)/vline.o

$(OUT_DIR)/vdatetime.o: src/vdatetime.cpp include/vdatetime.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vdatetime.cpp -o $(OUT_DIR)/vdatetime.o

$(OUT_DIR)/vglobal.o: src/vglobal.cpp include/vglobal.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vglobal.cpp -o $(OUT_DIR)/vglobal.o

$(OUT_DIR)/viodevice.o: src/viodevice.cpp include/viodevice.h include/private/viodevice_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/viodevice.cpp -o $(OUT_DIR)/viodevice.o

$(OUT_DIR)/vbuffer.o: src/vbuffer.cpp include/vbuffer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vbuffer.cpp -o $(OUT_DIR)/vbuffer.o

$(OUT_DIR)/vchar.o: src/vchar.cpp src/vunicodetables.cpp include/vchar.h include/private/vunicodetables_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vchar.cpp -o $(OUT_DIR)/vchar.o

$(OUT_DIR)/vstring.o: src/vstring.cpp include/vstring.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) src/vstring.cpp -o $(OUT_DIR)/vstring.o

test: $(TARGET) main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(TARGET) $(INCPATH) -o test

doc: Doxyfile $(HEADERS) $(SOURCES) html
	doxygen Doxyfile

html:

clean:
	rm $(OBJECTS) 

