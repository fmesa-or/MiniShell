/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tras_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:41:48 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/26 17:42:30 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup_quo(const char *s1)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = (char *) malloc (sizeof(char) * (ft_strlen(s1)-1));
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
char **listtoargv(t_list *lst)
{
	char	**av;
	int		i;

	i = 0;
	av = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
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
    return(av);
}

char **listtoenv(t_list *list)
{
    char    **env;
    int     i;
	t_list	*head;

    
    i = 0;
	head = list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = malloc(sizeof(char *) * i + 1);
	if (!env)
		throw_error("ERROR: ", NULL, NULL);
	i = 0;
	list = head;
    while (list)
    {
        env[i] = ft_strcjoin(list->key, list->value, '=');
        i++;
        list = list->next;
    }
	env[i] = NULL;
    return(env);
}

t_list	*envtolist(char **env)
{
    t_list *list;
	t_list *head;
    char    **aux;
    int     i;

	if (!env || !*env)
		return (NULL);
	list = NULL;
	head = NULL;
	aux = NULL;
	i = 0;
    while (env[i])
    {
        aux = ft_split(env[i], '=');
		if (list == NULL)
		{
			list =ft_lstnew(aux[0],aux[1]);
			head = list;
		}
		else
		{
			list->next =ft_lstnew(aux[0],aux[1]);
        	list = list->next;
		}
        i++;
    }
	free_2ptr(aux);
	return (head);
}
