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
#include <QClipboard>
#include <QKeySequence>
#include <QToolBar>
#include <QFont>
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
    void alSalir();
    void alBold();
    void alCursive();
    void alUnderline();
private:
    QClipboard *    portapapeles_;
    QTextEdit* txtEditor_;
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QMenu*          mnuFormato_;
    QMenu*          mnuEditar_;
    QMenu*          mnuAyuda_;
    QToolBar*       Toolbar_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QAction*        actFormatoFuente_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarRehacer_;
    QAction*        actEditarDeshacer_;
    QAction*        actHelp_;
    QAction*          bold_;
    QAction*          cursive_;
    QAction*          underliner_;
};

#endif // NOTEPADWINDOW_H
