#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <QString>
#include <QDate>

class Prestamo {
private:
    int id;
    int idUsuario;
    QString isbnLibro;
    QDate fechaPrestamo;
    QDate fechaDevolucion;
    QString estado;

public:
    // Constructores
    Prestamo();
    Prestamo(int idUsuario, const QString &isbnLibro, const QDate &fechaPrestamo, const QDate &fechaDevolucion, const QString &estado);
    Prestamo(int id, int idUsuario, const QString &isbnLibro, const QDate &fechaPrestamo, const QDate &fechaDevolucion, const QString &estado);

    // Getters
    int getId() const;
    int getIdUsuario() const;
    QString getIsbnLibro() const;
    QDate getFechaPrestamo() const;
    QDate getFechaDevolucion() const;
    QString getEstado() const;

    // Setters
    void setId(int id);
    void setIdUsuario(int idUsuario);
    void setIsbnLibro(const QString &isbn);
    void setFechaPrestamo(const QDate &fecha);
    void setFechaDevolucion(const QDate &fecha);
    void setEstado(const QString &estado);
};

#endif // PRESTAMO_H
