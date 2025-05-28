#ifndef GESTIONSOLICITUDES_H
#define GESTIONSOLICITUDES_H

#include "Conexion.h"
#include "Solicitud.h"
#include <QList>

class GestionSolicitudes {
public:
    GestionSolicitudes();

    bool registrarSolicitud(const Solicitud &solicitud);
    QList<Solicitud> obtenerSolicitudes(const QString &estadoFiltro = "", const QString &busqueda = "");
    QList<Solicitud> obtenerSolicitudesFiltradas(int id, const QString &estado);
    bool actualizarEstadoSolicitud(int idSolicitud, const QString &nuevoEstado);
    



private:
    Conexion conexion;
};

#endif // GESTIONSOLICITUDES_H
