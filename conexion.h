#ifndef CONEXION_H
#define CONEXION_H

#include <libpq-fe.h>
#include <QString>

class Conexion {
public:
    PGconn *conn;  // Ahora es público

    Conexion();
    ~Conexion();

    bool conectar();
    void desconectar();
};

#endif // CONEXION_H
