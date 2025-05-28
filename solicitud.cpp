#include "solicitud.h"

// Constructor para insertar solicitudes
Solicitud::Solicitud(int idSolicitud, int idUsuario, const QString &isbn,
                     const QString &tipo, const QString &estado, const QString &fecha)
    : id_solicitud(idSolicitud),
      id_usuario(idUsuario),
      isbn_libro(isbn),
      tipo(tipo),
      estado(estado),
      fecha_solicitud(fecha) {}

// Constructor para mostrar solicitudes (con datos de usuario y libro)
Solicitud::Solicitud(int idSolicitud, const QString &nombreUsuario, const QString &isbn,
                     const QString &tituloLibro, const QString &tipo,
                     const QString &estado, const QString &fecha)
    : id_solicitud(idSolicitud),
      nombre_usuario(nombreUsuario),
      isbn_libro(isbn),
      titulo_libro(tituloLibro),
      tipo(tipo),
      estado(estado),
      fecha_solicitud(fecha) {}

// Getters
int Solicitud::getIdSolicitud() const { return id_solicitud; }
int Solicitud::getIdUsuario() const { return id_usuario; }
QString Solicitud::getNombreUsuario() const { return nombre_usuario; }
QString Solicitud::getIsbnLibro() const { return isbn_libro; }
QString Solicitud::getTituloLibro() const { return titulo_libro; }
QString Solicitud::getTipo() const { return tipo; }
QString Solicitud::getEstado() const { return estado; }
QString Solicitud::getFechaSolicitud() const { return fecha_solicitud; }

// Setters
void Solicitud::setIdSolicitud(int id) { id_solicitud = id; }
void Solicitud::setIdUsuario(int id) { id_usuario = id; }
void Solicitud::setNombreUsuario(const QString &nombre) { nombre_usuario = nombre; }
void Solicitud::setIsbnLibro(const QString &isbn) { isbn_libro = isbn; }
void Solicitud::setTituloLibro(const QString &titulo) { titulo_libro = titulo; }
void Solicitud::setTipo(const QString &tipo) { this->tipo = tipo; }
void Solicitud::setEstado(const QString &estado) { this->estado = estado; }
void Solicitud::setFechaSolicitud(const QString &fecha) { fecha_solicitud = fecha; }
