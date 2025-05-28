#ifndef LIBRO_H
#define LIBRO_H

#include <QString>

class Libro {
private:
    QString isbn;
    QString titulo;
    QString autor;
    QString editorial;
    int anioPublicacion;
    QString materia;
    QString estado; // "disponible" o "prestado"
    int ejemplares;

public:
    // Constructor
    Libro(const QString &isbn = "", const QString &titulo = "", const QString &autor = "",
          const QString &editorial = "", int anioPublicacion = 0, const QString &materia = "",
          const QString &estado = "disponible", int ejemplares = 0);

    // Getters (const)
    QString getISBN() const;
    QString getTitulo() const;
    QString getAutor() const;
    QString getEditorial() const;
    int getAnioPublicacion() const;
    QString getMateria() const;
    QString getEstado() const;
    int getEjemplares() const;

    // Setters (modificadores)
    void setTitulo(const QString &titulo);
    void setAutor(const QString &autor);
    void setEditorial(const QString &editorial);
    void setAnioPublicacion(int anio);
    void setMateria(const QString &materia);
    void setEstado(const QString &estado);
    void setEjemplares(int cantidad);
};

#endif // LIBRO_H
