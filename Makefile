CC = g++
LIBS = -lSDL2
FLAGS = -O2 -w
SRCDIR = ./src
BINDIR = ./bin
OBJDIR = ./obj
INCDIR = ./include
LIBDIR = /usr/include/SDL2

OBJECTS = \
./$(OBJDIR)/Tile.o \
./$(OBJDIR)/Paddle.o \
./$(OBJDIR)/Ball.o \
./$(OBJDIR)/Board.o


all : main

main : $(OBJECTS)
	$(CC) $(FLAGS) -I$(INCDIR) -I$(LIBDIR) $(SRCDIR)/main.cpp $(OBJECTS) -o $(BINDIR)/main -w $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) -I$(INCDIR) -c $< -o $@

#obj/Tile.o : $(SRCDIR)/Tile.cpp $(INCDIR)/Tile.h
#	$(CC) $(FLAGS) -I$(INCDIR) -c $(SRCDIR)/Tile.cpp -o $(OBJDIR)/Tile.o

#obj/Paddle.o : $(SRCDIR)/Paddle.cpp $(INCDIR)/Paddle.h
#	$(CC) $(FLAGS) -I$(INCDIR) -c $(SRCDIR)/Paddle.cpp -o $(OBJDIR)/Paddle.o

#obj/Ball.o : $(SRCDIR)/Ball.cpp $(INCDIR)/Ball.h
#	$(CC) $(FLAGS) -I$(INCDIR) -c $(SRCDIR)/Ball.cpp -o $(OBJDIR)/Ball.o


clean :
	rm -f $(OBJDIR)/* ;
	rm -f $(BINDIR)/* ;
	rm -f $(SRCDIR)/*~;
	rm -f *~
