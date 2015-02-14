#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Notepad--"));

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);

    actSalir_ = new QAction(tr("&Salir"), this);
    actSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    mnuArchivo_->addAction(actSalir_);

    //MENU EDITAR
    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    //MENU FORMATO
    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    mnuHelp_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuHelp_);

    actAbout_ = new QAction(tr("&Acerca de ..."), this);
    mnuHelp_->addAction(actAbout_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Inicializamos el editor de texto
    txtEditor_ = new QPlainTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));
    connect(actAbout_,  SIGNAL(triggered()), this,          SLOT(alAbout()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
    connect(actSalir_, SIGNAL(triggered()), this, SLOT(alSalir()));

    //Toolbar con imagenes

    mainToolbar_ = new QToolBar(this);

    mainToolbar_->setAllowedAreas(Qt::TopToolBarArea); //fijo
    mainToolbar_->setMovable(false);

    mainToolbar_->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //imagen a la acción
    actArchivoAbrir_->setIcon(QIcon(":/actions/resource/abrir.ico"));
    actArchivoGuardar_->setIcon(QIcon(":/actions/resource/guardar.ico"));
    actEditarDeshacer_->setIcon(QIcon(":/actions/resource/atras.ico"));


    actArchivoAbrir_->setIconVisibleInMenu(false);


    //añadiendo lo que se va a mostrar
    mainToolbar_->addAction(actArchivoAbrir_);
    mainToolbar_->addAction(actArchivoGuardar_);
    mainToolbar_->addAction(actEditarDeshacer_);

    //añadido a la barra
    addToolBar(mainToolbar_);

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
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    mnuHelp_->deleteLater();
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
        if(!nombreArchivo.endsWith(".txt")){
          nombreArchivo += ".txt";
        }
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

void NotepadWindow::alAbout()
{
    QMessageBox about;
    about.setWindowTitle(tr("About"));
    about.setText(tr("Notepad -- de Haniel Martín"));
    about.addButton(tr("Cerrar"), QMessageBox::RejectRole);
    about.exec();
}

void NotepadWindow::alSalir()
{
    QMessageBox sure;
    sure.setWindowTitle(tr("Aviso"));
    sure.setText(tr("¿Está seguro que desea salir?"));
    sure.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    int ret = sure.exec();

    if (ret == QMessageBox::Ok)
        close(); //mas limpio que exit(0);
}
