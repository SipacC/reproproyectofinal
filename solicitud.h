#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <QString>

class Solicitud {
private:
    int id_solicitud;
    int id_usuario;
    QString nombre_usuario;     // Para mostrar con JOIN
    QString isbn_libro;
    QString titulo_libro;       // Para mostrar con JOIN
    QString tipo;
    QString estado;
    QString fecha_solicitud;

public:
    // Constructor principal (para insertar y operaciones normales)
    Solicitud(int idSolicitud = 0,
              int idUsuario = 0,
              const QString &isbn = "",
              const QString &tipo = "",
              const QString &estado = "pendiente",
              const QString &fecha = "");

    // Constructor extendido (para mostrar en vista con JOIN)
    Solicitud(int idSolicitud,
              const QString &nombreUsuario,
              const QString &isbn,
              const QString &tituloLibro,
              const QString &tipo,
              const QString &estado,
              const QString &fecha);

    // Getters
    int getIdSolicitud() const;
    int getIdUsuario() const;
    QString getNombreUsuario() const;
    QString getIsbnLibro() const;
    QString getTituloLibro() const;
    QString getTipo() const;
    QString getEstado() const;
    QString getFechaSolicitud() const;

    // Setters
    void setIdSolicitud(int id);
    void setIdUsuario(int id);
    void setNombreUsuario(const QString &nombre);
    void setIsbnLibro(const QString &isbn);
    void setTituloLibro(const QString &titulo);
    void setTipo(const QString &tipo);
    void setEstado(const QString &estado);
    void setFechaSolicitud(const QString &fecha);
};

#endif // SOLICITUD_H
