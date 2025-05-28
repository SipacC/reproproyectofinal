// SesionUsuario.h
#ifndef SESIONUSUARIO_H
#define SESIONUSUARIO_H

#include <QString>

class SesionUsuario {
public:
    static SesionUsuario& instancia() {
        static SesionUsuario instancia;
        return instancia;
    }

    void setUsuario(const QString& nombre, int id, const QString& tipo) {
        nombreUsuario = nombre;
        idUsuario = id;
        tipoUsuario = tipo;
    }

    QString getNombreUsuario() const { return nombreUsuario; }
    int getIdUsuario() const { return idUsuario; }
    QString getTipoUsuario() const { return tipoUsuario; }

private:
    QString nombreUsuario;
    int idUsuario = -1;
    QString tipoUsuario;

    // Evita instanciación externa
    SesionUsuario() {}
    SesionUsuario(const SesionUsuario&) = delete;
    void operator=(const SesionUsuario&) = delete;
};

#endif // SESIONUSUARIO_H
