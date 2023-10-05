
# -- Executable's name -- #
NAME		=	cub3D

# -- Compilation Flag -- #
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS	=	-Wall -Wextra -Werror -g -Wunreachable-code -fsanitize=address
# CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

# -- OS CHECK -- #
OS 			= $(shell uname)
OS_AIR 		= $(shell uname -p)

# -- MLX42 Flags depending on the OS -- #
# -- LINUX and WSL -- # 
LINUX 		= -ldl -lglfw -pthread -lm

# -- MAC -- #
MAC 		= -I /include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
MAC_AIR 	= -I /include -lglfw -L "/opt/homebrew/Cellar/glfw/3.3.8/lib"

# -- Check OS to get the correct FLAGS -- #
ifeq ($(OS_AIR), arm)
	GLFW = $(MAC_AIR)
else ifeq ($(OS), Linux)
	GLFW = $(LINUX)
else ifeq ($(OS), Darwin)
	GLFW = $(MAC)
endif

# -- Remove -- #
RM			=	rm -rf

# -- SRC Files -- #
SRCS_DIR	=	./srcs/
# SRCS_LST	= 	test.c 
SRCS_LST	= 	main.c arg_parsing.c error_management.c init.c \
				map_check.c map_parsing.c map2D.c hooks.c hooks2.c key_binding.c cursor.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

# -- OBJ Files -- #
OBJS_DIR	=	./obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS_LST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

# -- HEADER Files -- #
HEADER_DIR	=	./includes/
HEADER_LST	=	cub3d.h
HEADER	 	=	$(addprefix $(HEADER_DIR), $(HEADER_LST))

# -- LIBFT Files -- #
LIBFT_DIR	=	./libs/libft/
LIBFT		=	$(LIBFT_DIR)libft.a
LIBFT_H		=	$(LIBFT_DIR)include/libft.h

# -- MLX42 Files -- #
MLX42_DIR	=	./libs/MLX42
MLX42		=	$(MLX42_DIR)/build/libmlx42.a

# Includes
INCLUDE		= -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include/MLX42

# -- Colors -- #
RESET		= 	\033[0m
RED			= 	\033[0;31m
GREEN		= 	\033[0;32m
YELLOW		= 	\033[0;33m
BLUE		= 	\033[0;34m
PURPLE		= 	\033[0;35m
CYAN		= 	\033[0;36m
ERASE_LINE 	= 	\033[2K\r


# -- Executable's creation -- #
all : dir $(NAME)

# -- Compile library -- #
$(NAME): $(MLX42) $(LIBFT) $(OBJS) 
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MLX42) $(OPEN_GL) $(GLFW) -o $(NAME) $(INCLUDE)
	@echo "✅ $(GREEN)$(NAME)'s exectuable successfully created.\t✅$(RESET)"

$(MLX42):
	@if [ ! -f "./libs/MLX42/build/libmlx42.a" ]; then \
		cmake libs/MLX42 -B $(MLX42_DIR)/build &> /dev/null && make -C $(MLX42_DIR)/build -j4; \
	fi
	@echo "\n✅ $(GREEN)MLX42 successfully compiled.\t\t\t✅$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

# -- Create all files .o (object) from files .c (source code) -- #
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER)
	@printf "$(ERASE_LINE)🎛️  $(PURPLE)Compiling $(YELLOW)$(notdir $<)\r$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

run: all
	@./$(NAME)

# -- Create directory for *.o files -- #
dir:
	@mkdir -p $(OBJS_DIR)

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

leaks: all
	@reset
	leaks --atExit -- ./$(NAME)

# -- Removes objects -- #
clean :
	@make -C $(LIBFT_DIR) clean
	@printf "💥 $(RED)Removing $(NAME)'s objects...$(RESET)\t\t\t\t💥\n"
	@$(RM) $(OBJS_DIR)
	@printf "🗑️  $(CYAN)$(NAME)'s object successfully deleted.$(RESET)\t\t\t🗑️\n"

# -- Removes objects (with clean) and executable -- #
fclean : clean
	@printf "💥 $(RED)Removing executable(s)...$(RESET)\t\t\t\t💥\n"
	@$(RM) $(LIBFT)
	@$(RM) $(NAME)
	@$(RM) $(MLX42_DIR)/build
	@printf "🗑️  $(CYAN)Executable(s) and archive(s) successfully deleted.$(RESET)	🗑️\n\n"
				
# -- Removes objects and executable then remakes all -- #
re : fclean all 

#Open the subject
pdf : 
	@open https://cdn.intra.42.fr/pdf/pdf/105108/en.subject.pdf

# Run norminette
norm :
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE $W<<<<<<<<<<<<<<<<<<<<<<<<<<$Z\n"
	@norminette $(SRCS) $(HEADER) $(LIBFT_DIR)
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE ✅ $W<<<<<<<<<<<<<<<<<<<<<<<<<<"

# -- Avoid file-target name conflicts -- #
.PHONY : all bonus clean fclean re pdf
