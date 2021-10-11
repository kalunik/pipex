/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:09:44 by wjonatho          #+#    #+#             */
/*   Updated: 2021/10/11 18:37:43 by wjonatho         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;

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
