#include "VentanaLector.h"
#include <QVBoxLayout>
#include <QFont>

VentanaLector::VentanaLector(LoginCreativo* login, QWidget *parent)
    : QWidget(parent), loginRef(login) {

    setWindowTitle("Menú Lector");
    setFixedSize(400, 500);

    // Título
    titulo = new QLabel("Bienvenido Lector", this);
    titulo->setFont(QFont("Arial", 18, QFont::Bold));
    titulo->setAlignment(Qt::AlignCenter);

    // Botones
    btnBuscarLibros = new QPushButton("Buscar Libros 🔍", this);
    btnSolicitudes = new QPushButton("Mis Solicitudes 📋", this);
    btnVolver = new QPushButton("← Volver al Login", this);

    btnBuscarLibros->setMinimumHeight(50);
    btnSolicitudes->setMinimumHeight(50);
    btnVolver->setMinimumHeight(40);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titulo);
    layout->addSpacing(30);
    layout->addWidget(btnBuscarLibros);
    layout->addWidget(btnSolicitudes);
    layout->addSpacing(20);
    layout->addWidget(btnVolver);
    layout->setSpacing(20);
    layout->setContentsMargins(50, 40, 50, 40);
    setLayout(layout);

    // Eventos
    /*
    connect(btnBuscarLibros, &QPushButton::clicked, [=]() {
        ventanaBuscarLibros = new BuscarLibrosUs(this);
        this->hide();
        ventanaBuscarLibros->show();
    });

    connect(btnSolicitudes, &QPushButton::clicked, [=]() {
        ventanaSolicitudes = new VentSolicitud(this);
        this->hide();
        ventanaSolicitudes->show();
    });
    */

    connect(btnVolver, &QPushButton::clicked, [=]() {
        this->close();
        loginRef->show();
    });
}
