#include <stdio.h>

int main()
{
	char	test[3] = "abc";
	char	cnt = 8;
	int 	i = 0;
	char	message = 0;

	while (test[i])
	{
		while (cnt > 0)
		{
//			printf("cnt : %d\n", cnt);
			message <<= 1;
			if ((test[i] >> --cnt) & 1)
				message = message | 1;
			else
				message = message | 0;
			printf("%d\n", message);
		}
		printf("c : %c\n", message);
		++i;
		message = 0;
		cnt = 8;
	}
}