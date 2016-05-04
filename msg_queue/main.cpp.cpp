//
// Created by jasf on 5/3/16.
//
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/wait.h>

# include <iostream>
#include <unistd.h>

using namespace std;

#define SND_MODE 0


int main() {
    int pid, queue_id, status;
    int queue_key = 0x1234;
    string tag;

    struct message {
        long type_id;
        char msg[100];
    };
    long magic_number = 0x0ABCDEFABCDEF990;

    struct message msg;

    if ((queue_id = msgget(queue_key, IPC_CREAT | 0x1FF)) < 0) {

        cout << "error while creating queue" << endl;
        return 0;

    }else{
        cout << "queue created with sucess!" << endl;
    }

    if ((pid = fork()) < 0) {
        cout << "error while forking" << endl;
        return 0;
    }
    else if (pid == 0) {
        // child code
        tag = "[child]";
        int max = 10;
        msg.type_id = magic_number;

        cout << tag << "running..." << endl;

        for (int i = 1; i <= max; i++) {

            msg.msg[0] = i;
            cout << tag << "sending msgs with val " << i << endl;
            msgsnd(queue_id, &msg, sizeof(message), 0);

        }
        msg.msg[0] = 0;
        msgsnd(queue_id, &msg, sizeof(message), 0);

        cout << tag << "exiting..." << endl;
        _exit(0);

    } else {
        //parent code
        tag = "[parent]";
        char val;
        cout << tag << "waiting for input..." << endl;

        do {
            msgrcv(queue_id, &msg, sizeof(message), magic_number, 0);
            val = msg.msg[0];

            cout << tag << "(" << (int)val << "," << (int)val * val << ")" << endl;

        } while (val > 0);

        wait(&status);

        return 0;
    }


}



