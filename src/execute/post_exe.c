/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:54:52 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/20 19:10:39 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern int	g_sig;  ??????
static void ms_pilatos(t_token *tokens)
{
    int i = 0;

    // Encontrar el último token
    while (tokens[i].type != NONE)
        i++;
    i--;

    // Matar todos los procesos hijos excepto el último
    while (i >= 0)
    {
        if (tokens[i].pid > 0)
        {
            printf("Matando proceso hijo PID: %d\n", tokens[i].pid);
            kill(tokens[i].pid, SIGKILL);
        }
        i--;
    }
}


/*    V0.1
static void	ms_pilatos(t_token *tokens)
{
	int	i;

	i = 0;
	while(tokens[i].type != NONE)
		i++;
	i--;
	while (i >= 0)
	{
		if (tokens[i].pid > 0)
			kill(tokens[i].pid, SIGKILL);
		i--;
	}
}*/


/*
*token_prev es el último token
*/
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    // Iterar sobre todos los tokens y esperar a cada proceso hijo
    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
            dprintf(2, "Esperando proceso PID: %d\n", current->pid);
			dprintf(2, "fd[0]: %d fd[1]: %d\n", current->fd[0], current->fd[1]);
			dprintf(2, "post_exe command: %s\n", current->command);
            if (waitpid(current->pid, &status, 0) == -1)
            {
                perror("Error en waitpid");
            }
            else
            {
                dprintf(2, "Proceso PID: %d terminado con estado: %d command: %s\n", current->pid, status, current->command);

                // Actualizar el estado de salida del último proceso
                if (WIFEXITED(status))
                    data->l_status = WEXITSTATUS(status);
            }
        }

        // Cerrar descriptores de archivo si son pipes
        if (current->fd[0] >= 0)
        {
            printf("Cerrando fd[0]: %d\n", current->fd[0]);
            close(current->fd[0]);
            current->fd[0] = -1; // Marcar como cerrado
        }
        if (current->fd[1] >= 0)
        {
            printf("Cerrando fd[1]: %d\n", current->fd[1]);
            close(current->fd[1]);
            current->fd[1] = -1; // Marcar como cerrado
        }

        current++;
    }



    // Matar todos los procesos hijos excepto el último
    ms_pilatos(first_token);

    // Restaurar los descriptores de archivo estándar
    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);

    // Marcar el último token como NONE
    token_prev->type = NONE;

    // Esperar a cualquier proceso hijo restante
    while (waitpid(-1, &status, WNOHANG) > 0)
    {
        printf("Esperando proceso hijo restante...\n");
    }

	
/*   V0.8
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    // Iterar sobre todos los tokens y esperar a cada proceso hijo
    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
            printf("Esperando proceso PID: %d\n", current->pid);
            if (waitpid(current->pid, &status, 0) == -1)
            {
                perror("Error en waitpid");
            }
            else
            {
                printf("Proceso PID: %d terminado con estado: %d\n", current->pid, status);

                // Actualizar el estado de salida del último proceso
                if (WIFEXITED(status))
                    data->l_status = WEXITSTATUS(status);
            }
        }

        // Cerrar descriptores de archivo si son pipes
        if (current->fd[0] > 0)
        {
            printf("Cerrando fd[0]: %d\n", current->fd[0]);
            close(current->fd[0]);
            current->fd[0] = -1; // Marcar como cerrado
        }
        if (current->fd[1] > 0)
        {
            printf("Cerrando fd[1]: %d\n", current->fd[1]);
            close(current->fd[1]);
            current->fd[1] = -1; // Marcar como cerrado
        }

        current++;
    }

    // Restaurar los descriptores de archivo estándar
    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);

    // Matar todos los procesos hijos excepto el último
    ms_pilatos(first_token);

    // Marcar el último token como NONE
    token_prev->type = NONE;

    // Esperar a cualquier proceso hijo restante
    while (waitpid(-1, &status, WNOHANG) > 0)
    {
        printf("Esperando proceso hijo restante...\n");
    }
*/

/*    V0.7
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    // Iterar sobre todos los tokens y esperar a cada proceso hijo
    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
            printf("Esperando proceso PID: %d\n", current->pid);
            if (waitpid(current->pid, &status, 0) == -1)
            {
                perror("Error en waitpid");
            }
            else
            {
                printf("Proceso PID: %d terminado con estado: %d\n", current->pid, status);

                // Actualizar el estado de salida del último proceso
                if (WIFEXITED(status))
                    data->l_status = WEXITSTATUS(status);
            }
        }

        // Cerrar descriptores de archivo si son pipes
        if (current->fd[0] > 0)
        {
            printf("Cerrando fd[0]: %d\n", current->fd[0]);
            close(current->fd[0]);
        }
        if (current->fd[1] > 0)
        {
            printf("Cerrando fd[1]: %d\n", current->fd[1]);
            close(current->fd[1]);
        }

        current++;
    }

    // Restaurar los descriptores de archivo estándar
    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);

    // Matar todos los procesos hijos excepto el último
    ms_pilatos(first_token);

    // Marcar el último token como NONE
    token_prev->type = NONE;

    // Esperar a cualquier proceso hijo restante
    while (waitpid(-1, &status, WNOHANG) > 0)
    {
        printf("Esperando proceso hijo restante...\n");
    }
*/

