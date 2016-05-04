#include <unistd.h>
#include <sys/wait.h>

#include <iostream>

using namespace std;
string  tag = "[]";

void log(string msg){
    cout << tag <<  msg << endl;
}

int main(int argc, char **argv){
    int pid, uid, ppid, euid;

    int qtd = 3;
    tag = "[parent]";

    for (int i = 0; i < qtd; i++){
        if ((pid = fork()) < 0){
            log("error while forking");
            return 0;
        }else if( pid == 0){
            //child code
            tag = "[child#" + to_string(i) + "]";
            cout << tag << "executing..." << endl;
            // playing with primitives
            uid = getuid();
            pid = getpid();
            ppid = getppid();
            euid = geteuid();
            cout << tag << "uid:" << uid << endl;
            cout << tag << "pid:" << pid << endl;
            cout << tag << "ppid:" << ppid << endl;
            cout << tag << "euid:" << euid << endl;
            _exit(-1 -1 * pid);
        } else {
            cout << tag << "just created child " << pid << endl;
        }
    }

    int status;
    for (int i = 0; i < qtd; i++){
        wait(&status);
        cout << "received exit signal from child " << -1*status -1 << endl;

    }
    // playing with primitives
    uid = getuid();
    pid = getpid();
    ppid = getppid();
    euid = geteuid();

    cout << tag << "uid:" << uid << endl;
    cout << tag << "pid:" << pid << endl;
    cout << tag << "ppid:" << ppid << endl;
    cout << tag << "euid:" << euid << endl;


    return 0;


}
