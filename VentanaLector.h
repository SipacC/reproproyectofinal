#ifndef VENTANALECTOR_H
#define VENTANALECTOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "LoginCreativo.h"
#include "BuscarLibrosUs.h"

class VentanaSolicitudesUs;

class VentanaLector : public QWidget {

public:
    explicit VentanaLector(LoginCreativo* login, QWidget *parent = nullptr);

private:
    QLabel *titulo;
    QPushButton *btnBuscarLibros;
    QPushButton *btnSolicitudes;
    QPushButton *btnVolver;

    VentanaSolicitudesUs *ventanaSolicitudes;
    BuscarLibrosUs *ventanaBuscarLibros;
    LoginCreativo* loginRef;
    int idUsuario;
};

#endif // VENTANALECTOR_H
