CC = g++
LIBS = -lSDL2 -lSDL2_ttf
FLAGS = -O2 -w
SRCDIR = ./src
BINDIR = ./bin
OBJDIR = ./obj
INCDIR = ./include
LEVELDIR = ./levels
LIBDIR = /usr/include/SDL2

OBJECTS = \
./$(OBJDIR)/DockedRectangle.o \
./$(OBJDIR)/FloatingRectangle.o \
./$(OBJDIR)/MovableRectangle.o \
./$(OBJDIR)/Tile.o \
./$(OBJDIR)/Paddle.o \
./$(OBJDIR)/Ball.o \
./$(OBJDIR)/Board.o \
./$(OBJDIR)/GameScreen.o \
./$(OBJDIR)/CollisionManager.o \
./$(OBJDIR)/DrawablePane.o \
./$(OBJDIR)/DrawablePaneComposition.o \
./$(OBJDIR)/ScorePane.o \
./$(OBJDIR)/BasicMenuItem.o \
./$(OBJDIR)/Menu.o \
./$(OBJDIR)/MenuPane.o \
./$(OBJDIR)/MenuItemDrawer.o \
./$(OBJDIR)/MenuItem.o \
./$(OBJDIR)/Application.o \
./$(OBJDIR)/ChangePaneCommand.o

MENUOBJECTS = \
./$(OBJDIR)/FloatingRectangle.o \
./$(OBJDIR)/BasicMenuItem.o \
./$(OBJDIR)/Menu.o \
./$(OBJDIR)/MenuPane.o \
./$(OBJDIR)/MenuItemDrawer.o \
./$(OBJDIR)/MenuItem.o \
./$(OBJDIR)/DrawablePane.o



all : main 

main : $(OBJECTS) $(INCDIR)/Global.h
	$(CC) $(FLAGS) -I$(INCDIR) -I$(LIBDIR) $(SRCDIR)/main.cpp $(OBJECTS) -o $(BINDIR)/main $(LIBS)


menuTest : $(MENUOBJECTS)
	$(CC) $(FLAGS) -I$(INCDIR) -I$(LIBDIR) $(SRCDIR)/menuTest.cpp $(MENUOBJECTS) -o $(BINDIR)/menuTest $(LIBS)


$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCDIR)/%.h $(INCDIR)/Global.h
	$(CC) $(FLAGS) -I$(INCDIR) -I$(LIBDIR) -c $< -o $@ $(LIBS)

clean :
	rm -f $(OBJDIR)/* ;
	rm -f $(BINDIR)/* ;
	rm -f $(SRCDIR)/*~;
	rm -f $(INCDIR)/*~;
	rm -f $(LEVELDIR)/*~;
	rm -f *~

