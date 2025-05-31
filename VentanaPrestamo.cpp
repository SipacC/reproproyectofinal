#include "VentanaPrestamo.h"
#include <QMessageBox>
#include <QDate>

VentanaPrestamo::VentanaPrestamo(QWidget *ventanaAnterior, QWidget *parent)
    : QWidget(parent), ventanaAnterior(ventanaAnterior) {
    
    setWindowTitle("Registrar Préstamo / Devolución");

    QLabel *labelIdUsuario = new QLabel("ID Usuario:");
    inputIdUsuario = new QLineEdit();

    QLabel *labelIsbnLibro = new QLabel("ISBN Libro:");
    inputIsbnLibro = new QLineEdit();

    QLabel *labelFechaPrestamo = new QLabel("Fecha Préstamo:");
    inputFechaPrestamo = new QDateEdit(QDate::currentDate());
    inputFechaPrestamo->setCalendarPopup(true);
    inputFechaPrestamo->setDisplayFormat("yyyy-MM-dd");

    QLabel *labelFechaDevolucion = new QLabel("Fecha Devolución:");
    inputFechaDevolucion = new QDateEdit(QDate::currentDate().addDays(14));
    inputFechaDevolucion->setCalendarPopup(true);
    inputFechaDevolucion->setDisplayFormat("yyyy-MM-dd");

    QLabel *labelEstado = new QLabel("Estado:");
    comboEstado = new QComboBox();
    comboEstado->addItem("activo");
    comboEstado->addItem("devuelto");

    btnRegistrar = new QPushButton("Registrar");
    btnRegresar = new QPushButton("Regresar");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout();

    layoutPrincipal->addWidget(labelIdUsuario);
    layoutPrincipal->addWidget(inputIdUsuario);

    layoutPrincipal->addWidget(labelIsbnLibro);
    layoutPrincipal->addWidget(inputIsbnLibro);

    layoutPrincipal->addWidget(labelFechaPrestamo);
    layoutPrincipal->addWidget(inputFechaPrestamo);

    layoutPrincipal->addWidget(labelFechaDevolucion);
    layoutPrincipal->addWidget(inputFechaDevolucion);

    layoutPrincipal->addWidget(labelEstado);
    layoutPrincipal->addWidget(comboEstado);

    QHBoxLayout *layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(btnRegistrar);
    layoutBotones->addWidget(btnRegresar);

    layoutPrincipal->addLayout(layoutBotones);
    setLayout(layoutPrincipal);
    resize(320, 380);

    // Conexiones
    connect(btnRegistrar, &QPushButton::clicked, this, &VentanaPrestamo::registrar);
    connect(btnRegresar, &QPushButton::clicked, [=]() {
        this->close();
        if (ventanaAnterior) ventanaAnterior->show();
    });
}

void VentanaPrestamo::registrar() {
    bool okId;
    int idUsuario = inputIdUsuario->text().toInt(&okId);
    QString isbnLibro = inputIsbnLibro->text().trimmed();

    if (!okId || idUsuario <= 0) {
        QMessageBox::warning(this, "Datos inválidos", "El ID de usuario debe ser un número entero positivo.");
        return;
    }
    if (isbnLibro.isEmpty()) {
        QMessageBox::warning(this, "Datos inválidos", "Debe ingresar el ISBN del libro.");
        return;
    }

    Prestamo prestamo;
    prestamo.setIdUsuario(idUsuario);
    prestamo.setIsbnLibro(isbnLibro);
    prestamo.setFechaPrestamo(inputFechaPrestamo->date());
    prestamo.setFechaDevolucion(inputFechaDevolucion->date());
    prestamo.setEstado(comboEstado->currentText());

    bool exito = gestionPrestamos.registrarPrestamo(prestamo);
    if (exito) {
        QMessageBox::information(this, "Éxito", "Préstamo registrado correctamente.");
        inputIdUsuario->clear();
        inputIsbnLibro->clear();
        inputFechaPrestamo->setDate(QDate::currentDate());
        inputFechaDevolucion->setDate(QDate::currentDate().addDays(14));
        comboEstado->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Error", "No se pudo registrar el préstamo.");
    }
}
