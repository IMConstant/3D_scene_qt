#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>

#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QListWidget>
#include <QModelIndex>
#include <QAbstractItemModel>

#include <QLineEdit>
#include <QLabel>

#include "scenewidget.h"


namespace Ui {
class MainWindow;
}


enum SceneItemDataRole {
    FullDisplayRole = Qt::UserRole
};


class SceneDataModel : public QAbstractItemModel {
    Q_OBJECT

public:
    SceneDataModel(QObject *parent);
    virtual ~SceneDataModel();

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    void add(const SceneObjectData &data);
    void add(const QVector<SceneObjectData> &other);

private:
    QVector<SceneObjectData> *m_data;
};




class SceneObjectInfoWidget : public QWidget {
    Q_OBJECT

public:
    SceneObjectInfoWidget(QWidget *parent = nullptr);
    virtual ~SceneObjectInfoWidget();


signals:
    void objectStateChanged(QModelIndex index, SceneObjectData data);

public slots:
    void updateInfo(QModelIndex index);
    void saveButtonClicked();

private:
    QModelIndex modelIndex;
    SceneObjectData objectData;

    QVBoxLayout *m_mainLayout;
    QFormLayout *m_formLayout;

    QLabel *m_objectNameLabel;
    QLabel *m_objectTypeLabel;

    QLabel *m_errorLabel;

    QCheckBox *m_lightEnabledCheckBox;

    QLineEdit *m_xLineEdit;
    QLineEdit *m_yLineEdit;
    QLineEdit *m_zLineEdit;

    QLineEdit *m_dLineEdit;
    QLineEdit *m_sLineEdit;
    QLineEdit *m_aLineEdit;

    QPushButton *m_saveButton;
};



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setPerspectiveProjection();
    void setOrthogonalProjection();
    void shadersCheckBoxStateChanged(int value);
    void styleCheckBoxStateChanged(int value);
    void glInitializeHandler();

    void updateObject(QModelIndex index, SceneObjectData data);


private:
    Ui::MainWindow *ui;

    SceneObjectInfoWidget *m_sceneObjectInfoWidget;
    SceneDataModel *m_model;

    QRadioButton *m_perspectiveRadioButton;
    QRadioButton *m_orthogonalRadioButton;

    QCheckBox   *m_shadersCheckBox;
    QCheckBox   *m_styleCheckBox;

    SceneWidget *m_sceneWidget;
    QWidget     *m_centralWidget;

    QListView *m_listView;

    QHBoxLayout *m_lineLayout;
    QVBoxLayout *m_optionsLayout;
    QVBoxLayout *m_projectionLayout;
    QVBoxLayout *m_buttonLayout;
};

#endif // MAINWINDOW_H
