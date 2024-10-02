/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/02 19:16:05 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <errno.h>

/***********************************************************************
*                                 TOKEN                                *
*NONE	->Nothing                                                      *
*CMD	->Command                                                      *
*PIPE	->Pipe ("|")                                                   *
*IN		->Redirection, input fd ("<")                                  *
*HDOC	->Redirection, text input {HEREDOC} ("<<")                     *
*DOUT	->Redirection, destructive, deletes everything of the file(">")*
*NDOUT	->Redirection, non destructive, writes at the end (">>")       *
*BUIL	->I have no clue what is this.                                 *
***********************************************************************/
enum	e_token
{
	NONE,
	CMD,
	PIPE,
	IN,
	HDOC,
	DOUT,
	NDOUT,
	BUIL
};

/**************************************************************
*                         T_DATA                              *
*name			->Name of the program (minishell)             *
*prompt			->What user sees in the screen ("minishell> ")*
*home			->The route to home (root)                    *
*user_input		->What the user types                         *
*cmnds			->Array with the commands (like in pipex)     *
*exported_list	->Enviroment goes here                        *
*pwd			->The path to actaul position                 *
*l_status		->The state of the last command               *
*					(you can see it with echo $? for example) *
**************************************************************/
typedef struct s_data
{
	char			*name;
	char			*prompt;
	char			*home;
	char			*user_input;
	char			**cmnds;
	struct s_list	*exported_list;
	char			*pwd;
	int				l_status;
}	t_data;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

/**********************************************************************
*                            REDIRECTIONS                             *
*type	->The kind of redirection (</<</>/>>)                         *
*file	->The file for the redirection (except when is a HEREDOC (<<),*
*			in that case it's the limit)                              *
*next	->The next redirection ("< input.txt cat >> output.txt")      *
**********************************************************************/
typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/***************************************************************************
*                                TOKEN                                     *
*fd			->Files descriptor for the pipe process.                       *
*type		->The options are:                                             *
*				->Building.                                                *
*				->Normal command.                                          *
*				->Pipe (we can omit this option if we don't make the bonus)*
*argc		->Number of arguments we have in the command.                  *
*argv		->Array with arguments.                                        *
*command	->Pointer to the main command.                                 *
*pid		->Same as in the pipex.                                        *
*redir		->List of redirections (</<</>/>>)                             *
*l_status	->The state of the last command executed.                      *
*next		->Next command.                                                *
*prev		->Preview command.                                             *
***************************************************************************/
typedef struct s_token
{
	int				fd[2];
	int				type;
	int				argc;
	char			**argv;
	char			*command;
	int				pid;
	struct s_redir	*redir;
	int				l_status;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/*-----------split-----------*/
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
/*-----------strjoin-----------*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcjoin(char const *s1, char const *s2, char c);

/*----------list_utils----------*/
t_list	*ft_unset(t_list *list, char *ref);
char	**listtoenv(t_list *list);
t_list	*envtolist(char **env);

#endif