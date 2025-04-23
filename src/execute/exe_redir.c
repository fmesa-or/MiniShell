/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:22:05 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/23 12:15:05 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_red_mssg(char *file, int flag)
{
	if (flag == 0)
	{
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": Permission denied\n", 21);
		return (1);
	}
	else if (flag == 1)
	{
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	write(2, "Internal ERROR: flag not given.\n", 32);
	return (-1);
}

int	err_redir(t_sherpa *sherpa, int *fd)
{
	if (!access(sherpa->filein, F_OK) && access(sherpa->filein, R_OK)
			&& sherpa->typein == IN)
		return (e_red_mssg(sherpa->filein, 0));
	if (!access(sherpa->fileout, F_OK) && access(sherpa->fileout, W_OK)
			&& (sherpa->typeout != NONE))
		return (e_red_mssg(sherpa->fileout, 0));
	if (fd[0] < 0 && (sherpa->typein == IN))
		return (e_red_mssg(sherpa->filein, 1));
	if (fd[1] < 0 && (sherpa->typeout != NONE))
		return (e_red_mssg(sherpa->fileout, 1));
	return (0);
}

static t_sherpa *ms_sherpa_init(t_sherpa *sherpa)
{
	sherpa = malloc(sizeof(t_sherpa));
	if (!sherpa)
		return (NULL);
	sherpa->typein = NONE;
	sherpa->typeout = NONE;
	sherpa->filein = NULL;
	sherpa->fileout = NULL;
	sherpa->hdocflag = false;
	return (sherpa);
}

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	*ms_sherpa(t_token *token, t_redir *redir, t_sherpa *sherpa)
{
	static int		i= 0;

	i++;
	printf(CI"SHERPA:%d\n"RES, i);
	if (!sherpa)
		return (NULL);
	if (redir->type == IN || redir->type == HDOC)
	{
		sherpa->typein = redir->type;
		if (redir->type == IN)
			sherpa->filein = redir->file;
		else
		{
			sherpa->filein = NULL;
			sherpa->hdocflag = true;
		}
		printf("sherpa->filein = %s\n", sherpa->filein);
	}
	if (redir->type == DOUT || redir->type == NDOUT)
	{
		sherpa->typeout = redir->type;
		sherpa->fileout = redir->file;
		printf("sherpa->fileout = %s\n", sherpa->fileout);
	}
//	printf("redir->next = %p\n", redir->next);
//	printf("redir->next->file = %s\n", redir->next->file);//rompe
//	printf("redir->next->index = %d\n", redir->next->index);//rompe
//	printf("redir->next->next = %p\n", redir->next->next);//rompe
//	printf("redir->next->type = %d\n", redir->next->type);

	if (redir->next)
		sherpa = ms_sherpa(token, redir->next, sherpa);
	return (sherpa);
}

int	ms_c_redir(t_token *token, t_redir *redir, t_sherpa *sherpa, t_data *data, int *fd)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	ret = err_redir(sherpa, fd);
	if (ret == 0)
	{
		fd[1] = ms_tin_opener(sherpa->fileout, sherpa->typeout, token, data, fd);
		fd[0] = ms_tin_opener(sherpa->filein, sherpa->typein, token, data, fd);
	}
	//creo que este if no es necesaria
/*	if (redir->next && !ret)
	{
		if (ms_c_redir(token, redir->next, sherpa, data))
			ret = 1;
	}
*/
//tengo dudas de si esto va aquí o antes
	if (sherpa->hdocflag == true && sherpa->typein != HDOC)
		ft_fake_hdoc(token);
	return (ret);
}

int	ms_init_redir(t_token *token, t_data *data, int *fd)
{
	t_redir		*redir;
	t_sherpa	*sherpa;

	sherpa = NULL;
	sherpa = ms_sherpa_init(sherpa);
	dprintf(2, "Init REDIR\n");
	if (!(token->redir))
		return (0);
	if (token->type == BUIL || token->type == CMD)
	{
		dprintf(2, "Avemus BUIL or CMD\n");
		redir = token->redir;
		dprintf(2, "redir = %s\n", redir->file);
		return (ms_c_redir(token, redir, ms_sherpa(token, redir, sherpa), data, fd));
	}
	return (0);
}
