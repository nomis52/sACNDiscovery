#include "treemodel.h"

#include <QtGui>
#include <vector>

#include "treeitem.h"

using std::vector;

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent),
      root_(new RootTreeItem()) {
}

TreeModel::~TreeModel() {
  delete root_;
}

int TreeModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return static_cast<TreeItemInterface*>(parent.internalPointer())
        ->columnCount();
  } else {
    return root_->columnCount();
  }
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  TreeItemInterface *item = static_cast<TreeItemInterface*>(
      index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return 0;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section,
                               Qt::Orientation orientation,
                               int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
     return root_->data(section);

  return QVariant();
}

QModelIndex TreeModel::index(int row,
                             int column,
                             const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  TreeItemInterface *parentItem;

  if (!parent.isValid()) {
    parentItem = root_;
  } else {
    parentItem = static_cast<TreeItemInterface*>(parent.internalPointer());
  }

  TreeItemInterface *childItem = parentItem->child(row);
  if (childItem) {
    return createIndex(row, column, childItem);
  } else {
    return QModelIndex();
  }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  TreeItemInterface *item = static_cast<TreeItemInterface*>(
      index.internalPointer());
  TreeItemInterface *parent = item->parent();

  if (parent == root_) {
    return QModelIndex();
  }

  return createIndex(parent->row(), 0, parent);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
  TreeItemInterface *parentItem;
  if (parent.column() > 0) {
    return 0;
  }

  if (!parent.isValid()) {
    parentItem = root_;
  } else {
    parentItem = static_cast<TreeItemInterface*>(parent.internalPointer());
  }

  return parentItem->childCount();
}

void TreeModel::UpdateModel(const QVector<E131Source> &sources) {
  int i = 0;  // index into sources.
  int j = 0;  // index into root_'s children

  while (i != sources.size() && j != root_->childCount()) {
    const E131Source &source = sources[i];
    SourceTreeItem *item = root_->sourceAt(j);

    if (source.cid < item->cid()) {
      beginInsertRows(QModelIndex(), j, j + 1);
      SourceTreeItem *item = new SourceTreeItem(source, root_);
      root_->insert(j, item);
      UpdateSource(source, item, index(j, 0));
      endInsertRows();
      i++;
      j++;
    } else if (source.cid == item->cid()) {
      // Update Item in case IP / name has changed.
      UpdateSource(source, item, index(j, 0));
      item->Update(source);
      i++;
      j++;
    } else {
      // source.cid > item->cid()
      beginRemoveRows(QModelIndex(), j, j + 1);
      root_->Remove(j);
      endRemoveRows();
    }
  }

  // Remove any old entries.
  if (j != root_->childCount()) {
    beginRemoveRows(QModelIndex(), j, root_->childCount());
    while (j < root_->childCount()) {
      root_->Remove(j);
    }
    endRemoveRows();
  }

  // Add the remaining new entries
  if (i != sources.size()) {
    beginInsertRows(QModelIndex(),
                    root_->childCount() + i,
                    root_->childCount() + sources.size());
    while (i != sources.size()) {
      SourceTreeItem *item = new SourceTreeItem(sources[i], root_);
      root_->appendChild(item);
      UpdateSource(sources[i], item, index(root_->childCount(), 0));
      i++;
    }
    endInsertRows();
  }
}

void TreeModel::UpdateSource(const E131Source &source, SourceTreeItem *item,
                             const QModelIndex &parent) {
  const vector<uint16_t> &universes = source.universes;

  int i = 0;  // index into universes.
  int j = 0;  // index into items's children

  while (i != universes.size() && j != item->childCount()) {
    uint16_t universe_id = universes[i];
    UniverseTreeItem *uni_item = item->universeAt(j);

    if (universe_id < uni_item->universe()) {
      beginInsertRows(parent, j, j + 1);
      item->insert(j, new UniverseTreeItem(universe_id, item));
      endInsertRows();
      i++;
      j++;
    } else if (universe_id == uni_item->universe()) {
      i++;
      j++;
    } else {
      beginRemoveRows(parent, j, j + 1);
      item->Remove(j);
      endRemoveRows();
    }
  }

  if (j != item->childCount()) {
    beginRemoveRows(parent, j, item->childCount());
    while (j < item->childCount()) {
      item->Remove(j);
    }
    endRemoveRows();
  }

  if (i != universes.size()) {
    beginInsertRows(parent,
                    item->childCount() + i,
                    item->childCount() + universes.size());
    while (i != universes.size()) {
      item->appendChild(new UniverseTreeItem(universes[i++], item));
    }
    endInsertRows();
  }
}
