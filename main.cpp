#include <QApplication>
#include <QThread>

#include "mainwindow.h"
#include "olaworker.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QThread *thread = new QThread;
  OLAWorker *worker = new OLAWorker();

  if (!worker->Init()) {
    return -1;
  }

  worker->moveToThread(thread);
  QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
  QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
  QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
  QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

  MainWindow w(worker);
  thread->start();
  w.show();

  return a.exec();
}
