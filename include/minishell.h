/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/01/15 13:28:30 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

							/* COLORS */
# define RD		"\033[1;91m"
# define PR		"\033[4;95m"
# define CI		"\033[0;96m"
# define GR		"\033[0;92m"
# define PI		"\033[0;94m"
# define FF		"\033[0;97m"
# define RES	"\033[0m"

/***********************************************************************
*                                 TOKEN                                *
*NONE	->Nothing                                                      *
*CMD	->Command                                                      *
*PIPE	->Pipe ("|")                                                   *
*IN		->("<") Redirection, input fd                                  *
*HDOC	->("<<"){HEREDOC}Redirection, text input                     *
*DOUT	->(">")Redirection, destructive, deletes everything of the file*
*NDOUT	->(">>")Redirection, non destructive, writes at the end        *
*BUIL	->Commands we include in the built in, like env,  cd, pwd,etc. *
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
	BUIL,
};

/**************************************************************
*                         T_DATA                              *
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
	char			*home;
	char			*user_input;
	char			**cmnds;
	struct s_list	*exported_list;
	char			*pwd;
	int				l_status; 
}	t_data;

/**********************************************************
*                   Enviroment                            *
*key  ->The key of the enviroment variable (like "PATH")  *
*value->The value of the enviroment variable (like "/bin")*
*next  ->The next enviroment variable.                    *
**********************************************************/
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
*index	->Index of the first char in the original str                 *
*next	->The next redirection ("< input.txt cat >> output.txt")      *
**********************************************************************/
typedef struct s_redir
{
	int				type;
	int				index;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/***************************************************************************
*                                TOKEN                                     *
*We save what we need to execute a command line / user input               *
*fd			->Files descriptor for the pipe process.                       *
*type		->The options are:                                             *
*				->Building.                                                *
*				->Normal command.                                          *
*				->Pipe (we can omit this option if we don't make the bonus)*
*argc		->Number of arguments we have in the command.                  *
*argv		->Array with arguments.                                        *
*command	->Pointer to the main command.                                 *
*hdoc		->Limit string for the HEREDOC.                                *
*pid		->Same as in the pipex.                                        *
*l_status	->The state of the last command executed.                      *
*redir		->List of redirections (</<</>/>>).                            *
*env		->Enviroment.                                                  *
***************************************************************************/
typedef struct s_token
{
	int				fd[2];
	int				type;
	int				argc;
	char			**argv;
	char			*command;
	char			*hdoc;
	int				pid;
	int				l_status;
	struct s_redir	*redir;
	struct s_list	*env;
}	t_token;

/**************************************************************************
*	Note:                                                                 *
*1-Is any command after? -> Make a pipe. Modifying the fd.                *
*2-Redirect.                                                              *
*3-Check the type of command.                                             *
*                 In this point changes for the built ins                 *
*4-Is necesary to fork?->When is not exit, when is not a strange built-in,*
*	almost always.                                                        *
*5-Make dup2 of the fd and close.                                         *
*6-Execute.                                                               *
*7-From 1 to 7 in the next.                                               *
**************************************************************************/

/*------------freedom-----------*/
void	free_partial_data(t_data *data);
void	free_all_data(t_data *data);
void	free_2ptr(char **array);
void	ft_redirclear(t_redir **red);
void	ft_tokenclear(t_token *tk);
void	ft_envclear(t_list **lst);

/*------------redir------------*/
void	redir_fill(t_token *tk, char *str, int rd_type, int i);
char	*rd_strdel(t_token *tk, char *str);
void	tk_inrd(t_token *tk_node, char *str);
void	tk_outrd(t_token *tk_node, char *str);

/*------------Redir_utirs------------*/
void	printredir(t_redir *red, char *str);
char	*getfilename(char *str, int i);
void	ft_rediradd_back(t_redir **lst, t_redir *new);

/*----------Token_list----------*/
t_token	*tk_list_init(char **pipes);
t_token	*tk_list_make(char **pipes, t_list *env, t_data *data);

/*----------Expand-----------*/
char	*expand_var(char *str, t_list *list, t_data *data);

/*-----------Parse-----------*/
//int		close_quote(char *str, char c);
int		pipe_iteri(char *str, int i, char c);
t_token	*parse_main(char *str, t_list *list, t_data *data);
int		pipe_count(char *str);
char	**pip_separator(char *str);

/*-----------Error-----------*/
void	throw_error(const char *str, t_token *tk, t_data *data);
void	free_2ptr(char **array);

/*-----------Split-----------*/
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*-----------strCjoin-----------*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcjoin(char *s1, char *s2, char c);

/*-----------Builts_in-----------*/
int		ft_cd(char **argv, t_data *data);
int		ft_env(t_list *list);
int		ft_pwd();

/*-----------ft_echo-----------*/
int		ft_echo(char **argv);

/*-----------ft_exit-----------*/
int		ft_exit(char **av);
int		ft_atoi(const char *str);

/*----------List_utils----------*/
void	ft_unset(t_list **list, char *ref);
char	**listtoenv(t_list *list);
t_list	*envtolist(char **env);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *n_key, char *n_value);

/*-----------ft_export-----------*/
t_list	*find_key(t_list *list, char *n_key);
int		ft_strchr(const char *str, char c);
void	ft_voidexport(t_list *list);
int		ft_export(t_list *list, char *n_key);

/*-----------ft_itoa------------*/
char	*ft_itoa(int n);

/*----------Str_utils-----------*/
void	ft_putstr_fd(char *s, int fd);
int		ft_isalnum(int c);
int		end_quote(char *str, int i, char c);
int		ft_strchr(const char *str, char c);
int		ft_isspace(char c);

/*-----------Exewcuite---------*/
void	ft_execute(t_token token, t_data data);

/*-----------Minishell (MAIN)------------*/
void	mini_loop(t_data *data, t_list *list);
t_data	*data_init(t_list *env);
char	*ft_strdup(const char *s1);

#endif