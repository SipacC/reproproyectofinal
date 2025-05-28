#include "VentanaUno.h"
#include "VentanaPrincipal.h"
#include "VentAgregar.h"
#include "VentBuscar.h"
#include "VentModificar.h"
/*
#include "VentanaEliminarUsuario.h"
*/
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QLabel>

VentanaUno::VentanaUno(VentanaPrincipal *ventanaPrincipal, QWidget *parent)
    : QWidget(parent), principal(ventanaPrincipal) {
    setWindowTitle("Gestión de Usuarios");
    setFixedSize(400, 500);
    // Título de la ventana
    QLabel *titulo = new QLabel("Gestión de Usuarios", this);
    QFont tituloFont("Arial", 18, QFont::Bold);
    titulo->setFont(tituloFont);
    titulo->setAlignment(Qt::AlignCenter);
    // Botones con iconos
    QPushButton *btnAgregar = new QPushButton("➕ Agregar Usuario", this);
    //QPushButton *btnEliminar = new QPushButton("❌ Eliminar Usuario", this);
    QPushButton *btnBuscar = new QPushButton("🔍 Buscar Usuario", this);
    QPushButton *btnModificar = new QPushButton("✏️ Modificar Usuario", this);
    QPushButton *btnVolver = new QPushButton("🔙 Volver al Menú Principal", this);
    // Ajuste de altura mínima para los botones
    btnAgregar->setMinimumHeight(50);
    //btnEliminar->setMinimumHeight(50);
    btnBuscar->setMinimumHeight(50);
    btnModificar->setMinimumHeight(50);
    btnVolver->setMinimumHeight(50);
    // Layout para la ventana
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titulo);
    layout->addSpacing(20);
    layout->addWidget(btnAgregar);
    //layout->addWidget(btnEliminar);
    layout->addWidget(btnBuscar);
    layout->addWidget(btnModificar);
    layout->addSpacing(30);
    layout->addWidget(btnVolver);
    // Márgenes y espaciado
    layout->setSpacing(20);
    layout->setContentsMargins(50, 40, 50, 40);
    setLayout(layout);
    // Funcionalidades de los botones
    connect(btnAgregar, &QPushButton::clicked, [=]() {
        this->hide();
        VentAgregar *ventana = new VentAgregar(this);
        ventana->show();
    });

    connect(btnBuscar, &QPushButton::clicked, [=]() {
        this->hide();
        VentBuscar *ventana = new VentBuscar(this);
        ventana->show();
    });

    connect(btnModificar, &QPushButton::clicked, [=]() {
        this->hide();
        VentModificar *ventana = new VentModificar(this);
        ventana->show();
    });
     /*
     connect(btnEliminar, &QPushButton::clicked, [=]() {
        this->hide();
        VentanaEliminarUsuario *ventana = new VentanaEliminarUsuario(this);
        ventana->show();
    });
    */
    connect(btnVolver, &QPushButton::clicked, [=]() {
        this->close();
        principal->show();
    });
}
