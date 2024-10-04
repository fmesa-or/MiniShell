/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/04 14:01:58 by rmarin-j         ###   ########.fr       */
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

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

/*-----------Error-----------*/
void	throw_error(const char *str);
int		close_quote(char *str, char c);
/*-----------Split-----------*/
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
/*-----------strCjoin-----------*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcjoin(char *s1, char *s2, char c);

/*-----------Builts_in-----------*/
void	ft_env(t_list *list);
void 	ft_pwd(t_list *list);
/*----------List_utils----------*/
t_list  *ft_unset(t_list *list, char *ref);
char 	**listtoenv(t_list *list);
t_list  *envtolist(char **env);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *n_key, char *n_value);
/*-----------ft_export-----------*/
t_list	*find_key(t_list *list, char *n_key);
int ft_strchr(const char *str, char c);
void    ft_voidexport(t_list *list);
int	ft_export(t_list *list, char *n_key);

#endif