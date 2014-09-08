#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QTimer>
#include "olaworker.h"
#include "treemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(OLAWorker *worker, QWidget *parent = 0);
  ~MainWindow();

 public slots:
  void E131SourceList(const QVector<E131Source> &sources);
  void RefreshSourceList();

 private:
  OLAWorker *worker_;
  Ui::MainWindow *ui;
  TreeModel model_;
  QTimer timer_;
};

#endif  // MAINWINDOW_H_
