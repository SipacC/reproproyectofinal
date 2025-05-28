#include "VentanaUno.h"
#include "VentBuscar.h"
#include <QHeaderView>
#include <QApplication>
#include <QClipboard>

VentBuscar::VentBuscar(VentanaUno *anterior) : ventanaAnterior(anterior) {
    setWindowTitle("Buscar Usuario");
    resize(400, 500);//resize

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    QLabel *titulo = new QLabel("Buscar y filtrar usuarios");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 18px; font-weight: bold;");

    // Filtros
    inputBuscarNombre = new QLineEdit();
    inputBuscarNombre->setPlaceholderText("Buscar por nombre...");
    comboFiltroTipo = new QComboBox();
    comboFiltroTipo->addItem("Todos");
    comboFiltroTipo->addItem("lector");
    comboFiltroTipo->addItem("gestor");

    QHBoxLayout *filtrosLayout = new QHBoxLayout();
    filtrosLayout->addWidget(inputBuscarNombre);
    filtrosLayout->addWidget(comboFiltroTipo);

    // Tabla para mostrar resultados
    tablaUsuarios = new QTableWidget();
    tablaUsuarios->setColumnCount(4);
    QStringList encabezados = {"id usuario","Nombre", "Correo Electronico", "Tipo"};
    tablaUsuarios->setHorizontalHeaderLabels(encabezados);
    tablaUsuarios->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    tablaUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablaUsuarios->setTextElideMode(Qt::ElideNone);
    tablaUsuarios->setSelectionMode(QAbstractItemView::SingleSelection);
    //tablaUsuarios->horizontalHeader()->setStretchLastSection(true);
    tablaUsuarios->setContextMenuPolicy(Qt::ActionsContextMenu);
    

    tablaUsuarios->setStyleSheet("QTableWidget::item:selected { background-color: #0078d7; color: white; }");
    
    QAction* copiarCelda = new QAction("Copiar", this);
    connect(copiarCelda, &QAction::triggered, this, [=]() {
        QList<QTableWidgetItem*> items = tablaUsuarios->selectedItems();
        if (!items.isEmpty()) {
            QApplication::clipboard()->setText(items.first()->text());
        }
    });

    tablaUsuarios->addAction(copiarCelda);

    // Botón volver
    btnVolver = new QPushButton("⬅️ Volver al menú");

    // Agregar al layout
    layoutPrincipal->addWidget(titulo);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addLayout(filtrosLayout);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(tablaUsuarios);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(btnVolver);

    // Conectar eventos
    connect(inputBuscarNombre, &QLineEdit::textChanged, this, &VentBuscar::cargarUsuarios);
    connect(comboFiltroTipo, &QComboBox::currentTextChanged, this, &VentBuscar::cargarUsuarios);
    connect(btnVolver, &QPushButton::clicked, this, [=]() {
        this->close();
        ventanaAnterior->show();
    });

    cargarUsuarios(); // Cargar todos al inicio
}

void VentBuscar::cargarUsuarios() {
    QString filtroNombre = inputBuscarNombre->text();
    QString filtroTipo = comboFiltroTipo->currentText();

    GestionUsuario gestion;
    QList<Usuario> lista = gestion.buscarUsuarios(0, filtroNombre, filtroTipo);

    tablaUsuarios->setRowCount(lista.size());

    for (int i = 0; i < lista.size(); ++i) {
        Usuario u = lista.at(i);
        tablaUsuarios->setItem(i, 0, new QTableWidgetItem(QString::number(u.getId())));
        tablaUsuarios->setItem(i, 1, new QTableWidgetItem(u.getNombre()));
        tablaUsuarios->setItem(i, 2, new QTableWidgetItem(u.getCorreo()));
        tablaUsuarios->setItem(i, 3, new QTableWidgetItem(u.getTipo()));
    }


    tablaUsuarios->resizeColumnsToContents();
    tablaUsuarios->resizeRowsToContents();
}
