#include "VentanaSolicitudes.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>

VentanaSolicitudes::VentanaSolicitudes(VentanaDos* anterior, QWidget *parent)
    : QWidget(parent), ventanaAnterior(anterior) {

    setWindowTitle("Solicitudes Registradas");
    resize(800, 400);

    tabla = new QTableWidget;
    inputBusqueda = new QLineEdit;
    comboEstado = new QComboBox;
    botonActualizar = new QPushButton("Actualizar");
    botonRegresar = new QPushButton("Regresar");

    comboNuevoEstado = new QComboBox;
    botonGuardarEstado = new QPushButton("Guardar Estado");

    configurarInterfaz();
    conectarEventos();
    cargarSolicitudes();
}

void VentanaSolicitudes::configurarInterfaz() {
    comboEstado->addItem("Todos", "");
    comboEstado->addItem("pendiente", "pendiente");
    comboEstado->addItem("aceptada", "aceptada");
    comboEstado->addItem("rechazada", "rechazada");

    comboNuevoEstado->addItems({"pendiente", "aceptada", "rechazada"});
    comboNuevoEstado->setEnabled(false);
    botonGuardarEstado->setEnabled(false);

    inputBusqueda->setPlaceholderText("Buscar por ID de solicitud...");

    QHBoxLayout *filtrosLayout = new QHBoxLayout;
    filtrosLayout->addWidget(inputBusqueda);
    filtrosLayout->addWidget(comboEstado);
    filtrosLayout->addWidget(botonActualizar);
    filtrosLayout->addWidget(botonRegresar);

    QHBoxLayout *estadoLayout = new QHBoxLayout;
    estadoLayout->addWidget(comboNuevoEstado);
    estadoLayout->addWidget(botonGuardarEstado);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addLayout(filtrosLayout);
    layoutPrincipal->addWidget(tabla);
    layoutPrincipal->addLayout(estadoLayout);

    tabla->setColumnCount(6);
    tabla->setHorizontalHeaderLabels({"ID", "Usuario", "ISBN", "Tipo", "Estado", "Fecha"});
    tabla->setSortingEnabled(true);
    tabla->horizontalHeader()->setStretchLastSection(true);
}

void VentanaSolicitudes::cargarSolicitudes() {
    tabla->setRowCount(0);
    QString estado = comboEstado->currentData().toString();
    QString idTexto = inputBusqueda->text();
    int id = idTexto.toInt();

    QList<Solicitud> lista = gestor.obtenerSolicitudesFiltradas(id, estado);
    tabla->setRowCount(lista.size());

    for (int i = 0; i < lista.size(); ++i) {
        const Solicitud &s = lista[i];
        tabla->setItem(i, 0, new QTableWidgetItem(QString::number(s.getIdSolicitud())));
        tabla->setItem(i, 1, new QTableWidgetItem(QString::number(s.getIdUsuario())));
        tabla->setItem(i, 2, new QTableWidgetItem(s.getIsbnLibro()));
        tabla->setItem(i, 3, new QTableWidgetItem(s.getTipo()));
        tabla->setItem(i, 4, new QTableWidgetItem(s.getEstado()));
        tabla->setItem(i, 5, new QTableWidgetItem(s.getFechaSolicitud()));
    }

    tabla->resizeColumnsToContents();
    comboNuevoEstado->setEnabled(false);
    botonGuardarEstado->setEnabled(false);
    solicitudSeleccionadaId = -1;
}

void VentanaSolicitudes::conectarEventos() {
    connect(botonActualizar, &QPushButton::clicked, this, [=]() {
        cargarSolicitudes();
    });

    connect(inputBusqueda, &QLineEdit::textChanged, this, [=]() {
        cargarSolicitudes();
    });

    connect(comboEstado, &QComboBox::currentIndexChanged, this, [=]() {
        cargarSolicitudes();
    });

    connect(tabla, &QTableWidget::cellClicked, this, [=](int row, int) {
        QTableWidgetItem *item = tabla->item(row, 0);
        if (item) {
            solicitudSeleccionadaId = item->text().toInt();
            QString estadoActual = tabla->item(row, 4)->text();
            int index = comboNuevoEstado->findText(estadoActual);
            comboNuevoEstado->setCurrentIndex(index);
            comboNuevoEstado->setEnabled(true);
            botonGuardarEstado->setEnabled(true);
        }
    });

    connect(botonGuardarEstado, &QPushButton::clicked, this, [=]() {
        if (solicitudSeleccionadaId == -1) return;
        QString nuevoEstado = comboNuevoEstado->currentText();
        bool ok = gestor.actualizarEstadoSolicitud(solicitudSeleccionadaId, nuevoEstado);
        if (ok) {
            QMessageBox::information(this, "Éxito", "Estado actualizado correctamente.");
            cargarSolicitudes();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo actualizar el estado.");
        }
    });

    connect(botonRegresar, &QPushButton::clicked, this, [=]() {
        this->close();
        ventanaAnterior->show();
    });
}
