#ifndef VENTANADEVOLVERLIBRO_H
#define VENTANADEVOLVERLIBRO_H

#include <QWidget>
#include <QPushButton>

class VentanaDevolverLibro : public QWidget {
public:
    explicit VentanaDevolverLibro(QWidget *ventanaAnterior, QWidget *parent = nullptr);

private:
    QWidget *ventanaAnterior;
    QPushButton *btnRegresar;
};

#endif // VENTANADEVOLVERLIBRO_H
