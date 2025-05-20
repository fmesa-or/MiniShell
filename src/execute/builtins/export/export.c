/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/20 14:49:11 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	ft_lstadd_second(t_list **lst, t_list *new)
{
	t_list *tmp;

	tmp = (*lst)->next;
	(*lst)->next = new;
	new->next = tmp;
}
*/

/*Esta funcion busca dentro de la lista donde se encuentra una key
y retorna el nodo en el que esta o null si no lo encuetra*/
/*
t_list	*find_key(t_list *list, char *n_key)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, n_key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
*/

static int	export_is_key_valid(char *key)
{
	int	i;

	i = 0;
	if ((!key) || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_find_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	if (!argv[i])
		return (-1);
	return (i);
}

static int	export_var(t_list *list, char *argv)
{
	int		n;
	char	*value;
	char	*key;

	value = NULL;
	n = export_find_equal(argv);
	if (n != -1)
	{
		value = ft_strdup(&(argv[n + 1]));
		key = ft_substr(argv, 0, n);
	}
	else
		key = ft_strdup(argv);
	if (!export_is_key_valid(key))
	{
		free(key);
		free(value);
		throw_error("ERROR: Invalid identifier\n", NULL, NULL);
		return (1);
	}
	add_element_to_env(list, ft_strdup(key), ft_strdup(value));
	free(key);
	free(value);
	return (0);
}

/******************************************************************************
*This function prints the env to the screen with "declare -x" before each line*
******************************************************************************/
void	export_print_declare(t_list *list)
{
	while (list)
	{
		write(1, "declare -x ", 11);
		write(1, list->key, ft_strlen(list->key));
		write(1, "=\"", 2);
		if (list->value)
			write(1, list->value, ft_strlen(list->value));
		write(1, "\"\n", 2);
		list = list->next;
	}
}

/*********************************************************************
*This function will create and modify keys and their values according*
*to the arguments given.                                             *
*********************************************************************/
int	bi_export(t_list *list, char **argv)
{
	int	i;

	i = 1;
	if (!argv[1])
		export_print_declare(list);
	while (argv[i])
	{
		if (export_var(list, argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
