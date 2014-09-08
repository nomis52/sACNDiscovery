#include "mainwindow.h"

#include <QDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(OLAWorker *worker, QWidget *parent)
    : QMainWindow(parent),
      worker_(worker),
      ui(new Ui::MainWindow),
      timer_(this) {
  ui->setupUi(this);
  ui->sourceTreeView->setModel(&model_);

  QObject::connect(
      worker,
      SIGNAL(E131SourceList(const QVector<E131Source>&)),
      this,
      SLOT(E131SourceList(const QVector<E131Source>&)),
      Qt::BlockingQueuedConnection);
  connect(&timer_, SIGNAL(timeout()), this, SLOT(RefreshSourceList()));
  timer_.start(1000);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::E131SourceList(const QVector<E131Source> &sources) {
  model_.UpdateModel(sources);
}

void MainWindow::RefreshSourceList() {
  worker_->RefreshDiscoveredE131Sources();
  ui->sourceTreeView->resizeColumnToContents(0);
}
