/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/01 14:15:04 by rmarin-j         ###   ########.fr       */
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

typedef struct s_list
{
	char			*key;
	char			*value;
	struct t_list	*next;
}	t_list;

/*-----------split-----------*/
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
/*-----------strjoin-----------*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcjoin(char const *s1, char const *s2, char c);

/*----------list_utils----------*/
t_list  *ft_unset(t_list *list, char *ref);
char **listtoenv(t_list *list);
t_list  *envtolist(char **env);

#endif