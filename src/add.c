#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

void usage(void); 

int sumStream(FILE *file); 

int sumArguments(int amountOfArguments, char *arguments[]); 

int main(int argc, char *argv[]) {
        FILE *inputFile = fopen(argv[1], "r");

        bool emptyStdIn = isatty(fileno(stdin));
        bool noArguments = argc > 2;
        if (noArguments && emptyStdIn) {
                usage();
        }

        int sum = 0;
        if (inputFile != NULL) {
                sum = sumStream(inputFile);
                fclose(inputFile);
        } else if (argc > 1) {
                sum = sumArguments(argc, argv);
        } else {
                sum = sumStream(stdin);
        }

        printf("%d\n", sum);
        return 0;
}

int sumArguments(int amountOfArguments, char *arguments[]) {
        int sum = 0;

        for (int argIndex = 1; argIndex < amountOfArguments; argIndex++) {
                sum += atoi(arguments[argIndex]);
        }

        return sum;
}

int sumStream(FILE *file) {
        int sum = 0;
        char line[MAX_LINE_LENGTH]; 

        while (fgets(line, sizeof(line), file)) {
                sum += atoi(line);
        }

        return sum;
}

void usage(void) {
        printf("This is the help for MyWonderfulApp\n"
       "Options are:\n"
       "    --help: display what you are reading now\n"
       "    --quiet: output nothing\n");
        exit(EXIT_SUCCESS);
}
