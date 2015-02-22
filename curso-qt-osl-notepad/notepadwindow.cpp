#include "notepadwindow.h"

#include <QWebView>



NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent) //Invocamos al constructor padre
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Tiembla Microsoft Word")); //tr -> nos permite traduccir el programa al idioma del SO

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);
    funciones_ = new QToolBar(this);


    mnuArchivo_ = new QMenu(tr("&Archivo"), this); //Archivo y el padre que es el mismo
    mainMenu_->addMenu(mnuArchivo_); //Añadimos un menú

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S)); //Establecer el acceso directo de teclado
    actArchivoGuardar_->setIcon (QIcon(QPixmap(":/icons/Iconos/save.png")));
    mnuArchivo_->addAction(actArchivoGuardar_); //Añadimos la funcion al menu

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    actEditarCopiar_->setIcon (QIcon(QPixmap(":/icons/Iconos/copy.png")));
    mnuEditar_->addAction(actEditarCopiar_);
    funciones_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    actEditarPegar_->setIcon(QIcon(QPixmap(":/icons/Iconos/paste.png")));
    mnuEditar_->addAction(actEditarPegar_);
    funciones_->addAction(actEditarPegar_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    actFormatoFuente_->setIcon(QIcon(QPixmap(":/icons/Iconos/fuente.png")));
    mnuFormato_->addAction(actFormatoFuente_);

    actEditarCortar_ = new QAction(tr("&Cortar"),this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    actEditarCortar_->setIcon (QIcon(QPixmap(":/icons/Iconos/cut.png")));
    mnuEditar_->addAction(actEditarCortar_);
    funciones_->addAction(actEditarCortar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"),this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    actEditarDeshacer_->setIcon(QIcon(QPixmap(":/icons/Iconos/undo.png")));
    mnuEditar_->addAction(actEditarDeshacer_);
    funciones_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"),this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    actEditarRehacer_->setIcon(QIcon(QPixmap(":/icons/Iconos/redo.png")));
    mnuEditar_->addAction(actEditarRehacer_);
    funciones_->addAction(actEditarRehacer_);

    actArchivoSalir_ = new QAction(tr("&Salir"),this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F4));
    mnuArchivo_->addAction(actArchivoSalir_);

    messAyuda_ = new QMessageBox(this); //Nueva ventana
    actAyuda_ = new QAction(tr("&Ayuda"),this);
    actAyuda_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    actAyuda_->setIcon(QIcon(QPixmap(":/icons/Iconos/info28.png")));
    mainMenu_->addAction(actAyuda_);

    actBold_ = new QAction(tr("&Negrita"),this);
    actBold_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    actBold_->setIcon(QIcon(QPixmap(":/icons/Iconos/bold17.png")));
    mnuFormato_->addAction(actBold_);

    actItalics_ = new QAction(tr("&Cursiva"),this);
    actItalics_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    actItalics_->setIcon(QIcon(QPixmap(":/icons/Iconos/italic8.png")));
    mnuFormato_->addAction(actItalics_);

    actUnderline_ = new QAction(tr("&Subrayado"),this);
    actUnderline_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actUnderline_->setIcon(QIcon(QPixmap(":/icons/Iconos/underlined4.png")));
    mnuFormato_->addAction(actUnderline_);

    alinear_dcha_ = new QAction(tr("Alinear Derecha"),this);
    alinear_dcha_->setIcon(QIcon(QPixmap(":/icons/Iconos/derecha.png")));
    mnuFormato_->addAction(alinear_dcha_);

    alinear_izq_ = new QAction(tr("Alinear Izquierda"),this);
    alinear_izq_->setIcon(QIcon(QPixmap(":/icons/Iconos/izquierda.png")));
    mnuFormato_->addAction(alinear_izq_);

    alinear_cent_ = new QAction(tr("Centrar"),this);
    alinear_cent_->setIcon(QIcon(QPixmap(":/icons/Iconos/centrado.png")));
    mnuFormato_->addAction(alinear_cent_);

    justificar_ = new QAction(tr("Justificar"),this);
    justificar_->setIcon(QIcon(QPixmap(":/icons/Iconos/justificado.png")));
    mnuFormato_->addAction(justificar_);


    //Añadimos las opciones de justificado en la barra de tareas
    funciones_->addAction(alinear_dcha_);
    funciones_->addAction(alinear_izq_);
    funciones_->addAction(alinear_cent_);
    funciones_->addAction(justificar_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);
    this->addToolBar(funciones_);
    //Inicializamos el editor de texto

    txtEditor_ = new QTextEdit(this);
    txtEditor_->setAcceptRichText(true);


    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));

 //--------------------------------------------------------------------------------

     connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));
     connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
     connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));
     connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT (salir()));
     connect(actBold_,SIGNAL(triggered()),this,SLOT(negrita()));
     connect(actItalics_,SIGNAL(triggered()),this,SLOT(cursiva()));
     connect(actUnderline_,SIGNAL(triggered()),this,SLOT(subrayar()));

     connect(actAyuda_, &QAction::triggered, [&](){

         messAyuda_->information(this,"Acerca de","Editor de Texto");


       });

     //Conectamos las opciones de justificado con SLOTS LAMBDA
     connect(alinear_cent_, &QAction::triggered, [&](){

         QTextCursor cursor = txtEditor_->textCursor();
         QTextBlockFormat textBlockFormat = cursor.blockFormat();
         textBlockFormat.setAlignment(Qt::AlignCenter);
         cursor.mergeBlockFormat(textBlockFormat);
         txtEditor_->setTextCursor(cursor);

     });

     connect(alinear_dcha_, &QAction::triggered, [&](){

         QTextCursor cursor = txtEditor_->textCursor();
         QTextBlockFormat textBlockFormat = cursor.blockFormat();
         textBlockFormat.setAlignment(Qt::AlignRight);
         cursor.mergeBlockFormat(textBlockFormat);
         txtEditor_->setTextCursor(cursor);

     });

     connect(alinear_izq_, &QAction::triggered, [&](){

         QTextCursor cursor = txtEditor_->textCursor();
         QTextBlockFormat textBlockFormat = cursor.blockFormat();
         textBlockFormat.setAlignment(Qt::AlignLeft);
         cursor.mergeBlockFormat(textBlockFormat);
         txtEditor_->setTextCursor(cursor);

     });


     connect(justificar_, &QAction::triggered, [&](){

         QTextCursor cursor = txtEditor_->textCursor();
         QTextBlockFormat textBlockFormat = cursor.blockFormat();
         textBlockFormat.setAlignment(Qt::AlignJustify);
         cursor.mergeBlockFormat(textBlockFormat);
         txtEditor_->setTextCursor(cursor);

     });

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_); //En esta ventana el widget central es el txtEditor

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

    actArchivoSalir_->deleteLater();
    actEditarCortar_->deleteLater();
    actEditarDeshacer_->deleteLater();
    actEditarRehacer_->deleteLater();
    actAyuda_->deleteLater();
    actBold_->deleteLater();
    actItalics_->deleteLater();
    actUnderline_->deleteLater();
    alinear_cent_->deleteLater();
    alinear_dcha_->deleteLater();
    alinear_izq_->deleteLater();
    messAyuda_->deleteLater();

