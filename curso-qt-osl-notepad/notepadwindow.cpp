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
    actArchivoAbrir_->setIcon(QIcon::fromTheme("document-open"));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actArchivoGuardar_->setIcon(QIcon::fromTheme("document-save"));
    mnuArchivo_->addAction(actArchivoGuardar_);

    mnuArchivo_->addSeparator();

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QIcon::fromTheme("application-exit"));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    actEditarDeshacer_->setIcon(QIcon::fromTheme("edit-undo"));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    actEditarRehacer_->setIcon(QIcon::fromTheme("edit-redo"));
    mnuEditar_->addAction(actEditarRehacer_);

    mnuEditar_->addSeparator();

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    actEditarCopiar_->setIcon(QIcon::fromTheme("edit-copy"));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    actEditarPegar_->setIcon(QIcon::fromTheme("edit-paste"));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarCortar_ = new QAction(tr("Cort&ar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    actEditarCortar_->setIcon(QIcon::fromTheme("edit-cut"));
    mnuEditar_->addAction(actEditarCortar_);

    mnuEditar_->addSeparator();

    actEditarSeleccionarTodo_ = new QAction(tr("Seleccionar &todo"), this);
    actEditarSeleccionarTodo_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    actEditarSeleccionarTodo_->setIcon(QIcon::fromTheme("edit-select-all"));
    mnuEditar_->addAction(actEditarSeleccionarTodo_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    actFormatoFuente_->setIcon(QIcon::fromTheme("preferences-desktop-font"));
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("&Acerca de"), this);
    actAyudaAcercade_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    actAyudaAcercade_->setIcon(QIcon::fromTheme("help-about"));
    mnuAyuda_->addAction(actAyudaAcercade_);

    // ToolBar
    mainToolBar_ = new QToolBar(this);
    mainToolBar_->addAction(actArchivoAbrir_);
    mainToolBar_->addAction(actArchivoGuardar_);
    mainToolBar_->addSeparator();
    mainToolBar_->addAction(actEditarDeshacer_);
    mainToolBar_->addAction(actEditarRehacer_);
    mainToolBar_->addSeparator();
    mainToolBar_->addAction(actEditarCopiar_);
    mainToolBar_->addAction(actEditarPegar_);
    mainToolBar_->addAction(actEditarPegar_);

    addToolBar(mainToolBar_);



    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Inicializamos el editor de texto
    txtEditor_ = new QPlainTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actArchivoSalir_,   SIGNAL(triggered()), this,          SLOT(alSalir()));
    connect(actEditarRehacer_,  SIGNAL(triggered()), txtEditor_,    SLOT(redo()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_,    SLOT(undo()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actEditarCortar_,   SIGNAL(triggered()), txtEditor_,    SLOT(cut()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(selectAll()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));
    connect(actAyudaAcercade_,  SIGNAL(triggered()), this,          SLOT(alAcercaDe()));

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
        if (!nombreArchivo.endsWith(".txt")) {
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

void NotepadWindow::alAcercaDe()
{
  QMessageBox* msgBox = new QMessageBox(this);
  msgBox->setWindowTitle("Acerca de ....");
  msgBox->setText("Super editor.");
  msgBox->exec();
  delete msgBox;
}

void NotepadWindow::alSalir()
{
  QMessageBox* msgBox = new QMessageBox(this);
  msgBox->setText("Vas a salir del Super Editor.");
  msgBox->setInformativeText("¿Realmente quieres salir?");
  msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  msgBox->setDefaultButton(QMessageBox::Cancel);
  if (QMessageBox::Ok == msgBox->exec()) {
    close();
  }
  delete msgBox;
}
