#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int	main()
{
	printf("server pid : %d", getpid());
	pause();
	ft_get_signal();
}

ft_get_signal()
{
	static char	*g_message;

	g_message = (char *)malloc(sizeof(char));
	g_message = 0;
	signal(SIGUSR1, ft_write_sig(SIGUSR1));
	signal(SIGUSR2, ft_write_sig(SIGUSR2));
}

ft_write_sig(int signum)
{
	if (signum == SIGUSR1)
		g_message += g_message | 1;
	else
		g_message += g_message | 0;
	g_message << 1
}