#!/bin/bash

echo "=== TESTS COMPLEJOS DE PIPES EN MINISHELL ==="
echo

echo "--- TESTS BÁSICOS ---"
echo "1. Pipe simple:"
echo 'echo "hello world" | cat' | ./minishell
echo

echo "2. Pipe con múltiples palabras:"
echo 'echo "primera segunda tercera" | cat' | ./minishell
echo

echo "--- TESTS CON MÚLTIPLES PIPES ---"
echo "3. Triple pipe:"
echo 'echo "test" | cat | cat' | ./minishell
echo

echo "4. Cuádruple pipe:"
echo 'echo "pipeline" | cat | cat | cat' | ./minishell
echo

echo "--- TESTS CON COMANDOS DEL SISTEMA ---"
echo "5. ls con pipe:"
echo 'ls | head -3' | ./minishell
echo

echo "6. Contar archivos:"
echo 'ls -la | wc -l' | ./minishell
echo

echo "7. Filtrar archivos:"
echo 'ls -la | grep "\.c"' | ./minishell
echo

echo "--- TESTS CON BUILTINS ---"
echo "8. env con pipe:"
echo 'env | head -5' | ./minishell
echo

echo "9. env filtrado:"
echo 'env | grep USER' | ./minishell
echo

echo "10. pwd con pipe:"
echo 'pwd | cat' | ./minishell
echo

echo "--- TESTS CON ECHO BUILTIN ---"
echo "11. echo builtin con pipe:"
echo 'echo "desde builtin" | cat' | ./minishell
echo

echo "12. echo con opciones:"
echo 'echo -n "sin newline" | cat' | ./minishell
echo
echo

echo "--- TESTS DE EDGE CASES ---"
echo "13. Pipe con comando vacío (debería fallar):"
echo 'echo "test" | ' | ./minishell
echo

echo "14. Múltiples espacios:"
echo 'echo "espacios"   |   cat' | ./minishell
echo

echo "15. Pipe al final (debería fallar):"
echo 'echo "test" |' | ./minishell
echo

echo "--- TESTS CON REDIRECCIONES Y PIPES ---"
echo "16. Pipe + redirección:"
echo 'echo "test" | cat > /tmp/test_output && cat /tmp/test_output && rm /tmp/test_output' | ./minishell
echo

echo "--- TESTS DE RENDIMIENTO ---"
echo "17. Pipe con mucho contenido:"
echo 'ls -la /usr/bin | head -10' | ./minishell
echo

echo "18. Pipe complejo:"
echo 'echo "uno dos tres cuatro cinco" | tr " " "\n" | wc -l' | ./minishell
echo

echo "=== FIN DE TESTS COMPLEJOS ==="
