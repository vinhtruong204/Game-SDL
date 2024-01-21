#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++ -std=c++17

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I Library/SDL2-2.28.5/include/SDL2 -I Library/SDL2_image-2.8.1/include/SDL2 -I Library/SDL2_mixer-2.6.3/include/SDL2 -I Library/SDL2_ttf-2.20.2/include/SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L Library/SDL2-2.28.5/lib -L Library/SDL2_image-2.8.1/lib -L Library/SDL2_mixer-2.6.3/lib -L Library/SDL2_ttf-2.20.2/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)