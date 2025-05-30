#include "VentanaSolicitudesUs.h"  
#include "VentanaLector.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

VentanaSolicitudesUs::VentanaSolicitudesUs(VentanaLector* anterior, QWidget *parent)
    : QWidget(parent), ventanaAnterior(anterior)
{
    setWindowTitle("Solicitudes de Usuario");
    resize(800, 400);

    tablaSolicitudes = new QTableWidget(this);
    inputBusqueda = new QLineEdit(this);
    comboEstado = new QComboBox(this);
    botonActualizar = new QPushButton("Actualizar", this);
    botonRegresar = new QPushButton("Regresar", this);

    configurarInterfaz();
    conectarEventos();
    cargarSolicitudes();
}

// ✅ IMPLEMENTACIÓN DEL DESTRUCTOR para evitar el error del vtable
VentanaSolicitudesUs::~VentanaSolicitudesUs() {
    // Qt se encarga de liberar los widgets hijos automáticamente
}

void VentanaSolicitudesUs::configurarInterfaz() {
    comboEstado->addItem("Todos", "");
    comboEstado->addItem("pendiente", "pendiente");
    comboEstado->addItem("aceptada", "aceptada");
    comboEstado->addItem("rechazada", "rechazada");

    inputBusqueda->setPlaceholderText("Buscar por ID de solicitud...");

    QHBoxLayout *layoutFiltros = new QHBoxLayout;
    layoutFiltros->addWidget(inputBusqueda);
    layoutFiltros->addWidget(comboEstado);
    layoutFiltros->addWidget(botonActualizar);
    layoutFiltros->addWidget(botonRegresar);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addLayout(layoutFiltros);
    layoutPrincipal->addWidget(tablaSolicitudes);

    tablaSolicitudes->setColumnCount(6);
    tablaSolicitudes->setHorizontalHeaderLabels({"ID", "Usuario", "ISBN", "Tipo", "Estado", "Fecha"});
    tablaSolicitudes->setSortingEnabled(true);
    tablaSolicitudes->horizontalHeader()->setStretchLastSection(true);
    tablaSolicitudes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablaSolicitudes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablaSolicitudes->setSelectionMode(QAbstractItemView::SingleSelection);
}

void VentanaSolicitudesUs::cargarSolicitudes() {
    tablaSolicitudes->setRowCount(0);

    QString estado = comboEstado->currentData().toString();
    QString idTexto = inputBusqueda->text();
    int id = idTexto.toInt();

    QList<Solicitud> lista = gestor.obtenerSolicitudesFiltradas(id, estado);

    tablaSolicitudes->setRowCount(lista.size());

    for (int i = 0; i < lista.size(); ++i) {
        const Solicitud &s = lista[i];
        tablaSolicitudes->setItem(i, 0, new QTableWidgetItem(QString::number(s.getIdSolicitud())));
        tablaSolicitudes->setItem(i, 1, new QTableWidgetItem(QString::number(s.getIdUsuario())));
        tablaSolicitudes->setItem(i, 2, new QTableWidgetItem(s.getIsbnLibro()));
        tablaSolicitudes->setItem(i, 3, new QTableWidgetItem(s.getTipo()));
        tablaSolicitudes->setItem(i, 4, new QTableWidgetItem(s.getEstado()));
        tablaSolicitudes->setItem(i, 5, new QTableWidgetItem(s.getFechaSolicitud()));
    }

    tablaSolicitudes->resizeColumnsToContents();
}

void VentanaSolicitudesUs::conectarEventos() {
    connect(botonActualizar, &QPushButton::clicked, this, [this]() {
        cargarSolicitudes();
    });

    connect(inputBusqueda, &QLineEdit::textChanged, this, [this]() {
        cargarSolicitudes();
    });

    connect(comboEstado, &QComboBox::currentIndexChanged, this, [this]() {
        cargarSolicitudes();
    });

    connect(botonRegresar, &QPushButton::clicked, this, [this]() {
        this->close();
        ventanaAnterior->show();
    });
}
