#include "GestionPrestamos.h"
#include <QMessageBox>
#include <QDate>

GestionPrestamos::GestionPrestamos() {}

bool GestionPrestamos::registrarPrestamo(const Prestamo &prestamo) {
    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return false;
    }

    // 1. Verificar si ya existe un préstamo duplicado
    QString checkQuery = QString(
        "SELECT COUNT(*) FROM Prestamo WHERE id_usuario = %1 AND isbn_libro = '%2' AND fecha_prestamo = '%3'"
    ).arg(prestamo.getIdUsuario())
     .arg(prestamo.getIsbnLibro())
     .arg(prestamo.getFechaPrestamo().toString("yyyy-MM-dd"));

    PGresult *checkRes = PQexec(conexion.conn, checkQuery.toUtf8().constData());
    if (PQresultStatus(checkRes) != PGRES_TUPLES_OK) {
        QMessageBox::critical(nullptr, "Error al verificar duplicados", PQerrorMessage(conexion.conn));
        PQclear(checkRes);
        conexion.desconectar();
        return false;
    }

    int count = QString(PQgetvalue(checkRes, 0, 0)).toInt();
    PQclear(checkRes);

    if (count > 0) {
        QMessageBox::warning(nullptr, "Préstamo duplicado", "Ya existe un préstamo registrado con esos datos.");
        conexion.desconectar();
        return false;
    }

    // 2. Verificar ejemplares disponibles del libro
    QString ejemplaresQuery = QString(
        "SELECT ejemplares FROM Libro WHERE ISBN = '%1'"
    ).arg(prestamo.getIsbnLibro());

    PGresult *ejemplaresRes = PQexec(conexion.conn, ejemplaresQuery.toUtf8().constData());
    if (PQresultStatus(ejemplaresRes) != PGRES_TUPLES_OK || PQntuples(ejemplaresRes) == 0) {
        QMessageBox::critical(nullptr, "Error", "No se pudo verificar los ejemplares del libro.");
        PQclear(ejemplaresRes);
        conexion.desconectar();
        return false;
    }

    int ejemplares = QString(PQgetvalue(ejemplaresRes, 0, 0)).toInt();
    PQclear(ejemplaresRes);

    if (ejemplares <= 0) {
        QMessageBox::warning(nullptr, "Sin ejemplares", "No hay ejemplares disponibles para este libro.");
        conexion.desconectar();
        return false;
    }

    // 3. Insertar el préstamo en la base de datos
    QString insertQuery = QString(
        "INSERT INTO Prestamo (id_usuario, isbn_libro, fecha_prestamo, fecha_devolucion, estado) "
        "VALUES (%1, '%2', '%3', '%4', '%5')"
    ).arg(prestamo.getIdUsuario())
     .arg(prestamo.getIsbnLibro())
     .arg(prestamo.getFechaPrestamo().toString("yyyy-MM-dd"))
     .arg(prestamo.getFechaDevolucion().toString("yyyy-MM-dd"))
     .arg(prestamo.getEstado());

    PGresult *insertRes = PQexec(conexion.conn, insertQuery.toUtf8().constData());
    if (PQresultStatus(insertRes) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al registrar préstamo", PQerrorMessage(conexion.conn));
        PQclear(insertRes);
        conexion.desconectar();
        return false;
    }
    PQclear(insertRes);

    // 4. Actualizar ejemplares disponibles (restar 1)
    QString updateEjemplaresQuery = QString(
        "UPDATE Libro SET ejemplares = ejemplares - 1 WHERE ISBN = '%1'"
    ).arg(prestamo.getIsbnLibro());

    PGresult *updateEjemplaresRes = PQexec(conexion.conn, updateEjemplaresQuery.toUtf8().constData());
    if (PQresultStatus(updateEjemplaresRes) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al actualizar ejemplares", PQerrorMessage(conexion.conn));
        PQclear(updateEjemplaresRes);
        conexion.desconectar();
        return false;
    }
    PQclear(updateEjemplaresRes);

    // 5. Verificar si después de restar, los ejemplares son 0
    QString checkAfterUpdateQuery = QString(
        "SELECT ejemplares FROM Libro WHERE ISBN = '%1'"
    ).arg(prestamo.getIsbnLibro());

    PGresult *checkFinalEjemplaresRes = PQexec(conexion.conn, checkAfterUpdateQuery.toUtf8().constData());
    if (PQresultStatus(checkFinalEjemplaresRes) != PGRES_TUPLES_OK || PQntuples(checkFinalEjemplaresRes) == 0) {
        QMessageBox::critical(nullptr, "Error", "No se pudo verificar los ejemplares actualizados.");
        PQclear(checkFinalEjemplaresRes);
        conexion.desconectar();
        return false;
    }

    int ejemplaresRestantes = QString(PQgetvalue(checkFinalEjemplaresRes, 0, 0)).toInt();
    PQclear(checkFinalEjemplaresRes);

    if (ejemplaresRestantes == 0) {
        // 6. Cambiar estado del libro a 'prestado' solo si los ejemplares son 0
        QString updateEstadoQuery = QString(
            "UPDATE Libro SET estado = 'prestado' WHERE ISBN = '%1'"
        ).arg(prestamo.getIsbnLibro());

        PGresult *updateEstadoRes = PQexec(conexion.conn, updateEstadoQuery.toUtf8().constData());
        if (PQresultStatus(updateEstadoRes) != PGRES_COMMAND_OK) {
            QMessageBox::critical(nullptr, "Error al actualizar estado del libro", PQerrorMessage(conexion.conn));
            PQclear(updateEstadoRes);
            conexion.desconectar();
            return false;
        }
        PQclear(updateEstadoRes);
    }

    conexion.desconectar();
    return true;
}
