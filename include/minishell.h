/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oceanscorelive <oceanscorelive@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:52 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/30 20:35:46 by oceanscorel      ###   ########.fr       */
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
char	*ft_strcjoin(char const *s1, char const *s2, char c);

#endif