#ifndef VENTANASOLICITUDESUS_H
#define VENTANASOLICITUDESUS_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

#include "GestionSolicitudes.h"
#include "VentanaSolicitudesNuevas.h"

// ❗ Se eliminó inclusión circular innecesaria de "VentanaLector.h"
// En su lugar, se hace una declaración adelantada
class VentanaLector;

class VentanaSolicitudesUs : public QWidget {
public:
    explicit VentanaSolicitudesUs(int idUsuario, VentanaLector* ventanaAnterior, QWidget *parent = nullptr);
    
    // ✅ Definición del destructor agregada en el .cpp
    ~VentanaSolicitudesUs();

private:
    int idUsuario;

    VentanaLector* ventanaAnterior;
    QPushButton* botonNuevaSolicitud;
    VentanaSolicitudesNuevas* ventanaNuevas = nullptr;
    QTableWidget *tablaSolicitudes;
    QLineEdit *inputBusqueda;
    QComboBox *comboEstado;
    QPushButton *botonActualizar;
    QPushButton *botonRegresar;

    GestionSolicitudes gestor;

    void configurarInterfaz();
    void cargarSolicitudes();
    void conectarEventos();
};

#endif // VENTANASOLICITUDESUS_H
