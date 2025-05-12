/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/12 13:05:44 by fmesa-or         ###   ########.fr       */
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
# include <signal.h>

							/* COLORS */
# define RD		"\033[1;91m"
# define PR		"\033[4;95m"
# define CI		"\033[0;96m"
# define GR		"\033[0;92m"
# define PI		"\033[0;94m"
# define FF		"\033[0;97m"
# define RES	"\033[0m"

/**************************************************************************
*                                 TOKEN                                   *
*NONE	->(0)Nothing                                                      *
*CMD	->(1)Command                                                      *
*PIPE	->(2)Pipe ("|")                                                   *
*IN		->(3)("<") Redirection, input fd                                  *
*HDOC	->(4)("<<"){HEREDOC}Redirection, text input                       *
*DOUT	->(5)(">")Redirection, destructive, deletes everything of the file*
*NDOUT	->(6)(">>")Redirection, non destructive, writes at the end        *
*BUIL	->(7)Commands we include in the built in, like env,  cd, pwd,etc. *
**************************************************************************/
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
*bk_in/out		->BackUp for the standard in and out          *
**************************************************************/
typedef struct s_data
{
	char			*home;
	char			*user_input;
	char			**cmnds;
	struct s_list	*exported_list;
	char			*pwd;
	char			*oldpwd;
	int				l_status;
	int				bk_in;
	int				bk_out;
	int				fd[2];
	int				file_in;//elarchivo IN
	int				file_out;//archivo de salida
	int				typein;//tipo de entrada
	int				typeout;//tipo de salida
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
*index	->Index of the first char in the original str                 *
*file	->The file for the redirection (except when is a HEREDOC (<<),*
*			in that case it's the limit)                              *
*next	->The next redirection ("< input.txt cat >> output.txt")      *
**********************************************************************/
typedef struct s_redir
{
	int				type;
	int				index;
	int				end_in; //este es el indice del ultimo char del file
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
*pid		->Same as in the pipex.                                        *
*l_status	->The state of the last command executed.                      *
*redir		->List of redirections (</<</>/>>).                            *
*env		->Enviroment.                                                  *
***************************************************************************/
typedef struct s_token
{
	int				fd[2];//eliminar
	int				type;
	int				argc;
	char			*command;
	char			**argv;
	pid_t			pid;
	int				l_status;
	struct s_redir	*redir;
	struct s_list	*av_list;//añadir
	struct s_list	*env;
}	t_token;

/**************************************************
*This structure only should be called on commander*
*Stores the final redir and all its info          *
**************************************************/
typedef struct s_sherpa
{
	int		typein;
	int		typeout;
	char	*filein;
	char	*fileout;
	bool	hdocflag;
}	t_sherpa;

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
int	redir_fill(t_token *tk, char *str, int rd_type, int i, t_data *data);
char	*rd_strdel(t_redir *redir, char *str);
void	tk_inrd(t_token *tk_node, char *str);
void	tk_outrd(t_token *tk_node, char *str);

/*------------Redir_utirs------------*/
void	printredir(t_redir *red, char *str);
char	*getfilename(char *str, int i, t_redir *rd, t_token *tk, t_data *data);
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
/*int		ft_cd(char **argv, t_data *data);
int		ft_pwd();
*/
/*-----------ft_echo-----------*/
int		ft_echo(char **argv);

/*-----------ft_exit-----------*/
int		ft_atoi(const char *str);

/*----------List_utils----------*/
void	ft_unset(t_list **list, char *ref);
char	**listtoenv(t_list *list);
t_list	*envtolist(char **env);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *n_key, char *n_value);
char	**listtoargv(t_list *lst);
int	ft_lstsize(t_list *lst);

/*-----------ft_export-----------*/
int		ft_strchr(const char *str, char c);

/*-----------ft_itoa------------*/
char	*ft_itoa(int n);

/*----------Str_utils-----------*/
void	ft_putstr_fd(char *s, int fd);
int		ft_isalnum(int c);
int		end_quote(char *str, int i, char c);
int		ft_strchr(const char *str, char c);
int		ft_isspace(char c);

/*------CHILDS------*/
void	ms_exe_childs(t_token *token, t_data *data, int fd[2], int fd_in);
void	ms_check_permision(char *command, t_token *token);

/*------------EXE_REDIR------------------*/
int	ms_init_redir(t_token *token, t_data *data, int *fd, t_token *token_prev);
t_sherpa	*ms_sherpa(t_token *token, t_redir *redir, t_sherpa *sherpa, t_token *token_prev);
int	ms_c_redir(t_token *token, t_redir *redir, t_sherpa *sherpa, t_data *data, int *fd);
int	err_redir(t_sherpa *sherpa, int *fd);
int	e_red_mssg(char *file, int flag);

/*-----------EXECUTE---------*/
void	ms_main_exe(t_token *token, t_data *data);
void ms_commander(t_token *token, t_data *data, int fd[2], int fd_in, t_token *token_prev);
void	ms_fds(t_token *token, t_token *token_prev, t_data *data, int *fd);
void	child_process(t_token *token);

/*------FAKEHDOC--------*/
void	ft_fake_hdoc(t_token *token);

/*----FREE_ARRAY---*/
void	ft_freearray(char **array);

/*---MINI_LOOP----*/
void	mini_loop();

/*----MS_HDOC---*/
void	ms_here_doc(t_token *token, t_data *data, int *fd);
void	ms_hdoc_writer(int *fd, char *line, char *limiter);

/*------------PIPE-------------------*/
void	ms_pipe(t_token *token, t_token *token_prev);

/*----PIPEX_EXECUTE----*/
void	ft_execute(char *argv, char **envp);
char	*find_path(char *cmd, char **envp);
char	*fp_loop(char *path, char *cmd, char **paths, int i);
char	**awk_split(const char *argv, int i);

/*----POST_EXE----*/
void	ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token);

/*-------------TIN_OPENER---------------*/
int	ms_tin_opener(char *argv, int flag, t_token *token, t_data *data, int *fd);

/*-----------UTILS_EXE-----------*/
int	ms_gnl(char **line);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ms_tolower_str(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ms_cmd_nf(char *cmd);
int		ft_isalpha(int c);


/*------BUILTINS------*/
int		ms_builts(t_token *token, t_data *data, t_token *token_prev);
int		bi_print_working_directory(t_data *data);
int		bi_change_dir(t_token *token, t_data *data);
int		bi_echo(t_token *token);
t_list	*find_key(t_list *list, char *n_key);
//int		bi_env(t_list *list);
int		bi_env(t_data *data, t_token *token);
char	**ms_return_env(t_data *data);
int		bi_exit(char **av);
int		bi_unset(t_list *list, char **argv);


/*-------EXPORT------*/
void	add_element_to_env(t_list *list, char *n_key, char *n_value);
void	export_print_declare(t_list *list);
int		bi_export(t_list *list, char **argv);





/*-----------Minishell (MAIN)------------*/
void	mini_loop(t_data *data, t_list *list);
t_data	*data_init(t_list *env);
char	*ft_strdup(const char *s1);

/*--------SIGNAL-------*/
void	ctrl_c_handler(int sig);
void	ctrl_quit_handler(int sig);
void	ctrl_quit_handler_hd(int sig);
void	ctrl_c_handler_hd(int sig);
void setup_signal_handlers(void);
void setup_signal_handlers_hd(void);

/*------PROMPT----*/
/*******************************************************
*This PROMPT is exclusive for 42MALAGA CAMPUS computers*
*******************************************************/
char	*ms_prompt(t_data *data);

#endif