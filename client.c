/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:05:35 by sumsong           #+#    #+#             */
/*   Updated: 2022/06/14 14:55:03 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_str(pid_t pid, char *message);
void	ft_send_signal(pid_t pid, char chr);

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
	{
		ft_putstr_fd("type => \"./client <pid> <string>\"\n", 1);
		exit (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	ft_send_str(pid, message);
}

void	ft_send_str(pid_t pid, char *message)
{
	while (*message)
	{
		ft_send_signal(pid, *message);
		usleep(30);
		++message;
	}
	ft_send_signal(pid, '\0');
}

void	ft_send_signal(pid_t pid, char chr)
{
	char			cnt;
	unsigned char	bit;

	cnt = 0;
	bit = 128;
	while (++cnt <= 8)
	{
		if ((chr & bit) == bit)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		bit >>= 1;
		usleep(60);
	}
}
