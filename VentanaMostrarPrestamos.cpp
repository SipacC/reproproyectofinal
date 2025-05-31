#include "VentanaMostrarPrestamos.h"
#include <QHeaderView>
#include <QMessageBox>

VentanaMostrarPrestamos::VentanaMostrarPrestamos(QWidget *ventanaAnterior, QWidget *parent) : QWidget(parent), ventanaAnterior(ventanaAnterior) {
    configurarInterfaz();
    cargarPrestamos();
}

void VentanaMostrarPrestamos::configurarInterfaz() {
    tabla = new QTableWidget(this);
    tabla->setColumnCount(5);
    QStringList encabezados = {"ID Usuario", "ISBN Libro", "Fecha Préstamo", "Fecha Devolución", "Estado"};
    tabla->setHorizontalHeaderLabels(encabezados);
    tabla->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabla->setSelectionMode(QAbstractItemView::SingleSelection);

    botonRegresar = new QPushButton("Regresar", this);
    botonDevolver = new QPushButton("Devolver Préstamo", this);

    comboFiltroEstado = new QComboBox(this);
    comboFiltroEstado->addItem("Todos", "todos");
    comboFiltroEstado->addItem("Activos", "activo");
    comboFiltroEstado->addItem("Devueltos", "devuelto");

    // Layout para filtros y botones
    QHBoxLayout *layoutBotones = new QHBoxLayout;
    layoutBotones->addWidget(comboFiltroEstado);
    layoutBotones->addWidget(botonDevolver);
    layoutBotones->addStretch();
    layoutBotones->addWidget(botonRegresar);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addWidget(tabla);
    layoutPrincipal->addLayout(layoutBotones);

    setLayout(layoutPrincipal);
    setFixedSize(400, 500);
    connect(botonDevolver, &QPushButton::clicked, this, &VentanaMostrarPrestamos::devolverPrestamoSeleccionado);
    connect(comboFiltroEstado, &QComboBox::currentTextChanged, this, &VentanaMostrarPrestamos::filtroEstadoCambiado);

    connect(botonRegresar, &QPushButton::clicked, [=]() {
    this->close();
    ventanaAnterior->show();
   });
}

void VentanaMostrarPrestamos::cargarPrestamos(const QString &estadoFiltro) {
    QList<Prestamo> prestamos = gestor.mostrarPrestamos();
    tabla->setRowCount(0);  // Limpiar tabla antes de recargar

    int fila = 0;
    for (const Prestamo &p : prestamos) {
        if (estadoFiltro != "todos" && p.getEstado() != estadoFiltro) {
            continue; // Saltar si no coincide con filtro
        }

        tabla->insertRow(fila);
        tabla->setItem(fila, 0, new QTableWidgetItem(QString::number(p.getIdUsuario())));
        tabla->setItem(fila, 1, new QTableWidgetItem(p.getIsbnLibro()));
        tabla->setItem(fila, 2, new QTableWidgetItem(p.getFechaPrestamo().toString("yyyy-MM-dd")));
        tabla->setItem(fila, 3, new QTableWidgetItem(p.getFechaDevolucion().toString("yyyy-MM-dd")));
        tabla->setItem(fila, 4, new QTableWidgetItem(p.getEstado()));
        fila++;
    }

    if (tabla->rowCount() == 0) {
        QMessageBox::information(this, "Información", "No hay préstamos que mostrar para este filtro.");
    }
}

void VentanaMostrarPrestamos::filtroEstadoCambiado(const QString &nuevoEstado) {
    QString estadoClave;
    if (nuevoEstado == "Activos") estadoClave = "activo";
    else if (nuevoEstado == "Devueltos") estadoClave = "devuelto";
    else estadoClave = "todos";

    cargarPrestamos(estadoClave);
}

void VentanaMostrarPrestamos::devolverPrestamoSeleccionado() {
    int fila = tabla->currentRow();
    if (fila == -1) {
        QMessageBox::warning(this, "Atención", "Por favor selecciona un préstamo para devolver.");
        return;
    }

    int idUsuario = tabla->item(fila, 0)->text().toInt();
    QString isbnLibro = tabla->item(fila, 1)->text();
    QDate fechaPrestamo = QDate::fromString(tabla->item(fila, 2)->text(), "yyyy-MM-dd");

    bool exito = gestor.devolverPrestamo(idUsuario, isbnLibro, fechaPrestamo);
    if (exito) {
        QMessageBox::information(this, "Éxito", "El préstamo ha sido marcado como devuelto.");
        filtroEstadoCambiado(comboFiltroEstado->currentText());
    } else {
        QMessageBox::critical(this, "Error", "No se pudo actualizar el préstamo.");
    }
}
