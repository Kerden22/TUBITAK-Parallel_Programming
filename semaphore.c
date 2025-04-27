#include <semaphore.h>   // POSIX semaphores
#include <fcntl.h>       // O_CREAT, O_* bayrakları
#include <stdio.h>
#include <unistd.h>      // fork, sleep
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    // 1. Adlandırılmış bir semafor oluştur (başlangıç değeri: 1)
    sem_t* sem = sem_open("/mysem", O_CREAT, 0644, 1);

    pid_t pid = fork();

    if (pid == 0) {
        // ### Çocuk işlem ###
        sem_wait(sem); // Kilitle (critical section'a giriş)
        printf("[Child] In critical section\n");
        sleep(2);
        printf("[Child] Exiting critical section\n");
        sem_post(sem); // Serbest bırak
        sem_close(sem);
        exit(0);
    } else {
        // ### Ana işlem ###
        sem_wait(sem);
        printf("[Parent] In critical section\n");
        sleep(2);
        printf("[Parent] Exiting critical section\n");
        sem_post(sem);
        wait(NULL);         // Çocuğu bekle
        sem_close(sem);     // Semaforu kapat
        sem_unlink("/mysem"); // Sistemden sil
    }

    return 0;
}
