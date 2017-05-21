##
## Makefile for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
##
## Made by Baptiste veyssiere
## Login   <VEYSSI_B@epitech.net>
##
## Started on  Wed May 18 21:26:30 2016 Baptiste veyssiere
##

NAME	= server

RM	= rm -f

CC	= gcc

MKDIR	= mkdir -p

SRC	= src/main.c \
	src/get_client_command.c \
	src/server_main.c \
	src/server_pi.c \
	src/login.c \
	src/directory_handler.c \
	src/miscellaneous.c \
	src/port.c \
	src/pasv.c \
	src/basic_functions.c \
	src/dtp.c \
	src/list.c \
	src/retr.c

SRCDIR	= src

OBJDIR	= obj

OBJ	= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS	= -Iinclude -W -Wextra -Wall -Werror

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
