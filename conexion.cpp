#include "conexion.h"
#include <QMessageBox>

Conexion::Conexion() : conn(nullptr) {}

Conexion::~Conexion() {
    desconectar();
}

bool Conexion::conectar() {
    const char *conninfo = "dbname=biblioteca user=postgres password=manuel59 host=localhost port=5432";

    conn = PQconnectdb(conninfo);
    
    if (PQstatus(conn) != CONNECTION_OK) {
        QMessageBox::critical(nullptr, "Error de conexión", PQerrorMessage(conn));
        PQfinish(conn);
        conn = nullptr;
        return false;
    }

    return true;
}

void Conexion::desconectar() {
    if (conn) {
        PQfinish(conn);
        conn = nullptr;
    }
}
