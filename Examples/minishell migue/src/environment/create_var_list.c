/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:52:58 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:21 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_varlist	*new_var_list_node(char *key, char *value)
{
	t_varlist	*node;

	node = malloc(sizeof(t_varlist));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	edit_element_to_list_export(t_all *data, char *key, char *value)
{
	t_varlist	*head;

	head = data->exported_list;
	while (head)
	{
		if (same_string(head->key, key))
		{
			free(head->value);
			free(key);
			head->value = value;
			return ;
		}
		head = head->next;
	}
}

void	add_element_to_list_export(t_all *data, char *key, char *value)
{
	t_varlist	*head;

	head = data->exported_list;
	while (head)
	{
		if (same_string(head->key, key))
		{
			free(head->value);
			free(key);
			head->value = value;
			return ;
		}
		else if (!head->next)
		{
			head->next = new_var_list_node(key, value);
			return ;
		}
		head = head->next;
	}
	if (!head)
	{
		data->exported_list = new_var_list_node(key, value);
		return ;
	}
}

void	create_export_list(t_all *data, char **env)
{
	unsigned int		i;
	char				*value;
	char				*key;

	i = 0;
	while (env[i])
	{
		if (find_equal(env[i]) == -1)
		{
			key = ft_strdup(env[i]);
			value = NULL;
		}
		else
		{
			value = ft_strdup(&(env[i][find_equal(env[i]) + 1]));
			key = ft_substr(env[i], 0, find_equal(env[i]));
		}
		add_element_to_list_export(data, key, value);
		i++;
	}
}

void	free_varlist(t_varlist **lst_ptr)
{
	t_varlist	*list;
	t_varlist	*next;

	list = *lst_ptr;
	while (list)
	{
		next = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = next;
	}
	*lst_ptr = NULL;
}
