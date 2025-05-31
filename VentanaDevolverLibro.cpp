#include "VentanaDevolverLibro.h"
#include <QVBoxLayout>

VentanaDevolverLibro::VentanaDevolverLibro(QWidget *ventanaAnterior, QWidget *parent)
    : QWidget(parent), ventanaAnterior(ventanaAnterior)
{
    setWindowTitle("Devolver Libro");
    setFixedSize(300, 200);

    btnRegresar = new QPushButton("Regresar", this);
    btnRegresar->setMinimumHeight(40);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(btnRegresar);
    layout->addStretch();
    setLayout(layout);

    connect(btnRegresar, &QPushButton::clicked, [=]() {
        this->close();
        ventanaAnterior->show();
    });
}
