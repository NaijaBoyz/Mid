#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
    printf("Current working directory: %s\n", cwd);

    char hello_world_path[1024];
    snprintf(hello_world_path, sizeof(hello_world_path), "%s/helloworld.c", cwd);

    // Create the hello world file
    FILE* fp = fopen(hello_world_path, "w");
    if (fp == NULL) {
        perror("fopen() error");
        exit(EXIT_FAILURE);
    }
    fputs("#include <stdio.h>\n\nint main() {\n    printf(\"Hello, world!\\n\");\n    return 0;\n}\n", fp);
    fclose(fp);

    // Compile the hello world file
    if (system("gcc -o helloworld helloworld.c") == -1) {
        perror("system() error");
        exit(EXIT_FAILURE);
    }

    // Create the dir1 directory
    char dirpath[1024];
    snprintf(dirpath, sizeof(dirpath), "%s/dir1", cwd);
    if (mkdir(dirpath, 0777) == -1) {
        perror("mkdir() error");
        exit(EXIT_FAILURE);
    }
    printf("Created directory: %s\n", dirpath);

    // Print the working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
    printf("Current working directory: %s\n", cwd);

    // Copy the hello world file to dir1
    char destpath[1024];
    snprintf(destpath, sizeof(destpath), "%s/helloworld", dirpath);
    if (system("cp helloworld dir1/") == -1) {
        perror("system() error");
        exit(EXIT_FAILURE);
    }

    // Change to the dir1 directory
    if (chdir(dirpath) == -1) {
        perror("chdir() error");
        exit(EXIT_FAILURE);
    }
    printf("Changed directory to: %s\n", dirpath);

    // Run the hello world program in dir1
    if (system("./helloworld") == -1) {
        perror("system() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}
