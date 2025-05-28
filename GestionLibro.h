#ifndef GESTIONLIBRO_H
#define GESTIONLIBRO_H

#include "Libro.h"
#include "Conexion.h"

class GestionLibro {
public:
    GestionLibro();
    bool agregarLibro(const Libro &libro);

    QList<Libro> buscarLibros(const QString &termino, const QString &estado);

    Libro obtenerLibroPorISBN(const QString &isbn);
    bool eliminarLibro(const QString &isbn, const QString &tituloConfirmacion);

private:
    Conexion conexion;
};

#endif // GESTIONLIBRO_H
