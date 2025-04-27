#include <sys/ipc.h>    // IPC anahtarları için
#include <sys/shm.h>    // Paylaşımlı bellek için
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // fork, sleep vs.
#include <sys/wait.h>   // wait()

int main() {
    // 1. Paylaşımlı bellek segmenti oluştur (bir adet int için)
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // 2. Bellek segmentine attach ol (işlem adres uzayına dahil et)
    int* data = (int*)shmat(shmid, NULL, 0);

    *data = 0;  // Başlangıç değeri ata

    pid_t pid = fork(); // Yeni bir process oluştur

    if (pid == 0) { // ### Çocuk işlem ###
        *data += 1;
        printf("[Child] Data: %d\n", *data);
        shmdt(data); // Bellekten detach
        exit(0);
    } else { // ### Ana işlem ###
        wait(NULL); // Çocuğun bitmesini bekle
        *data += 1;
        printf("[Parent] Data: %d\n", *data);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL); // Segmenti kaldır
    }

    return 0;
}
