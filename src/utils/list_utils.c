/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/25 14:16:20 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion elimina un nodo de nuestra lista, q necesita
q la pasemos con &, ya que usa doble puntero*/

void	ft_unset(t_list **list, char *ref)
{
	t_list  *aux;
	t_list	*prev;
	aux = *list;
 	if (ft_strcmp((*list)->key, ref) == 0)
	{
		*list =(*list)->next;
		free(aux->value);
		free(aux->key);
		free(aux);
		return ;
	}
	while (aux && ft_strcmp(aux->key, ref) != 0)
	{
		prev = aux;
		aux = aux->next;
	}
	if (aux && ft_strcmp(aux->key, ref) == 0)
	{
		prev->next = aux->next;
		free(aux->value);
		free(aux->key);
		free(aux);
	}
}
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
char	**listtoargv(t_list *lst)
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
		aux = ft_split(env[i], '=');
			printf("%s%s\n", aux[0], aux[1]);

		if (!aux || (!aux[0] || !aux[1]))
		{
			free_2ptr(aux);
			throw_error("ERROR: Split failed.", NULL, NULL);
		}
		if (list == NULL)
		{
			list =ft_lstnew(aux[0],aux[1]);
			head = list;
		}
		else if (env[i + 1])
		{
			list->next =ft_lstnew(aux[0],aux[1]);
			list = list->next;
		}
		i++;
	}
	free_2ptr(aux);
	return (head);
}

/*Esta funcion añade un nodo nuevo al final de un t_list */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return;
	}
	while (current && current->next)
		current = current->next;
	current->next = new;
}


t_list	*ft_lstnew(char *n_key, char *n_value)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->key = n_key;
	node->value = n_value;
	node->next = NULL;
	return (node);
}