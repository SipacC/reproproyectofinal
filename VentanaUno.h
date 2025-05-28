#ifndef VENTANAUNO_H
#define VENTANAUNO_H

#include <QWidget>

class VentanaPrincipal;  // Declaración adelantada

class VentanaUno : public QWidget {
public:
    VentanaUno(VentanaPrincipal *ventanaPrincipal, QWidget *parent = nullptr);

private:
    VentanaPrincipal *principal;
};

#endif // VENTANAUNO_H
