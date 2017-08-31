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
./$(OBJDIR)/Board.o \
./$(OBJDIR)/View.o \
./$(OBJDIR)/RectangularObject.o \
./$(OBJDIR)/MovableRectangularObject.o \
./$(OBJDIR)/CollisionManager.o

all : main 

main : $(OBJECTS) $(INCDIR)/Global.h
	$(CC) $(FLAGS) -I$(INCDIR) -I$(LIBDIR) $(SRCDIR)/main.cpp $(OBJECTS) -o $(BINDIR)/main $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCDIR)/Global.h
	$(CC) $(FLAGS) -I$(INCDIR) -I$(LIBDIR) -c $< -o $@ $(LIBS)

clean :
	rm -f $(OBJDIR)/* ;
	rm -f $(BINDIR)/* ;
	rm -f $(SRCDIR)/*~;
	rm -f $(INCDIR)/*~;
	rm -f *~

