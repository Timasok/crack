OBJ_DIR := ./obj/
LOGS_DIR:= ./logs/	
SRC_DIR	:= ./
I_FLAG 	:=
CC 		:= g++
CFLAGS  := -Wno-format -g -fsanitize=address
CFLAGS_NO_SANITIZER := -Wno-format -g

CRACK_EXE  := crack

SRC    := $(wildcard $(SRC_DIR)*.cpp)
OBJ    := $(patsubst $(SRC_DIR)%.cpp,  $(OBJ_DIR)%.o, $(SRC))

all : $(CRACK_EXE)

$(CRACK_EXE): $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $(CRACK_EXE)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@$(CC) $(I_FLAG) -c $< -o $@

mkdir :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LOGS_DIR)

clean :
	@rm $(CRACK_EXE) $(OBJ_DIR)*.o 