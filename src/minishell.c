/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/05 17:09:43 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_token	token;
	int		input = 0;
	int		output = 0;
	int		i = 0;

	if (!env[0])
		throw_error(RD"ERROR: Enviroment empty"RES);
	while (argv[++i] && argc > 0)
	{
		if (!argv[i][0])
			throw_error(RD"Error: One or more arguments empty"RES);
		i++;
	}

/*     cmd1 << LIMITER | cmd2 >> file
	if (????)
	{
		i = 3;
		output = tin_opener(argv[argc - 1], 0);
		here_doc(argv[2], argc);
	}
*/
	else
	{
		i = 2;
		output = tin_opener(argv[argc - 1], 1);
		input = tin_opener(argv[1], 2);
		dup2(input, STDIN_FILENO);
	}
	while (i < (argc - 2))
		child_process_bonus(argv[i++], env);
	dup2(output, STDOUT_FILENO);
	ft_execute(argv[argc - 2], env);
	wait(NULL);

}





/*     V0.1
	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1 && argv)
	{
		input = open("files/input", O_RDONLY);
		output = open("files/output", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		token.type = 1;
		token.argc = 1;
		token.argv[0] = "cat";
	//	token.command = "/bin/cat/";
	}
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	ft_execute(token.argv[0], env);
	wait(NULL);

	//	mini_loop();
	return (0);
}
*/


/*
typedef struct s_token
{
	int				fd[2];
	int				type; //cmd
	int				argc; //3
	char			**argv; // [0]= ls; [1]=-l; [2]=-a; [3]=NULL
	char			*command; // /bin/ls
	int				pid;
	struct s_redir	*redir; //NULL
	int				l_status; //indiferente
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;
*/
