/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:29:14 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:20 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_export(t_all *data)
{
	t_varlist	*list;

	list = data->exported_list;
	while (list)
	{
		write(1, "declare -x ", 11);
		write(1, list->key, ft_strlen(list->key));
		if (list->value)
		{
			write(1, "=", 1);
			write(1, list->value, ft_strlen(list->value));
		}
		write(1, "\n", 1);
		list = list->next;
	}
	return (1);
}

static int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_single(t_all *data, char *arg)
{
	char	*key;
	char	*value;

	value = NULL;
	if (find_equal(arg) != -1)
	{
		value = ft_strdup(&(arg[find_equal(arg) + 1]));
		key = ft_substr(arg, 0, find_equal(arg));
	}
	else
		key = ft_strdup(arg);
	if (!is_valid_key(key))
	{
		free(key);
		free(value);
		write(2, " not a valid identifier\n", 25);
		return (1);
	}
	add_element_to_list_export(data, ft_strdup(key), ft_strdup(value));
	free(key);
	free(value);
	return (0);
}

int	ft_export(t_all *data, char **argv)
{
	int		i;

	i = 1;
	if (!argv[1])
		ft_print_export(data);
	while (argv[i])
	{
		if (export_single(data, argv[i]))
			return (1);
		i++;
	}
	return (0);
}
