/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:22:05 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/05 17:04:43 by rmarin-j         ###   ########.fr       */
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
/*
*Checks the access to the filein and the fileout and the file descriptors
*/
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
	{
		throw_error("ERROR: malloc failed in sherpa", NULL, NULL);//esto en verdad deberiamos de poder pasarle el data y eso para liberar
		exit(errno);
	}
	sherpa->typein = NONE;
	sherpa->typeout = NONE;
	sherpa->filein = NULL;
	sherpa->fileout = NULL;
	sherpa->hdocflag = false;
	return (sherpa);
}

/****************************************
*Returns "argv", adding "new" at the end*
****************************************/
static char	**ms_red_argv(char **argv, char *new)
{
	int	i;
	char	**newarray;

	i = 0;
	if (!argv[0])
		return (NULL);//cambiar por un error
	while (argv[i])
		i++;
	newarray = (char **)malloc(sizeof(char *) * i + 2);
	if (!newarray)
	{
		throw_error("ERROR: malloc failed in ms_red_argv", NULL, NULL); //esto habria q pasarle tambien el data
		exit (errno);
	}
	i = 0;
	while (argv[i])
	{
		newarray[i] = argv[i];
		i++;
	}
	newarray[i] = ft_strdup(new);
	if (!newarray[i]) // Verifica si strdup falló
	{
		free(newarray); // Libera la memoria asignada
		return (NULL); // Cambiar por un error
	}
	newarray[i + 1] = NULL;
//	free_2ptr(argv);//revisar leaks de memoria
	return(newarray);
}

/*******************************************************************
*Checks if the command is wc, cat or grep to adapt the input redir.*
*******************************************************************/
static void	ms_redin_except(t_token *token, t_sherpa *sherpa)
{
	if ((ft_strcmp(token->argv[0], "wc") == 0) || (ft_strcmp(token->argv[0], "cat") == 0) || (ft_strcmp(token->argv[0], "grep") == 0))
	{
		//añade al final
		token->argv = ms_red_argv(token->argv, sherpa->filein);
	}
//	else if (ft_strcmp(token->argv[0], "grep") == 0)
//		token->argv = ms_red_argv(token->argv, sherpa->filein);
}

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	*ms_sherpa(t_token *token, t_redir *redir, t_sherpa *sherpa, t_token *token_prev)
{
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
//		dprintf(2, "sherpa->filein = %s\n", sherpa->filein);
	}
	if (redir->type == DOUT || redir->type == NDOUT)//>/>>
	{
		sherpa->typeout = redir->type;
		sherpa->fileout = redir->file;
		printf("sherpa->fileout = %s\n", sherpa->fileout);
	}
	if (redir->next)
		sherpa = ms_sherpa(token, redir->next, sherpa, token_prev);
	else if (sherpa->typein == IN && !(token->argv[1]))
		ms_redin_except(token, sherpa);
	return (sherpa);
}
/*
*
*/
int	ms_c_redir(t_token *token, t_redir *redir, t_sherpa *sherpa, t_data *data, int *fd)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	data->typein = sherpa->typein;
	data->typeout = sherpa->typeout;
	ret = err_redir(sherpa, fd);
	if (ret == 0)
	{
//		if (data->typeout)
			data->file_out = ms_tin_opener(sherpa->fileout, data->typeout, token, data, fd);
//		if (!(sherpa->filein && (ft_strcmp(token->argv[0], "wc") == 0 && token->argv[2])))
			data->file_in = ms_tin_opener(sherpa->filein, data->typein, token, data, fd);
//		dup2(fd[0], STDIN_FILENO);
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

int	ms_init_redir(t_token *token, t_data *data, int *fd, t_token *token_prev)
{
	t_redir		*redir;
	t_sherpa	*sherpa;

	sherpa = NULL;
//	dprintf(2, "Init REDIR\n");
	if (!(token->redir))
		return (0);
	if (token->type == BUIL || token->type == CMD)
	{
		sherpa = ms_sherpa_init(sherpa);
//		dprintf(2, "Avemus BUIL or CMD\n");
		redir = token->redir;
//		dprintf(2, "redir = %s\n", redir->file);
		return (ms_c_redir(token, redir, ms_sherpa(token, redir, sherpa, token_prev), data, fd));
	}
	return (0);
}
