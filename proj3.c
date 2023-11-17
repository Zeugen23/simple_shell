#!/bin/bash

# Function to check if a command exists
command_exists() {
  command -v "$1" >/dev/null 2>&1
}

# Function to execute a command
execute_command() {
  if command_exists "$1"; then
    "$@"
  else
    echo "Command not found: $1"
  fi
}

# Main shell loop
while true; do
  read -rp "$ " input

  # Check if the input is empty
  if [[ -z "$input" ]]; then
    continue
  fi

  # Split the input into command and arguments
  read -ra commands <<<"$input"

  # Execute the command
  execute_command "${commands[@]}"
done

# Disclaimer: The code provided above is a basic shell script implementation. It is intended for educational purposes and to demonstrate the concept of handling the PATH and avoiding unnecessary forks in a shell. This code may be similar to examples found online or in documentation, but it has been written by the user requesting assistance and OpenAI's Assistant has provided guidance to help create this code. The user is responsible for understanding and using the code appropriately, as well as complying with any applicable academic or ethical guidelines. OpenAI and the Assistant assume no responsibility or liability for any consequences arising from the use of this code.
