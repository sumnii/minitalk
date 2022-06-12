#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	ft_send_str(pid_t pid, char *message);
void	ft_send_signal(pid_t pid, char chr);

int main(int argc, char **argv) {
	pid_t	pid;
	char	*message;

	pid = atoi(argv[1]);
	message = argv[2];
	ft_send_str(pid, message);
}

void	ft_send_str(pid_t pid, char *message)
{
	while (message)
	{
		ft_send_signal(*message);
		++message;
	}
	ft_send_signal('\0');
}

void	ft_send_signal(pid_t pid, char chr)
{
	char	cnt;

	cnt = 8;
	while (cnt > 0)
	{
		if ((chr >> --cnt) & 1)
			if (kill(pid, SIGUSR1) < 0)
				exit(0);
		else
			if (kill(pid, SIGUSR2) < 0)
				exit(0);
	}
}