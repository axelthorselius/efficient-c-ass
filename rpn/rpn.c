#include <stdio.h>
#include <ctype.h>

#define N (10)

int stack[N];
int l = 0;

int main()
{
	int i = 0;
	int c;
	int n;

	while(1)
	{
		c = getchar();
		if(isdigit(c))
		{
			n = 0;
			while(isdigit(c))
			{
				n = (n*10) + (c - '0');
				c = getchar();
			}
			stack[i] = n;
			i++;
		}
		if(c == '+')
		{
			// printf("plus found %d\n", i);
			if (i < 2) break;
			stack[i - 2] = stack[i - 2] + stack[i - 1];
			i--;
		}
		if(c == '-')
		{
			if (i < 2) break;
			stack[i - 2] = stack[i - 2] - stack[i - 1];
			i--;
		}
		if(c == '*')
		{
			if (i < 2) break;
			stack[i - 2] = stack[i - 2] * stack[i - 1];
			i--;
		}
		if(c == '/')
		{
			if (i < 2 || stack[i - 1] == 0) break;
			stack[i - 2] = stack[i - 2] / stack[i - 1];
			i--;
		}
		if (c == EOF)
		{
			// printf("EOF\n");
			break;
		}
		if (c == '\n')
		{
			break;
		}
	}

	while(i > 0)
	{
		i--;
		// printf("Print loop\n");
		printf("%d\n", stack[i]);
	}
	return 0;
}
