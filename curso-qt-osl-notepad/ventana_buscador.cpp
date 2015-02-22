#include "ventana_buscador.hpp"
#include "ui_ventana_buscador.h"

ventana_buscador::ventana_buscador(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ventana_buscador)
{
  ui->setupUi(this);
  ui->webView->load(QUrl("https://plus.google.com/u/0/115199172449707867537/posts"));

}

ventana_buscador::~ventana_buscador()
{
  delete ui;
}