//    print_BW_->deleteLater();
//    print_color_->deleteLater();
//    mnImprimir_->deleteLater();


}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)")); //Abrir un cuadro de dialogo
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo); //Establecemos el nombre del archivo
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setPlainText(archivo.readAll()); //Esto no se puede realizar con ficheros grandes porque todo va a memoria
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

        if(!nombreArchivo.endsWith(".txt"))
            nombreArchivo+=".txt"; //Si el usuario no ha puesto el .txt lo ponemos

        archivo.setFileName(nombreArchivo);

        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) { //Si existe lo crea, y si existe elimina el contenido y lo reemplaza
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8()); //Convertimos el texto en QByteArray
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this); //Nos devuelve la fuente que selecciono
    if (ok) { //el booleano que dice si se dio a OK o cancelar
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font); //cambiamos la fuente
    }
}

void NotepadWindow::salir(){

    QMessageBox* adv = new QMessageBox(this);
    adv->setWindowTitle ("Atención");
    adv->setText("¿Esta seguro que desea salir sin guardar?");
    QPushButton* salir = adv->addButton("Guardar y Salir",QMessageBox::AcceptRole);
    QPushButton* save_exit = adv->addButton ("Salir",QMessageBox::RejectRole);


    connect(adv, &QMessageBox::accepted, [&](){this->close();});
    connect(adv, &QMessageBox::rejected, [&] (){

           this->alGuardar ();
            this->close();

    });

    adv->open();

}

void NotepadWindow::negrita()
{
    QTextCharFormat fmt;
    QTextCursor cursor = txtEditor_->textCursor();

      if (!cursor.hasSelection())
          cursor.select(QTextCursor::WordUnderCursor);

      if( cursor.charFormat().fontWeight() == QFont::Bold  )
          fmt.setFontWeight( QFont::Normal);
      else
      {
         fmt.setFontWeight( QFont::Bold);
      }


      cursor.mergeCharFormat( fmt );

}

void NotepadWindow::cursiva()
{

    QTextCharFormat fmt;
    QTextCursor cursor = txtEditor_->textCursor();

      if (!cursor.hasSelection())
          cursor.select(QTextCursor::WordUnderCursor);

      if( cursor.charFormat().fontItalic() == QFont::Cursive)
          fmt.setFontItalic(QFont::Normal);
      else
          fmt.setFontItalic(QFont::Cursive);
      cursor.mergeCharFormat( fmt );
}

void NotepadWindow::subrayar(){

    QTextCharFormat fmt;
    QTextCursor cursor = txtEditor_->textCursor();

    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if(!cursor.charFormat().fontUnderline() == QFont::UnderlineResolved)
        fmt.setFontUnderline(QFont::Normal);

    else
        fmt.setFontUnderline(QFont::UnderlineResolved);

        cursor.mergeCharFormat(fmt);

}


//txtEditor_->font() nos devuelve la fuente que hay ahora mismo en el txtEditor_
