#ifndef BUSCARLIBROSUS_H
#define BUSCARLIBROSUS_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "GestionLibro.h"

class VentanaLector; // Declaración adelantada

class BuscarLibrosUs : public QWidget {
public:
    BuscarLibrosUs(VentanaLector* ventanaAnterior, QWidget *parent = nullptr);

private:
    QLineEdit *inputBusqueda;
    QComboBox *comboEstado;
    QTableWidget *tablaResultados;

    void buscarLibros();
    VentanaLector* ventanaLector;
};

#endif // BUSCARLIBROSUS_H
