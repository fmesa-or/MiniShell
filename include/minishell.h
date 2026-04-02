/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2026/04/02 17:29:04 by fmesa-or         ###   ########.fr       */
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

# define MEM_HASH_SIZE 1031

/*Description for ALLOC FAIL*/
enum e_type
{
	NO_MEMORY = 90,
	DUP_FAIL = 46,
	DUP2_FAIL = 47,
	PIPE_FAIL = 48
};

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

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
*oldpwd			->The last path.                              *
*l_status		->The state of the last command               *
*					(you can see it with echo $? for example) *
*bk_in/out		->BackUp for the standard in and out          *
*file_in/_out	->Last in/out file opened.                    *
*typein/out		->Last type of in/out redirection.            *
*mem_table		->Where we are gonna store the info of mem    *
*fd_table		->Same but for file descriptors               *
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
	int				file_in;
	int				file_out;
	int				typein;
	int				typeout;
	t_mem			*mem_table[MEM_HASH_SIZE];
	int				fd_table[1024];
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
*end_in	->   *missing info, ask rmarin-j*                             *
*file	->The file for the redirection (except when is a HEREDOC (<<),*
*			in that case it's the limit)                              *
*next	->The next redirection ("< input.txt cat >> output.txt")      *
**********************************************************************/
typedef struct s_redir
{
	int				type;
	int				index;
	int				end_in;
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
*command	->Pointer to the main command.                                 *
*argv		->Array with arguments.                                        *
*pid		->Same as in the pipex.                                        *
*l_status	->The state of the last command executed.                      *
*redir		->List of redirections (</<</>/>>).                            *
*av_list	->    *missing info, ask rmarin-j*                             *
***************************************************************************/
typedef struct s_token
{
	int				type;
	int				argc;
	char			*command;
	char			**argv;
	pid_t			pid;
	int				l_status;
	struct s_redir	*redir;
	struct s_list	*av_list;
}	t_token;

/**************************************************
*This structure only should be called on commander*
*Stores the final redir and all its info          *
**************************************************/
typedef struct s_sherpa
{
	int				typein;
	int				typeout;
	char			*filein;
	char			*fileout;
	bool			hdocflag;
}	t_sherpa;

/*-----------------List_Convers------------------*/
char		**listtoenv(t_list *list);
t_list		*envtolist(char **env, t_list *list, t_list *head, char **aux);
char		**listtoargv(t_list *lst);

/*------------freedom-----------*/
void		free_partial_data(t_data *data);
void		free_all_data(t_data *data);
void		free_2ptr(char **array);
void		ft_redirclear(t_redir **red);
void		ft_tokenclear(t_token *tk);
void		ft_envclear(t_list **lst);

/*------------redir------------*/
int			redir_fill(t_token *tk, char *str, int rd_type, int i);
char		*rd_strdel(t_redir *redir, char *str);

/*------------Redir_utirs------------*/
char		*getfilename(char *str, int i, t_redir *rd, t_token *tk);
void		ft_rediradd_back(t_redir **lst, t_redir *new);
int			get_redir(t_token *tk, char *str, int j);
t_redir		*ft_redirlast(t_redir *rd);

/*----------Token_list----------*/
t_token		*tk_list_make(char **pipes, t_list *env, t_data *data);

/*----------Expand-----------*/
char		*expand_var(char *str, t_list *list, t_token *tk);
/*---------Get_Argv---------*/
int			is_cmd(char *av, t_token *tk, t_list *env, t_data *data);
int			is_builtin(t_token *tk, char *av);
int			get_av(t_list **lst, char *str, int j, t_token *tk);

/*-----------Parse-----------*/
int			pipe_iteri(char *str, int i, char c);
t_token		*parse_main(char *str, t_list *list, t_data *data);
int			pipe_count(char *str);

/*-----------Error-----------*/
void		throw_error(const char *str, t_token *tk, t_data *data);

/*-----------Split-----------*/
char		**ft_split(char const *s, char c);
int			ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_countstr(char const *s, char c);
char		**fill_split(char **ptr, char const *s, char c);

/*-----------strCjoin-----------*/
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcjoin(char *s1, char *s2, char c);

/*-----------ft_exit-----------*/
int			ft_atoi(const char *str);

/*----------List_utils----------*/
void		ft_unset(t_list **list, char *ref);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(char *n_key, char *n_value);
int			ft_lstsize(t_list *lst);

/*-----------ft_export-----------*/
int			ft_strchr(const char *str, char c);

/*-----------ft_itoa------------*/
char		*ft_itoa(int n);

/*----------Str_utils-----------*/
void		ft_putstr_fd(char *s, int fd);
int			ft_isalnum(int c);
int			end_quote(char *str, int i, char c, t_token *tk);
int			ft_strchr(const char *str, char c);
int			ft_isspace(char c);

/*------CHILDS------*/
void		ms_exe_childs(t_token *token, t_data *data, int fd[2], int fd_in);
void		ms_check_permision(char *command);

/*------------EXE_REDIR------------------*/
int			ms_init_redir(t_token *token, int *fd, t_token *token_prev);
t_sherpa	*ms_sherpa(t_token *tk, t_redir *re, t_sherpa *sh, t_token *t_prev);
int			ms_c_redir(t_token *token, t_redir *redir, t_sherpa *sherpa,
				int *fd);
int			err_redir(t_sherpa *sherpa);
int			e_red_mssg(char *file);

/*-----------EXECUTE---------*/
void		ms_main_exe(t_token *token, t_data *data, int i);
void		ms_commander(t_token *token, int fd[2], int fd_in,
				t_token *token_prev);
void		ms_fds(t_token *token, t_token *token_prev, int *fd);

/*------FAKEHDOC--------*/
void		ft_fake_hdoc(t_token *token);

/*----MS_HDOC---*/
void		ms_here_doc(t_token *token, t_data *data, int *fd, char *limiter);
void		ms_hdoc_writer(int *fd, char *line, char *limiter);

/*----POST_EXE----*/
void		ms_post_exe(t_data *data, t_token *token_prev,
				t_token *first_token);

/*-------------TIN_OPENER---------------*/
int			ms_tin_opener(char *argv, int flag, t_token *token, int *fd);

/*-----------UTILS_EXE-----------*/
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		*ms_tolower_str(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ms_cmd_nf(char *cmd);
int			ft_isalpha(int c);

/*------BUILTINS------*/
int			ms_builts(t_token *token, t_data *data, t_token *token_prev);
int			bi_print_working_directory(t_data *data);
int			bi_change_dir(t_token *token, t_data *data);
int			bi_echo(t_token *token);
t_list		*find_key(t_list *list, char *n_key);
int			bi_env(t_data *data, t_token *token);
char		**ms_return_env(t_data *data, int i);
int			bi_exit(char **av, long nb);
int			bi_unset(t_list *list, char **argv);

/*-------EXPORT------*/
void		add_element_to_env(t_list *list, char *n_key, char *n_value);
void		export_print_declare(t_list *list);
int			bi_export(t_list *list, char **argv);

/*-----------Minishell (MAIN)------------*/
void		mini_loop(t_data *data, t_list *list);
char		*ft_strdup(const char *s1);

/*--------SIGNAL-------*/
void		ctrl_c_handler(int sig);
void		ctrl_quit_handler(int sig);
void		ctrl_quit_handler_hd(int sig);
void		ctrl_c_handler_hd(int sig);
void		setup_signal_handlers(void);
void		setup_signal_handlers_hd(void);

/*------PROMPT----*/
void		ms_prompt(t_data *data);
char		*p_pwd_sub1(t_list *aux);
char		*p_pwd_sub2(char *old_prompt, char *char_aux, int i, int start);
char		*prompt_comp_first(char *char_aux, char *char_aux2, int i,
				int start);

int			export_var(t_list *list, char *argv);
int			err_argv_command(char **argv);

/*-------MEM-------*/
t_data		*get_pdata(t_data *data);
void		*ft_memset(void *b, int c, int len);
void		alloc_fail(int type);
char		*get_cwd(void);
void		mem_add(void *ptr);
void		mem_delete(void *ptr);
void		mem_clear(void);
void		*smalloc(long bytes);
void		sfree(void *ptr);
void		sfree_all(void);
int			sopen(const char *file, int oflag, int perm);
int			sclose(int fd);
void		sclose_all(void);
int			sdup(int fd);
int			sdup2(int fd1, int fd2);
int			spipe(int *fd);
void		sexit(int code);

/*-----NOT DECLARED!!!!---*/
char		*ft_expand(char *str, int i, t_list *list);
char		*put_lstat(char *str, int i, t_data *data);
char		*ms_get_argv_nquotes(char *str, int *j, char *av, t_token *tk);
char		*ms_quote_loop(char *av, int *j, char *str, t_token *tk);
void		tk_init(t_token *new);
int			str_isspace(char *str);
char		**pipe_separator(char *str, t_data *data);

#endif