#include "AgregarLibro.h"
#include "VentanaDos.h"
#include <QMessageBox>
#include <QDate>

AgregarLibro::AgregarLibro(VentanaDos *ventanaAnterior, QWidget *parent) : QWidget(parent), ventanaAnterior(ventanaAnterior) {
    setWindowTitle("Agregar Libro");
    resize(400, 370);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *titulo = new QLabel("Formulario para agregar un nuevo libro");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 16px; font-weight: bold;");

    QFormLayout *formLayout = new QFormLayout;

    inputISBN = new QLineEdit();
    inputTitulo = new QLineEdit();
    inputAutor = new QLineEdit();
    inputEditorial = new QLineEdit();
    inputAnio = new QLineEdit();
    inputMateria = new QLineEdit();
    comboEstado = new QComboBox();
    comboEstado->addItems({"disponible"});
    inputEjemplares = new QSpinBox();
    inputEjemplares->setMinimum(1);
    inputEjemplares->setMaximum(1000);

    formLayout->addRow("ISBN:", inputISBN);
    formLayout->addRow("Título:", inputTitulo);
    formLayout->addRow("Autor:", inputAutor);
    formLayout->addRow("Editorial:", inputEditorial);
    formLayout->addRow("Año de publicación:", inputAnio);
    formLayout->addRow("Materia:", inputMateria);
    formLayout->addRow("Estado:", comboEstado);
    formLayout->addRow("Ejemplares:", inputEjemplares);

    btnAgregar = new QPushButton("➕ Agregar Libro");
    btnAgregar->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");
    btnAgregar->setMinimumHeight(35);

    btnVolver = new QPushButton("⬅️ Volver al menú");
    btnVolver->setStyleSheet("font-size: 14px;");
    btnVolver->setMinimumHeight(35);

    mainLayout->addWidget(titulo);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(btnAgregar);
    mainLayout->addWidget(btnVolver);

    connect(btnAgregar, &QPushButton::clicked, this, &AgregarLibro::agregarLibro);
    connect(btnVolver, &QPushButton::clicked, [=]() {
        this->close();
        ventanaAnterior->show();
    });
}

void AgregarLibro::agregarLibro() {
    QString isbn = inputISBN->text();
    QString titulo = inputTitulo->text();
    QString autor = inputAutor->text();
    QString editorial = inputEditorial->text();
    int anio = inputAnio->text().toInt();
    QString materia = inputMateria->text();
    QString estado = comboEstado->currentText();
    int ejemplares = inputEjemplares->value(); 

    

    Libro libro(isbn, titulo, autor, editorial, anio, materia, estado, ejemplares);
    GestionLibro gestor;

    if (gestor.agregarLibro(libro)) {
        inputISBN->clear();
        inputTitulo->clear();
        inputAutor->clear();
        inputEditorial->clear();
        inputAnio->clear();
        inputMateria->clear();
        comboEstado->setCurrentIndex(0);
        inputEjemplares->setValue(0);

    }
}
