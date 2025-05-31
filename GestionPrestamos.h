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

     QList<Prestamo> mostrarPrestamos();

    // Cambiar el estado de un préstamo identificado por usuario+isbn+fecha a "devuelto"
    bool devolverPrestamo(int idUsuario, const QString &isbnLibro, const QDate &fechaPrestamo);

private:
    Conexion conexion;
};

#endif // GESTIONPRESTAMOS_H
