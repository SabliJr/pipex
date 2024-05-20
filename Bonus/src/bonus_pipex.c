/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:45 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/20 19:05:51 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	ft_create_childern(t_pipex_bonus *data, int cmd_index);
static void	ft_run_first_cmd(t_pipex_bonus *data);
static void	ft_run_last_cmd(t_pipex_bonus *data);
static void	ft_run_middle_cmd(t_pipex_bonus *data, int cmd_index);

int	main(int ac, char *av[], char *envp[])
{
	t_pipex_bonus	data;
	int				cmd_index;
	int				x;
	int				exit_status;

	x = -1;
	data.argc = ac;
	data.argv = av;
	data.env = envp;
	data.pids_num = 0;
	data.pids = NULL;
	cmd_index = ft_init_data(&data, ac, av, envp);
	while (cmd_index <= ac - 2)
		ft_create_childern(&data, cmd_index++);
	if (data.paths)
		ft_free(data.paths);
	while (++x < data.pids_num)
		waitpid(data.pids[x], &exit_status, 0);
	if (data.pids)
		free(data.pids);
	exit(ft_get_exit_status(exit_status));
}

static void	ft_create_childern(t_pipex_bonus *data, int cmd_index)
{
	if (cmd_index == 2 || (cmd_index == 3 && data->here_doc))
		ft_run_first_cmd(data);
	else if (cmd_index == data->argc - 2)
		ft_run_last_cmd(data);
	else
		ft_run_middle_cmd(data, cmd_index);
}

static void	ft_run_first_cmd(t_pipex_bonus *data)
{
	int		infile;
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		ft_err_handler(data, 1, NULL);
	if (data->here_doc == TRUE)
		infile = ft_here_doc(data, data->argv[2]);
	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	if (pid == 0)
	{
		close(fds[0]);
		if (data->here_doc == FALSE)
			infile = ft_open_infile(data, fds);
		dup2(infile, STDIN_FILENO);
		(dup2(fds[1], STDOUT_FILENO), close(fds[1]));
		ft_execute(data, data->argv[2 + data->here_doc]);
	}
	else
		data->pids[data->pids_num++] = pid;
	(dup2(fds[0], STDIN_FILENO), close(fds[0]), close(fds[1]));
	if (data->here_doc == TRUE && infile != -1)
		close(infile);
}

static void	ft_run_last_cmd(t_pipex_bonus *data)
{
	char	*lsat_cmd;
	int		outfile;
	pid_t	pid;

	lsat_cmd = data->argv[data->argc - 2];
	pid = fork();
	if (pid == 0)
	{
		outfile = ft_open_outfile(data);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		ft_execute(data, lsat_cmd);
	}
	else
		data->pids[data->pids_num++] = pid;
	close(STDIN_FILENO);
}

static void	ft_run_middle_cmd(t_pipex_bonus *data, int cmd_index)
{
	char	*middle_cmds;
	int		fds[2];
	pid_t	pid;

	middle_cmds = data->argv[cmd_index];
	if (pipe(fds) == -1)
		ft_err_handler(data, 1, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		ft_execute(data, middle_cmds);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		data->pids[data->pids_num++] = pid;
	}
}
