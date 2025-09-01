#!/bin/bash

echo "=== TESTING HEREDOC + PIPES FUNCTIONALITY ==="
echo

# Test 1: Heredoc básico con pipe
echo "Test 1: Heredoc básico con pipe"
echo 'cat << EOF | grep hello
hello world
test line
hello there
end
EOF' | ./minishell
echo "Expected: hello world, hello there"
echo

# Test 2: Heredoc con múltiples pipes
echo "Test 2: Heredoc con múltiples pipes"
echo 'cat << END | grep hello | wc -l
hello world
test line
hello there
another hello
END' | ./minishell
echo "Expected: 3"
echo

# Test 3: Heredoc con variables
echo "Test 3: Heredoc con variables"
echo 'export MYVAR=test
cat << EOF | grep $MYVAR
this is a test line
hello world
test content
EOF' | ./minishell
echo "Expected: this is a test line, test content"
echo

# Test 4: Heredoc con comillas (no expansión)
echo "Test 4: Heredoc con comillas (no expansión)"
echo 'export MYVAR=test
cat << "EOF" | grep test
this is a $MYVAR line
hello world
test content
EOF' | ./minishell
echo "Expected: test content"
echo

# Test 5: Pipe antes de heredoc
echo "Test 5: Pipe después de heredoc con redirection"
echo 'cat << EOF | sort | head -2
zebra
apple
banana
EOF' | ./minishell
echo "Expected: apple, banana"
echo

# Test 6: Comando simple sin pipes (regresión)
echo "Test 6: Comando simple sin pipes"
echo 'echo "simple test"' | ./minishell
echo "Expected: simple test"
echo

# Test 7: Pipe simple sin heredoc (regresión)
echo "Test 7: Pipe simple sin heredoc"
echo 'echo "hello world" | grep hello' | ./minishell
echo "Expected: hello world"
echo

echo "=== END OF TESTS ==="
