#ifndef LOGINCREATIVO_H
#define LOGINCREATIVO_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class LoginCreativo : public QWidget {
public:
    LoginCreativo(QWidget *parent = nullptr);

private:
    QLineEdit *usuarioInput;
    QLineEdit *contrasenaInput;
    QCheckBox *mostrarContrasena;

    void toggleMostrarContrasena(bool checked);
    void simularLogin();
};

#endif // LOGINCREATIVO_H
