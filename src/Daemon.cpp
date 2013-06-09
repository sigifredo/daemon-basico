

#include <Daemon.hpp>

// STD / UNIX
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#define ARCHIVO_LOG	"/tmp/daemon.log"
// #define ARCHIVO_PID	"/var/run/daemon.pid"
#define ARCHIVO_PID	"/tmp/daemon.pid"

Daemon::Daemon()
{
    pid_t pid, sid;
    int iChdir;
    _eEstado = Falla;

    /* creamos el proceso hijo */
    pid = fork();

    if (pid >= 0)
    {
        /* Cuando tenemos un PID correcto podemos cerrar
         * el proceso padre.
         * Atención al control de errores, es una buena
         * técnica de programación comprobar todas las
         * situaciones donde se pueden dar errores. */
        if (pid > 0)
        {
            guardarPID(pid);
            exit(EXIT_SUCCESS);
        }

        /* Cambiamos el modo de la mascara de ficheros */
        /* Hacemos esto para que los fichero generados por el
         * demonio sean accesibles por todo el mundo */
        umask(0);

        /* Creamos un nuevo SID */
        /* Esto se hace porque al haber matado al padre el hijo puede quedarse
         * en el sistema como un proceso zombie, generando un nuevo SID hacemos
         * que el sistema se haga cargo del proceso huérfano otorgándole un nuevo SID */
        if (setsid() < 0)
            perror("Falla la creación del nuevo SID.");
        else
        {
            /* Por seguridad, cambiamos el directorio de trabajo */
            if (chdir("/") < 0)
                perror("Falla en el cambio de directorio de trabajo actual.");
            else
                _eEstado = Activo;
        }

        /*
         * Cerramos los descriptores standard
         * El demonio no puede usar la terminal, por lo que estos
         * descriptores son inútiles y un posible riesgo de seguridad.
         */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }
}

Daemon::~Daemon()
{
    if (_eEstado == Activo && remove(ARCHIVO_PID) != 0)
        perror("No ha sido posible eliminar el archivo.");
}

bool Daemon::escribeLog(char * str)
{
    int fd = open(ARCHIVO_LOG, O_WRONLY | O_CREAT, 0600);

    if (fd == -1)
    {
        perror ("Error en la apertura del archivo de log.");

        return false;
    }
    else
    {
        write(fd, str, strlen(str));
        close(fd);

        return true;
    }
}

void Daemon::guardarPID(const pid_t& pid)
{
    int fd;
    char spid[7];

    if ((fd = open(ARCHIVO_PID, O_WRONLY | O_CREAT, 0600)) == -1)
    {
        perror("Error en la apertura del fichero.");
        _eEstado = Falla;
    }
    else
    {
        memset(spid, '\0', 7);
        sprintf(spid, "%d\n", pid);

        write(fd, spid, strlen(spid));
        close(fd);
    }
}

