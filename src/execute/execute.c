/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/28 14:06:52 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_writer(int *fd, char *line, char *limiter)
{
	int	i;

	i = 5;
	if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		write(1, "> ", 2);
	else if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS); //revisar
	write(fd[1], line, ft_strlen(line));
}


/***********************************************
*1st:	Set the pipe.                          *
*2nd:	Sets the child process and executes it.*
***********************************************/
void	child_process(t_token token)
{
	if (pipe(token->fd) == -1)
		//ERROR
	token->pid = fork();
	if (token->pid == -1)
		//ERROR
	if (pid == 0)
	{
		close(token->fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_execute(token->type, token->env);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
	}
}

/*************************************************************************
*1st:	Starts the pipe.                                                 *
*2nd:	Starts the child process.                                        *
*3rd:	Read from the STDIN with GNL until it finds the limiter.         *
*************************************************************************/
void	ft_here_doc(t_token *token, t_data *data)
{
	pid_t	reader;
	char	*line;

	if (pipe(token->fd) == -1)
		throw_error("Error: Pipe not working.", token, &data);
	reader = fork();
	if (reader == 0)
	{
		close(token->fd[0]);
		write(1, "> ", 2);
		while (ms_gnl(&line))
			ft_writer(token->fd, line, token->redir->file);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
}

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	ft_sherpa(t_redir *redir);
{
	t_sherpa	sherpa;//INICIALIZAR

	sherpa->typein = NULL;
	sherpa->typeout = NULL;
	sherpa->filein = NULL;
	sherpa->fileout = NULL;
	sherpa->hdocflag = false;

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
	}
	if (redir->type == DOUT || redir->type == NDOUT)
	{
		sherpa->typeout = redir->type;
		sherpa->fileout = redir->file;
	}
	if (redir->next)
		sherpa = ft_sherpa(redir->next);
	return (sherpa);
}

void	ms_commander(t_token *token, t_data *data)
{
	//cd Desktop | ls -l | wc -l <input.txt >out.txt >file.txt
	//token[2]->redir (es una lista)-> <input.txt >out.txt >file.txt
	//token[0]->argv[0] -> cd // argv[1] -> Desktop
	//token[1]->argv[0] -> ls // argv[1] -> -l
	//token[2]->argv[0] -> wc // argv[1] -> -l

//tengo que controlar, que si no hay redir y NECESITO un out o un in, tengo que tener en cuenta las salidas y entradas de la pipe

	int			filein;
	int			fileout;
	t_sherpa	sherpa;

	if (token->type != CMD && token->type != BUIL)
		return ;
	else
	{
		token->pid = fork();
		//pipe??
		if (token->type == BUIL)
			token->l_status = //run_builtin;
		if (token->redir)
			sherpa = ft_sherpa(token->redir);
		if (sherpa->hdocflag == true && sherpa->typein != HDOC)
		{
			ft_fake_hdoc(token);
		/*	if (token->type == BUIL)
			{
				//run_builtin;
				exit(0);
			}
			else if (token->type == CMD)
			{
				fileout = tin_opener(sherpa->fileout, 1);
				filein = tin_opener(sherpa->filein, 2);
				dup2(filein, STDIN_FILENO);
			}
		*/
		}
		if (sherpa->typein == HDOC)
				ft_here_doc(token, &data);
		else
		{
			fileout = tin_opener(sherpa->fileout, 1);
			filein = tin_opener(sherpa->filein, 2);
			dup2(filein, STDIN_FILENO);
		}
	}





	/*
	Esto puede ser una función recursiva que se llame a si misma en caso de
	existir un token posterior, por lo que se ejecutan del último al primero.

	Lo importante es ir manejando los fd para que cada comando desemboque en el anterior.
	
	EJEMPLO:
	if (token->next)
		ms_kindergarden(token->next)
	ft_execute(...);
	*/

	dup2(fileout, STDOUT_FILENO);
	/*tenemos qu ejecutar el último comando aquí*/
	ft_execute(token->command, &(token->env));
	wait(NULL);
}

void	ft_main_exe(t_token *token, t_data *data)
{
/*V0.2*/
	t_token	*token_prev;

	While(token->type != NONE)
	{
		ms_commander(token, data);
		//more
		token++;
	}

/* V0.1

	if (token->command == "exit")//por que está aquí?? No lo recuerdo(Paco)
		ft_exit(token->argv);
	if (token->type == BUIL)
		ft_builtin(token, data);
	if (token->type == CMD)
		ft_commander(&token, &data);
*/
	//1-Existe un comando después? -> Hacer una pipe. Modificando el fd.
	

	//2-Redirecciones ->



	//3-Hacemos fork si existe un comando despues



	//4-Hacer dup2 de los fd y close.



	//5-Comprobar tipo de comando


	/****Aquí cambia para los built in****/
	//6-Ejecutar
	//7-Del 1 al 7 en el siguiente.

}