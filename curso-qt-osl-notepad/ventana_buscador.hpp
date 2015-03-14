#ifndef VENTANA_BUSCADOR_HPP
#define VENTANA_BUSCADOR_HPP

#include <QMainWindow>
#include <QWebView>

namespace Ui {
  class ventana_buscador;
}

class ventana_buscador : public QMainWindow
{
  Q_OBJECT

public:
  explicit ventana_buscador(QWidget *parent = 0);
  ~ventana_buscador();

private:
  Ui::ventana_buscador *ui;
};

#endif // VENTANA_BUSCADOR_HPP
