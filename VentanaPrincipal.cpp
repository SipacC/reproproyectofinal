#include "VentanaPrincipal.h"
#include <QVBoxLayout>
#include <QFont>

VentanaPrincipal::VentanaPrincipal(LoginCreativo* login, QWidget *parent)
    : QWidget(parent), loginRef(login) {

    setWindowTitle("Menú Principal");
    setFixedSize(400, 500);

    titulo = new QLabel("Sistema de Biblioteca", this);
    QFont tituloFont("Arial", 18, QFont::Bold);
    titulo->setFont(tituloFont);
    titulo->setAlignment(Qt::AlignCenter);

    btnGestionUsuarios = new QPushButton("Gestión de Usuarios 👤", this);
    btnGestionLibros = new QPushButton("Gestión de Libros 📚", this);
    btnVolver = new QPushButton("← Volver al Login", this); // <-- nuevo botón

    btnGestionUsuarios->setMinimumHeight(50);
    btnGestionLibros->setMinimumHeight(50);
    btnVolver->setMinimumHeight(40);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titulo);
    layout->addSpacing(30);
    layout->addWidget(btnGestionUsuarios);
    layout->addWidget(btnGestionLibros);
    layout->addSpacing(20);
    layout->addWidget(btnVolver); // <-- agregamos botón al layout
    layout->setSpacing(20);
    layout->setContentsMargins(50, 40, 50, 40);

    setLayout(layout);

    connect(btnGestionUsuarios, &QPushButton::clicked, [=]() {
        ventanaUsuarios = new VentanaUno(this);
        this->hide();
        ventanaUsuarios->show();
    });

    connect(btnGestionLibros, &QPushButton::clicked, [=]() {
        ventanaLibros = new VentanaDos(this);
        this->hide();
        ventanaLibros->show();
    });

    connect(btnVolver, &QPushButton::clicked, [=]() {
        this->close();
        loginRef->show();
    });
}
