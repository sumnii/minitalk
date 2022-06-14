/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumsong <sumsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:06:45 by sumsong           #+#    #+#             */
/*   Updated: 2022/06/14 14:53:46 by sumsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_write_sig(int signum);

int	main(void)
{
	ft_putstr_fd("server pid <", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd(">\n", 1);
	signal(SIGUSR1, (void *)ft_write_sig);
	signal(SIGUSR2, (void *)ft_write_sig);
	while (1)
		pause();
}

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
