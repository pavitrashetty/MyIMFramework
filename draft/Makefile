#Native Graphics Engine library

CC = g++
CFLAGS= -fPIC -g -c -Wall -std=c++0x
HEADERS= base.hpp frame_manager.hpp  multi_frame_manager.hpp transformer.hpp movement.hpp utils.hpp frame_transformer.hpp mynge.hpp
CFILES= utils.cpp frame_manager.cpp transformer.cpp movement.cpp multi_frame_manager.cpp frame_transformer.cpp
OBJECTS= utils.o frame_manager.o transformer.o movement.o multi_frame_manager.o frame_transformer.o
MAGICKFLAGS= -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16
INCLUDEDIR= /usr/local/include/ImageMagick-6
MYNGELIB= libmynge.so


all: end_user
	@echo SIMPLE NOTE: please set LD_LIBRARY_PATH to current directory
#This because GCC fails to find libmynge.so, not sure why

end_user: $(MYNGELIB)
	$(CC) -w $(MAGICKFLAGS) -I $(INCLUDEDIR) test2.cpp -L. -lmynge `Magick++-config --cppflags --cxxflags --ldflags --libs`

$(MYNGELIB): $(OBJECTS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ -lc

%.o: %.cpp
	$(CC) $(CFLAGS) $(MAGICKFLAGS) -I $(INCLUDEDIR) -o $@ $<

clean:
	\rm *.o $(MYNGELIB) a.out



#EXAMPLES:
#g++ -fPIC -g -c -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -Wall -I /usr/local/include/ImageMagick-6 transformer.cpp
#g++ -shared -Wl,-soname,libmynge.so -o libmynge.so transformer.o frame_manager.o multi_frame_manager.o -lc
#g++ -w -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6 move_affine.cpp -L. -lmynge `Magick++-config --cppflags --cxxflags --ldflags --libs`
