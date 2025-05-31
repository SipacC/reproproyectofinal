#ifndef GESTIONPRESTAMOS_H
#define GESTIONPRESTAMOS_H

#include "Conexion.h"
#include "Prestamo.h"
#include <QList>

class GestionPrestamos {
public:
    GestionPrestamos();

    // Registra un nuevo préstamo en la base de datos
    bool registrarPrestamo(const Prestamo &prestamo);

    // Aquí luego se pueden agregar más métodos como:
    // bool devolverPrestamo(int idPrestamo);
    // QList<Prestamo> buscarPrestamos(int idUsuario);
    // QList<Prestamo> listarPrestamos();

private:
    Conexion conexion;
};

#endif // GESTIONPRESTAMOS_H
