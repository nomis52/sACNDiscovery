#include "TreeItem.h"

#include <QDebug>
#include <QStringList>

const int TreeItemInterface::kColumnCount = 3;

// RootTreeItem
RootTreeItem::~RootTreeItem() {
  qDeleteAll(children_);
}

void RootTreeItem::reset() {
  qDeleteAll(children_);
  children_.clear();
}

int RootTreeItem::childCount() const {
  return children_.count();
}

TreeItemInterface *RootTreeItem::child(int row) {
  return children_.value(row);
}

QVariant RootTreeItem::data(int column) const {
  switch (column) {
    case 0:
      return "CID";
    case 1:
      return "IP";
    case 2:
      return "Source Name";
    default:
      return QVariant();
  }
}

SourceTreeItem *RootTreeItem::sourceAt(int i) {
  return children_.value(i);
}

void RootTreeItem::Remove(int i) {
  delete children_.value(i);
  children_.removeAt(i);
}

int RootTreeItem::indexOf(const SourceTreeItem *item) const {
  return children_.indexOf(const_cast<SourceTreeItem*>(item));
}

void RootTreeItem::insert(int i, SourceTreeItem *child) {
  children_.insert(i, child);
}

void RootTreeItem::appendChild(SourceTreeItem *child) {
  children_.append(child);
}

int RootTreeItem::row() const {
  return 0;
}

// SourceTreeItem
SourceTreeItem::SourceTreeItem(const E131Source &data, RootTreeItem *parent)
    : parent_(parent),
      source_(data),
      row_data_(data.cid.ToString().c_str()) {
  /*
  for (uint16_t universe : data.universes) {
    children_.append(new UniverseTreeItem(universe, this));
  }
  */
}

SourceTreeItem::~SourceTreeItem() {
  qDeleteAll(children_);
}

int SourceTreeItem::childCount() const {
  return children_.count();
}

TreeItemInterface *SourceTreeItem::child(int row) {
  return children_.value(row);
}

int SourceTreeItem::columnCount() const {
  return kColumnCount;
}

QVariant SourceTreeItem::data(int column) const {
  switch (column) {
    case 0:
      return row_data_;
    case 1:
      return source_.ip_address.ToString().c_str();
    case 2:
      return source_.source_name.c_str();
    default:
      return QVariant();
  }
}

int SourceTreeItem::row() const {
  if (parent_)
    return parent_->indexOf(this);

  return 0;
}

int SourceTreeItem::indexOf(const UniverseTreeItem *item) const {
  return children_.indexOf(const_cast<UniverseTreeItem*>(item));
}

void SourceTreeItem::insert(int i, UniverseTreeItem *child) {
  children_.insert(i, child);
}

void SourceTreeItem::appendChild(UniverseTreeItem *child) {
  children_.append(child);
}

void SourceTreeItem::Update(const E131Source &entry) {
  // TODO(simon): handle the ip / name changing here
  source_ = entry;

  // Perform the universe update
}

void SourceTreeItem::Remove(int i) {
  delete children_.value(i);
  children_.removeAt(i);
}

UniverseTreeItem *SourceTreeItem::universeAt(int i) {
  return children_.value(i);
}


// UniverseTreeItem
UniverseTreeItem::UniverseTreeItem(uint16_t universe, SourceTreeItem *parent)
  : parent_(parent),
    universe_id_(universe),
    universe_("Universe ") {
  universe_.append(QString::number(universe));
}

int UniverseTreeItem::row() const {
  return parent_ ? parent_->indexOf(this) : 0;
}

QVariant UniverseTreeItem::data(int column) const {
  return column == 0 ? universe_ : QVariant();
}