/*    V0.6
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    // Iterar sobre todos los tokens y esperar a cada proceso hijo
    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
            printf("Esperando proceso PID: %d\n", current->pid);
            waitpid(current->pid, &status, 0);
            printf("Proceso PID: %d terminado con estado: %d\n", current->pid, status);

            // Actualizar el estado de salida del último proceso
            if (WIFEXITED(status))
                data->l_status = WEXITSTATUS(status);
        }

        // Cerrar descriptores de archivo si son pipes
        if (current->fd[0] > 0)
            close(current->fd[1]);
        if (current->fd[1] > 0)
            close(current->fd[1]);

        current++;
    }

    // Restaurar los descriptores de archivo estándar
    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);

    // Matar todos los procesos hijos excepto el último
    ms_pilatos(first_token);

    // Marcar el último token como NONE
    token_prev->type = NONE;
*/


/*   V0.5
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    // Iterar sobre todos los tokens y esperar a cada proceso hijo
    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
            printf("Esperando proceso PID: %d\n", current->pid);
            waitpid(current->pid, &status, 0);
            printf("Proceso PID: %d terminado con estado: %d\n", current->pid, status);

            // Actualizar el estado de salida del último proceso
            if (WIFEXITED(status))
                data->l_status = WEXITSTATUS(status);
        }

        // Cerrar descriptores de archivo si son pipes
        if (current->fd[0] > 0)
            close(current->fd[1]);
        if (current->fd[1] > 0)
            close(current->fd[1]);

        current++;
    }

    // Restaurar los descriptores de archivo estándar
    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);

    // Marcar el último token como NONE
    token_prev->type = NONE;
*/


/*   V0.4
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    // Iterar sobre todos los tokens y esperar a cada proceso hijo
    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
            printf("Esperando proceso PID: %d\n", current->pid);
            waitpid(current->pid, &status, 0);
            printf("Proceso PID: %d terminado con estado: %d\n", current->pid, status);

            // Actualizar el estado de salida del último proceso
            if (WIFEXITED(status))
                data->l_status = WEXITSTATUS(status);
        }
        current++;
    }

    // Restaurar los descriptores de archivo estándar
    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);

	token_prev->type = NONE;
*/

/*     V0.3
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
    int status;
    t_token *current = first_token;

    while (current->type != NONE)
    {
        if (current->pid > 0)
        {
			printf("Esperando proceso PID: %d\n", token_prev->pid);
			waitpid(token_prev->pid, &(token_prev->l_status), 0);
			printf("Proceso PID: %d terminado con estado: %d\n", token_prev->pid, token_prev->l_status);
		}
        current = current + 1;
    }

    if (WIFEXITED(status))
        data->l_status = WEXITSTATUS(status);

    dup2(data->bk_in, STDIN_FILENO);
    dup2(data->bk_out, STDOUT_FILENO);
*/


/*      V0.2
void	ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
	//g_sig = 2 ?????
	//signal_handler(); ?????
	waitpid(token_prev->pid, &(token_prev->l_status), 0);
	data->l_status = token_prev->l_status;
	if (WIFEXITED(token_prev->l_status))
		token_prev->l_status = WEXITSTATUS(token_prev->l_status);
	data->l_status = token_prev->l_status;
	//aquí Jhon manda el last_token->prev. Es el comando anterior al último
	//Lo ideal sería almacenarlo de forma local de algún modo, para no tener que reestructurar todo el trabajo de ramón
	
	ms_pilatos(first_token);//kill all children except last one

	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);

*/

/*     V0.1
void	ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
	//g_sig = 2 ?????
	//signal_handler(); ?????
	waitpid(token_prev->pid, &(token_prev->l_status), 0);
	data->l_status = token_prev->l_status;
	if (WIFEXITED(token_prev->l_status))
		token_prev->l_status = WEXITSTATUS(token_prev->l_status);
	data->l_status = token_prev->l_status;
	//aquí Jhon manda el last_token->prev. Es el comando anterior al último
	//Lo ideal sería almacenarlo de forma local de algún modo, para no tener que reestructurar todo el trabajo de ramón

	ms_pilatos(first_token);//kill all children except last one

	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);
	*/
}