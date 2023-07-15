#OBJS specifies which files to compile as part of the project
OBJS = src/cpp/*.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++11

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin/jvm

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)