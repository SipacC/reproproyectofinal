#ifndef VENTBUSCAR_H
#define VENTBUSCAR_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "GestionUsuario.h"

class  VentanaUno;

class VentBuscar : public QWidget {
public:
    VentBuscar(VentanaUno *anterior = nullptr);

private:
    VentanaUno *ventanaAnterior;
    QLineEdit *inputBuscarNombre;
    QComboBox *comboFiltroTipo;
    QTableWidget *tablaUsuarios;
    QPushButton *btnVolver;

    void cargarUsuarios();
};

#endif // VENTBUSCAR_H
