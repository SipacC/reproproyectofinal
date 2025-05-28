#ifndef GESTIONUSUARIO_H
#define GESTIONUSUARIO_H

#include "Usuario.h"
#include "Conexion.h"

class GestionUsuario {
public:
    GestionUsuario();
    bool agregarUsuario(const Usuario &usuario);
    QList<Usuario> buscarUsuarios(int id = 0, const QString &nombre = "", const QString &tipo = "Todos");
    bool modificarUsuario(const Usuario &usuario);
    QString obtenerNombrePorId(int id);
    bool modificarUsuario(int id, const Usuario &usuario);
    

private:
    Conexion conexion;
};

#endif // GESTIONUSUARIO_H
