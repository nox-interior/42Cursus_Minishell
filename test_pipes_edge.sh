#!/bin/bash

echo "=== TESTS EDGE CASES ESPECÍFICOS ==="
echo

echo "1. Test con archivos .c (desde src/):"
echo 'ls src/executor/ | grep "\.c"' | ./minishell
echo

echo "2. Test con builtin export:"
echo 'export TEST_VAR="test_value"' | ./minishell
echo 'env | grep TEST_VAR' | ./minishell
echo

echo "3. Test con múltiples pipes y builtins:"
echo 'echo "testing builtin" | cat | cat' | ./minishell
echo

echo "4. Test con pipe y cd (no debería funcionar porque cd cambia el shell padre):"
echo 'pwd | cat' | ./minishell
echo

echo "5. Test stress - 5 pipes:"
echo 'echo "stress test" | cat | cat | cat | cat | cat' | ./minishell
echo

echo "=== FIN TESTS EDGE CASES ==="
