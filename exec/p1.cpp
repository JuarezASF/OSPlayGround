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

    tag = "[p1]";

    // playing with primitives
    uid = getuid();
    pid = getpid();
    ppid = getppid();
    euid = geteuid();

    cout << tag << "uid:" << uid << endl;
    cout << tag << "pid:" << pid << endl;
    cout << tag << "ppid:" << ppid << endl;
    cout << tag << "euid:" << euid << endl;

    int *p;

    *p = 12;

    _exit(0);



}
