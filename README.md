# TODO-list

## Features
- I want to be able to add todos to my TODO-list
- I want to give the todos a title
- I want to give the todos a description
- I want to be able to list my todos 
- I want to be able to sort my todos by their topic
- I want to be able to remove todos from my list
- I want to be able to edit my todos
- I want to be able to create global todolists
- I want to be able to create project specific todos

## Possible additional Features
- See finished todos

## How to achieve this?
- It will be written in C
- It will save the todos in a file (How to handle injections?)
- Add todos with "todo add -t "..." -d "..." #... #... 
    -t = title | -d = description | #... = topic | -i = id (edit, remove & finish)
- global todos will be saved in ~/.todolist/todo & ~/.todolist/todo_history
- (local todos will be saved in ./.todolist/todo ./.todolist/todo_history)
- the files will be in json format where the id is the "primary key"
- every todo will thet a id autoasigned (hashvalue?)
- the todos will be saved in a json array
- to add a todo to the list, the array has to be in the ram --> add new object --> write to file

## Setup

### build the binary
```bash
mkdir -p build
cd build
cmake ..
make
```

### rename binary
```bash
mv todo-shell todo
```

### move the binary to ~/.local/bin
```bash
mkdir ~/.local/bin/
mv todo ~/.local/bin/
```

### Add the folder to your PATH in your home.nix
```nix
  home.sessionPath = [
    "$HOME/.local/bin"
  ];
```

# Todo Command-Line Tool

This is a simple command-line tool for managing tasks with options for adding, editing, removing, finishing, and listing tasks.

## Usage

### Adding a Task

To add a task, use the following command:

```bash
todo add -t "<Title>" -d "<Description>" #<Topic1> #<Topic2> ...
```

#### Options:
- `-t <Title>`: The title of the task.
- `-d <Description>`: A detailed description of the task.
- `#<Topic>`: One or more topics for the task (with `#` before the topic).
- `-i <ID>`: The ID of the task (for editing, removing, or completing the task).

#### Examples:
```bash
todo add -t "Project Preparation" -d "Creating the project plan" "#Project" "#Work"
todo add -t "Code Review" -d "Reviewing the code for errors" "#Development" "#Team"
```

### Listing Tasks

To list all tasks:

```bash
todo list
```

To list tasks by a specific flag or topic:

```bash
todo list "#Flag"
```

### Other Commands

#### Edit a Task

To edit an existing task, use the following command:

```bash
todo edit -i <ID> -t "<New Title>" -d "<New Description>" "#NewFlag"
```

#### Remove a Task

To remove a task by its ID:

```bash
todo remove -i <ID>
```

#### Finish a Task

To mark a task as finished:

```bash
todo finish -i <ID>
```
