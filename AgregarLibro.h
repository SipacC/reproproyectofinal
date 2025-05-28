#ifndef AGREGARLIBRO_H
#define AGREGARLIBRO_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "Libro.h"
#include "GestionLibro.h"

class VentanaDos;

class AgregarLibro : public QWidget {
public:
    AgregarLibro(VentanaDos *ventanaAnterior, QWidget *parent = nullptr);

private:
    QLineEdit *inputISBN;
    QLineEdit *inputTitulo;
    QLineEdit *inputAutor;
    QLineEdit *inputEditorial;
    QLineEdit *inputAnio;
    QLineEdit *inputMateria;
    QComboBox *comboEstado;
    QSpinBox *inputEjemplares;

    QPushButton *btnAgregar;
    QPushButton *btnVolver;

    void agregarLibro();
    VentanaDos *ventanaAnterior;
};

#endif // AGREGARLIBRO_H
