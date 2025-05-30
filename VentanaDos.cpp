#include "VentanaDos.h"
#include "VentanaPrincipal.h"
#include "AgregarLibro.h"
#include "BuscarLibro.h"
#include "VentanaSolicitudes.h"
/*
#include "VentanaPrestarLibro.h"
#include "VentanaDevolverLibro.h"
*/
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QLabel>

VentanaDos::VentanaDos(VentanaPrincipal *ventanaPrincipal, QWidget *parent)
    : QWidget(parent), principal(ventanaPrincipal) {

    setWindowTitle("Gestión de Libros");
    setFixedSize(400, 500);

    // Título de la ventana
    QLabel *titulo = new QLabel("Gestión de Libros", this);
    QFont tituloFont("Arial", 18, QFont::Bold);
    titulo->setFont(tituloFont);
    titulo->setAlignment(Qt::AlignCenter);

    // Botones con iconos
    QPushButton *btnAgregar = new QPushButton("📚 Agregar Libro", this);
    QPushButton *btnPrestar = new QPushButton("📤 Prestar Libro", this);
    QPushButton *btnDevolver = new QPushButton("📥 Devolver Libro", this);
    QPushButton *btnBuscar = new QPushButton("🔍 Buscar Libro", this);
    QPushButton *btnMostrar = new QPushButton("📖 Gestionar solicitudes", this);
    QPushButton *btnVolver = new QPushButton("🔙 Volver al Menú Principal", this);

    // Ajuste de altura mínima para los botones
    btnAgregar->setMinimumHeight(50);
    btnPrestar->setMinimumHeight(50);
    btnDevolver->setMinimumHeight(50);
    btnBuscar->setMinimumHeight(50);
    btnMostrar->setMinimumHeight(50);
    btnVolver->setMinimumHeight(50);

    // Layout de la ventana
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titulo);
    layout->addSpacing(20);
    layout->addWidget(btnAgregar);
    layout->addWidget(btnPrestar);
    layout->addWidget(btnDevolver);
    layout->addWidget(btnBuscar);
    layout->addWidget(btnMostrar);
    layout->addSpacing(30);
    layout->addWidget(btnVolver);

    
    // Márgenes y espaciado
    layout->setSpacing(20);
    layout->setContentsMargins(50, 40, 50, 40);
    setLayout(layout);

    // Funcionalidades de los botones
    connect(btnAgregar, &QPushButton::clicked, [=]() {
        this->hide();
        AgregarLibro *ventana = new AgregarLibro(this);
        ventana->show();
    });

    connect(btnBuscar, &QPushButton::clicked, [=]() {
        this->hide();
        BuscarLibro *ventana = new BuscarLibro(this);
        ventana->show();
    });

    
    /*

    connect(btnPrestar, &QPushButton::clicked, [=]() {
        this->hide();
        VentanaPrestarLibro *ventana = new VentanaPrestarLibro(this);
        ventana->show();
    });

    connect(btnDevolver, &QPushButton::clicked, [=]() {
        this->hide();
        VentanaDevolverLibro *ventana = new VentanaDevolverLibro(this);
        ventana->show();
    });
    */
   connect(btnMostrar, &QPushButton::clicked, [=]() {
        this->hide();
        VentanaSolicitudes *ventana = new VentanaSolicitudes(this);
        ventana->show();
    });

    connect(btnVolver, &QPushButton::clicked, [=]() {
        this->close();
        principal->show();
    });
}
