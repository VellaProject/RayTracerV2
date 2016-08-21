# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igomez <igomez@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/25 12:40:20 by igomez            #+#    #+#              #
#    Updated: 2016/06/19 01:40:52 by igomez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := rt

INCS := includes
SRCS := srcs
OBJS := objs
LIB := libft
LIX := libx

SHELL := /bin/bash

INCLUDES := -I$(INCS) -I$(LIB)/$(INCS) -I$(LIX)/
LIBS := -L/usr/lib -L $(LIB) -lft -L $(LIX) -lft -L/usr/lib -lreadline -lpthread

# Search source files
C_FILES := $(shell find $(SRCS) -type f -name *.c)
C_DIRS := $(shell find $(SRCS) -depth -type d)
C_FLAGS += -MMD -std=c99 -g -Wall -Wextra -Werror -O3
FMLX := -framework OpenGL -framework AppKit -lmlx

# Build .o list
O_DIRS := $(addprefix $(OBJS)/,$(C_DIRS))
O_FILES_TMP := $(C_FILES:%.c=$(OBJS)/%.o)
O_FILES := $(O_FILES_TMP:%.s=$(OBJS)/%.o)

DEPS := $(O_FILES:.o=.d)

# Create OBJS and childs
$(shell mkdir -p $(O_DIRS) $(OBJS))

# Print
ACTUAL = $(words $(COUNT))
TOTAL = $(words $(filter %.c,$(C_FILES)))
INCREMENT = $(eval COUNT+=1)

PRINTINC = $(INCREMENT) $(PRINT)
PRINT = printf "\r \033[31;1m%3s%%\033[0m\t -->>\t\033[31;1m%-65s\033[0m\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$^"
PRINTDONE = printf "\r \033[32;1m%3s%%\033[0m\t -->>\t\033[32;1m%-65s\033[0m\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$@"

all:
	@make $(NAME)

$(NAME): $(O_FILES)
	@make -C $(LIB)
	@make -C $(LIX)
	@clang $(C_FLAGS) $(INCLUDES) $(LIBS) -o $@ $(O_FILES) $(FMLX) && $(PRINTDONE) && echo || exit

$(OBJS)/%.o: %.c
	@clang $(C_FLAGS) $(INCLUDES) -o $@ -c $< && $(PRINTINC) || exit

clean:
	@make -C $(LIB) clean
	@make -C $(LIX) clean
	@rm -rf $(O_FILES) $(OBJS)

fclean: clean
	@make -C $(LIB) fclean
	@make -C $(LIX) fclean
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
.SILENT:
