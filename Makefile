ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
CC=gcc
FLAGS=-Wall -Wextra -Werror -g
INCLUDE=-I ./inc/
OBJDIR := ./obj/
#MACRO=-D NO_MT_SAFE
SRC := $(filter %.c, $(shell find src -type f))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
RUN = ./run.sh

all: $(NAME)

$(NAME): $(OBJ) $(RUN)
	@$(CC) $(FLAGS) $(MACRO) $(INCLUDE) $(OBJ) -shared -o $(NAME) $(LINK)
	@ln -sf $(NAME) libft_malloc.so

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -fPIC $(MACRO) $(INCLUDE) -o $@ -c $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) libft_malloc.so run.sh

$(RUN):
	@echo "#!/bin/bash" > run.sh
	@echo "#MAC OS" >> run.sh
	@echo "export DYLD_LIBRARY_PATH=." >> run.sh
	@echo "export DYLD_INSERT_LIBRARIES=\"libft_malloc.so\"" >> run.sh
	@echo "export DYLD_FORCE_FLAT_NAMESPACE=1" >> run.sh
	@echo '$$@' >> run.sh
	@chmod +x run.sh

re: fclean all
