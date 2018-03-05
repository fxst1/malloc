ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
LIBNAME=libft_malloc_$(HOSTTYPE).a
CC=gcc
FLAGS=-Wall -Wextra -Werror -g
INCLUDE=-I ./inc/
OBJDIR := ./obj/so/
OBJDIRLIB := ./obj/a/
#MACRO=-D NO_MT_SAFE
SRC := $(filter %.c, $(shell find src -type f))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) launcher
	@$(CC) $(FLAGS) -fPIC $(MACRO) $(INCLUDE) $(OBJ) -shared -o $(NAME) $(LINK)
	@ln -s $(NAME) libft_malloc.so

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -fPIC $(MACRO) $(INCLUDE) -o $@ -c $<

clean:
	@rm -rf $(OBJDIR) $(OBJDIRLIB) test_*

fclean: clean
	@rm -f $(NAME) $(LIBNAME) libft_malloc.a libft_malloc.so launcher.sh

launcher:
	@echo "#!/bin/bash" > launcher.sh
	#@echo "export DYLD_INSERT_LIBRARIES=$(DYLD_INSERT_LIBRARIES):$(NAME) #MAC" >> launcher
	@echo "export DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH):$(NAME) #MAC" >> launcher.sh
	@echo "export LD_PRELOAD=$(LD_PRELOAD):$(NAME) #Linux (prefered)" >> launcher.sh
	@echo "export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(NAME) #Linux" >> launcher.sh
	#@echo "export LD_DEBUG=all cat #Linux" >> launcher.sh
	@echo 'echo Starting $$@' >> launcher.sh
	@echo '$$@' >> launcher.sh
	@chmod +x launcher.sh
	##
	@echo "#!/bin/bash" > debugger.sh
	@echo 'echo Debugging $$@' >> debugger.sh
	@echo 'gdb -iex "set exec-wrapper env LD_PRELOAD=./$(NAME) env LD_LIBRARY_PATH=$(NAME)" $$1' >> debugger.sh
	@chmod +x debugger.sh

bin:
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/marco.c -o overlap -L . $(NAME)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_thread.c -o test_thread -L . $(NAME) -lpthread
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_error.c -o test_error -L . $(NAME)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_many.c -o test_many -L . $(NAME)

re: fclean all
