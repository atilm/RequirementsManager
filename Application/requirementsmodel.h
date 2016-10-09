#ifndef REQUIREMENTSMODEL_H
#define REQUIREMENTSMODEL_H

#include <QAbstractItemModel>
#include "requirement.h"
#include "requirementfactory.h"
#include "filestatetracker.h"
#include "attributecontext.h"
#include "requirementtomodelmapper.h"
#include <exception>

class InvalidModelIndexException : public std::exception{

};

/*! Editable tree data model for the requirements

  The class RequirementsModel extends the class QAbstractItemModel.
  It holds the root pointer to a tree structure and provides access
  and edit functions to it, which work together with the Qt view classes.
 */
class RequirementsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RequirementsModel(RequirementFactory *factory,
                               shared_ptr<FileStateTracker> fileState,
                               AttributeContext *attributeContext,
                               LinkContext *linkContext,
                               RequirementToModelMapper *dataMapper,
                               QObject *parent = 0);

    virtual ~RequirementsModel();

    virtual void init();
    virtual void clearModel();

    // required overriden functions
    virtual int columnCount(const QModelIndex & = QModelIndex()) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	 index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	 parent(const QModelIndex & index) const;

    // additional overriden functions
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    // functions needed for drag and drop
    Qt::DropActions supportedDropActions() const;

    // requirement-specific functions
    virtual uint getID(const QModelIndex &index);
    virtual void setType(const QModelIndex &index, Requirement::Type type);
    virtual Requirement::Type getType(const QModelIndex &index) const;
    virtual QModelIndex appendSibling(const QModelIndex &index);
    virtual QModelIndex appendChild(const QModelIndex &index, const QString &name = "",
                                    Requirement::Type type = Requirement::UserRequirement,
                                    uint requestedID = 0);

    /*! Insert a requirement before the given row under the given parent

     If beforeRow = -1, the item is appended to the end.
     */
    virtual QModelIndex insertChild(Requirement *newItem,
                                    const QModelIndex &parentIndex,
                                    int beforeRow);
    virtual bool removeRequirement(const QModelIndex &index);
    virtual void moveRequirement(const QModelIndex &source, const QModelIndex &destination);
    virtual Requirement* getRequirement(const QModelIndex &index) const;
    virtual QModelIndex createReferenceTo(const QModelIndex &index);

    virtual AttributeContext* getAttributeContext() const;
    virtual LinkContext* getLinkContext() const;
    virtual QTextDocument* getDescription(const QModelIndex &index);
    virtual shared_ptr<RiskAssessmentModel> getRiskAssessment(const QModelIndex &index);
    virtual LinkContainer* getLinkContainer(const QModelIndex &index);

signals:
    void columnsChanged();
    void requirementRemoved(unsigned int id);

public slots:

    void handleAttributeAboutToBeInserted(int index);
    void handleAttributeInserted();
    void handleAttributeAboutToBeRemoved(int index);
    void handleAttributeRemoved();
    void handleAttributeChanged(const QModelIndex &begin,
                                const QModelIndex &end);

private:
    RequirementFactory *factory;
    Requirement *root;
    AttributeContext *attributeContext;
    LinkContext *linkContext;
    shared_ptr<FileStateTracker> fileState;
    RequirementToModelMapper *dataMapper;

    void connectSignals();
    Requirement *asRequirement(const QModelIndex &index) const;
    Requirement *getValidItem(const QModelIndex &index) const;

private slots:
    void handleDescriptionChanged();
};

#endif // REQUIREMENTSMODEL_H
