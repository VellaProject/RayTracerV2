#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

ACTUAL = $(words $(COUNT))
TOTAL = $(words $(SRC))
INCREMENT = $(eval COUNT+=1)

PRINTINC = $(INCREMENT) $(PRINT)
PRINT = printf "\r \033[31;1m%3s%%\033[0m\t -->>\t\033[31;1m%-65s\033[0m\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$^"
PRINTDONE = printf "\r \033[32;1m%3s%%\033[0m\t -->>\t\033[32;1m%-65s\033[0m\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$@"


all: $(NOM)

$(NOM):	$(OBJ)
	@ar rcs $@ $^ && $(PRINTDONE) && echo || exit

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NOM)

%.o: %.m
	@cc -o $@ -c $< && $(PRINTINC) || exit

%.o: %.c
	@cc -o $@ -c $< && $(PRINTINC) || exit

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
.SILENT:
