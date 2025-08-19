# 🚀 Guía de Implementación - Funcionalidades Pendientes

## 📊 Estado Actual del Proyecto

**Progreso estimado: 85% completo** ✅

### ✅ **YA IMPLEMENTADO CORRECTAMENTE:**
- Tokenización completa (todos los tokens reconocidos)
- Parsing de comandos simples y complejos
- Todos los built-ins requeridos (echo, cd, pwd, export, unset, env, exit)
- Expansión de variables de entorno y `$?`
- Gestión de memoria y error handling básico
- Historial con readline
- Búsqueda en PATH para ejecutables
- Estructura de datos bien diseñada

### ❌ **FUNCIONALIDADES CORE FALTANTES:**
1. **Redirecciones** (`<`, `>`, `>>`) - CRÍTICO
2. **Here Documents** (`<<`) - IMPORTANTE  
3. **Pipes** (`|`) - IMPORTANTE

---

## 🎯 Plan de Implementación por Prioridades

# FASE 1: REDIRECCIONES (PRIORIDAD MÁXIMA)

## 📝 Estado Actual
- ✅ **Tokenización**: `T_REDIR_IN`, `T_REDIR_OUT`, `T_APPEND` funcionan
- ✅ **Parsing**: `cmd->infile`, `cmd->outfile`, `cmd->append` se asignan correctamente
- ❌ **Ejecución**: El executor no configura los file descriptors

## 🔧 Implementación Necesaria

### Ubicación: `src/executor/01_executor.c`

**Modificar la función `ft_fork_and_exec()`** para añadir configuración de redirecciones antes del `execve()`:

```
static int ft_setup_redirections(t_command *cmd)
{
    // Configurar input redirection (<)
    if (cmd->infile)
    {
        int fd_in = open(cmd->infile, O_RDONLY);
        if (fd_in == -1)
        {
            perror("minishell");
            return (-1);
        }
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            perror("minishell: dup2");
            close(fd_in);
            return (-1);
        }
        close(fd_in);
    }
    
    // Configurar output redirection (> o >>)
    if (cmd->outfile)
    {
        int flags = O_WRONLY | O_CREAT;
        if (cmd->append)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
            
        int fd_out = open(cmd->outfile, flags, 0644);
        if (fd_out == -1)
        {
            perror("minishell");
            return (-1);
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("minishell: dup2");
            close(fd_out);
            return (-1);
        }
        close(fd_out);
    }
    
    return (0);
}
```

### Integración en ft_fork_and_exec():

```c
static void ft_fork_and_exec(t_command *cmd, t_shell *shell)
{
    pid_t   pid;
    int     status;
    char    *cmd_path;

    if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
        cmd_path = cmd->argv[0];
    else
        cmd_path = ft_find_in_path(cmd->argv[0], shell);
    if (!cmd_path)
        return ;
    
    pid = fork();
    if (pid < 0)
    {
        perror("minishell: fork");
        shell->exit_status = 1;
        return ;
    }
    if (pid == 0)
    {
        // *** AÑADIR AQUÍ LA CONFIGURACIÓN DE REDIRECCIONES ***
        if (ft_setup_redirections(cmd) == -1)
            exit(1);
            
        execve(cmd_path, cmd->argv, shell->envp);
        perror("minishell");
        exit(127);
    }
    waitpid(pid, &status, 0);
    ft_handle_child_status(status, shell);
}
```

### Casos de Prueba:
```bash
# Input redirection
cat < archivo.txt

# Output redirection
echo "hola" > output.txt

# Append redirection  
echo "mundo" >> output.txt

# Múltiples redirecciones
cat < input.txt > output.txt
```

---

# FASE 2: HERE DOCUMENTS (PRIORIDAD ALTA)

## 📝 Estado Actual
- ✅ **Tokenización**: `T_HEREDOC` detectado
- ✅ **Parsing parcial**: `cmd->heredoc = 1` y `cmd->delimit` asignado
- ❌ **Implementación**: No lee input hasta delimiter

## 🔧 Implementación Necesaria

### Crear nueva función en `src/executor/01_executor.c`:

```c
static int ft_handle_heredoc(t_command *cmd)
{
    if (!cmd->heredoc || !cmd->delimit)
        return (0);
        
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("minishell: pipe");
        return (-1);
    }
    
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return (-1);
    }
    
    if (pid == 0)
    {
        // Proceso hijo: lee líneas hasta delimiter
        close(pipefd[0]);
        
        char *line;
        while ((line = readline("> ")))
        {
            if (ft_strcmp(line, cmd->delimit) == 0)
            {
                free(line);
                break;
            }
            write(pipefd[1], line, ft_strlen(line));
            write(pipefd[1], "\n", 1);
            free(line);
        }
        close(pipefd[1]);
        exit(0);
    }
    
    // Proceso padre
    close(pipefd[1]);
    int status;
    waitpid(pid, &status, 0);
    
    // Redirigir el pipe al stdin
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(pipefd[0]);
        return (-1);
    }
    close(pipefd[0]);
    
    return (0);
}
```

### Integración en ft_setup_redirections():

```c
static int ft_setup_redirections(t_command *cmd)
{
    // Manejar heredoc primero
    if (ft_handle_heredoc(cmd) == -1)
        return (-1);
        
    // Solo configurar input redirection si no hay heredoc
    if (cmd->infile && !cmd->heredoc)
    {
        // ... código de input redirection anterior
    }
    
    // Configurar output redirection (igual que antes)
    if (cmd->outfile)
    {
        // ... código anterior
    }
    
    return (0);
}
```

### Casos de Prueba:
```bash
# Here document básico
cat << EOF
línea 1
línea 2
EOF

# Here document con comando
grep "pattern" << DELIMITER
texto a buscar
pattern encontrado
DELIMITER
```

---

# FASE 3: PIPES (PRIORIDAD ALTA)

## 📝 Estado Actual
- ✅ **Tokenización**: `T_PIPE` funciona
- ✅ **Parsing**: Lista enlazada de comandos con `cmd->next`
- ❌ **Ejecución**: Solo ejecuta el primer comando

## 🔧 Implementación Necesaria

### Crear funciones auxiliares en `src/executor/01_executor.c`:

```c
static int ft_count_commands(t_command *cmd_list)
{
    t_command *current = cmd_list;
    int count = 0;
    
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

static int **ft_create_pipes(int pipe_count)
{
    int **pipes;
    int i;
    
    pipes = malloc(sizeof(int *) * pipe_count);
    if (!pipes)
        return (NULL);
        
    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i] || pipe(pipes[i]) == -1)
        {
            // Cleanup en caso de error
            while (--i >= 0)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
                free(pipes[i]);
            }
            free(pipes);
            return (NULL);
        }
        i++;
    }
    return (pipes);
}

static void ft_close_all_pipes(int **pipes, int pipe_count)
{
    int i = 0;
    
    while (i < pipe_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

static void ft_setup_child_pipes(int **pipes, int cmd_index, int pipe_count)
{
    // Si no es el primer comando, conectar stdin al pipe anterior
    if (cmd_index > 0)
        dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
        
    // Si no es el último comando, conectar stdout al pipe siguiente  
    if (cmd_index < pipe_count)
        dup2(pipes[cmd_index][1], STDOUT_FILENO);
        
    // Cerrar todos los pipes en el proceso hijo
    ft_close_all_pipes(pipes, pipe_count);
}

static void ft_execute_pipeline(t_command *cmd_list, t_shell *shell)
{
    int cmd_count = ft_count_commands(cmd_list);
    int pipe_count = cmd_count - 1;
    int **pipes = ft_create_pipes(pipe_count);
    
    if (!pipes && pipe_count > 0)
    {
        shell->exit_status = 1;
        return;
    }
    
    t_command *current = cmd_list;
    int cmd_index = 0;
    
    while (current)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("minishell: fork");
            ft_close_all_pipes(pipes, pipe_count);
            shell->exit_status = 1;
            return;
        }
        
        if (pid == 0)
        {
            // Proceso hijo
            ft_setup_child_pipes(pipes, cmd_index, pipe_count);
            
            // Configurar redirecciones (solo para último comando en output)
            if (!current->next && current->outfile)
                ft_setup_redirections(current);
            // Para input, solo el primer comando puede tener redirección
            if (cmd_index == 0 && current->infile)
                ft_setup_redirections(current);
                
            // Ejecutar comando
            char *cmd_path;
            if (current->argv[0][0] == '/' || current->argv[0][0] == '.')
                cmd_path = current->argv[0];
            else
                cmd_path = ft_find_in_path(current->argv[0], shell);
                
            if (!cmd_path)
                exit(127);
                
            execve(cmd_path, current->argv, shell->envp);
            perror("minishell");
            exit(127);
        }
        
        current = current->next;
        cmd_index++;
    }
    
    // Cerrar pipes en proceso padre
    ft_close_all_pipes(pipes, pipe_count);
    
    // Esperar a todos los procesos hijos
    int i = 0;
    int status;
    while (i < cmd_count)
    {
        wait(&status);
        if (i == cmd_count - 1) // Solo guardar exit status del último comando
            ft_handle_child_status(status, shell);
        i++;
    }
}
```

### Modificar ft_executor() principal:

```c
void ft_executor(t_command *cmd_list, t_shell *shell)
{
    if (!cmd_list || !cmd_list->argv || !cmd_list->argv[0])
    {
        shell->exit_status = 0;
        return ;
    }
    
    // Detectar si hay pipes
    if (cmd_list->next)
    {
        ft_execute_pipeline(cmd_list, shell);
        return;
    }
    
    // Comando único (código actual)
    if (ft_is_builtin(cmd_list))
    {
        shell->exit_status = ft_exec_builtin(cmd_list, shell);
        return ;
    }
    ft_fork_and_exec(cmd_list, shell);
}
```

### Casos de Prueba:
```bash
# Pipe simple
ls | grep .c

# Pipe múltiple
cat file.txt | grep pattern | wc -l

# Pipe con redirecciones
cat < input.txt | sort | uniq > output.txt
```

---

## 🔧 Actualizar Header (inc/minishell.h)

Añadir declaraciones de las nuevas funciones:

```c
// Redirecciones y pipes
int     ft_setup_redirections(t_command *cmd);
int     ft_handle_heredoc(t_command *cmd);
void    ft_execute_pipeline(t_command *cmd_list, t_shell *shell);
int     ft_count_commands(t_command *cmd_list);
int     **ft_create_pipes(int pipe_count);
void    ft_close_all_pipes(int **pipes, int pipe_count);
```

---

## 🧪 Plan de Testing

### Fase 1 - Redirecciones:
```bash
# Tests básicos
echo "test" > file.txt
cat < file.txt
echo "append" >> file.txt

# Tests con comandos
ls > filelist.txt
grep ".c" < filelist.txt
```

### Fase 2 - Here Documents:
```bash
cat << EOF
línea 1
línea 2  
EOF

sort << END
zebra
apple
banana
END
```

### Fase 3 - Pipes:
```bash
ls | wc -l
ps aux | grep bash | wc -l
cat /etc/passwd | cut -d: -f1 | sort
```

### Tests Combinados:
```bash
# Pipes + Redirecciones
cat < input.txt | sort | uniq > output.txt

# Here doc + Pipes
cat << EOF | grep pattern
texto sin pattern
texto con pattern aquí
EOF
```

---

## 📋 Checklist de Implementación

### Redirecciones:
- [ ] Implementar `ft_setup_redirections()`
- [ ] Integrar en `ft_fork_and_exec()`
- [ ] Testear `<`, `>`, `>>`
- [ ] Manejar errores de archivos

### Here Documents:
- [ ] Implementar `ft_handle_heredoc()`
- [ ] Integrar con redirecciones
- [ ] Testear lectura hasta delimiter
- [ ] Verificar que no actualiza historial

### Pipes:
- [ ] Implementar funciones auxiliares de pipes
- [ ] Modificar `ft_executor()` para detectar pipes
- [ ] Implementar `ft_execute_pipeline()`
- [ ] Testear pipes simples y múltiples
- [ ] Verificar exit status del último comando

### Testing Final:
- [ ] Todos los casos del subject funcionan
- [ ] No hay memory leaks
- [ ] Manejo correcto de errores
- [ ] Comportamiento igual que bash

---

## 🚀 Estimación de Tiempo

- **Redirecciones**: 1-2 días
- **Here Documents**: 2-3 días  
- **Pipes**: 3-4 días
- **Testing y debugging**: 2-3 días

**Total estimado: 8-12 días**

---

## 💡 Consejos Importantes

1. **Implementar paso a paso**: No intentar hacer todo a la vez
2. **Testear cada fase**: Asegurar que funciona antes de continuar
3. **Usar bash como referencia**: Para casos de duda
4. **Manejar errores**: Cada `open()`, `pipe()`, `fork()` puede fallar
5. **Liberar memoria**: Especialmente en caso de errores
6. **Exit status**: Solo el último comando en pipeline determina `$?`

¡Tu proyecto está muy bien estructurado y estas implementaciones completarán la funcionalidad core del minishell! 🎉
