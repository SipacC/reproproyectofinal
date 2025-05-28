#include "GestionLibro.h"
#include <QMessageBox>
#include <QDate>

GestionLibro::GestionLibro() {}

bool GestionLibro::agregarLibro(const Libro &libro) {
    if (libro.getISBN().isEmpty() || libro.getTitulo().isEmpty() || libro.getAutor().isEmpty() ||
        libro.getEditorial().isEmpty() || libro.getMateria().isEmpty() || libro.getEstado().isEmpty()) {
        QMessageBox::warning(nullptr, "Campos vacíos", "Por favor, complete todos los campos obligatorios.");
        return false;
    }

    int anio = libro.getAnioPublicacion();
    if (anio == 0 || anio < -9999 || anio > QDate::currentDate().year()) {
        QMessageBox::warning(nullptr, "Año inválido", "Ingrese un año válido entre -9999 (a.C.) y el año actual.");
        return false;
    }

    if (libro.getEjemplares() < 0) {
        QMessageBox::warning(nullptr, "Cantidad inválida", "La cantidad de ejemplares no puede ser negativa.");
        return false;
    }

    if (!conexion.conectar()) {
        return false;
    }

    QString query = QString(
        "INSERT INTO Libro (ISBN, Titulo, Autor, Editorial, Anio_publicacion, Materia, Estado, ejemplares) "
        "VALUES('%1', '%2', '%3', '%4', %5, '%6', '%7', %8)"
    ).arg(
        libro.getISBN(), libro.getTitulo(), libro.getAutor(), libro.getEditorial(),
        QString::number(libro.getAnioPublicacion()), libro.getMateria(), libro.getEstado(),
        QString::number(libro.getEjemplares())  // nuevo campo
    );

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al agregar", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return false;
    }

    QMessageBox::information(nullptr, "Éxito", "Libro agregado correctamente.");
    PQclear(res);
    conexion.desconectar();
    return true;
}

QList<Libro> GestionLibro::buscarLibros(const QString &termino, const QString &estado) {
    QList<Libro> resultados;

    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return resultados;
    }

    QString query = QString(
        "SELECT ISBN, Titulo, Autor, Editorial, Anio_publicacion, Materia, Estado, Ejemplares "
        "FROM Libro "
        "WHERE (ISBN ILIKE '%%%1%%' OR Titulo ILIKE '%%%1%%' OR Autor ILIKE '%%%1%%' "
        "OR Editorial ILIKE '%%%1%%' OR Materia ILIKE '%%%1%%' OR CAST(Anio_publicacion AS TEXT) ILIKE '%%%1%%') "
        "AND Estado ILIKE '%%%2%%'"
    ).arg(termino, estado);

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        QMessageBox::critical(nullptr, "Error al buscar", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return resultados;
    }

    int filas = PQntuples(res);
    for (int i = 0; i < filas; ++i) {
        QString isbn       = PQgetvalue(res, i, 0);
        QString titulo     = PQgetvalue(res, i, 1);
        QString autor      = PQgetvalue(res, i, 2);
        QString editorial  = PQgetvalue(res, i, 3);
        int anio           = QString(PQgetvalue(res, i, 4)).toInt();
        QString materia    = PQgetvalue(res, i, 5);
        QString estadoLibro = PQgetvalue(res, i, 6);
        int ejemplares     = QString(PQgetvalue(res, i, 7)).toInt();

        Libro libro(isbn, titulo, autor, editorial, anio, materia, estadoLibro, ejemplares);
        resultados.append(libro);
    }

    PQclear(res);
    conexion.desconectar();
    return resultados;
}


Libro GestionLibro::obtenerLibroPorISBN(const QString &isbn) {
    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return Libro();
    }

    QString query = QString("SELECT ISBN, Titulo, Autor, Editorial, Anio_publicacion, Materia, Estado "
                            "FROM Libro WHERE ISBN = '%1'").arg(isbn);

    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());
    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        PQclear(res);
        conexion.desconectar();
        return Libro(); // libro vacío
    }

    QString titulo     = PQgetvalue(res, 0, 1);
    QString autor      = PQgetvalue(res, 0, 2);
    QString editorial  = PQgetvalue(res, 0, 3);
    int anio           = QString(PQgetvalue(res, 0, 4)).toInt();
    QString materia    = PQgetvalue(res, 0, 5);
    QString estadoLibro = PQgetvalue(res, 0, 6);

    Libro libro(isbn, titulo, autor, editorial, anio, materia, estadoLibro);

    PQclear(res);
    conexion.desconectar();
    return libro;
}

bool GestionLibro::eliminarLibro(const QString &isbn, const QString &tituloConfirmacion) {
    Libro libro = obtenerLibroPorISBN(isbn);
    if (libro.getISBN().isEmpty()) {
        QMessageBox::warning(nullptr, "Libro no encontrado", "No se encontró ningún libro con ese ISBN.");
        return false;
    }

    if (libro.getTitulo().toLower() != tituloConfirmacion.toLower()) {
        QMessageBox::warning(nullptr, "Confirmación incorrecta", "El título proporcionado no coincide con el libro.");
        return false;
    }

    if (!conexion.conectar()) {
        QMessageBox::critical(nullptr, "Error de conexión", "No se pudo conectar a la base de datos.");
        return false;
    }

    QString query = QString("DELETE FROM Libro WHERE ISBN = '%1'").arg(isbn);
    PGresult *res = PQexec(conexion.conn, query.toUtf8().constData());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        QMessageBox::critical(nullptr, "Error al eliminar", PQerrorMessage(conexion.conn));
        PQclear(res);
        conexion.desconectar();
        return false;
    }

    PQclear(res);
    conexion.desconectar();
    return true;
}