/*
    Autor: Adrián Rodríguez Bazaga
    Aplicación: Bloc de notas
    Correo electrónico: alu0100826456@ull.edu.es
*/


#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QPlainTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QColor>
#include <QComboBox>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>

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
    void alLimpiar();
    void alCortar();
    void alDeshacer();
    void alRehacer();
    void alAcercaDe();
    void alCambiarFuente();
    void alCambiarTam();
    void alCambiarColor();
    void alPonerNegrita();
    void alPonerCursiva();
    void alPonerSubrayado();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QMenu*          mnuEditar_;
    QTextEdit*      txtEditor_;
    QAction*        bhArchivoAbrir_;
    QAction*        bhArchivoGuardar_;
    QAction*        bhArchivoSalir_;
    QAction*        bhEdicionLimpiar_;
    QAction*        bhEdicionCortar_;
    QAction*        bhEdicionDeshacer_;
    QAction*        bhEdicionRehacer_;
    QAction*        bhAyudaAD_;
    QToolBar*       toolbar;
    QActionGroup*   actionGroup;
    QComboBox*      selector_col;
    QComboBox*      selector;
    QComboBox*      selector_tam;
    QMessageBox*    acerca_de_;

};

#endif // NOTEPADWINDOW_H
