// include headers
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <stdlib.h>


int main() {
    char *EXECUTABLE = "./runme";
    char *OUTPUTFILE = "./result.txt";
    double CORRECT = 1.0;

    // arguments to pass to executable - test on lattice D3
    char *args[] = {EXECUTABLE, "[1.0", "0.0", "0.0]", "[0.0", "1.0", "0.0]",
                    "[0.0", "0.0", "1.0]", NULL};


    // create child process
    pid_t processID = fork();

    if (processID == -1) {
        // error in creating process
        perror("Fork failed:");
        return 1;

    } else if (processID == 0) {
        // following code is run by the child process
        int status = execvp(args[0], args);
        if (status == -1) {
            perror("Error running executable:");
            return 1;
        }

    } else {
        // code run by parent - wait for child to terminate
        waitpid(0, NULL, 0);

        // open result file
        FILE *f = fopen(OUTPUTFILE, "r");
        if (f == NULL) {
            // handle file opening error
            printf("Error opening output file: %s\n", OUTPUTFILE);
            return 1;
        }

        // read solution from file
        char contents[50];
        if (fgets(contents, sizeof(contents), f) != NULL) {
            double sol = atof(contents);
            // verify solution
            if (fabs(sol - CORRECT) / CORRECT < 0.01) {
                printf("Test passed\n");
            } else {
                printf("Test failed - incorrect solution\n");
            }
        } else {
            printf("Test failed - output file is empty or cannot be read\n");
        }
    }
}
