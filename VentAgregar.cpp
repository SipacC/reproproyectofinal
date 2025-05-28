#include "VentAgregar.h"
#include "VentanaUno.h"
#include <QCryptographicHash>

VentAgregar::VentAgregar(VentanaUno *anterior) : ventanaAnterior(anterior) {
    setWindowTitle("Agregar Usuario");
    resize(400, 350);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titulo = new QLabel("Formulario para agregar un nuevo usuario");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 16px; font-weight: bold;");

    QFormLayout *formLayout = new QFormLayout;

    inputNombre = new QLineEdit();
    inputCorreo = new QLineEdit();
    comboTipo = new QComboBox();
    comboTipo->addItems({"lector", "gestor"});
    inputContrasena = new QLineEdit();
    inputContrasena->setEchoMode(QLineEdit::Normal);

    formLayout->addRow("Nombre:", inputNombre);
    formLayout->addRow("Correo:", inputCorreo);
    formLayout->addRow("Tipo:", comboTipo);
    formLayout->addRow("Contraseña:", inputContrasena);

    btnAgregar = new QPushButton("➕ Agregar Usuario");
    btnAgregar->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");
    btnAgregar->setMinimumHeight(35);

    btnVolver = new QPushButton("⬅️ Volver al menú");
    btnVolver->setMinimumHeight(35);
    btnVolver->setStyleSheet("font-size: 14px;");

    mainLayout->addWidget(titulo);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(btnAgregar);
    mainLayout->addWidget(btnVolver);

    // Conectar el botón para agregar el usuario
    connect(btnAgregar, &QPushButton::clicked, this, &VentAgregar::agregarUsuario);
    connect(btnVolver, &QPushButton::clicked, [=]() {
    this->close();                 // Cierra la ventana actual
    ventanaAnterior->show();      // Muestra la ventana anterior (VentanaUno)
});

}

void VentAgregar::agregarUsuario() {
    QString nombre = inputNombre->text();
    QString correo = inputCorreo->text();
    QString tipo = comboTipo->currentText();
    QString contrasena = inputContrasena->text();

    // Crear objeto Usuario con los datos del formulario
    Usuario usuario(nombre, correo, tipo, contrasena);

    // Usar GestionUsuario para agregar el usuario a la base de datos
    GestionUsuario gestionUsuario;
    if (gestionUsuario.agregarUsuario(usuario)) {
        // Limpiar los campos solo si el usuario fue agregado correctamente
        inputNombre->clear();
        inputCorreo->clear();
        inputContrasena->clear();
    }
}
