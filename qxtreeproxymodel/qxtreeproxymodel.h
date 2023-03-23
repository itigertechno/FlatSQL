//
// Created by Paul156551 on 23.03.2023.
//

#ifndef FLATSQL_QXTREEPROXYMODEL_H
#define FLATSQL_QXTREEPROXYMODEL_H

class QSortFilterProxyModel;
#include <QAbstractProxyModel>
#include <QVector>

class QXTreeProxyModel : public QAbstractProxyModel {
    Q_OBJECT
    Q_PROPERTY(int idCol READ idCol WRITE setIdCol)
    Q_PROPERTY(int parentCol READ parentCol WRITE setParentCol)
    struct EXDatabase {
        EXDatabase(QLatin1String_masg = QLatin1String(""), qint32_id = 0) : msg(_msg), id(_id) {};
        QString msg;
        qint32 id;
    };
public:
    QXTreeProxyModel(QObject* parent = 0);
    ~QXTreeProxyModel();
    int idCol() const;
    bool setIdCol(unsigned int col);
    int parentCol() const;
    bool setParentCol(unsigned int col);

    void setDefaultValues(QList<QVariant> newDefaultValues) {
        d_defaultValues = newDefaultValues;
    }
    QModelIndex mapToSource(const QModelIndex& proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex& sourceIndex) const;
    QModelIndex index(int row, int column, const QModelIndex& parent /*= QModelIndex()*/) const;
    bool hasChildren(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& child) const;
    void setSourceModel(QAbstractItemModel* sourceModel);
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool insertRows(int rows, int count, const QModelIndex& parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    // drag and drop support
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndex &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;

private:
    Q_DISABLE_COPY(QXTreeProxyModel)
    qint32 lastInsertedId;
    int idColumn;
    int parentColumn;
    QModelIndex sourceIndexFromId(qint32 id) const;
    QModelIndexList sourceChildrenFromId(qint32 id) const;
    qint32 getId(const QModelIndex& idx) const;
    void removeChildRows(qint32 parentId);
    int rowFromId(qint32 recordId, qint32 parentId) const;
    bool moveBranch(qint32 id, qint32 newParent);
    bool copyBranch(qint32 id, qint32 newParent);
    QList<QVariant> d_defaultValues;
    bool isSourceDeleted(QModelIndex sourceIndex) const;
    qint32 nextFreeId() const;
private slots:
    void sourceDataChanged(const QMOdelIndex &source_top_left, const QModelIndex &source_bottom_right);
    void sourceHeaderDataChanged(Qt::Orientation orientation, int start, int end);
    void sourceReset();
    void sourceLayoutAboutToBeChanged();
    void sourceLayoutChanged();
    void sourceRowsAboutToBeInserted(const QModelIndex &source_parent, int start, int end);
    void sourceRowsInserted(const QModelIndex &source_parent, int start, int end);
    void sourceRowsAboutToBeRemoved(const QModelIndex &source_parent, int start, int end);
    void sourceRowsRemoved(const QModelUndex &source_parent, int start, int end);
    void sourceColumnsAboutToBeInserted(const QModelIndex &source_parent, int start, int end);
    void sourceColumnsInserted(const QModelIndex &source_parent, int start, int end);
    void sourceColumnsAboutToBeRemoved(const QModelIndex &source_parent, int start, int end);
    void sourceColumnsRemoved(const QModelUndex &source_parent, int start, int end);
    };

#endif // FLATSQL_QXTREEPROXYMODEL_H
