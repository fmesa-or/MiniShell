/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/16 18:39:44 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

/*
*This structure only should be called on commander
*Stores the final redir and all its info
**/
typedef struct s_sherpa
{
	int	typein;
	int	typeout;
	char	*filein;
	char	*fileout;
	bool	hdocflag;
}	t_sherpa;

t_sherpa	ft_sherpa(s_redir *redir);
{
	t_sherpa	sherpa;

	while(redir->next)
	{
		if (redir->type == IN || redir->type == HDOC)
		{
			sherpa->typein = redir->type;
			sherpa->filein = redir->file;
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
	//esto es el piex
	//pid está en data
	//token->redir -> type = IN || file = "input.txt" || next= NULL
	//token->argv -> [0]= ls; [1]=-l; [2]=-a; [3]=NULL

	//ultimo input y ultimo output

	int			filein;
	int			fileout;
	t_sherpa	sherpa;

	sherpa = ft_sherpa(token->redir);

	if (token->type == HDOC)
	{
		
	}
	else
	{
		filout = tin_opener(token->redir->file, 1);
		filein = tin_opener(token->redir->file, 2);
		dup2(filein, STDIN_FILENO);
	}

//neceisto almacenar la info de los redir en una
//estructura para no hacer open y close infinitamente....
/*
	int	i;
	int	fileout;
	int	filein;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		fileout = tin_opener(argv[argc - 1], 0);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		fileout = tin_opener(argv[argc - 1], 1);
		filein = tin_opener(argv[1], 2);
		dup2(filein, STDIN_FILENO);
	}
	while (i < (argc - 2))
		child_process_bonus(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
	wait(NULL);
*/



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

void	ft_execute(t_token token, t_data data)
{

	if (token->command == "exit")
		ft_exit(token->argv);
	if (token->type == BUIL)
		ft_builtin(token->command);
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