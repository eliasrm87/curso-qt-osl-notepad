#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    fileName_ = "";

    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Editor de texto - <unnamed>"));

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

    mnuArchivo_->addSeparator();

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    mnuEditar_->addSeparator();

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRehacer_);

    /* FORMATO */
    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    actFormatoNegrita_ = new QAction(tr("&Negrita"), this);
    actFormatoNegrita_->setCheckable(true);
    mnuFormato_->addAction(actFormatoNegrita_);

    actFormatoCursiva_ = new QAction(tr("&Cursiva"), this);
    actFormatoCursiva_->setCheckable(true);
    mnuFormato_->addAction(actFormatoCursiva_);

    actFormatoSubrayado_ = new QAction(tr("&Subrayado"), this);
    actFormatoSubrayado_->setCheckable(true);
    mnuFormato_->addAction(actFormatoSubrayado_);

    /* AYUDA */
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercaDe_ = new QAction(tr("&Acerca de..."), this);
    mnuAyuda_->addAction(actAyudaAcercaDe_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    // Creamos un toolbar con la funciones principales del programa
    QToolBar* toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    addToolBar(toolbar);

    toolbar->addAction(actArchivoAbrir_);
    toolbar->addAction(actArchivoGuardar_);
    toolbar->addSeparator();
    toolbar->addAction(actEditarCortar_);
    toolbar->addAction(actEditarCopiar_);
    toolbar->addAction(actEditarPegar_);
    toolbar->addSeparator();
    toolbar->addAction(actFormatoCursiva_);
    toolbar->addAction(actFormatoNegrita_);
    toolbar->addAction(actFormatoSubrayado_);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,       SIGNAL(triggered()),        this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_,     SIGNAL(triggered()),        this,          SLOT(alGuardar()));
    connect(actArchivoSalir_,       SIGNAL(triggered()),        this,          SLOT(alCerrar()));
    connect(actEditarCopiar_,       SIGNAL(triggered()),        txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,        SIGNAL(triggered()),        txtEditor_,    SLOT(paste()));
    connect(actEditarDeshacer_,     SIGNAL(triggered()),        txtEditor_,    SLOT(undo()));
    connect(actEditarRehacer_,      SIGNAL(triggered()),        txtEditor_,    SLOT(redo()));
    connect(actFormatoFuente_,      SIGNAL(triggered()),        this,          SLOT(alFuente()));
    connect(actFormatoCursiva_,     SIGNAL(toggled(bool)),      this,          SLOT(alCursiva(bool)));
    connect(actFormatoNegrita_,     SIGNAL(toggled(bool)),      this,          SLOT(alNegrita(bool)));
    connect(actFormatoSubrayado_,   SIGNAL(toggled(bool)),      this,          SLOT(alSubrayado(bool)));
    connect(actAyudaAcercaDe_,      SIGNAL(triggered()),        this,          SLOT(alAcercaDe()));
    connect(txtEditor_,             SIGNAL(cursorPositionChanged()), this, SLOT(actualizarCursor()));

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos (no necesario, sólo cuando no tienen padre)
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

void NotepadWindow::alCerrar()
{
    QMessageBox::StandardButton pressed;
    pressed = QMessageBox::question(this, tr("Salir"), tr("¿Estás seguro que deseas salir?"));
    if (pressed == QMessageBox::Yes)
        close();
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
            actualizarTitulo(nombreArchivo);
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
            //nombreArchivo.chop(4);
            nombreArchivo += ".txt";
        }

        archivo.setFileName(nombreArchivo/* + ".txt"*/);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Se cierra el fichero
            archivo.close();
            actualizarTitulo(nombreArchivo);
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setCurrentFont(font);
    }
}

void NotepadWindow::alAcercaDe()
{
    QMessageBox::about(this,
                       tr("Acerca de..."),
                       tr("<b>Editor de texto</b><tr/>"
                          "Versión 1.0. Copyright ..... 2015"));
}

void NotepadWindow::alNegrita(bool negrita)
{
    QFont font = txtEditor_->currentFont();
    font.setBold(negrita);
    txtEditor_->setCurrentFont(font);
}

void NotepadWindow::alCursiva(bool cursiva)
{
    QFont font = txtEditor_->currentFont();
    font.setItalic(cursiva);
    txtEditor_->setCurrentFont(font);
}

void NotepadWindow::alSubrayado(bool subrayado)
{
    QFont font = txtEditor_->currentFont();
    font.setUnderline(subrayado);
    txtEditor_->setCurrentFont(font);
}

void NotepadWindow::actualizarCursor()
{
    QFont font = txtEditor_->currentFont();
    actFormatoCursiva_->setChecked(font.italic());
    actFormatoNegrita_->setChecked(font.bold());
    actFormatoSubrayado_->setChecked(font.underline());
}

void NotepadWindow::actualizarTitulo(QString titulo)
{
    fileName_ = titulo;
    setWindowTitle("Editor de texto - " + titulo);
}

