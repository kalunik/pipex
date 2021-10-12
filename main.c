/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:09:44 by wjonatho          #+#    #+#             */
/*   Updated: 2021/10/12 18:13:08 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include "pipex.h"

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
		printf("%s\n", env[position]);
		if (ft_strncmp("PATH", env[position], 4))
		{
			return (position);
		}
		position++;
	}
	return (-1);
}

void	find_path(int argc, char **argv, char **env)
{
	char	**split;

	printf("%d ---- where\n", where_is_path(env));
	split = ft_split(env[where_is_path(env)], ':');
	printf("%s\n", split[1]);
	leek_case(10, split);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	find_path(argc, argv, env);
	if (getenv(argv[1]))
	{
		printf("it's ok\n");
	}
	else
	{
		perror("Can't find env");
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
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "round", NULL);
		//execve("grep", argv[3], NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
