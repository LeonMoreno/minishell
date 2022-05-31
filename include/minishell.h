#ifndef MINISHELL_H
# define MINISHELL_H

// Include stddef stdio stlib unistd limits stdarg fcntl
#include "../libft/include/libft.h"

// Include readline
#include <readline/readline.h>

typedef struct s_sh
{
	char	*line;
	char	**line_split;
}	t_sh;


#endif
