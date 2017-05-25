#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int sig, pid;
    int i;

    while (1)
    {
        pid = fork();

        // Parent
        if (pid > 0)
        {
            wait(&sig);

            printf("%d", sig);

            if (sig == 0)
            {
                printf("Finished.\n");
                break;
            }
            else if (sig == SIGSEGV || sig == 139)
            {
                printf("Core dumped. Restart...\n");
                continue;
            }
            else
            {
                printf("Unhandled signal!\n");
            }
        }
        // Child
        else if (pid == 0)
        {
            char weightDir[50] = { 0 };

            // Find lastest weights file
            for (i = 100000; i > 0; i -= 100)
            {
                int flag = 0;
                char* realDir = (char*)calloc(1, 50 * sizeof(char));
                char* fileName = (char*)calloc(1, 30 * sizeof(char));
                char* num = (char*)calloc(1, 10 * sizeof(char));

                // Make file name : yolo_xxxx.weights
                sprintf(num, "%d", i);
                strcat(fileName, "yolo_");
                strcat(fileName, num);
                strcat(fileName, ".weights");

                // Make file name and dir : ./darknet/backup/xxx
                strcat(realDir, "./backup/");
                strcat(realDir, fileName);

                // Access if exists
                if (access(realDir, F_OK) != -1)
                {
                    printf("Weights files found : %s\n", fileName);
                    strcpy(weightDir, realDir);
                    printf("%s\n", weightDir);
                    flag = 1;
                }

                free(realDir);
                free(fileName);
                free(num);

                if (flag) break;
                else strcpy(weightDir, "./darknet19_448.conv.23");
            }

            execl("./darknet", "darknet",
                "detector", "train",
                "cfg/coco.data",
                "cfg/yolo.cfg",
                weightDir,
                (char*)0);
        }
    }

    return 0;
}