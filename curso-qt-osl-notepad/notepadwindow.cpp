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
    actArchivoAbrir_->setIcon(QIcon(":/iconos/iconos/open.png"));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actArchivoGuardar_->setIcon(QIcon(":/iconos/iconos/write.png"));
    mnuArchivo_->addAction(actArchivoGuardar_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QIcon(":/iconos/iconos/exit.png"));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    actEditarCopiar_->setIcon(QIcon(":/iconos/iconos/copy.png"));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    actEditarCortar_->setIcon(QIcon(":/iconos/iconos/cut.png"));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    actEditarPegar_->setIcon(QIcon(":/iconos/iconos/paste.png"));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    actEditarDeshacer_->setIcon(QIcon(":/iconos/iconos/deshacer.png"));
    mnuEditar_->addAction(actEditarDeshacer_);


    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    actEditarRehacer_->setIcon(QIcon(":/iconos/iconos/rehacer.png"));
    mnuEditar_->addAction(actEditarRehacer_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    actFormatoFuente_->setIcon(QIcon(":/iconos/iconos/fuente.png"));
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("&Acerca de"), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    actAyudaAcercade_->setIcon(QIcon(":/iconos/iconos/about.png"));
    mnuAyuda_->addAction(actAyudaAcercade_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    toolbar_ = new QToolBar(tr("Toolbar Way"), this);

    this->addToolBar(toolbar_);
    toolbar_->addAction(actArchivoAbrir_);
    toolbar_->addAction(actArchivoGuardar_);
    toolbar_->addAction(actArchivoSalir_);
    toolbar_->addAction(actFormatoFuente_);
    toolbar_->addAction(actEditarCopiar_);
    toolbar_->addAction(actEditarCortar_);
    toolbar_->addAction(actEditarPegar_);
    toolbar_->addAction(actEditarDeshacer_);
    toolbar_->addAction(actEditarRehacer_);
    toolbar_->addAction(actAyudaAcercade_);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoSalir_,   SIGNAL(triggered()), this,          SLOT(close()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarCortar_,   SIGNAL(triggered()), txtEditor_,    SLOT(cut()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_,    SLOT(undo()));
    connect(actEditarRehacer_,  SIGNAL(triggered()), txtEditor_,    SLOT(redo()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));
    connect(actAyudaAcercade_,  SIGNAL(triggered()), this,          SLOT(alAcercade()));

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    actEditarDeshacer_->deleteLater();
    actEditarRehacer_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
    actArchivoSalir_->deleteLater();
    mnuAyuda_->deleteLater();
    actAyudaAcercade_->deleteLater();
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
        if (!nombreArchivo.endsWith(".txt")){
            //archivo.setFileName(nombreArchivo + ".txt");
            nombreArchivo += ".txt";
        }
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }
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

void NotepadWindow::alAcercade()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Acerca de");
    msgBox.setText("Super editor de texto creado en QT");
    msgBox.setMinimumWidth(4000);
    msgBox.exec();
}
