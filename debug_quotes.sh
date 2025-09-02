#!/bin/bash

echo "=== Testing quote concatenation ==="
echo
echo "Test 1: echo hello\"world\"test"
echo 'echo hello"world"test' | ./minishell
echo
echo "Test 2: echo \"hello\"world\"test\""
echo 'echo "hello"world"test"' | ./minishell
echo
echo "Test 3: echo hello\"world\""
echo 'echo hello"world"' | ./minishell
echo
echo "Test 4: echo \"world\"test"
echo 'echo "world"test' | ./minishell
