/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:46:13 by jholland          #+#    #+#             */
/*   Updated: 2024/04/29 18:51:18 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c);

unsigned int	string_end(char *str)
{
	unsigned int	end;
	char			quote;

	end = 0;
	while (str[end] && ft_isspace(str[end]))
		end++;
	quote = '\0';
	while (str[end] && (quote || !ft_isspace(str[end])))
	{
		if (quote && str[end] == quote)
			quote = '\0';
		else if (!quote && (str[end] == '"' || str[end] == '\''))
			quote = str[end];
		end++;
	}
	return (end);
}
