#define _GNU_SOURCE
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// int main(void)
// {
// 	char *rl;
// 	char *pwd;
// 	char *prompt;

// 	while (1)
// 	{
// 		pwd = getcwd(NULL, 0);
// 		asprintf(&prompt, "%s$ ", pwd); //strlcat (??)
// 		free(pwd);
// 		rl = readline(prompt);
// 		if (!rl)
// 			break ;
// 		if (*rl)
// 			add_history(rl);
// 		if (strcmp("exit", rl) == 0)
// 		{
// 			free(rl);
// 			free(prompt);
// 			return (0);
// 		}
// 		free(prompt);
// 		free(rl);
// 	}
// 	return (0);
// }

// Obtener el directorio actual
char	*ft_get_current_directory(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	return (pwd);
}

// Función para construir el prompt
char	*ft_build_prompt(const char *pwd)
{
	size_t	pwd_len;
	size_t	prompt_len;
	char	*prompt;

	pwd_len = strlen(pwd);
	prompt_len = pwd_len + 3; // +3 para "$ " y el terminador nulo
	prompt = malloc(prompt_len);
	if (!prompt)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(prompt, pwd, pwd_len);  // Copiar el directorio actual
	prompt[pwd_len] = '\0';
	strncat(prompt, "$ ", 3); // Concatenar "$ "
	return (prompt);
}

// Función principal del bucle de la shell
int	main(void)
{
	char	*rl;
	char	*pwd;
	char	*prompt;

	while (1)
	{
		pwd = ft_get_current_directory();
		prompt = ft_build_prompt(pwd);
		free(pwd);
		rl = readline(prompt);
		free(prompt);
		if (!rl)
			break ;
		if (*rl)
			add_history(rl);
		if (strcmp("exit", rl) == 0)
		{
			free(rl);
			break ;
		}
		free(rl);
	}
	return (0);
}
