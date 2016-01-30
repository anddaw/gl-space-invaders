CC = g++
HEADERS = Model.h Ship.h Geometry.h View.h Missile.h
OBJS = main.o Model.o Geometry.o View.o Ship.o Missile.o
FLAGS = -g -Wall -std=c++11 -lpthread -lglut -lGL -lGLU -lm

TARGET = main.a

#vpath %.cpp src
#vpath %.h src


$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) -o  $@ $+

%.o: %.cpp $(HEADERS)
	$(CC) $(FLAGS) -o $@ -c  $<

clean:
	rm -f *.o

clean-all:
	rm -f *.o $(TARGET)
