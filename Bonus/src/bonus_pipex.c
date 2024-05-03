/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:45 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/03 08:38:11 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	main(int ac, char *av[], char *env[])
{
	if (ac < 5)
		ft_args_err();
	ft_pipex(ac, av, env);
	return (0);
}

void	ft_pipex(int ac, char **av, char **env)
{
	int	x;
	int	infile;
	int	outfile;

	if (!ft_strncmp_b("here_doc", av[1], ft_strlen("here_doc")))
	{
		x = 3;
		outfile = ft_open_file(av[ac - 1], 0);
		if (ac < 6)
			ft_args_err();
		ft_here_doc(av[2]);
	}
	else
	{
		x = 2;
		outfile = ft_open_file(av[ac - 1], 1);
		infile = ft_open_file(av[1], 2);
		dup2(infile, 0);
	}
	while (x < ac - 2)
		ft_child_process(av[x++], env);
	dup2(outfile, 1);
	ft_execute(av[ac - 2], env);
	close(infile);
	close(outfile);
}

void	ft_child_process(char *av, char *env[])
{
	pid_t	pid;
	int		p[2];

	if (pipe(p) == -1)
		ft_process_err();
	pid = fork();
	if (pid == -1)
		ft_process_err();
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		ft_execute(av, env);
	}
	else
	{
		close(p[1]);
		dup2(p[0], 0);
		waitpid(pid, NULL, 0);
	}
}

void	ft_here_doc(char *limiter)
{
	pid_t	pid;
	int		p[2];

	if (pipe(p) == -1)
		ft_process_err();
	pid = fork();
	if (pid == -1)
		ft_process_err();
	if (pid == 0)
	{
		close(p[0]);
		ft_process_here_doc(p[1], limiter);
	}
	else
	{
		close(p[0]);
		dup2(p[0], 0);
		wait(NULL);
	}
}

void	ft_process_here_doc(int fd, char *limiter)
{
	char *line;

	write(1, "heredoc> ", 9);
	while (ft_get_next_line(&line))
	{
		if (!ft_strncmp_b(line, limiter, ft_strlen(line)))
			exit(EXIT_SUCCESS);
		write(fd, line, ft_strlen(line));
		write(1, "heredoc> ", 9);
	}
}