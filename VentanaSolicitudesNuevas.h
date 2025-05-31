#ifndef VENTANASOLICITUDESNUEVAS_H
#define VENTANASOLICITUDESNUEVAS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include "GestionSolicitudes.h"

class VentanaSolicitudesUs;

class VentanaSolicitudesNuevas : public QWidget {
public:
    explicit VentanaSolicitudesNuevas(VentanaSolicitudesUs* anterior, QWidget *parent = nullptr);
    ~VentanaSolicitudesNuevas();

private:
    VentanaSolicitudesUs* ventanaAnterior;
    QPushButton* botonRegresar;
    QPushButton* botonEnviar;

    QLineEdit* inputIdUsuario;
    QLineEdit* inputIsbn;
    QComboBox* comboTipo;

    void configurarInterfaz();
    void conectarEventos();
};

#endif // VENTANASOLICITUDESNUEVAS_H
