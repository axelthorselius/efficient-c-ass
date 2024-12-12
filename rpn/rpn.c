#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define N (10)

int stack[N];
int c;
int n;
int i;
int l = 0;

void print_line(int c)
{
	l++;
	printf("line %d: %d\n", l, stack[i - 1]);
}

void error(int c)
{
	l++;
	if (c == '\n')
	{
		printf("line %d: error at \\n\n", l);
		return;
	}
	// if(isdigit(c))
	// {
	// 	printf("line %d: error at %d\n", l, c);
	// 	return;
	// }
	printf("line %d: error at %c\n", l, c);
	while(getchar() != '\n');
}

int main()
{
	while(1)
	{
		i = 0;
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
				if (i == 10)
				{
					error(n + '0');
					break;
				}
				stack[i] = n;
				i++;

			}
			// switch (c)
			// {
			// 	case '+':
			// 		if (i < 2)
			// 		{
			// 			error(c);
			// 			break;
			// 		}
			// 		stack[i - 2] = stack[i - 2] + stack[i - 1];
			// 		i--;
			// 		// break;
			// 	case '-':
			// 		if (i < 2)
			// 		{
			// 			error(c);
			// 			break;
			// 		}
			// 		stack[i - 2] = stack[i - 2] - stack[i - 1];
			// 		i--;
			// 		// break;
			// 	case '*':
			// 		if (i < 2)
			// 		{
			// 			error(c);
			// 			break;
			// 		}
			// 		stack[i - 2] = stack[i - 2] * stack[i - 1];
			// 		i--;
			// 		// break;
			// 	case '/':
			// 		if (i < 2 || stack[i - 1] == 0)
			// 		{
			// 			error(c);
			// 			break;
			// 		}
			// 		stack[i - 2] = stack[i - 2] / stack[i - 1];
			// 		i--;
			// 		// break;
			// 	case EOF:
			// 		printf("EOF\n");
			// 		exit(1);
			// 	case '\n':
			// 		if (i != 1)
			// 		{
			// 			error(c);
			// 			break;
			// 		}
			// 		print_line(c);
			// 		break;
			// 	case ' ':
			// 	default:
			// 	printf("DEFAULT\n");
			// 	exit(1);
			// }
			if(c == '+')
			{
				if (i < 2)
				{
					error(c);
					break;
				}
				stack[i - 2] = stack[i - 2] + stack[i - 1];
				i--;
			}
			if(c == '-')
			{
				if (i < 2)
				{
					error(c);
					break;
				}
				stack[i - 2] = stack[i - 2] - stack[i - 1];
				i--;
			}
			if(c == '*')
			{
				if (i < 2)
				{
					error(c);
					break;
				}
				stack[i - 2] = stack[i - 2] * stack[i - 1];
				i--;
			}
			if(c == '/')
			{
				if (i < 2 || stack[i - 1] == 0)
				{
					error(c);
					break;
				}
				stack[i - 2] = stack[i - 2] / stack[i - 1];
				i--;
			}
			if (c == EOF)
			{
				return 0;
			}
			if (c == '\n')
			{
				if (i != 1)
				{
					error(c);
					break;
				}
				print_line(c);
				break;
			}
			if (c == '!')
			{
				error(c);
				break;
			}
			// error(c);
			// break;
		}

		// while(i > 0)
		// {
		// 	i--;
		// 	// printf("Print loop\n");
		// 	printf("%d\n", stack[i]);
		// }
	}
	return 0;
}
