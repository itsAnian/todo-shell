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
    -t = title | -d = description | #... = topic
- global todos will be saved in ~/.todolist/todo & ~/.todolist/todo_history
- local todos will be saved in ./.todolist/todo ./.todolist/todo_history
- the files will be in json format where the id is the "primary key"
- every todo will thet a id autoasigned (hashvalue?)
