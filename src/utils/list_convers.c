/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_convers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:59:36 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 23:32:31 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup_quo(const char *s1, t_data *data)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = (char *) smalloc(sizeof(char) * (ft_strlen(s1)-1), data);
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

char	**listtoargv(t_list *lst, t_data *data)
{
	char	**av;
	int		i;

	i = 0;
	av = smalloc(sizeof(char *) * (ft_lstsize(lst) + 1), data);
	if (!av)
	{
		throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		sexit(errno, data);
	}
	while (lst)
	{
		if (lst->value && (lst->value)[0] == 'q')
			av[i] = ft_strdup_quo(lst->key, data);
		else
			av[i] = ft_strdup(lst->key, data);
		i++;		
		lst = lst->next;
	}
	av[i] = NULL;
	return(av);
}

char **listtoenv(t_list *list, t_data *data)
{
	char	**env;
	int	 i;
	t_list	*head;

	i = 0;
	head = list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = smalloc(sizeof(char *) * i + 1, data);
	if (!env)
	{
		throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		sexit(errno, data);
	}
	i = 0;
	list = head;
	while (list)
	{
		env[i] = ft_strcjoin(list->key, list->value, '=', data);
		i++;
		list = list->next;
	}
	env[i] = NULL;
	return(env);
}

static void	env_free_2ptr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*t_list	*mig_lstnew(char *n_key, char *n_value)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	if (!node)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		exit(errno);
	}
	node->key = n_key;
	node->value = n_value;
	node->next = NULL;
	return (node);
}*/

t_list	*envtolist(char **env)
{
	t_list *list;
	t_list *head;
	char	**aux;
	int	 i;

	if (!env || !*env)
		return (NULL);
	list = NULL;
	head =NULL;
	aux = NULL;
	i = 0;
	while (env[i])
	{
		//Hay que revisar las fugas de memoria, ya que estamos reasignando memoria 
		//	a una memoria ya reservada previamente sin liberarla.
		//	La prueba aquí.
		//		if (i > 0)
		//			printf("%s%s\n", aux[0], aux[1]);
		aux = mig_split(env[i], '=');
		if (!aux || !aux[0])
		{
			env_free_2ptr(aux);
			throw_error("ERROR: Split failed.", NULL, NULL);
		}
		if (list == NULL)
		{
			list = mig_lstnew(aux[0],aux[1]);
			head = list;
		}
		else if (env[i + 1])
		{
			list->next =mig_lstnew(aux[0],aux[1]);
			list = list->next;
		}
		i++;
	}
	env_free_2ptr(aux);
	return (head);
}
