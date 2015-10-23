CXX			:= c++
CXXFLAGS	:= -std=c++1y -stdlib=libc++

INCLUDES := -I/usr/local/Cellar/v8/4.5.103.35 -I/usr/local/Cellar/v8/4.5.103.35/include -I/usr/local/Cellar/v8/4.5.103.35/include/libplatform -I/usr/local/include -I../../ -I/usr/local/Cellar/boost/include

LIBS :=  -L/usr/local/Cellar/v8/4.5.103.35/lib -L/usr/local/lib -L/usr/local/Cellar/boost/1.58.0/lib -lboost_system -lboost_filesystem -lwkhtmltox.0.12.2 -lv8_nosnapshot -lv8_snapshot -lv8_base -lv8_libbase -lv8_libplatform -lv8

OBJECTS := main.o latex.o

build: $(OBJECTS)
	$(MAKE) image
	$(MAKE) clean

image: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o image $(LIBS)

latex.o: ../../latex.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c ../../latex.cpp -o latex.o

main.o: main.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o

reset:
	$(MAKE) clean
	rm -f *.png
	rm -f *.svg
	rm -f *.jpg
	rm -f image

.PHONY: clean reset
