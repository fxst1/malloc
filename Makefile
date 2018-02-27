ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
CC=gcc
FLAGS=-Wall -Wextra -g -fPIC
INCLUDE=-I ./inc/
#MACRO=-D NO_MT_SAFE
SRC := $(filter %.c, $(shell find src -type f))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) $(OBJ) -shared -o $(NAME) $(LINK)
	ln -s $(NAME) libft_malloc.so

%.o: %.c
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) -o $@ -c $< 

clean:
	@rm -vfr $(OBJ) test_*

fclean: clean
	@rm -vf $(NAME) libft_malloc.so

bin:
	@echo "#!/bin/bash" > launch
	#@echo "export DYLD_INSERT_LIBRARIES=$(DYLD_INSERT_LIBRARIES):$(NAME) #MAC" >> launch
	@echo "export DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH):$(NAME) #MAC" >> launch
	@echo "export LD_PRELOAD=$(LD_PRELOAD):$(NAME) #Linux (prefered)" >> launch
	@echo "export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(NAME) #Linux" >> launch
	@echo 'echo Starting $$@' >> launch
	@echo '$$@' >> launch
	@chmod +x launch
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_loop.c -o test_loop -L . $(NAME)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_malloc.c -o test_malloc -L . $(NAME)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_free.c -o test_free -L . $(NAME)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_realloc.c -o test_realloc -L . $(NAME)
	#$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_thread.c -o test_thread -L . $(NAME) -lpthread
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_error.c -o test_error -L . $(NAME)
	$(CC) $(FLAGS) $(MACRO) $(INCLUDE) test/test_many.c -o test_many -L . $(NAME)

testbin:
	@echo "#!/bin/bash" > launch
	#@echo "export DYLD_INSERT_LIBRARIES=$(DYLD_INSERT_LIBRARIES):$(NAME) #MAC" >> launch
	@echo "export DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH):$(NAME) #MAC" >> launch
	@echo "export LD_PRELOAD=$(LD_PRELOAD):$(NAME) #Linux (prefered)" >> launch
	@echo "export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(NAME) #Linux" >> launch
	@echo 'echo Starting $$@' >> launch
	@echo '$$@' >> launch
	@chmod +x launch
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_loop.c -o test_loop
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_malloc.c -o test_malloc
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_free.c -o test_free
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_realloc.c -o test_realloc
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_thread.c -o test_thread -lpthread
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_error.c -o test_error
	$(CC) $(FLAGS) $(MACRO) -D NOFT $(INCLUDE) test/test_many.c -o test_many


re: fclean all
