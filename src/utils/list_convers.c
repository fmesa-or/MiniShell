/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_convers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:59:36 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/29 18:50:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup_quo(const char *s1)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = (char *) smalloc(sizeof(char) * (ft_strlen(s1)-1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 1;
	while (j < (ft_strlen(s1) - 1))
	{
		ptr[i] = s1[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**listtoargv(t_list *lst)
{
	char	**av;
	int		i;

	i = 0;
	av = smalloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!av)
	{
		throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, NULL);
		sexit(errno);
	}
	while (lst)
	{
		if (lst->value && (lst->value)[0] == 'q')
			av[i] = ft_strdup_quo(lst->key);
		else
			av[i] = ft_strdup(lst->key);
		i++;
		lst = lst->next;
	}
	av[i] = NULL;
	return (av);
}

static void	listtoenv_error(void)
{
	throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, NULL);
	sexit(errno);
}

char	**listtoenv(t_list *list)
{
	char	**env;
	int		i;
	t_list	*head;

	i = 0;
	head = list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = smalloc(sizeof(char *) * i + 1);
	if (!env)
		listtoenv_error();
	i = 0;
	list = head;
	while (list)
	{
		env[i] = ft_strcjoin(list->key, list->value, '=');
		i++;
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}
