#include "BuscarLibrosUs.h"
#include "VentanaLector.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QApplication>

BuscarLibrosUs::BuscarLibrosUs(VentanaLector* ventanaAnterior, QWidget *parent)
    : QWidget(parent), ventanaLector(ventanaAnterior) {
    setWindowTitle("Buscar Libros");
    resize(820, 500);

    // Barra de menú
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menuArchivo = new QMenu("Menú", this);
    QAction *accionRegresar = new QAction("Regresar", this);
    connect(accionRegresar, &QAction::triggered, [=]() {
        this->close();
        ventanaLector->show();
    });
    menuArchivo->addAction(accionRegresar);
    menuBar->addMenu(menuArchivo);

    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMenuBar(menuBar);

    QHBoxLayout *busquedaLayout = new QHBoxLayout;

    inputBusqueda = new QLineEdit();
    inputBusqueda->setPlaceholderText("Buscar por ISBN, título, autor, etc.");

    comboEstado = new QComboBox();
    comboEstado->addItem("Todos");
    comboEstado->addItem("disponible");
    comboEstado->addItem("prestado");

    busquedaLayout->addWidget(new QLabel("Buscar:"));
    busquedaLayout->addWidget(inputBusqueda);
    busquedaLayout->addWidget(new QLabel("Estado:"));
    busquedaLayout->addWidget(comboEstado);

    tablaResultados = new QTableWidget();
    tablaResultados->setColumnCount(8);
    tablaResultados->setHorizontalHeaderLabels({"ISBN", "Título", "Autor", "Editorial", "Año", "Materia", "Estado", "Ejemplares"});
    tablaResultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    tablaResultados->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablaResultados->setSelectionMode(QAbstractItemView::SingleSelection);
    tablaResultados->setSelectionBehavior(QAbstractItemView::SelectItems);
    tablaResultados->setTextElideMode(Qt::ElideNone);
    tablaResultados->setContextMenuPolicy(Qt::ActionsContextMenu);
    tablaResultados->setStyleSheet("QTableWidget::item:selected { background-color: #0078d7; color: white; }");

    QAction* copiarCelda = new QAction("Copiar", this);
    connect(copiarCelda, &QAction::triggered, this, [=]() {
        QList<QTableWidgetItem*> items = tablaResultados->selectedItems();
        if (!items.isEmpty()){
            QApplication::clipboard()->setText(items.first()->text());
        }
    });
    tablaResultados->addAction(copiarCelda);

    mainLayout->addLayout(busquedaLayout);
    mainLayout->addWidget(tablaResultados);

    connect(inputBusqueda, &QLineEdit::textChanged, this, &BuscarLibrosUs::buscarLibros);
    connect(comboEstado, &QComboBox::currentTextChanged, this, &BuscarLibrosUs::buscarLibros);

    buscarLibros();
}

void BuscarLibrosUs::buscarLibros() {
    QString termino = inputBusqueda->text();
    QString estado = comboEstado->currentText();
    if (estado == "Todos") estado = "";

    GestionLibro gestor;
    QList<Libro> libros = gestor.buscarLibros(termino, estado);

    tablaResultados->clearContents();
    tablaResultados->setRowCount(libros.size());

    for (int i = 0; i < libros.size(); ++i) {
        const Libro &libro = libros[i];
        tablaResultados->setItem(i, 0, new QTableWidgetItem(libro.getISBN()));
        tablaResultados->setItem(i, 1, new QTableWidgetItem(libro.getTitulo()));
        tablaResultados->setItem(i, 2, new QTableWidgetItem(libro.getAutor()));
        tablaResultados->setItem(i, 3, new QTableWidgetItem(libro.getEditorial()));
        tablaResultados->setItem(i, 4, new QTableWidgetItem(QString::number(libro.getAnioPublicacion())));
        tablaResultados->setItem(i, 5, new QTableWidgetItem(libro.getMateria()));
        tablaResultados->setItem(i, 6, new QTableWidgetItem(libro.getEstado()));
        tablaResultados->setItem(i, 7, new QTableWidgetItem(QString::number(libro.getEjemplares())));
    }
}
