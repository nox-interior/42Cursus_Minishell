#!/bin/bash

echo "Testing quote concatenation in interactive mode..."
echo ""

# Test 1: Basic concatenation
echo "Test 1: Basic concatenation"
echo 'echo lswodowk"okoeevj"'\''$PATH'\' | ./minishell

echo ""
echo "Expected: lswodowkokoeevj\$PATH"
echo ""

# Test 2: Multiple quotes
echo "Test 2: Multiple quotes"  
echo 'echo "hello"'\''world'\'"test"' | ./minishell

echo ""
echo "Expected: helloworldtest"
echo ""

# Test 3: Word with quotes
echo "Test 3: Word with quotes"
echo 'echo pre"middle"post' | ./minishell

echo ""
echo "Expected: premiddlepost"
echo ""
