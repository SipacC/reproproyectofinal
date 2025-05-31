#include "VentanaSolicitudesNuevas.h"
#include "VentanaSolicitudesUs.h"
#include <QMessageBox>
#include <QDateTime>

VentanaSolicitudesNuevas::VentanaSolicitudesNuevas(VentanaSolicitudesUs* anterior, QWidget *parent)
    : QWidget(parent), ventanaAnterior(anterior) {
    setWindowTitle("Nueva Solicitud");
    resize(400, 250);

    botonRegresar = new QPushButton("Regresar", this);
    botonEnviar = new QPushButton("Enviar Solicitud", this);

    inputIdUsuario = new QLineEdit(this);
    inputIsbn = new QLineEdit(this);

    comboTipo = new QComboBox(this);
    comboTipo->addItem("prestamo");
    comboTipo->addItem("devolucion");

    configurarInterfaz();
    conectarEventos();
}

VentanaSolicitudesNuevas::~VentanaSolicitudesNuevas() {}

void VentanaSolicitudesNuevas::configurarInterfaz() {
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    formLayout->addRow("ID Usuario:", inputIdUsuario);
    formLayout->addRow("ISBN Libro:", inputIsbn);
    formLayout->addRow("Tipo:", comboTipo);

    layoutPrincipal->addLayout(formLayout);
    layoutPrincipal->addWidget(botonEnviar);
    layoutPrincipal->addWidget(botonRegresar);
}

void VentanaSolicitudesNuevas::conectarEventos() {
    connect(botonRegresar, &QPushButton::clicked, this, [this]() {
        this->close();
        ventanaAnterior->show();
    });

    connect(botonEnviar, &QPushButton::clicked, this, [this]() {
        QString idUsuarioStr = inputIdUsuario->text().trimmed();
        QString isbn = inputIsbn->text().trimmed();
        QString tipo = comboTipo->currentText();

        if (idUsuarioStr.isEmpty() || isbn.isEmpty()) {
            QMessageBox::warning(this, "Campos vacíos", "Por favor complete todos los campos.");
            return;
        }

        bool ok;
        int idUsuario = idUsuarioStr.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "ID inválido", "El ID del usuario debe ser un número entero.");
            return;
        }

        Solicitud solicitud;
        solicitud.setIdUsuario(idUsuario);
        solicitud.setIsbnLibro(isbn);
        solicitud.setTipo(tipo);
        solicitud.setEstado("pendiente");
        solicitud.setFechaSolicitud("");  // dejar que la clase use la fecha actual

        GestionSolicitudes gestor;
        if (gestor.registrarSolicitud(solicitud)) {
            QMessageBox::information(this, "Éxito", "Solicitud registrada correctamente.");
            inputIdUsuario->clear();
            inputIsbn->clear();
            comboTipo->setCurrentIndex(0);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo registrar la solicitud.");
        }
    });
}
