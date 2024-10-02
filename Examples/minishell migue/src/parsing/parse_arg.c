/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:41:18 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:25 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *str)
{
	unsigned int	i;

	i = 0;
	if (str && str++[i] == '$')
	{
		if (str[i] == '?')
			return (ft_substr(str, 0, 1));
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	else
		return (NULL);
	return (ft_substr(str, 0, i));
}

unsigned int	*var_lengths(t_all *data, char *str)
{
	char			*key;
	char			*value;
	unsigned int	*lengths;

	lengths = malloc(sizeof(unsigned int) * 2);
	key = get_key(str);
	lengths[0] = ft_strlen(key);
	if (*key == '?')
		value = ft_itoa(data->last_status);
	else
		value = find_var(data->exported_list, key);
	lengths[1] = ft_strlen(value);
	free(key);
	free(value);
	return (lengths);
}

static void	insert_value(t_all *data, char	**parsed_arg,
	char **arg, unsigned int *index)
{
	char			*value;
	unsigned int	j;
	char			*key;
	unsigned int	*lengths;

	key = get_key(*arg);
	lengths = var_lengths(data, *arg);
	if (*key == '?')
		value = ft_itoa(data->last_status);
	else
		value = find_var(data->exported_list, key);
	free(key);
	*arg += lengths[0];
	j = 0;
	while (j < lengths[1])
		(*parsed_arg)[(*index)++] = value[j++];
	free(lengths);
	free(value);
}

void	insert_all(t_all *data, char **arg, char *parsed_arg,
			unsigned int *index)
{
	static char	quoted = '\0';
	static int	esc = 0;

	if (!esc && !quoted && (**arg == '\"' || **arg == '\''))
		quoted = **arg;
	else if (!esc && quoted && quoted == **arg)
		quoted = '\0';
	else if (!esc && quoted != '\'' && **arg == '$')
		insert_value(data, &parsed_arg, arg, index);
	else if (!esc && !quoted && **arg == '\\')
		esc = 1;
	else
	{
		esc = 0;
		parsed_arg[(*index)++] = **arg;
	}
	(*arg)++;
}

char	*parse_arg(t_all *data, char *arg)
{
	char			*parsed_arg;
	unsigned int	index;

	if (!arg)
		return (NULL);
	parsed_arg = parsed_allocation(data, arg);
	index = 0;
	while (*arg)
		insert_all(data, &arg, parsed_arg, &index);
	parsed_arg[index] = '\0';
	return (parsed_arg);
}
