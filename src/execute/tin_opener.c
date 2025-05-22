/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tin_opener.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:48:54 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 12:10:24 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************
*Opens the file                                      *
*O_WRONLY = Opens the file in writing mode.          *
*O_CREAT  = If the file doesn't exist, it creates it.*
*O_APPEND = Adds the content if the file exists.     *
*O_TRUNC  = Truncates to zero bytes before writting. *
*O_RDONLY = Opens the file in read mode.             *
*			Deleting any previous content.           *
*****************************************************/
int	ms_tin_opener(char *argv, int flag, t_token *token, t_data *data, int *fd)
{
	int	file;

	file = 0;
	if (flag == NDOUT)
		file = sopen(argv, O_WRONLY | O_CREAT | O_APPEND, 0777, data);
	else if (flag == DOUT)
		file = sopen(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777, data);
	else if (flag == IN)
		file = sopen(argv, O_RDONLY, 0777, data);
	else if (flag == HDOC)
		ms_here_doc(token, data, fd, argv);
	if (file == -1)
		throw_error(RD"Error: No such file or directory\n"RES, NULL, NULL);
	return (file);
}