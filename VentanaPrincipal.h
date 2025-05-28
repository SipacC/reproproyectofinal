#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "VentanaUno.h"
#include "VentanaDos.h"
#include "loginCreativo.h"

class VentanaPrincipal : public QWidget {
public:
    VentanaPrincipal(LoginCreativo* login, QWidget *parent = nullptr); // <-- constructor modificado

private:
    QPushButton *btnGestionUsuarios;
    QPushButton *btnGestionLibros;
    QPushButton *btnVolver;              // <-- nuevo botón
    QLabel *titulo;
    VentanaUno *ventanaUsuarios;
    VentanaDos *ventanaLibros;
    LoginCreativo* loginRef;             // <-- referencia al login

    void abrirVentanaUsuarios();
    void abrirVentanaLibros();
};

#endif // VENTANAPRINCIPAL_H
