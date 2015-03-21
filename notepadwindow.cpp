#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent) // Porque hereda de QMainWindow
{

    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600); // (x,y,ancho,alto)

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto")); // translate to other language

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this); // this es el parent. La barra menú será hija de QMainWindow

    mnuArchivo_ = new QMenu(tr("&Archivo"), this); // El & es para permitir un acceso más rápido desde el teclado , por ejemplo ALT + A ( Abrir )
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);

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

    actEditarCortar_ = new QAction(tr("&Cortar"),this);
    actEditarCortar_->setShortcut((QKeySequence(Qt::CTRL + Qt::Key_X)));
    actEditarCortar_->setIcon(QIcon(":/actions/toolbar/tijeras.png"));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"),this);
    actEditarDeshacer_->setShortcut((QKeySequence(Qt::CTRL + Qt::Key_Z)));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"),this);
    actEditarRehacer_->setShortcut((QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Z)));
    mnuEditar_->addAction(actEditarRehacer_);

    // Edición de fuente
    actBold_ = new QAction(tr("&Negrita"),this);
    actBold_->setShortcut((QKeySequence(Qt::CTRL + Qt::Key_N)));

    actUnderline_ = new QAction(tr("&Subrayar"),this);
    actUnderline_->setShortcut((QKeySequence(Qt::CTRL + Qt::Key_U)));

    actItalic_ = new QAction(tr("&Cursiva"),this);
    actItalic_->setShortcut((QKeySequence(Qt::CTRL + Qt::Key_I)));
    /////

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    toolbar_ = new QToolBar();
    toolbar_->addAction(actEditarCopiar_);
    toolbar_->addAction(actEditarPegar_);
    toolbar_->addAction(actEditarCortar_);
    toolbar_->addAction(actEditarDeshacer_);
    toolbar_->addAction(actEditarRehacer_);
    toolbar_->addSeparator();
    toolbar_->addAction(actBold_);
    toolbar_->addAction(actItalic_);
    toolbar_->addAction(actUnderline_);
    addToolBar(toolbar_);

    actAyudaAcerca_ = new QAction(tr("&Acerca"),this);
    actAyudaAcerca_->setShortcut((QKeySequence(Qt::CTRL + Qt::Key_H)));
    actAyudaAcerca_->setIcon(QIcon(":/actions/toolbar/Mario-icon.png"));


    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mnuAyuda_->addAction(actAyudaAcerca_);

    mainMenu_->addMenu(mnuAyuda_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_); // EL THIS es explícito, también funciona : setMenuBar(mainMenu_);


    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar())); // (Emisor, cual de sus puertos, receptor, cual de sus puertos)
    connect(actArchivoSalir_,   SIGNAL(triggered()), this,          SLOT(close()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actEditarCortar_,   SIGNAL(triggered()), txtEditor_,    SLOT(cut()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_,    SLOT(undo()));
    connect(actEditarRehacer_,  SIGNAL(triggered()), txtEditor_,    SLOT(redo()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));
    connect(actAyudaAcerca_,    SIGNAL(triggered()), this,          SLOT(acerca()));
    connect(actBold_,           SIGNAL(triggered()), this,          SLOT(textBold()));
    connect(actItalic_,         SIGNAL(triggered()), this,          SLOT(textItalic()));
    connect(actUnderline_,      SIGNAL(triggered()), this,          SLOT(textUnderline()));


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
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    actEditarCortar_->deleteLater();
    actEditarDeshacer_->deleteLater();
    actEditarRehacer_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
    toolbar_->deleteLater();
    mnuAyuda_->deleteLater();
    actAyudaAcerca_->deleteLater();
    actBold_->deleteLater();
    actItalic_->deleteLater();
    actUnderline_->deleteLater();
}

void NotepadWindow::acerca()
{
    QMessageBox msgBox;
    msgBox.setText("Me llamo ruda");
    msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Cancel);
    msgBox.exec();

}

void NotepadWindow::textBold()
{
    QFont* mifuente = new QFont ();
    if(txtEditor_->currentFont().bold())
        mifuente->setBold(false);
    else
        mifuente->setBold(true);
    txtEditor_->setCurrentFont(*mifuente);
}

void NotepadWindow::textItalic()
{
    QFont* mifuente = new QFont ();
    if(txtEditor_->currentFont().italic())
        mifuente->setItalic(false);
    else
        mifuente->setItalic(true);
    txtEditor_->setCurrentFont(*mifuente);
}

void NotepadWindow::textUnderline()
{
    QFont* mifuente = new QFont ();
    if(txtEditor_->currentFont().underline())
        mifuente->setUnderline(false);
    else
        mifuente->setUnderline(true);
    txtEditor_->setCurrentFont(*mifuente);
}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "", // Es el directorio donde se abre, así "" se abre en el que estemos.
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
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8()); // El toUft8 te convierte el QString en un QByteArray
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this); // (boton ok, fuente establecida anteriormente, objeto que se verá afectado )
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}
