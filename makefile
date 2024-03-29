#OBJS specifies which files to compile as part of the project
OBJS = game_object.cpp main.cpp map_generator.cpp road.cpp texture_manager.cpp texture.cpp tile_graph.cpp tile.cpp wall.cpp collision.cpp menu.cpp MazeAlgos/maze3gen.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lglut -lGLEW

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) -g
