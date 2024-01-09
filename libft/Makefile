### PROGRAM NAME ###
NAME		:= libft.a

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
GREEN    	:= \033[0;32m
YELLOW    	:= \033[0;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m

### DIREECTORIES ###
SRC_DIR 	:= src
GNL_DIR		:= ft_gnl
PTF_DIR		:= ft_printf
INCLD_DIR 	:= include
OBJS_DIR 	:= objs

### FILES ###
define INCLUDES	:=
	$(INCLD_DIR)
endef
INCLUDES	:= $(strip $(INCLUDES))

define SRC	:=
	$(addprefix $(GNL_DIR)/, get_next_line_utils.c \
	get_next_line.c)
	$(addprefix $(PTF_DIR)/, ft_count_digits.c \
	ft_printf.c \
	ft_putnbr_unsigned_fd.c \
	print_base.c \
	print_char.c \
	print_hexa.c \
	print_int.c \
	print_str.c \
	print_unsigned_int.c)
	ft_abs.c
	ft_atoi.c
	ft_atol.c
	ft_bzero.c
	ft_calloc.c
	ft_isalnum.c
	ft_isalpha.c
	ft_isascii.c
	ft_isdigit.c
	ft_isprint.c
	ft_itoa.c
	ft_lstadd_back.c
	ft_lstadd_front.c
	ft_lstclear.c
	ft_lstdelone.c
	ft_lstiter.c
	ft_lstlast.c
	ft_lstmap.c
	ft_lstnew.c
	ft_lstsize.c
	ft_max.c
	ft_memchr.c
	ft_memcmp.c
	ft_memcpy.c
	ft_memmove.c
	ft_memset.c
	ft_min.c
	ft_putchar_fd.c
	ft_putendl_fd.c
	ft_putnbr_fd.c
	ft_putstr_fd.c
	ft_split.c
	ft_strchr.c
	ft_strcut.c
	ft_strdup.c
	ft_striteri.c
	ft_strjoin.c
	ft_strlcat.c
	ft_strlcpy.c
	ft_strlen.c
	ft_strmapi.c
	ft_strncmp.c
	ft_strnstr.c
	ft_strrchr.c
	ft_strtrim.c
	ft_substr.c
	ft_tolower.c
	ft_toupper.c
endef
SRC 		:= $(strip $(SRC))

OBJS 		:= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

### UTILS ###
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g3
RM 			:= rm -rf
INCLD_FLAG 	:= $(addprefix -I , $(INCLUDES))

### PROJECT ###
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@ar rcs $@ $(OBJS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)/$(GNL_DIR)
	@mkdir -p $(OBJS_DIR)/$(PTF_DIR)
	@$(CC) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

.PHONY: clean
clean: ; @printf "$(PURPLE)[$(NAME)] $(RED)Removing $(DEFAULT)$(OBJS_DIR) files\n"
	@$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean ; @printf "$(PURPLE)[$(NAME)] $(RED)Removing $(DEFAULT)$(NAME)\n"
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	@norminette $(SRC_DIR) $(INCLD_DIR) | awk '/Error/ {print; found=1} END \
	{if (!found) {print "$(PURPLE)[$(NAME)] $(DEFAULT)Norm: $(BWHITE)OK$(DEFAULT)"; exit 0 }; exit 1 }'
