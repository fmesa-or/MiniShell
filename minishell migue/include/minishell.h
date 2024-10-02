/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:24:16 by jholland          #+#    #+#             */
/*   Updated: 2024/10/02 19:00:21 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

enum	e_token
{
	NONE,
	CMD,
	PIPE,
	GT,
	GGT,
	LT,
	LLT,
	BUIL
};

typedef struct s_all
{
	int					bk_in; //no sabemos
	int					bk_out; //tampoco sabemos
	char				*prog_name; //nombre del progrmama (minishell)
	char				*prompt; //lo que se ve en la terminal "minishel>"
	char				*home; //la ruta del home (raiz)
	char				*user_input; //lo que vamos escribiendo en "la terminal"
	char				**commands; //array con los comandos (como en el pipex)
	struct s_varlist	*exported_list; //aquí almacenamos el enviroment
	char				*pwd; //la dirección en la que nos encontramos actualmente
	int					last_status; //el estado del ultimo comando. (echo $?)
}	t_all;

typedef struct s_varlist
{
	char				*key; //
	char				*value;
	struct s_varlist	*next;
}	t_varlist;

/*****************************************
* < Lee desde un archivo                 *
* > Sobreescribe dentro de un archivo    *
* >> Añade contenido dentro de un archivo*
* << El input es un HEREDOC              *
*****************************************/
typedef struct s_redir
{
	int				type; //el tipo (</<</>/>>)
	char			*file; //el archivo de la redirección (excepto cuando es un HEREDOC que es el limitador)
	struct s_redir	*next; //la siguiente redirección ("< input.txt cat >> output.txt")
}	t_redir;

/*********************************************
*Por cada comando generamos un token (parseo)*
*********************************************/
typedef struct s_token
{
	int				fd[2]; //para la pipe
	int				type; //building, comando normal o pipe (se puede obviar la pipe si no hacemos bonus)
	int				argc; //número de argumentos que tiene el comando
	char			**argv; //el array con los argumentos
	char			*command; //puntero al comando principal (argv[0])
	int				pid; //igual que en el pipex
	struct s_redir	*redir; //lista de redirecciones ("<" "<<" ">" ">>")
	int				last_status; //el estado del último comando que se ejecutó
	struct s_token	*next; //siguiente comando
	struct s_token	*prev; //comando anterior
}	t_token;

// UTILS
void			free_ptr_array(char ***array);
int				same_string(char *str1, char *str2);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(char c);
int				find_equal(char *str);
int				ft_isalnum(char c);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);

// INPUT
char			*user_input(t_all *data);
int				valid_syntax(t_token *tokens, t_all *data);

// ENVIRONMENT
void			create_export_list(t_all *data, char **env);
char			*find_var(t_varlist *list, char *key);
void			free_varlist(t_varlist **lst_ptr);
void			add_element_to_list_export(t_all *data, char *key, char *value);
void			edit_element_to_list_export(t_all *data,
					char *key, char *value);

// PARSING
unsigned int	search_arg_end(char *line);
char			*parsed_allocation(t_all *data, char *str);
char			*parse_arg(t_all *data, char *arg);
unsigned int	*var_lengths(t_all *data, char *str);

// TOKENIZATION
void			tk_add_redir(t_token *node, char **line, t_all *data);
void			tk_set_command(t_token *node, char **line, t_all *data);
void			get_tokens(t_token **tk_list, char *line, t_all *data);
void			free_token_list(t_token **tk_list);
char			*get_arg(t_all *data, char **line);

// BUILTINS
int				is_builtin(char **argv);
int				run_builtin(t_all *data, t_token *l_token);

int				ft_cd(t_all *data, t_token *l_token);
int				ft_echo(char **argv);
int				ft_env(t_all *data);
int				ft_exit(t_all *data, char **argv);
int				ft_export(t_all *data, char **argv);
int				ft_pwd(t_all *data);
int				ft_unset(t_all *data, char **argv);

char			**ft_return_env(t_all *data);

int				ft_ishexadec(char c);
char			hexadec_char(char **str);
int				ft_isoctal(char c);
char			octal_char(char **str);

// EXECUTION
int				init_redir(t_token *l_token);
void			create_pipe(t_token *l_token);
char			*find_path(char *bin, t_all *data);
void			prepare_to_execute(t_all *data, t_token *l_token);
void			execute_child(t_all *data, t_token *l_token);
int				create_heredoc(char *eof);

// OTHERS
int				com_not_found(t_all *data, char **argv_ptr);
int				com_error(t_all *data, char *com, char *arg, char *message);
void			signal_handler(void);
void			sigint_handler(int signum);

#endif