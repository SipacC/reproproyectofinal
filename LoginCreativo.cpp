#include "loginCreativo.h"
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QFont>
#include <QPalette>
#include <QPixmap>
#include <QCheckBox>
#include "conexion.h"
#include <libpq-fe.h>
#include <QCryptographicHash>
#include <QByteArray>
#include "VentanaPrincipal.h"
#include "SesionUsuario.h"
#include "VentanaLector.h"



LoginCreativo::LoginCreativo(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Inicio de sesion Biblioteca");
    setFixedSize(400, 500);

    // Fondo degradado
    QPalette pal = palette();
    QLinearGradient grad(0, 0, 0, height());
    grad.setColorAt(0, QColor(70, 130, 180)); // steel blue
    grad.setColorAt(1, QColor(240, 248, 255)); // alice blue
    pal.setBrush(QPalette::Window, grad);
    setAutoFillBackground(true);
    setPalette(pal);

    auto *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    // Logo o imagen superior
    QLabel *logo = new QLabel();
    logo->setPixmap(QPixmap("C:\\c++ClionProyects\\OIP.jpg").scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignCenter);
    layout->addWidget(logo);

    // Título
    QLabel *titulo = new QLabel("Sistema de Biblioteca");
    titulo->setFont(QFont("Arial", 18, QFont::Bold));
    titulo->setAlignment(Qt::AlignCenter);
    layout->addWidget(titulo);

    // Marco decorativo
    QFrame *marco = new QFrame();
    marco->setFrameShape(QFrame::StyledPanel);
    marco->setStyleSheet("background-color: rgba(249, 250, 252, 0.9); border-radius: 15px;");
    QVBoxLayout *formLayout = new QVBoxLayout(marco);
    formLayout->setContentsMargins(20, 20, 20, 20);
    formLayout->setSpacing(15);

    // Campo de usuario
    QLabel *lblUsuario = new QLabel("Usuario:");
    lblUsuario->setFont(QFont("Segoe UI", 10));
    usuarioInput = new QLineEdit();
    usuarioInput->setPlaceholderText("Ingresa tu nombre de usuario");
    usuarioInput->setStyleSheet("padding: 6px;");
    formLayout->addWidget(lblUsuario);
    formLayout->addWidget(usuarioInput);

    // Campo de contraseña
    QLabel *lblContrasena = new QLabel("Contraseña:");
    lblContrasena->setFont(QFont("Segoe UI", 10));
    contrasenaInput = new QLineEdit();
    contrasenaInput->setPlaceholderText("Ingresa tu contraseña");
    contrasenaInput->setEchoMode(QLineEdit::Password);
    contrasenaInput->setStyleSheet("padding: 6px;");
    formLayout->addWidget(lblContrasena);
    formLayout->addWidget(contrasenaInput);

    // Mostrar/ocultar contraseña
    mostrarContrasena = new QCheckBox("Mostrar contraseña");
    formLayout->addWidget(mostrarContrasena);
    connect(mostrarContrasena, &QCheckBox::toggled, this, &LoginCreativo::toggleMostrarContrasena);

    // Botón iniciar sesión
    auto *btnLogin = new QPushButton("Iniciar sesión");
    btnLogin->setCursor(Qt::PointingHandCursor);
    btnLogin->setStyleSheet(
        "QPushButton {"
        "  background-color: #4682B4;"      // steelblue
        "  color: white;"
        "  padding: 10px 20px;"
        "  font-weight: bold;"
        "  border-radius: 8px;"
        "  border: 2px solid #3a6ea5;"
        "}"
        "QPushButton:hover {"
        "  background-color: #5a9bd5;"      // azul más claro al pasar mouse
        "  border: 2px solid #2a4c73;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #2c5a88;"      // azul más oscuro al presionar
        "  border: 2px solid #1f3e5a;"
       "}"
    );
    connect(btnLogin, &QPushButton::clicked, this, &LoginCreativo::simularLogin);
    formLayout->addWidget(btnLogin);

    layout->addWidget(marco);

}

void LoginCreativo::toggleMostrarContrasena(bool checked) {
    contrasenaInput->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void LoginCreativo::simularLogin() {
    Conexion conexion;
    QString usuario = usuarioInput->text();
    QString contrasenaIngresada = contrasenaInput->text();
    QString contrasenaHasheada = QCryptographicHash::hash(contrasenaIngresada.toUtf8(), QCryptographicHash::Sha256).toHex();


    if (usuario.isEmpty() || contrasenaIngresada.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor completa todos los campos.");
        return;
    }

    if (!conexion.conectar()) {
        QMessageBox::critical(this, "Error", "No se pudo conectar a la base de datos.");
        return;
    }

    // Consulta por nombre de usuario
    //const char* consulta = "SELECT Nombre, Contrasena, Tipo FROM Usuario WHERE Nombre = $1;";
    const char* consulta = "SELECT id_usuario, Nombre, Contrasena, Tipo FROM Usuario WHERE Nombre = $1;";

    QByteArray nombreUtf8 = usuario.toUtf8();
    const char* valores[] = {nombreUtf8.constData()};

    PGresult *res = PQexecParams(conexion.conn, consulta, 1, nullptr, valores, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        QMessageBox::critical(this, "Error", "Error al consultar la base de datos.");
        PQclear(res);
        return;
    }

    if (PQntuples(res) == 0) {
        QMessageBox::critical(this, "Error", " las credendicales soon incorrectas.");
        PQclear(res);
        return;
    }

    int idUsuario = QString(PQgetvalue(res, 0, 0)).toInt();     // id_usuario
    QString dbNombre = PQgetvalue(res, 0, 1);                   // nombre
    QString dbContrasena = PQgetvalue(res, 0, 2);               // Contrasena
    QString dbTipo = PQgetvalue(res, 0, 3);                     // Tipo

    if (dbContrasena != contrasenaHasheada) {
        QMessageBox::critical(this, "Error", "las credendicales son incorrectas");
        PQclear(res);
        return;
    }

    SesionUsuario::instancia().setUsuario(dbNombre, idUsuario, dbTipo);  // guarda quien inicio sesion

    if (dbTipo == "gestor") {
        VentanaPrincipal *ventanages = new VentanaPrincipal(this);
        ventanages->show();
        usuarioInput->clear();
        contrasenaInput->clear();
        mostrarContrasena->setChecked(false);
        this->close();
    } else if (dbTipo == "lector") {
        VentanaLector *lector = new VentanaLector(this);
        lector->show();
        this->close();
        usuarioInput->clear();
        contrasenaInput->clear();
        mostrarContrasena->setChecked(false);
    } else {
        QMessageBox::critical(this, "Error", "Tipo de usuario no reconocido.");
    }

    PQclear(res);
    conexion.desconectar();
}


