/*
    Autor: Adrián Rodríguez Bazaga
    Aplicación: Bloc de notas
    Correo electrónico: alu0100826456@ull.edu.es
*/

#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    txtEditor_ = new QTextEdit(this);
    txtEditor_->setFont (QFont("Abyssinica SIL", 8));

    acerca_de_ = new QMessageBox();
    acerca_de_->setText("Información acerca de la aplicación:");
    acerca_de_->setInformativeText("\nAplicación desarrollada por:\nAdrián Rodríguez Bazaga\n\nCorreo electrónico:\nalu0100826456@ull.edu.es");
    acerca_de_->setWindowTitle("Ayuda: Acerca de...");
    acerca_de_->setMinimumSize(400, 300); // No hace efecto ¿Bug?
    acerca_de_->setWindowFlags(Qt::FramelessWindowHint);
    acerca_de_->setStandardButtons(QMessageBox::Ok);

    setCentralWidget(txtEditor_);

    // Barra de herramientas

    toolbar = new QToolBar("Barra de herramientas", this);
    toolbar->setMovable(false);

    //Archivo
    bhArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    bhArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    bhArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    bhArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    bhArchivoSalir_ = new QAction(tr("&Salir"), this);
    bhArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));

    QToolButton *botonArchivo=new QToolButton(this);
       botonArchivo->setText("Archivo");
       botonArchivo->setPopupMode(QToolButton::InstantPopup);
       QMenu *menuArchivo=new QMenu(botonArchivo);
       menuArchivo->addAction(bhArchivoAbrir_);
       menuArchivo->addAction(bhArchivoGuardar_);
       menuArchivo->addAction(bhArchivoSalir_);
       botonArchivo->setMenu(menuArchivo);
       toolbar->addWidget(botonArchivo);
    //
    //Edición
    bhEdicionLimpiar_ = new QAction(tr("&Limpiar"), this);
    bhEdicionLimpiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    bhEdicionCortar_ = new QAction(tr("&Cortar"), this);
    bhEdicionCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    bhEdicionDeshacer_ = new QAction(tr("&Deshacer"), this);
    bhEdicionDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    bhEdicionRehacer_ = new QAction(tr("&Rehacer"), this);
    bhEdicionRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    QToolButton *botonEdicion=new QToolButton(this);
       botonEdicion->setText("Edición");
       botonEdicion->setPopupMode(QToolButton::InstantPopup);
       QMenu *menuEdicion=new QMenu(botonEdicion);
       menuEdicion->addAction(bhEdicionLimpiar_);
       menuEdicion->addAction(bhEdicionCortar_);
       menuEdicion->addAction(bhEdicionDeshacer_);
       menuEdicion->addAction(bhEdicionRehacer_);
       botonEdicion->setMenu(menuEdicion);
       toolbar->addWidget(botonEdicion);
    //
    //Ayuda
    bhAyudaAD_ = new QAction(tr("&Acerca de"), this);
    bhAyudaAD_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));

    QToolButton *botonAyuda=new QToolButton(this);
       botonAyuda->setText("Ayuda");
       botonAyuda->setPopupMode(QToolButton::InstantPopup);
       QMenu *menuAyuda=new QMenu(botonAyuda);
       menuAyuda->addAction(bhAyudaAD_);
       botonAyuda->setMenu(menuAyuda);
       toolbar->addWidget(botonAyuda);
       toolbar->addSeparator();
    //
    //Negrita, cursiva y subrayado
    QToolButton *botonNegrita=new QToolButton(this);
       botonNegrita->setIcon(QIcon("img/Negrita.png"));
       botonNegrita->setPopupMode(QToolButton::InstantPopup);
       botonNegrita->setToolButtonStyle(Qt::ToolButtonIconOnly);
       toolbar->addWidget(botonNegrita);

    QToolButton *botonCursiva=new QToolButton(this);
       botonCursiva->setIcon(QIcon("img/Cursiva.png"));
       botonCursiva->setPopupMode(QToolButton::InstantPopup);
       botonCursiva->setToolButtonStyle(Qt::ToolButtonIconOnly);
       toolbar->addWidget(botonCursiva);

    QToolButton *botonSubrayado=new QToolButton(this);
       botonSubrayado->setIcon(QIcon("img/Subrayado.png"));
       botonSubrayado->setPopupMode(QToolButton::InstantPopup);
       botonSubrayado->setToolButtonStyle(Qt::ToolButtonIconOnly);
       toolbar->addWidget(botonSubrayado);
       toolbar->addSeparator();

    //
    //Selector de color (unos cuantos por defecto)
    selector_col=new QComboBox();
    selector_col->addItem("Negro");
    selector_col->addItem("Rojo");
    selector_col->addItem("Azul");
    selector_col->addItem("Verde");
    selector_col->addItem("Amarillo");
    selector_col->addItem("Naranja");
    toolbar->addWidget(selector_col);
    //
    //Selector de fuente
    selector=new QComboBox();
    QStringList fuentes = QFontDatabase().families();
    for(int i=0; i<fuentes.size(); i++)
    {
        selector->addItem(QString(fuentes.at(i)));
    }
    toolbar->addWidget(selector);
    //
    //Selector de tamaño
    selector_tam=new QComboBox();
    for(int i=8; i!=50; i+=2)
    {
        selector_tam->addItem(QString::number(i));
    }
    toolbar->addWidget(selector_tam);
    //


    QMainWindow::addToolBar(Qt::TopToolBarArea, toolbar);

    //Conexiones barra de herramintas
    connect(bhArchivoAbrir_,   SIGNAL(triggered()), this, SLOT(alAbrir()));
    connect(bhArchivoGuardar_, SIGNAL(triggered()), this, SLOT(alGuardar()));
    connect(bhArchivoSalir_, SIGNAL(triggered()), this, SLOT(alSalir()));
    connect(bhEdicionLimpiar_, SIGNAL(triggered()), this, SLOT(alLimpiar()));
    connect(bhEdicionCortar_, SIGNAL(triggered()), this, SLOT(alCortar()));
    connect(bhEdicionDeshacer_, SIGNAL(triggered()), this, SLOT(alDeshacer()));
    connect(bhEdicionRehacer_, SIGNAL(triggered()), this, SLOT(alRehacer()));
    connect(bhAyudaAD_, SIGNAL(triggered()), this, SLOT(alAcercaDe()));
    connect(selector, SIGNAL(activated(int)),this, SLOT(alCambiarFuente()));
    connect(selector_tam, SIGNAL(activated(int)),this, SLOT(alCambiarTam()));
    connect(selector_col, SIGNAL(activated(int)),this, SLOT(alCambiarColor()));
    connect(botonNegrita, SIGNAL(clicked()),this, SLOT(alPonerNegrita()));
    connect(botonCursiva, SIGNAL(clicked()),this, SLOT(alPonerCursiva()));
    connect(botonSubrayado, SIGNAL(clicked()),this, SLOT(alPonerSubrayado()));
    //

    // Fin barra de herramientas
}

