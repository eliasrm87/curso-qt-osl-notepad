#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
#include <QDebug>
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
#include <QMessageBox>
#include <QDialog>
#include <QToolBar>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alSalir();
    void alAcercade();
    void alFuente();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarRehacer_;
    QAction*        actEditarDeshacer_;
    QMenu*          mnuAyuda_;
    QAction*        actAyudaAcercade_;
    QTextEdit*      txtEditor_;
    // para acceder y modificar el contenido del clipboard directamente (no necesario)
    // QClipboard *    portapapeles_;
    QToolBar*       editToolBar_;
};

#endif // NOTEPADWINDOW_H
