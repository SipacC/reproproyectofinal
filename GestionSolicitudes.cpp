#include "GestionSolicitudes.h"
#include <QMessageBox>
#include <QDateTime>

GestionSolicitudes::GestionSolicitudes() {}

bool GestionSolicitudes::registrarSolicitud(const Solicitud &solicitud) {
    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return false;
    }

    QString fechaFinal = solicitud.getFechaSolicitud().isEmpty()
                         ? QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                         : solicitud.getFechaSolicitud();

    QString insertQuery = QString(
        "INSERT INTO Solicitud (id_usuario, isbn_libro, tipo, estado, fecha_solicitud) "
        "VALUES (%1, '%2', '%3', '%4', '%5')"
    ).arg(solicitud.getIdUsuario())
     .arg(solicitud.getIsbnLibro())
     .arg(solicitud.getTipo())
     .arg(solicitud.getEstado())
     .arg(fechaFinal);

    PGresult *res = PQexec(conexion.conn, insertQuery.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al registrar solicitud", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return false;
    }

    PQclear(res);
    conexion.desconectar();
    return true;
}

QList<Solicitud> GestionSolicitudes::obtenerSolicitudesFiltradas(int id, const QString &estado) {
    QList<Solicitud> lista;

    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return lista;
    }

    QString query = R"(
        SELECT 
            id_solicitud,
            id_usuario,
            isbn_libro,
            tipo,
            estado,
            fecha_solicitud
        FROM Solicitud
        WHERE 1=1
    )";

    if (id > 0) {
        query += QString(" AND id_solicitud = %1").arg(id);
    }

    if (!estado.isEmpty()) {
        query += QString(" AND estado = '%1'").arg(estado);
    }

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        QMessageBox::critical(nullptr, "Error al obtener solicitudes", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return lista;
    }

    int filas = PQntuples(res);
    for (int i = 0; i < filas; ++i) {
        int id_solicitud = QString(PQgetvalue(res, i, 0)).toInt();
        int id_usuario = QString(PQgetvalue(res, i, 1)).toInt();
        QString isbn = PQgetvalue(res, i, 2);
        QString tipo = PQgetvalue(res, i, 3);
        QString estado_solicitud = PQgetvalue(res, i, 4);
        QString fecha = PQgetvalue(res, i, 5);
        Solicitud solicitud(id_solicitud, id_usuario, isbn, tipo, estado_solicitud, fecha);
        lista.append(solicitud);
    }

    PQclear(res);
    conexion.desconectar();
    return lista;
}

bool GestionSolicitudes::actualizarEstadoSolicitud(int idSolicitud, const QString &nuevoEstado) {
    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return false;
    }

    QString query = QString("UPDATE Solicitud SET estado = '%1' WHERE id_solicitud = %2")
                    .arg(nuevoEstado)
                    .arg(idSolicitud);

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al actualizar", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return false;
    }

    PQclear(res);
    conexion.desconectar();
    return true;
}
