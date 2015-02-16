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
#include <QMessageBox>
#include <QToolBar>
#include <QTextEdit>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAbout();
    void alSalir();
    void Negrita();
    void Cursiva();
    void Subrayado();
    void Aumentar_Zoom();
    void Disminuir_Zoom();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QMenu*          mnuFormato_;
    QMenu*          mnuEditar_;
    QMenu*          mnuHelp_;

    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actFormatoFuente_;
    QAction*        actAbout_;
    QAction*        actSalir_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarDeshacer_;
    QAction*        actEditarRehacer_;
    QAction*        actFormatoNegrita_;
    QAction*        actFormatoCursiva_;
    QAction*        actFormatoSubrayado_;
    QAction*        actEditarTodo_;
    QAction*        actEditarMenosZoom_;
    QAction*        actEditarMasZoom_;
    QTextEdit*      txtEditor_; //cambiado de texto plano anterior
    QClipboard *    portapapeles_;
    QToolBar*       mainToolbar_;



};

#endif // NOTEPADWINDOW_H
