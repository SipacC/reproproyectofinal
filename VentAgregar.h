#ifndef VENTAGREGAR_H
#define VENTAGREGAR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "Usuario.h"
#include "GestionUsuario.h"

class VentanaUno;

class VentAgregar : public QWidget {
public:
    explicit VentAgregar(VentanaUno *anterior = nullptr);

private:
    
    VentanaUno *ventanaAnterior;
    QLineEdit *inputNombre;
    QLineEdit *inputCorreo;
    QComboBox *comboTipo;
    QLineEdit *inputContrasena;
    QPushButton *btnAgregar;
    QPushButton *btnVolver;

    void agregarUsuario();
};

#endif // VENTAGREGAR_H
