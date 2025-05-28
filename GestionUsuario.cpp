#include "GestionUsuario.h"
#include <QMessageBox>
#include <QCryptographicHash>

GestionUsuario::GestionUsuario() {}

bool GestionUsuario::agregarUsuario(const Usuario &usuario) {
    if (usuario.getNombre().isEmpty() || usuario.getCorreo().isEmpty() || usuario.getContrasena().isEmpty()) {
        QMessageBox::warning(nullptr, "Campos vacíos", "Por favor, complete todos los campos.");
        return false;
    }

    if (usuario.getNombre().contains(" ")) {
        QMessageBox::warning(nullptr, "Nombre inválido", "El nombre de usuario no debe contener espacios.");
        return false;
    }

    // Encriptar la contraseña con SHA-256
    QString contrasenaHasheada = QCryptographicHash::hash(usuario.getContrasena().toUtf8(), QCryptographicHash::Sha256).toHex();

    // Conexión a la base de datos
    if (!conexion.conectar()) {
        return false;
    }

    QString query = QString("INSERT INTO Usuario (Nombre, Correo, Tipo, Contrasena) "
                            "VALUES('%1', '%2', '%3', '%4')")
                            .arg(usuario.getNombre(), usuario.getCorreo(), usuario.getTipo(), contrasenaHasheada);

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al agregar", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return false;
    }

    QMessageBox::information(nullptr, "Éxito", "Usuario agregado correctamente.");
    PQclear(res);
    conexion.desconectar();
    return true;
}


QList<Usuario> GestionUsuario::buscarUsuarios(int id, const QString &nombre, const QString &tipo) {
    QList<Usuario> lista;

    if (!conexion.conectar()) return lista;

    QString query = "SELECT Id_usuario, Nombre, Correo, Tipo FROM Usuario WHERE 1=1";

    if (id > 0) {
        query += QString(" AND id_usuario = %1").arg(id);
    }
    
    if (!nombre.isEmpty()) {
        query += QString(" AND LOWER(Nombre) LIKE '%%1%%'").arg(nombre.toLower());


    }

    if (tipo != "Todos") {
        query += QString(" AND Tipo = '%1'").arg(tipo);
    }

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; ++i) {
            int id = QString(PQgetvalue(res, i, 0)).toInt();
            QString nombre = PQgetvalue(res, i, 1);
            QString correo = PQgetvalue(res, i, 2);
            QString tipo = PQgetvalue(res, i, 3);
            lista.append(Usuario(id, nombre, correo, tipo, ""));
        }
    }

    PQclear(res);
    conexion.desconectar();
    return lista;
}

QString GestionUsuario::obtenerNombrePorId(int id) {
    QString nombre;

    if (!conexion.conectar()) {
        return nombre;  // Retorna vacío si no se pudo conectar
    }

    QString query = QString("SELECT Nombre FROM Usuario WHERE id_usuario = %1").arg(id);

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
        nombre = PQgetvalue(res, 0, 0);  // Obtener el primer resultado (Nombre)
    }

    PQclear(res);
    conexion.desconectar();
    return nombre;
}
bool GestionUsuario::modificarUsuario(int id, const Usuario &usuario) {
    if (id <= 0) {
        QMessageBox::warning(nullptr, "ID inválido", "El ID del usuario no es válido.");
        return false;
    }

    if (usuario.getNombre().isEmpty() || usuario.getCorreo().isEmpty() || usuario.getContrasena().isEmpty()) {
        QMessageBox::warning(nullptr, "Campos vacíos", "Por favor, complete todos los campos.");
        return false;
    }

    if (usuario.getNombre().contains(" ")) {
        QMessageBox::warning(nullptr, "Nombre inválido", "El nombre de usuario no debe contener espacios.");
        return false;
    }

    if (!conexion.conectar()) {
        return false;
    }

    QString query = QString("UPDATE Usuario SET "
                            "Nombre = '%1', Correo = '%2', Tipo = '%3', Contrasena = '%4' "
                            "WHERE id_usuario = %5")
                        .arg(usuario.getNombre(),
                             usuario.getCorreo(),
                             usuario.getTipo(),
                             usuario.getContrasena())  // ← ya viene hasheada desde VentModificar
                        .arg(id);

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_COMMAND_OK || atoi(PQcmdTuples(res)) == 0) {
        QMessageBox::critical(nullptr, "Error al modificar", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return false;
    }

    PQclear(res);
    conexion.desconectar();
    return true;
}
