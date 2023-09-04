# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csenand <csenand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 15:11:55 by csenand           #+#    #+#              #
#    Updated: 2023/09/04 15:49:50 by csenand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

RM			= 	rm -rf
AR			= 	ar rcs 

SRCS_DIR	=	./srcs/
SRCS_LST	= 	ft_atof.c \
				ft_atoi_base.c \
				ft_atoi.c \
				ft_atol.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_char_tab_len.c \
				ft_free_tab_char.c \
				ft_free_tab_int.c \
				ft_freenull.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_str_isdigit.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin_free.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c
				
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS_DIR	=	./obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS_LST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

HEADER_DIR	=	./include/
HEADER_LST	=	libft.h
HEADER	 	=	$(addprefix $(HEADER_DIR), $(HEADER_LST))


# -- Colors -- #
RESET	= \033[0m
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m

# -- Executable's creation -- #
all : dir $(NAME)

# -- Compile library -- #
$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "✅ $(GREEN)Libft successfully created. ✅     $(RESET)"

# -- Create all files .o (object) from files .c (source code) -- #
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@printf "🎛️  $(PURPLE)Compilation of $(YELLOW)$(notdir $<)\r$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# -- Create directory for *.o files -- #
dir:
	@mkdir -p $(OBJS_DIR)

# -- Removes objects -- #
clean :
	@printf "💥 $(RED)Removing $(NAME)'s objects... $(RESET)💥\n"
	@$(RM) $(OBJS_DIR)
	@printf "🗑️  $(CYAN)libft's object successfully deleted.$(RESET) 🗑️\n"

# -- Removes objects (with clean) and executable -- #
fclean : clean
	@printf "💥 $(RED)Removing $(NAME)'s executable... $(RESET)💥\n"
	@$(RM) $(NAME)
	@printf "🗑️  $(CYAN)Executable(s) and archive(s) successfully deleted.$(RESET) 🗑️\n"

# -- Removes objects and executable then remakes all -- #
re : fclean all

# -- Avoid file-target name conflicts -- #
.PHONY: all bonus clean fclean re