/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/18 13:01:51 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"



void	ft_writer(int *fd, char *line, char *limiter)
{
	int	i;

	i = 5;
	if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		write(1, "> ", 2);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS);
	write(fd[1], line, ft_strlen(line));
}

/*************************************************************************
*1st:	Starts the pipe.                                                 *
*2nd:	Starts the child process.                                        *
*3rd:	Read from the STDIN with GNL until it finds the limiter.         *
*************************************************************************/
void	ft_here_doc(t_token token)
{
	pid_t	reader;
	char	*line;

	if (pipe(token->fd) == -1)
		//ERROR
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		write(1, "> ", 2);
		while (get_next_line_pipex(&line))
			ft_writer(token->fd, line, token->hdoc);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
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



/*
*This structure only should be called on commander
*Stores the final redir and all its info
**/
typedef struct s_sherpa
{
	int		typein;
	int		typeout;
	char	*filein;
	char	*fileout;
	bool	hdocflag;
}	t_sherpa;

/**********************************************************
*Fills t_sherpa data structure info with the t_redir list.*
**********************************************************/
t_sherpa	ft_sherpa(t_redir *redir);
{
	t_sherpa	sherpa;

	while(redir->next)
	{
		if (redir->type == IN || redir->type == HDOC)
		{
			sherpa->typein = redir->type;
			if (redir->type == IN)
				sherpa->filein = redir->file;
			else
				sherpa->filein = NULL;
		}
		if (redir->type == HDOC)
			sherpa->hdocflag = true;
		if (redir->type == DOUT || redir->type == NDOUT)
		{
			sherpa->typeout = redir->type;
			sherpa->fileout = redir->file;
		}
		redir = redir->next;
	}
	return(sherpa);
}

void	ft_commander(t_token *token, t_data *data)
{
	//token->redir -> type = IN || file = "input.txt" || next= NULL
	//token->argv -> [0]= ls; [1]=-l; [2]=-a; [3]=NULL

	int			filein;
	int			fileout;
	t_sherpa	sherpa;

	sherpa = ft_sherpa(token->redir);

	if (sherpa->hdocflag == true)
	{
		//hace sus cositas con el get_next_line para mostrar en pantalla
		if (sherpa->typein == HDOC)
			//lo mínimo que entra en bash = "<< LIMITADOR"
			ft_here_doc(token);
		else
		{
			//Deberá comportarse como si tuviera un HDOC,
			//pero luego ejecutará con el último INPUT
			//Por lo que escribiremos en pantalla de forma normal,
			//pero luego no servirá para ejecutar.
			ft_fake_hdoc(token);
			fileout = tin_opener(sherpa->fileout, 1);
			filein = tin_opener(sherpa->filein, 2);
			dup2(filein, STDIN_FILENO);
		}
		//Esto se debe a que bash muestra en pantalla la opción de
		//escribir en el terminar dando igual cual sea la última redirección,
		//siempre que aparezca "<<", pero ejecutará como input solo la última.
	}
	else
	{
		fileout = tin_opener(sherpa->fileout, 1);
		filein = tin_opener(sherpa->filein, 2);
		dup2(filein, STDIN_FILENO);
	}

	//Probablemente aquí necesitemos una forma de llamar a ejecutar lo que
	//viene a continuación, ya que excev cierra una vez termina de ejecutar.
	//En el pipex se llama al proceso hijo, pero tengo que ver como
	//integrar esto aquí.
	/*
	El ejemplo de lo que podemos necesitar sería algo así:
	
	while ("una forma de controlar si hay otro comando a continuación")
		child_process(primer cmd y el resto en una iteración, envp);
	*/

	dup2(fileout, STDOUT_FILENO);
	ft_execute(token->type/*tenemos qu eejecutar el último comando aquí*/, token->env);
	wait(NULL);
}

void	ft_builtin(char *command)
{
	if export
	if unset
	if cd
	if pwd
	if env
	if echo
}

void	ft_main_exe(t_token token, t_data data)
{

	if (token->command == "exit")
		ft_exit(token->argv);
	if (token->type == BUIL)
		ft_builtin(token, data);
	if (token->type == CMD)
		ft_commander(token, data);

	//1-Existe un comando después? -> Hacer una pipe. Modificando el fd.
	

	//2-Redirecciones ->



	//3-Hacemos fork si existe un comando despues



	//4-Hacer dup2 de los fd y close.



	//5-Comprobar tipo de comando


	/****Aquí cambia para los built in****/
	//6-Ejecutar
	//7-Del 1 al 7 en el siguiente.

}