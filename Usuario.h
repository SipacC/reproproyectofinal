#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario {
public:
    Usuario();
    Usuario(int id, const QString &nombre, const QString &correo, const QString &tipo, const QString &contrasena);
    Usuario(QString nombre, QString correo, QString tipo, QString contrasena); 

    int getId() const;
    QString getNombre() const;
    QString getCorreo() const;
    QString getTipo() const;
    QString getContrasena() const;

     void setId(int id);
    void setNombre(const QString &nombre);
    void setCorreo(const QString &correo);
    void setTipo(const QString &tipo);
    void setContrasena(const QString &contrasena);

private:
    int id; 
    QString nombre;
    QString correo;
    QString tipo;
    QString contrasena;
};

#endif // USUARIO_H
