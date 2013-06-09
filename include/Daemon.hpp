

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
    /**
     * Revisa que no exista una instancia del demonio corriendo actualmente.
     *
     * \return Retorna verdadero si el proceso ya existe, de lo contrario, retorna falso.
     *
     */
    bool pidExiste();
    void guardarPID(const pid_t& pid);
};

inline Daemon::DaemonEstado Daemon::estado() const
{
    return _eEstado;
}

#endif

