/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:45 by sumsong           #+#    #+#             */
/*   Updated: 2022/06/14 14:43:29 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_write_sig(int signum)
{
	static char	chr = 0;
	static char	bit_cnt = 0;

	chr <<= 1;
	if (signum == SIGUSR1)
		chr = chr | 1;
	else
		chr = chr | 0;
	++bit_cnt;
	if (bit_cnt == 8)
	{
		write(1, &chr, 1);
		if (chr == 0)
			write(1, "\n", 1);
		bit_cnt = 0;
	}
}

void	ft_sigaction(int signum, siginfo_t *info, void *ucp)
{
	static char	chr = 0;
	static char	bit_cnt = 0;

	(void)ucp;
	chr <<= 1;
	if (signum == SIGUSR1)
		chr = chr | 1;
	else
		chr = chr | 0;
	++bit_cnt;
	if (bit_cnt == 8)
	{
		write(1, &chr, 1);
		if (chr == 0)
		{
			kill(info->si_pid, SIGUSR1);
			write(1, "\n", 1);
		}
		bit_cnt = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sig;

	ft_putstr_fd("server pid <", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd(">\n", 1);
	s_sig.sa_flags = SA_SIGINFO;
	s_sig.sa_sigaction = ft_sigaction;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
}
