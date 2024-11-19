#include <stdio.h>
#include <ctype.h>

#define N		(10)

int stack[N];

int main()
{
	int i = 0;
	int c;

	while(1)
	{
		// i = 0;
		int c = getchar();
		if (isdigit(c))
		{
			stack[i] = c - '0';
			i++;
		}
		if(c == '+')
		{
			// printf("plus found %d\n", i);
			if (i < 2) break;
			stack[i - 2] = stack[i - 2] + stack[i - 1];
			i--;
		}
		if (c == EOF)
		{
			// printf("EOF\n");
			break;
		}
	}

	// printf("i at start in print: %d\n", i);
	while(i > 0)
	{
		i--;
		// printf("Print loop\n");
		printf("%d\n", stack[i]);
	}
	return 0;
}
