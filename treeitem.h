#ifndef TREEITEM_H_
#define TREEITEM_H_

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "olaworker.h"

class TreeItemInterface {
 public:
  virtual ~TreeItemInterface() {}

  virtual TreeItemInterface *parent() = 0;

  virtual int childCount() const = 0;
  virtual TreeItemInterface *child(int row) = 0;

  virtual int columnCount() const = 0;
  virtual QVariant data(int column) const = 0;
  virtual int row() const = 0;

  static const int kColumnCount;
};

class SourceTreeItem;
class UniverseTreeItem;

class RootTreeItem : public TreeItemInterface {
 public:
  ~RootTreeItem();

  TreeItemInterface* parent() { return NULL; }

  void reset();

  int childCount() const;
  TreeItemInterface *child(int row);

  int columnCount() const { return kColumnCount; }
  QVariant data(int column) const;
  int row() const;

  int indexOf(const SourceTreeItem *item) const;

  void insert(int i, SourceTreeItem *child);
  void appendChild(SourceTreeItem *child);

  SourceTreeItem *sourceAt(int i);
  void Remove(int i);

 private:
  QList<SourceTreeItem*> children_;
};

class SourceTreeItem : public TreeItemInterface {
 public:
  SourceTreeItem(const E131Source &data, RootTreeItem *parent);
  ~SourceTreeItem();

  TreeItemInterface* parent() { return parent_; }

  int childCount() const;
  TreeItemInterface *child(int row);

  int columnCount() const;
  QVariant data(int column) const;
  int row() const;

  int indexOf(const UniverseTreeItem *item) const;

  void insert(int i, UniverseTreeItem *child);
  void appendChild(UniverseTreeItem *child);

  void Update(const E131Source &entry);

  ola::acn::CID cid() const { return source_.cid; }

  UniverseTreeItem *universeAt(int i);
  void Remove(int i);

 private:
  RootTreeItem *parent_;
  E131Source source_;
  QVariant row_data_;
  QList<UniverseTreeItem*> children_;
};

class UniverseTreeItem : public TreeItemInterface {
 public:
  UniverseTreeItem(uint16_t universe, SourceTreeItem *parent);

  TreeItemInterface* parent() { return parent_; }

  int childCount() const { return 0; }
  TreeItemInterface *child(int row) { return NULL; }

  int columnCount() const { return kColumnCount; }
  QVariant data(int column) const;
  int row() const;

  uint16_t universe() const { return universe_id_; }

 private:
  SourceTreeItem *parent_;
  uint16_t universe_id_;
  QString universe_;
};

#endif  // TREEITEM_H_
