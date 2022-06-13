#Variables
NAME	= minishell
SRC_DIR	= src/
OBJ_DIR	= obj/
CFLAGS	= -Werror -Wall -Wextra -I include/
CC		= gcc
RM		= rm -f

#Libft
LIBFT_A		= libft.a
LIBFT_DIR	= libft/
LIBFT		= $(addprefix $(LIBFT_DIR), $(LIBFT_A))

#Sources Files
SRC_FILES =	minishell ft_expansion ft_parsing_meta ft_reading\
			ft_quoting start_builtins check_builtins start_exec\
			ft_utils ft_init_cmd start_childs utils_childs ft_sigaction

#SRC
SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF	=	.cache_exists

####

all	: $(NAME)

$(NAME):	$(OBJ)
			make -C $(LIBFT_DIR)
			$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
				$(CC) $(CFLAGS) -c $< -o $@


$(OBJF)	:
			mkdir -p $(OBJ_DIR)

clean	:
			$(RM) -r $(OBJ_DIR)
			make -C $(LIBFT_DIR) clean
			$(RM) $(OBJF)

fclean	:	clean
			$(RM) $(NAME)
			make -C $(LIBFT_DIR) fclean

re		: fclean all

