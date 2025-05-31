#ifndef VENTANAMOSTRARPRESTAMOS_H
#define VENTANAMOSTRARPRESTAMOS_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

#include "GestionPrestamos.h"

class VentanaMostrarPrestamos : public QWidget {
private:
    QTableWidget *tabla;
    QPushButton *botonRegresar;
    QPushButton *botonDevolver;
    QComboBox *comboFiltroEstado;   // Aquí se usa QComboBox, por eso debe estar incluido
    GestionPrestamos gestor;

public:
    explicit VentanaMostrarPrestamos(QWidget *ventanaAnterior, QWidget *parent = nullptr);


private:
    void configurarInterfaz();
    void cargarPrestamos(const QString &estadoFiltro = "todos");
    void filtroEstadoCambiado(const QString &nuevoEstado);
    void devolverPrestamoSeleccionado();
    QWidget *ventanaAnterior;
    QPushButton *btnRegresar;
};

#endif // VENTANAMOSTRARPRESTAMOS_H
