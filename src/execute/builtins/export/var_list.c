/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:03:32 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 22:15:04 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*new_var_list_node(char *key, char *value)
{
	t_list	*node;

	node = (t_list *)smalloc(sizeof(t_list));
	if (!node)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);
		sexit(errno);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

static int	same_string(char *str1, char *str2)
{
	unsigned int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] != str2[i])
		return (0);
	return (1);
}

void	add_element_to_env(t_list *list, char *n_key, char *n_value)
{
	t_list	*head;

	head = list;
	while (head)
	{
		if (same_string(head->key, n_key))
		{
			sfree(head->value);
			sfree(n_key);
			head->value = n_value;
			return ;
		}
		else if (!head->next)
		{
			head->next = new_var_list_node(n_key, n_value);
			return ;
		}
		head = head->next;
	}
	if (!head)
	{
		list = new_var_list_node(n_key, n_value);
		return ;
	}
}