NotepadWindow::~NotepadWindow()
{

}

void NotepadWindow::alAbrir() {
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt);;Archivos de texto enriquecido HTML (*.html)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->clear();
            txtEditor_->insertHtml(archivo.readAll());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alGuardar() {
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt);;Archivos de texto enriquecido HTML (*.html)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        if(!nombreArchivo.contains(".txt") && !nombreArchivo.contains(".html"))
        {
            archivo.setFileName(nombreArchivo+".txt");
        }
        else
        {
            archivo.setFileName(nombreArchivo);
        }
        QImage img(":/new/prefix1/video-x-generic.png"); // ???
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toHtml().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alSalir() {
    QApplication::quit();
}

void NotepadWindow::alLimpiar() {
    txtEditor_->clear();
}

void NotepadWindow::alCortar() {
    txtEditor_->cut();
}

void NotepadWindow::alDeshacer() {
    txtEditor_->undo();
}

void NotepadWindow::alRehacer() {
    txtEditor_->redo();
}

void NotepadWindow::alAcercaDe() {
    acerca_de_->show();
}

void NotepadWindow::alCambiarFuente() {
    QTextCharFormat formato;

    QTextCursor cursor = txtEditor_->textCursor();

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    formato.setFont(QFont (selector->currentText()));

    cursor.mergeCharFormat(formato);

    txtEditor_->mergeCurrentCharFormat(formato);
}

void NotepadWindow::alCambiarTam() {
    QTextCharFormat formato;

    QTextCursor cursor = txtEditor_->textCursor();

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    formato.setFont (QFont (selector->currentText(), selector_tam->currentText().toInt()));

    cursor.mergeCharFormat(formato);

    txtEditor_->mergeCurrentCharFormat(formato);
}

void NotepadWindow::alCambiarColor() {
    QTextCharFormat formato;

    QTextCursor cursor = txtEditor_->textCursor();

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    //Examinamos que color es el elegido
    if(selector_col->currentText() == "Rojo")
    {
        formato.setForeground(Qt::red);
    }
    if(selector_col->currentText() == "Azul")
    {
        formato.setForeground(Qt::blue);
    }
    if(selector_col->currentText() == "Verde")
    {
        formato.setForeground(Qt::green);
    }
    if(selector_col->currentText() == "Amarillo")
    {
        formato.setForeground(Qt::yellow);
    }
    if(selector_col->currentText() == "Naranja")
    {
        formato.setForeground(QColor(255,165,0));
    }
    if(selector_col->currentText() == "Negro")
    {
        formato.setForeground(Qt::black);
    }
    //

    cursor.mergeCharFormat(formato);

    txtEditor_->mergeCurrentCharFormat(formato);
}

void NotepadWindow::alPonerNegrita() {
    QTextCharFormat formato;

    QTextCursor cursor = txtEditor_->textCursor();

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if(cursor.charFormat().fontWeight() == QFont::Bold)
        formato.setFontWeight(QFont::Normal);
    else
    {
        formato.setFontWeight(QFont::Bold);
    }

    cursor.mergeCharFormat(formato);

    txtEditor_->mergeCurrentCharFormat(formato);
}

void NotepadWindow::alPonerCursiva() {
    QTextCharFormat formato;

    QTextCursor cursor = txtEditor_->textCursor();

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if(cursor.charFormat().fontItalic() == true)
        formato.setFontItalic(false);
    else
    {
        formato.setFontItalic(true);
    }

    cursor.mergeCharFormat(formato);

    txtEditor_->mergeCurrentCharFormat(formato);
}

void NotepadWindow::alPonerSubrayado() {
    QTextCharFormat formato;

    QTextCursor cursor = txtEditor_->textCursor();

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if(cursor.charFormat().fontUnderline() == true)
        formato.setFontUnderline(false);
    else
    {
        formato.setFontUnderline(true);
    }

    cursor.mergeCharFormat(formato);

    txtEditor_->mergeCurrentCharFormat(formato);
}



