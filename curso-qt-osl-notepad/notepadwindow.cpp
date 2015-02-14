#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto"));

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actArchivoAbrir_->setIcon(QIcon(":/actions/icons/open.png"));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actArchivoGuardar_->setIcon(QIcon(":/actions/icons/save.png"));
    mnuArchivo_->addAction(actArchivoGuardar_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QIcon(":/actions/icons/exit.png"));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCortar_ = new QAction(tr("Co&rtar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    actEditarCortar_->setIcon(QIcon(":/actions/icons/cut.png"));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    actEditarCopiar_->setIcon(QIcon(":/actions/icons/copy.png"));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    actEditarPegar_->setIcon(QIcon(":/actions/icons/paste.png"));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    actEditarDeshacer_->setIcon(QIcon(":/actions/icons/undo.png"));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    actEditarRehacer_->setIcon(QIcon(":/actions/icons/redo.png"));
    mnuEditar_->addAction(actEditarRehacer_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    actFormatoFuente_->setIcon(QIcon(":/actions/icons/font.png"));
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("Ac&erca de este editor"), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    actAyudaAcercade_->setIcon(QIcon(":/actions/icons/help.png"));
    mnuAyuda_->addAction(actAyudaAcercade_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    editToolBar_ = new QToolBar(tr("Edit"), this);
    editToolBar_->addAction(actEditarCortar_);
    editToolBar_->addAction(actEditarCopiar_);
    editToolBar_->addAction(actEditarPegar_);
    this->addToolBar(editToolBar_);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,              SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,              SLOT(alGuardar()));
    connect(actArchivoSalir_,   SIGNAL(triggered()), this,              SLOT(alSalir()));
    connect(actEditarCortar_,   SIGNAL(triggered()), txtEditor_,        SLOT(cut()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,        SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,        SLOT(paste()));
    connect(actEditarRehacer_,  SIGNAL(triggered()), txtEditor_,        SLOT(redo()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_,        SLOT(undo()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,              SLOT(alFuente()));
    connect(actAyudaAcercade_,  SIGNAL(triggered()), this,              SLOT(alAcercade()));

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    actArchivoSalir_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCortar_ ->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    actEditarDeshacer_->deleteLater();
    actEditarRehacer_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    mnuAyuda_->deleteLater();
    actAyudaAcercade_ ->deleteLater();
    editToolBar_->deleteLater();
    txtEditor_->deleteLater();
}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setPlainText(archivo.readAll());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        if (!nombreArchivo.endsWith(".txt", Qt::CaseInsensitive)) {
            archivo.setFileName(nombreArchivo + ".txt");
        }else{
            archivo.setFileName(nombreArchivo);
        }

        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alSalir()
{
    close();
}

void NotepadWindow::alAcercade()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Acerca de este esditor");
    msgBox.setText("Editor de Ayuda versión 1.0 (c) Adrián Rodríguez Vargas");
    msgBox.exec();
}

void NotepadWindow::alFuente()
{



    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}
