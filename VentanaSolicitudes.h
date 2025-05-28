#ifndef VENTANASOLICITUDES_H
#define VENTANASOLICITUDES_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "GestionSolicitudes.h"
#include "Solicitud.h"
#include "VentanaDos.h"

class VentanaSolicitudes : public QWidget {
public:
    explicit VentanaSolicitudes(VentanaDos* ventanaAnterior, QWidget *parent = nullptr);

private:
    VentanaDos* ventanaAnterior;

    QTableWidget *tabla;
    QLineEdit *inputBusqueda;
    QComboBox *comboEstado;
    QPushButton *botonActualizar;

    GestionSolicitudes gestor;
    QComboBox *comboNuevoEstado;
    QPushButton *botonGuardarEstado;
    int solicitudSeleccionadaId = -1;
    QPushButton *botonRegresar;

    void configurarInterfaz();
    void cargarSolicitudes();
    void conectarEventos();
};

#endif // VENTANASOLICITUDES_H
