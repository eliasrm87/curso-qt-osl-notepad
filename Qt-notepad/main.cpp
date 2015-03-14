/*
    Autor: Adrián Rodríguez Bazaga
    Aplicación: Bloc de notas
    Correo electrónico: alu0100826456@ull.edu.es
*/


#include "notepadwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("img/icono.jpg"));
    NotepadWindow w;
    w.setWindowTitle("Curso de QT: Editor de texto (Adrián Rodríguez Bazaga)");
    w.resize(750, 500);
    w.show();

    return a.exec();
}
