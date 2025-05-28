#include "VentModificar.h"
#include "VentanaUno.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QCryptographicHash>

VentModificar::VentModificar(VentanaUno *anterior) : ventanaAnterior(anterior) {
    setWindowTitle("Modificar Usuario");
    resize(400, 350);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    inputId = new QLineEdit();
    inputId->setValidator(new QIntValidator(1, 999999, this));
    inputNombre = new QLineEdit();
    inputCorreo = new QLineEdit();
    comboTipo = new QComboBox();
    comboTipo->addItem("Elige un tipo de usuario");
    comboTipo->addItem("lector");
    comboTipo->addItem("gestor");
    comboTipo->setCurrentIndex(0);
    inputContrasena = new QLineEdit();
    inputContrasena->setEchoMode(QLineEdit::Normal);

    formLayout->addRow("ID Usuario:", inputId);
    formLayout->addRow("Nombre:", inputNombre);
    formLayout->addRow("Correo:", inputCorreo);
    formLayout->addRow("Tipo:", comboTipo);
    formLayout->addRow("Contraseña:", inputContrasena);

    btnModificar = new QPushButton("✅ Modificar Usuario");
    btnRegresar = new QPushButton("🔙 Regresar"); 

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(btnModificar);
    mainLayout->addWidget(btnRegresar);

    // Actualiza automáticamente el nombre al escribir un ID válido
    connect(inputId, &QLineEdit::textChanged, [this]() {
        cargarNombre();
    });

    connect(btnModificar, &QPushButton::clicked, [this]() {
        modificarUsuario();
    });

    connect(btnRegresar, &QPushButton::clicked, [this]() {
    this->close();
    ventanaAnterior->show();
    });
}

void VentModificar::cargarNombre() {
    int id = inputId->text().toInt();
    if (id > 0) {
        GestionUsuario gestor;
        QString nombre = gestor.obtenerNombrePorId(id);
        inputNombre->setText(nombre);
    } else {
        inputNombre->clear();
    }
}

void VentModificar::modificarUsuario() {
    int id = inputId->text().toInt();
    QString nombre = inputNombre->text();
    QString correo = inputCorreo->text();
    QString tipo = comboTipo->currentText();
    QString contrasena = inputContrasena->text();

    if (id <= 0 || nombre.isEmpty() || correo.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Campos inválidos", "Todos los campos deben estar completos.");
        return;
    }

    if (comboTipo->currentIndex() == 0) {
        QMessageBox::warning(this, "Error", "Debes seleccionar un tipo de usuario.");
        return;
    }


    QString contrasenaHash = QCryptographicHash::hash(contrasena.toUtf8(), QCryptographicHash::Sha256).toHex();
    Usuario u(id, nombre, correo, tipo, contrasenaHash);

    GestionUsuario gestor;
    if (gestor.modificarUsuario(id, u)) {
        QMessageBox::information(this, "Éxito", "Usuario modificado correctamente.");
        inputId->clear();
        inputNombre->clear();
        inputCorreo->clear();
        comboTipo->setCurrentIndex(0); // o setCurrentText("lector")
        inputContrasena->clear();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo modificar el usuario.");
    }
}
