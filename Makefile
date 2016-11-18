PROJECT = Breakout

CC = g++

CFLAGS = -Wall -std=c++11

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

ODIR = obj

SDIR = src

SOURCE_FILES := $(wildcard $(SDIR)/*.cpp)

OBJECTS = $(patsubst $(SDIR)%.cpp, $(ODIR)%.o, $(SOURCE_FILES))


all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $(OBJECTS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(LIBS) $(CFLAGS)

clean:
	rm -rf $(OBJ)/*.o $(PROJECT)
