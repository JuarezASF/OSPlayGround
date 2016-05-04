#include <unistd.h>
#include <sys/wait.h>

#include <iostream>
#include <vector>

using namespace std;
string tag = "[]";

void log(string msg) {
    cout << tag << msg << endl;
}

int main(int argc, char **argv) {
    int pid, uid;

    //create two way pipe
    int fd[2];

    int err = pipe(fd);

    char msg[100];

    if (err < 0) {
        cout << "Error while creating pipe" << endl;
        return 0;
    }


    tag = "[parent]";

    char greeting = 0xCD;
    int status;

    if ((pid = fork()) < 0) {
        log("error while forking");
        return 0;
    } else if (pid == 0) {
        //child code
        //forbids child to read from pipe
        fd[0] = 0;
        tag = "[child#" + to_string(0) + "]";
        cout << tag << "executing..." << endl;
        vector<string> myClasses{"SO", "OA", "Automatos", "IDJ", "TG1"};

        msg[0] = greeting;
        write(fd[1], msg, 1);

        for (auto s : myClasses) {
            s.copy(msg + 1, s.size(), 0);
            msg[s.size() + 1] = '\0';
            msg[0] = (char) s.size() + 1;
            write(fd[1], msg, 1 + msg[0]);
        }
        msg[0] = 0;
        write(fd[1], msg, 1 + msg[0]);
        _exit(0);
    } else {
        //forbids parent to write to pipe
        fd[1] = 0;
        char msg_size = 1;
        int i = 0;

        do {
            read(fd[0], msg, msg_size);
            if (i == 0) {
                if (msg[0] != greeting) {
                    cout << tag << "protocol failure!" << endl;
                    break;
                }
                i++;
            }else{
                string myClass(msg, msg_size-1);

                cout << tag << myClass << endl;
            }

            read(fd[0], msg, 1);

            msg_size = msg[0];

        } while (msg_size > 0);

        wait(&status);
        return 0;


    }


    return 0;


}
