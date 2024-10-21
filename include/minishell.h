/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/16 18:09:59 by rmarin-j         ###   ########.fr       */
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
*IN		->Redirection, input fd ("<")                                  *
*HDOC	->Redirection, text input {HEREDOC} ("<<")                     *
*DOUT	->Redirection, destructive, deletes everything of the file(">")*
*NDOUT	->Redirection, non destructive, writes at the end (">>")       *
*BUIL	->Commands we include in the built in, like env,  cd, pwd,etc.                                 *
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
//1-Exite un comando después? -> Hacer una pipe. Modificando el fd.
//2-Redirecciones ->
//3-Comprobar tipo de comando
/****Aquí cambia para los built in****/
//4-Es necesario hacer un fork?->Cuando no es exit, cuando no es un built-in extraño, casi siempre.
//5-Hacer dup2 de los fd y close.
//6-Ejecutar
//7-Del 1 al 7 en el siguiente.

/*----------Token_list----------*/
t_token	*tk_list_init(char **pipes);

/*----------Expand-----------*/
char	*expand_var(char *str, t_list *list);
/*-----------Parse-----------*/
//int		close_quote(char *str, char c);
int	pipe_iteri(char *str, int i, char c);
void	parse_main(char *str, t_list *list);
int	ft_isspace(char c);
int	pipe_count(char *str);
char	**pip_separator(char *str);
/*-----------Error-----------*/
void	throw_error(const char *str);
/*-----------Split-----------*/
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*-----------strCjoin-----------*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcjoin(char *s1, char *s2, char c);

/*-----------Builts_in-----------*/
void	ft_env(t_list *list);
void 	ft_pwd(t_list *list);
/*----------List_utils----------*/
void	ft_unset(t_list **list, char *ref);
char 	**listtoenv(t_list *list);
t_list  *envtolist(char **env);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *n_key, char *n_value);
/*-----------ft_export-----------*/
t_list	*find_key(t_list *list, char *n_key);
int ft_strchr(const char *str, char c);
void    ft_voidexport(t_list *list);
int	ft_export(t_list *list, char *n_key);


void	mini_loop(t_data *data, t_list *list);
t_data	*data_init(t_list *env);
char	*ft_strdup(const char *s1);

#endif