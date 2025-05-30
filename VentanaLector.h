#ifndef VENTANALECTOR_H
#define VENTANALECTOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "LoginCreativo.h"
#include "BuscarLibrosUs.h"
//#include "VentSolicitud.h"

class VentanaLector : public QWidget {

public:
    explicit VentanaLector(LoginCreativo* login, QWidget *parent = nullptr);

private:
    QLabel *titulo;
    QPushButton *btnBuscarLibros;
    QPushButton *btnSolicitudes;
    QPushButton *btnVolver;

    QWidget *ventanaSolicitudes;
    BuscarLibrosUs *ventanaBuscarLibros;
    LoginCreativo* loginRef;
};

#endif // VENTANALECTOR_H
