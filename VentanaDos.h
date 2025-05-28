#ifndef VENTANADOS_H
#define VENTANADOS_H

#include <QWidget>

class VentanaPrincipal;

class VentanaDos : public QWidget {
public:
    VentanaDos(VentanaPrincipal *ventanaPrincipal, QWidget *parent = nullptr);
private:
    VentanaPrincipal *principal;
};

#endif // VENTANADOS_H
