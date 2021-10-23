/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:09:44 by wjonatho          #+#    #+#             */
/*   Updated: 2021/10/23 16:44:25 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include "includes/pipex.h"

/*int	main(void)
{
	int	s = -1;

	//s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == -1)
	{ // some error has occurred
	// prints "socket error: " + the error message:
		perror("socket error");
	}
	// similarly:
	if (s == 1)
	{
	// this prints "an error: " + the error message from errno:
		printf("an error: %s\n", strerror(errno));
	}*/
//}
static int	str_count(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
		i++;
	return (i);
}

/// It could find string with PATH in env
/// @param env It will show UNIX enviroment, like command `env`
/// @return
/// position of line, where "PATH" had been found
/// or -1, if nothing found.
static void	*leek_case(size_t num_segment, char **arr)
{
	size_t	i;

	i = 0;
	while (i < num_segment)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

int	where_is_path(char **env)
{
	int	position;

	position = 0;
	while (env[position])
	{
		//printf("env[%d] -- %s\n", position, env[position] + 5);
		if (ft_strncmp("PATH", env[position], 4) == 0)
		{
			return (position);
		}
		position++;
	}
	return (-1);
}

char	*find_path_to_command(char *command_with_args, char **env)
{
	char	**splited;
	char	*path_to_command;
	int		i = 0;
	char	**command;

	//printf("%d ---- where\n", where_is_path(env));
	splited = ft_split(env[where_is_path(env)] + 5, ':');
	command = ft_split(command_with_args, ' ');
	while (i < str_count(env))
	{
		//printf("%s -- splited\n", splited[i]);
		path_to_command = ft_strjoin(splited[i], "/");
		path_to_command = ft_strjoin(path_to_command, command[0]);
		if (access(path_to_command, R_OK) == 0)
		{
			//printf("%s -- path\n", path_to_command);
			break ;
		}
		i++;
	}
	leek_case(i, splited);
	return (path_to_command);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**arguments;
	char	*cmd;

	if (argc != 5)
	{
		perror("You should give more arguments");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
	{
		return (2);
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		//execlp("ping", "ping", "-c", "5", "google.com", NULL);
		cmd = find_path_to_command(argv[2], env);
		arguments = ft_split(argv[2], ' ');
		execve(cmd, arguments, env);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		return (2);
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		//execlp("grep", "grep", "round", NULL);
		cmd = find_path_to_command(argv[3], env);
		arguments = ft_split(argv[3], ' ');
		execve(cmd, arguments, env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

/*
int	main(int argc, char **argv)
{
	int arr[] = {1, 3, 5, 54, 3, 23, 4, 4, 2};
*/
/*	int	fd[2];

	//fd[0] - read
	//fd[1] - write
	if (pipe(fd) == -1)
	{
		printf("An error occured with opening pipe\n");
	}
	int id = fork();
	if (id == 0)
	{
		int x = 3;
		close(fd[0]);
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			perror("writing in pipe");
		close(fd[1]);
	}
	else
	{
		int y;
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}*//*

	*/
/*
	int	id;
	int	n;

	id = fork();
	if (id == 0)
	{
		n = 1;
	}
	else
	{
		n = 6;
	}
	if (id != 0)
	{
		wait(0);
	}
	int	i;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
*//*


}*/
