#ifndef BUSCARLIBRO_H
#define BUSCARLIBRO_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "GestionLibro.h"

class VentanaDos; // Declaración adelantada

class BuscarLibro : public QWidget {
public:
    BuscarLibro(VentanaDos* ventanaAnterior, QWidget *parent = nullptr);

private:
QLineEdit *inputBusqueda;
QComboBox *comboEstado;
QPushButton *btnBuscar;
QTableWidget *tablaResultados;

void buscarLibros();
VentanaDos* ventanaDos;
};

#endif // BUSCARLIBRO_H
