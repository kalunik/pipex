/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:08:07 by wjonatho          #+#    #+#             */
/*   Updated: 2021/10/30 20:36:23 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static inline void	close_fd_and_waitpid(int fd[3], int pid[2])
{
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	if (pid != NULL)
	{
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
	}
}

static inline void	process(int *pid, int *fd, char *cmd_argv, char **env)
{
	if (fd[2] == -1)
	{
		if (pid[0] == 0)
			error_n_exit("Can't open file to read");
		if (pid[1] == 0)
			error_n_exit("Can't open file to write");
	}
	else
	{
		if (pid[0] == 0)
			dup2(fd[2], STDIN_FILENO);
		if (pid[1] == 0)
			dup2(fd[2], STDOUT_FILENO);
	}
	if (pid[0] == 0)
		dup2(fd[1], STDOUT_FILENO);
	if (pid[1] == 0)
		dup2(fd[0], STDIN_FILENO);
	close_fd_and_waitpid(fd, NULL);
	execve(find_command_path(cmd_argv, env), ft_split(cmd_argv, ' '), env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[3];
	int		pid[2];

	if (argc != 5)
		error_n_exit("You should give four arguments");
	if (pipe(fd) == -1)
		error_n_exit("Can't create a pipe");
	pid[0] = fork();
	if (pid[0] < 0)
		error_n_exit("Can't create a new process");
	if (pid[0] == 0)
	{
		fd[2] = open(argv[1], O_RDONLY);
		process(pid, fd, argv[2], env);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		error_n_exit("Can't create a new process");
	if (pid[1] == 0)
	{
		fd[2] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		process(pid, fd, argv[3], env);
	}
	close_fd_and_waitpid(fd, pid);
	return (0);
}
