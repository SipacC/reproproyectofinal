#ifndef VENTANAPRESTAMO_H
#define VENTANAPRESTAMO_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "GestionPrestamos.h"

class VentanaPrestamo : public QWidget {
public:
    explicit VentanaPrestamo(QWidget *ventanaAnterior, QWidget *parent = nullptr);

private:
    QWidget *ventanaAnterior;

    QLineEdit *inputIdUsuario;
    QLineEdit *inputIsbnLibro;
    QDateEdit *inputFechaPrestamo;
    QDateEdit *inputFechaDevolucion;
    QComboBox *comboEstado;

    QPushButton *btnRegistrar;
    QPushButton *btnRegresar;

    GestionPrestamos gestionPrestamos;

    void registrar();
};

#endif // VENTANAPRESTAMO_H
