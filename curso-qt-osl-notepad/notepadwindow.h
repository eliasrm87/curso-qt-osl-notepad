#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QKeySequence>
#include <QMessageBox>
#include <QToolBar>
#include <QCloseEvent>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();


protected:
     void closeEvent(QCloseEvent *event);

private slots:
    bool alCerrar();
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAcercaDe();

    void alNegrita(bool negrita);
    void alCursiva(bool cursiva);
    void alSubrayado(bool subrayado);
    void alModificarTexto();

    void actualizarCursor();
    void actualizarTitulo(QString titulo, bool modificado);

private:
    QString         fileName_;
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QAction*        actFormatoNegrita_;
    QAction*        actFormatoCursiva_;
    QAction*        actFormatoSubrayado_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarDeshacer_;
    QAction*        actEditarRehacer_;
    QMenu*          mnuAyuda_;
    QAction*        actAyudaAcercaDe_;
    QTextEdit*      txtEditor_;

};

#endif // NOTEPADWINDOW_H
