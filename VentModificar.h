#ifndef VENTMODIFICAR_H
#define VENTMODIFICAR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include "GestionUsuario.h"
#include "Usuario.h"

class VentanaUno;

class VentModificar : public QWidget {
public:
    VentModificar(VentanaUno *anterior = nullptr);

private:

    VentanaUno *ventanaAnterior;
    QLineEdit *inputId;
    QLineEdit *inputNombre;
    QLineEdit *inputCorreo;
    QComboBox *comboTipo;
    QLineEdit *inputContrasena;
    QPushButton *btnModificar;
    QPushButton *btnRegresar;

    void cargarNombre();
    void modificarUsuario();
};

#endif // VENTMODIFICAR_H
