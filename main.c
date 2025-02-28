#include <stdio.h>
#include <string.h>

const int argnumber = 1;

struct todostruct{
    int id;
    char* titel;
    char* description;
    char* flags[4];
};


int main(int argc, char* argv[])
{
    struct todostruct todo;
    int id;
    char* titel;
    char* description;
    char* flags[argc];
    int flagCount = 0;
    int state = 0;

    if(strcmp(argv[argnumber], "add") == 0){
        printf("ADD\n");
        state = 1;
    }
    if(strcmp(argv[argnumber], "edit") == 0){
        printf("EDIT\n");
        state = 2;
    }
    if(strcmp(argv[argnumber], "remove") == 0){
        printf("REMOVE\n");
        state = 3;
    }
    if(strcmp(argv[argnumber], "finish") == 0){
        printf("FINISH\n");
        state = 4;
    }

    for (int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "-t") == 0){
            titel = argv[i+1];
        }
        if(strcmp(argv[i], "-d") == 0){
            description = argv[i+1];
        }
        if(argv[i][0] == '#'){
            flags[flagCount] = argv[i];
            flagCount++;
        }
    }

    todo.id = 187;
    todo.titel = titel;
    todo.description = description;
    for (int i = 0; i < flagCount; i++) {
        todo.flags[i] = flags[i];
    }

    printf("id: %d\ntitel: %s\ndescription: %s\n", todo.id, todo.titel, todo.description);
    for (int i = 0; i < flagCount; i++) {
        printf("flags: %s\n", todo.flags[i]);
    }

    return 0;
}
