#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// int	main(void)
// {
// 	char	*input;

// 	input = readline("minishell> ");
// 	printf("Your input: %s\n", input);
// 	free (input);
// 	return (0);
// }

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		printf("Your input: %s\n", input);
		free (input);
	}
	return (0);
}