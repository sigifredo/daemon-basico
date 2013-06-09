

#ifndef DAEMON_HPP
#define DAEMIN_HPP


#include <cstdlib>

class Daemon
{
public:
    enum DaemonEstado { Activo = EXIT_SUCCESS, Falla = EXIT_FAILURE };

    Daemon();
    ~Daemon();

    DaemonEstado estado() const;
    bool escribeLog(char * str);

protected:
    DaemonEstado _eEstado;

private:
    void guardarPID(const pid_t& pid);
};

inline Daemon::DaemonEstado Daemon::estado() const
{
    return _eEstado;
}

#endif

