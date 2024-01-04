### PROGRAM NAME ###
NAME		:= minishell

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

### DIRECTORIES ###
SRC_DIR 	:= src
INCLD_DIR 	:= include
OBJS_DIR 	:= objs
LIBFT_DIR 	:= libft

### FILES ###
LIBFT		:= $(LIBFT_DIR)/libft.a

define LIB 	:=
	$(LIBFT)
endef
LIB 		:= $(strip $(LIB))

define SRC 	:=
	main.c
endef
SRC 		:= $(strip $(SRC))

define INCLUDES	:=
	$(INCLD_DIR)/
	$(LIBFT_DIR)/$(INCLD_DIR)/
endef
INCLUDES 	:= $(strip $(INCLUDES))

OBJS 		:= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

### UTILS ###
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -g3
RM 			:= rm -rf
INCLD_FLAG 	:= $(addprefix -I , $(INCLUDES))
MAKE_FLAG 	:= --no-print-directory --silent

### PROJECT ###
.PHONY: all
all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(INCLD_FLAG) -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

.PHONY: clean
clean:
	@echo "$(RED)! Removing$(DEFAULT) $(OBJS_DIR) files"
	@$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

### LIBFT ###
$(LIBFT):
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) $(MAKE_FLAG)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

.PHONY: cleanlib
cleanlib:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) clean $(MAKE_FLAG)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

.PHONY: fcleanlib
fcleanlib:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) fclean $(MAKE_FLAG)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

.PHONY: relib
relib:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) re $(MAKE_FLAG)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"

### NORM ###
.PHONY: norm
norm:
	@echo "$(YELLOW)$(WD) ./$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) norm $(MAKE_FLAG)
	@echo "$(YELLOW)$(WD) ./$(DEFAULT)"
	@norminette $(SRC_DIR) $(INCLD_DIR) | awk '/Error/ {print; found=1} END \
	{if (!found) {print "$(PURPLE)Norm OK$(DEFAULT)"; exit 0 }; exit 1 }'
