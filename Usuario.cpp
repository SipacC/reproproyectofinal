#include "Usuario.h"

Usuario::Usuario() : id(-1), nombre(""), correo(""), tipo(""), contrasena("") {}

Usuario::Usuario(int id, const QString &nombre, const QString &correo, const QString &tipo, const QString &contrasena)
    : id(id), nombre(nombre), correo(correo), tipo(tipo), contrasena(contrasena) {}

Usuario::Usuario(QString nombre, QString correo, QString tipo, QString contrasena)
    : id(-1), nombre(nombre), correo(correo), tipo(tipo), contrasena(contrasena) {}


int Usuario::getId() const {
    return id;
}

QString Usuario::getNombre() const {
    return nombre;
}

QString Usuario::getCorreo() const {
    return correo;
}

QString Usuario::getTipo() const {
    return tipo;
}

QString Usuario::getContrasena() const {
    return contrasena;
}

void Usuario::setId(int id) {
    this->id = id;
}

void Usuario::setNombre(const QString &nombre) {
    this->nombre = nombre;
}

void Usuario::setCorreo(const QString &correo) {
    this->correo = correo;
}

void Usuario::setTipo(const QString &tipo) {
    this->tipo = tipo;
}

void Usuario::setContrasena(const QString &contrasena) {
    this->contrasena = contrasena;
}
