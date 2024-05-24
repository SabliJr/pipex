/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:38:42 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/21 16:27:06 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (!envp)
		(ft_print_err("The env is empty!"), exit(EXIT_FAILURE));
	if (argc != 5)
		(ft_print_err("The usage: i.e ./pipex file1 cmd1 cmd2 file2"),
			exit(EXIT_FAILURE));
	return (ft_pipex(&data, argv, envp));
}

int	ft_pipex(t_pipex *data, char **args, char **env)
{
	int	status;

	status = 0;
	if (pipe(data->fd) == -1)
		(ft_print_err("An Error with pipe\n"), exit(EXIT_FAILURE));
	data->child1 = fork();
	if (data->child1 < 0)
		(ft_print_err(FORK_C1), exit(EXIT_FAILURE));
	if (data->child1 == 0)
		ft_first_child_process(data, args, env);
	data->child2 = fork();
	if (data->child2 < 0)
		(ft_print_err(FORK_C2), exit(EXIT_FAILURE));
	if (data->child2 == 0)
		ft_second_child_process(data, args, env);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->child1, &status, 0);
	waitpid(data->child2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (status);
}

void	ft_first_child_process(t_pipex *data, char **args, char **env)
{
	char	**cmd;
	char	*la_path;

	close(data->fd[0]);
	data->in_file = open(args[1], O_RDONLY);
	ft_check_file(data, args);
	if (dup2(data->in_file, 0) == -1)
		ft_err(data);
	if (dup2(data->fd[1], 1) == -1)
		ft_err(data);
	close(data->fd[1]);
	cmd = ft_split(args[2], 32);
	if (cmd == NULL || cmd[0] == NULL)
		(ft_free(cmd), close(data->fd[0]), close(data->fd[1]),
			close(data->in_file), exit(EXIT_FAILURE));
	la_path = ft_check_path(cmd[0], env);
	close(data->in_file);
	if (!la_path)
		(ft_free(cmd), free(la_path), ft_print_err(CMD_ERR), exit(127));
	execve(la_path, cmd, env);
	(ft_free(cmd), ft_print_err(CMD_ERR), exit(127));
}

void	ft_second_child_process(t_pipex *data, char **args, char **env)
{
	char	**cmd;
	char	*la_path;

	close(data->fd[1]);
	data->out_file = open(args[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->out_file < 0)
	{
		if (access(args[4], W_OK) != 0)
			(close(data->fd[0]), ft_print_err(PER_ERR), exit(127));
		else
			(close(data->fd[0]), perror("bash"), exit(EXIT_FAILURE));
	}
	if (dup2(data->out_file, 1) == -1)
		ft_err(data);
	if (dup2(data->fd[0], 0) == -1)
		ft_err(data);
	(close(data->fd[0]), cmd = ft_split(args[3], 32));
	if (cmd == NULL || cmd[0] == NULL)
		(ft_free(cmd), close(data->fd[1]), close(data->fd[0]),
			close(data->out_file), exit(EXIT_FAILURE));
	la_path = ft_check_path(cmd[0], env);
	close(data->out_file);
	if (!la_path)
		(ft_free(cmd), free(la_path), ft_print_err(CMD_ERR), exit(127));
	(execve(la_path, cmd, env), ft_free(cmd), ft_print_err(CMD_ERR), exit(127));
}

void	ft_err(t_pipex *data)
{
	close(data->fd[0]);
	close(data->out_file);
	(ft_print_err(DUP_ERR), exit(EXIT_FAILURE));
}
