/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:28:05 by jholland          #+#    #+#             */
/*   Updated: 2024/04/29 18:11:03 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	same_string(char *str1, char *str2)
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
