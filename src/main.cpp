

// Own
#include <Daemon.hpp>

// STD
#include <cstdio>

// UNIX
#include <signal.h>


Daemon * daemon;

void terminar(int sig);

int main()
{
    char str[20];
    daemon = new Daemon();

    signal(SIGTERM, &terminar);

    std::sprintf(str, "Estado: %d\n", daemon->estado());
    daemon->escribeLog(str);

    while(1) ;
}

void terminar(int sig)
{
    delete daemon;
}

