#!/bin/bash

echo "=== Probando pipes en minishell ==="
echo

echo "1. Probando: echo \"hello\" | cat"
echo 'echo "hello" | cat' | ./minishell
echo

echo "2. Probando: echo \"test\" | cat"
echo 'echo "test" | cat' | ./minishell
echo

echo "3. Probando: ls | wc -l"
echo 'ls | wc -l' | ./minishell
echo

echo "4. Probando: env | grep PATH"
echo 'env | grep PATH' | ./minishell
echo

echo "=== Fin de las pruebas ==="
