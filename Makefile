CC = g++
LIBS = -lSDL2 -lSDL2_ttf
FLAGS = -O2 -w -std=c++11
SRCDIR = ./src
BINDIR = ./bin
OBJDIR = ./obj
INCDIR = ./include
LEVELDIR = ./levels
LIBDIR = /usr/include/SDL2

LDFLAGS = $(flags)
ifeq ($(shell uname -s), Darwin)
    flags = -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework Cocoa
else
    flags = -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf
endif

COMMANDS = \
./$(OBJDIR)/commands/QuitCommand.o \
./$(OBJDIR)/commands/SwitchToGameCommand.o \
./$(OBJDIR)/commands/MenuNavigationCommand.o \
./$(OBJDIR)/commands/DoNothingCommand.o

CONTROLLERS = \
./$(OBJDIR)/controllers/MenuInputHandler.o \
./$(OBJDIR)/controllers/GameInputHandler.o

MODELS = \
./$(OBJDIR)/model/GameObject.o \
./$(OBJDIR)/model/Tile.o \
./$(OBJDIR)/model/Paddle.o \
./$(OBJDIR)/model/Ball.o \
./$(OBJDIR)/model/Board.o \
./$(OBJDIR)/model/Powerup.o \
./$(OBJDIR)/model/Bullet.o \
./$(OBJDIR)/model/Enemy.o

GEOMETRY = \
./$(OBJDIR)/geometry/DockedRectangle.o \
./$(OBJDIR)/geometry/FloatingRectangle.o \
./$(OBJDIR)/geometry/MovableRectangle.o \
./$(OBJDIR)/geometry/CollisionManager.o

PANES = \
./$(OBJDIR)/panes/GameScreen.o \
./$(OBJDIR)/panes/DrawablePane.o \
./$(OBJDIR)/panes/DrawablePaneComposition.o \
./$(OBJDIR)/panes/ScorePane.o \
./$(OBJDIR)/panes/MenuPane.o  \
./$(OBJDIR)/panes/GamePane.o

MENUS = \
./$(OBJDIR)/menus/Menu.o \
./$(OBJDIR)/menus/MenuItemDrawer.o \
./$(OBJDIR)/menus/MenuItem.o \
./$(OBJDIR)/menus/ActionMenuItem.o \
./$(OBJDIR)/menus/MainMenu.o \
./$(OBJDIR)/menus/OptionsMenu.o \
./$(OBJDIR)/menus/SetValueMenuItem.o

ANIMATORS = \
./$(OBJDIR)/animators/Animator.o \
./$(OBJDIR)/animators/ExplosionAnimator.o \
./$(OBJDIR)/animators/BorderAnimator.o \
./$(OBJDIR)/SpriteUtils.o

MONITORS = \
./$(OBJDIR)/observers/GameEventMonitor.o

OBJECTS = \
./$(OBJDIR)/Application.o \
./$(OBJDIR)/Configuration.o \
$(MENUS) \
$(GEOMETRY) \
$(PANES) \
$(MODELS) \
$(COMMANDS) \
$(CONTROLLERS) \
$(ANIMATORS) \
$(OBSERVERS) \
$(MONITORS)

ABSTRACTS = \
./$(INCDIR)/commands/AbstractCommand.h \
./$(INCDIR)/controllers/AbstractInputHandler.h


all : main

main : $(OBJECTS) $(ABSTRACTS)
	$(CC) $(FLAGS) -I$(INCDIR) $(LDFLAGS) $(SRCDIR)/main.cpp $(OBJECTS) -o $(BINDIR)/main

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CC) $(FLAGS) -I$(INCDIR) $(LDFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJDIR)/* ;
	rm -f $(BINDIR)/* ;
	rm -rf $(SRCDIR)*~;
	rm -rf $(INCDIR)/*~;
	rm -rf $(LEVELDIR)/*~;
	rm -rf *~;
	mkdir $(OBJDIR)/menus;
	mkdir $(OBJDIR)/geometry;
	mkdir $(OBJDIR)/model;
	mkdir $(OBJDIR)/panes;
	mkdir $(OBJDIR)/commands;
	mkdir $(OBJDIR)/controllers;
	mkdir $(OBJDIR)/animators;
	mkdir $(OBJDIR)/observers;
