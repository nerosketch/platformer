CC=g++
CFLAGS=-c -Wall -g -DDBG -std=c++11 -MMD -MP \
	`pkg-config --cflags sdl2` \
	-Ilib/oxygine-framework/oxygine/src \
	-Ilib/oxygine-sound/src

LDFLAGS=-Llib/oxygine-framework/libs \
	./lib/oxygine-framework/liboxygine-framework.a \
	./lib/oxygine-sound/liboxygine-sound.a \
	./lib/oxygine-sound/tremor/libtremor.a \
	-lpthread -lGL -lGLU -lglut -lpng -lz -lSDL2 -ljpeg -logg -lopenal \
	./lib/oxygine-framework/libs/SDL2main.lib


EXECUTABLE=platphormer

SOURCES=BaseCollider.cpp \
	Btn.cpp \
	CollidedUnit.cpp \
	DebugRectSprite.cpp \
	DynamicUnit.cpp \
	Enemy.cpp \
	Game.cpp \
	GameStage.cpp \
	InputEvent.cpp \
	Landscape.cpp \
	Level.cpp \
	Menu.cpp \
	ObjectLoader.cpp \
	Player.cpp \
	resources.cpp \
	SoundManager.cpp \
	StageManager.cpp \
	StartMenu.cpp \
	StaticCollider.cpp \
	StaticUnit.cpp \
	TextPanel.cpp \
	Unit.cpp \
	main.cpp


OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rfv *.o *.d $(EXECUTABLE)

.PHONY: clean
