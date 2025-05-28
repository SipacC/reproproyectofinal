#include <QApplication>
#include "loginCreativo.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginCreativo w;
    w.show();
    return app.exec();
}
//g++ -o login.exe login.cpp  loginCreativo.cpp conexion.cpp ventanaPrincipal.cpp ventanaUno.cpp ventanaDos.cpp AgregarLibro.cpp GestionLibro.cpp Libro.cpp BuscarLibro.cpp Usuario.cpp GestionUsuario.cpp VentAgregar.cpp ventBuscar.cpp VentModificar.cpp -I"C:/msys64/ucrt64/include/qt6" -I"C:/msys64/ucrt64/include/qt6/QtWidgets" -I"C:/msys64/ucrt64/include/qt6/QtCore" -I"C:/msys64/ucrt64/include/qt6/QtGui" -I"C:/Program Files/PostgreSQL/15/include" -L"C:/msys64/ucrt64/lib" -L"C:/Program Files/PostgreSQL/15/lib" -lQt6Core -lQt6Gui -lQt6Widgets -lpq
