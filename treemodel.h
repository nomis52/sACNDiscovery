#ifndef TREEMODEL_H_
#define TREEMODEL_H_

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "olaworker.h"
#include "treeitem.h"

class RootTreeItem;

class TreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit TreeModel(QObject *parent = 0);
  ~TreeModel();

  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const;

  QModelIndex parent(const QModelIndex &index) const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  void UpdateModel(const QVector<E131Source> &sources);

 private:
  RootTreeItem *root_;

  void UpdateSource(const E131Source &source,
                    SourceTreeItem *item,
                    const QModelIndex &parent);
};

#endif  // TREEMODEL_H_
