#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

struct Data {
    int flag;
    char msg[100];
};

int main() {
    key_t key = ftok("chatfile", 65);
    int id = shmget(key, sizeof(Data), 0666 | IPC_CREAT);
    Data *d = (Data*)shmat(id, NULL, 0);

    d->flag = 0;

    while (true) {
        while (d->flag == 1);

        cout << "Writer: ";
        cin.getline(d->msg, 100);

        d->flag = 1;

        if (strcmp(d->msg, "exit") == 0)
            break;
    }

    shmdt(d);
    return 0;
}