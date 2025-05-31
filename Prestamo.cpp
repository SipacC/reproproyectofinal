#include "Prestamo.h"

// Constructor por defecto
Prestamo::Prestamo() : id(0), idUsuario(0), isbnLibro(""), estado("activo") {}

// Constructor para insertar en base de datos (sin id)
Prestamo::Prestamo(int idUsuario, const QString &isbnLibro, const QDate &fechaPrestamo, const QDate &fechaDevolucion, const QString &estado)
    : id(0), idUsuario(idUsuario), isbnLibro(isbnLibro), fechaPrestamo(fechaPrestamo), fechaDevolucion(fechaDevolucion), estado(estado) {}

// Constructor para consultar (con id)
Prestamo::Prestamo(int id, int idUsuario, const QString &isbnLibro, const QDate &fechaPrestamo, const QDate &fechaDevolucion, const QString &estado)
    : id(id), idUsuario(idUsuario), isbnLibro(isbnLibro), fechaPrestamo(fechaPrestamo), fechaDevolucion(fechaDevolucion), estado(estado) {}

// Getters
int Prestamo::getId() const {
    return id;
}

int Prestamo::getIdUsuario() const {
    return idUsuario;
}

QString Prestamo::getIsbnLibro() const {
    return isbnLibro;
}

QDate Prestamo::getFechaPrestamo() const {
    return fechaPrestamo;
}

QDate Prestamo::getFechaDevolucion() const {
    return fechaDevolucion;
}

QString Prestamo::getEstado() const {
    return estado;
}

// Setters
void Prestamo::setId(int id) {
    this->id = id;
}

void Prestamo::setIdUsuario(int idUsuario) {
    this->idUsuario = idUsuario;
}

void Prestamo::setIsbnLibro(const QString &isbn) {
    isbnLibro = isbn;
}

void Prestamo::setFechaPrestamo(const QDate &fecha) {
    fechaPrestamo = fecha;
}

void Prestamo::setFechaDevolucion(const QDate &fecha) {
    fechaDevolucion = fecha;
}

void Prestamo::setEstado(const QString &estado) {
    this->estado = estado;
}
