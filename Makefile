# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:09:03 by sumsong           #+#    #+#              #
#    Updated: 2022/06/14 14:58:24 by sumsong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIB_NAME = ft
LIB_DIR = ./libft/
LIB = $(LIB_DIR)lib$(LIB_NAME).a

HEADER = minitalk.h
SRC_S = server.c
SRC_C = client.c
OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

BONUS_SRC_S = server_bonus.c
BONUS_SRC_C = client_bonus.c
BONUS_OBJ_S = $(BONUS_SRC_S:.c=.o)
BONUS_OBJ_C = $(BONUS_SRC_C:.c=.o)

all: $(SERVER) $(CLIENT)

clean:
	rm -f $(OBJ_S) $(OBJ_C) $(BONUS_OBJ_S) $(BONUS_OBJ_C)
	make -C $(LIB_DIR) clean

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(LIBFT)
	rm -f $(SERVER) $(CLIENT)

re: fclean all

bonus: $(SERVER) $(BONUS_OBJ_S) $(CLIENT) $(BONUS_OBJ_C) $(HEADER)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -l $(LIB_NAME) $(BONUS_OBJ_S) -o $(SERVER)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -l $(LIB_NAME) $(BONUS_OBJ_C) -o $(CLIENT)

$(SERVER): $(LIB) $(OBJ_S) $(HEADER)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -l $(LIB_NAME) $(OBJ_S) -o $(SERVER)

$(CLIENT): $(LIB) $(OBJ_C) $(HEADER)
	$(CC) $(CFLAGS) -L $(LIB_DIR) -l $(LIB_NAME) $(OBJ_C) -o $(CLIENT)

$(LIB):
	make -C $(LIB_DIR)

.PHONY: all clean fclean re bonus