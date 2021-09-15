ENGINE=#SDL

CC=g++ --std=c++14
FILEEXT = cc
INC = -I ./inc/
FLAGS=-Wall -Wextra -Werror -g #-D SDL_ENGINE

OBJDIR := ./obj/

DRV_SDL = $(filter %.$(FILEEXT), $(shell find ./src/sdl -type f)
DRV_NCURSES = $(filter %.$(FILEEXT), $(shell find ./src/ncurses -type f)
SRC_GAME := $(filter-out $(DRV_SDL) $(DRV_NCURSES) , $(filter %.$(FILEEXT), $(shell find ./src -type f)))
OBJ = $(addprefix $(OBJDIR),$(SRC:.$(FILEEXT)=.o))
TARGET = spaceinv


ifeq ($(ENGINE),SDL)
    FLAGS += -D SDL_ENGINE
    SRC := $(SRC_GAME) $(DRV_SDL)
    LIB = -lSDL2 -lSDL2_image
else
    SRC := $(SRC_GAME) $(DRV_NCURSES)
    LIB = -lncurses
endif


### DYNAMIC
LIB_TARGET = $(TARGET).so
#LIB_FLAGS = -dynamic_lib -flat_namespace
LIB_FLAGS = -fPIC

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(FLAGS) $(INC) $(MACRO) -o $(TARGET) $(OBJ) $(LIB)

$(OBJDIR)%.o: %.$(FILEEXT)
		@mkdir -p $(@D)
		$(CC) $(FLAGS) $(INC) $(MACRO) -c $< -o $@

clean:
		@rm -vrf $(OBJDIR)

fclean:
		@rm -vf $(TARGET)
		@rm -vrf $(OBJDIR)
		@rm -vrf bin

re: fclean all

bin: $(TARGET)
	make -C tests/
