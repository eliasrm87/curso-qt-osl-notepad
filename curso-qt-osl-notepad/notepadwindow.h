#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QFileDialog> //Abrir y guardar (ventana)
#include <QFile> //Abrir, Leer y escribir y cerrar ficheros
#include <QFontDialog> //elegir la fuente
#include <QClipboard> //Gestion de portapapeles
#include <QKeySequence> //Atajos de teclado
#include <QMessageBox>
#include <QToolBar>
#include <QWidget>
#include <QDialogButtonBox>
#include <QColor>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT //Directica al precompilador para indicar que hay funciones de Qt

public:

    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:

    void alAbrir();
    void alGuardar();
    void alFuente();
    void ayuda();
    void salir();
    void negrita();
//    void cursiva();
//    void subrayar();


private:



    QMenuBar*       mainMenu_; //Menu principal
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QTextEdit*      txtEditor_; //Cuadro de texto
    QClipboard *    portapapeles_; //Portapapeles


    QAction*        actEditarCortar_;
    QAction*        actEditarDeshacer_;
    QAction*        actEditarRehacer_;

    QAction*        actArchivoSalir_;

    QMessageBox*    messAyuda_;
    QAction*        actAyuda_;
    QToolBar*       funciones_;

    QAction*        actBold_;
    QAction*        actItalics_;
    QAction*        actUnderline_;

 };

#endif // NOTEPADWINDOW_H
