#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>
#include <QToolBar>
#include <QMessageBox>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT  // Clase necesaria para poder utilizar funcionalidades de directivas de Qt: slots, signals, ...

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAcercaDe();
    void alSalir();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarDeshacer_;
    QAction*        actEditarRehacer_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarSeleccionarTodo_;
    QMenu*          mnuAyuda_;
    QAction*        actAyudaAcercade_;
    QPlainTextEdit* txtEditor_;
    QToolBar*       mainToolBar_;
    QClipboard *    portapapeles_;

};

#endif // NOTEPADWINDOW_H
