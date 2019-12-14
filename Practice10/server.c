#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ     27

int main(int argc, char ** argv){

    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    
    key = ftok("cs392_key", 0);

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    
    s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = 0;

    while (*shm != '*')
        sleep(1);

    shmdt(shm);

    shmctl(shmid, IPC_RMID, 0);

    printf("Congratulations! You Win!\n");

    return 0;
}
