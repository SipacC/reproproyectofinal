#include "Libro.h"

// Constructor con parámetros por defecto
Libro::Libro(const QString &isbn, const QString &titulo, const QString &autor,
             const QString &editorial, int anioPublicacion, const QString &materia,
             const QString &estado, int ejemplares)
    : isbn(isbn), titulo(titulo), autor(autor), editorial(editorial),
      anioPublicacion(anioPublicacion), materia(materia), estado(estado), ejemplares(ejemplares) {}

// Getters
QString Libro::getISBN() const {
    return isbn;
}

QString Libro::getTitulo() const {
    return titulo;
}

QString Libro::getAutor() const {
    return autor;
}

QString Libro::getEditorial() const {
    return editorial;
}

int Libro::getAnioPublicacion() const {
    return anioPublicacion;
}

QString Libro::getMateria() const {
    return materia;
}

QString Libro::getEstado() const {
    return estado;
}

int Libro::getEjemplares() const {
    return ejemplares;
}

// Setters
void Libro::setTitulo(const QString &titulo) {
    this->titulo = titulo;
}

void Libro::setAutor(const QString &autor) {
    this->autor = autor;
}

void Libro::setEditorial(const QString &editorial) {
    this->editorial = editorial;
}

void Libro::setAnioPublicacion(int anio) {
    this->anioPublicacion = anio;
}

void Libro::setMateria(const QString &materia) {
    this->materia = materia;
}

void Libro::setEstado(const QString &estado) {
    this->estado = estado;
}

void Libro::setEjemplares(int cantidad) {
    ejemplares = cantidad;
}
