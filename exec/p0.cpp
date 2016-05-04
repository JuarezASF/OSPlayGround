#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;
string  tag = "[]";


int main(int argc, char **argv){
    int pid, uid, ppid, euid;

    if ((pid = fork()) < 0){
        cout << tag << "error while forking!" << endl;
        }
    if (pid == 0){
        int err = execl("p1", "p1", (char *) 0);
        cout << "failed while running execl!" << std::endl;
        cout << "returned error is " << err << std::endl;
        return 0;
    }
    tag = "[p0]";

    int status = 0;
    wait(& status);

    cout << tag << "wait returned " << status << endl;


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
