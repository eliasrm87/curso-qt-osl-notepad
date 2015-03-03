#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit> // Si queremos dar controlador de sintaxis , hay que usar TextEdit.
#include <QFileDialog> // Ventana para nombrar, elegir .
#include <QFile> // Abrir ficheros, leerlos y escribirlos.
#include <QFontDialog>
#include <QClipboard> // Gestión de portapapeles.
#include <QKeySequence> // Accesos directos.
#include <QToolBar>
#include <QMessageBox>
#include <QDebug>
#include <QFont>
#include <QJsonDocument>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT // Directiva del precompilador QT. Esta clase tiene cositas de un objeto de QT

public:
    NotepadWindow(QWidget *parent = 0); // Si no se especifica, es huérfano.
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void acerca();
    void textBold();
    void textItalic();
    void textUnderline();

private:   // Todos son punteros porque
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarDeshacer_;
    QAction*        actEditarRehacer_;
    QTextEdit*      txtEditor_;
    QClipboard*     portapapeles_;
    QToolBar*       toolbar_;
    QMenu*          mnuAyuda_;
    QAction*        actAyudaAcerca_;
    QAction*        actBold_;
    QAction*        actItalic_;
    QAction*        actUnderline_;
};

#endif // NOTEPADWINDOW_H
