#include "mainwindow.h"
#include "ui_mainwindow.h"



SceneDataModel::SceneDataModel(QObject *parent) :
    QAbstractItemModel(parent), m_data(new QVector<SceneObjectData>()) {

}

SceneDataModel::~SceneDataModel() {
    delete m_data;
}

int SceneDataModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

int SceneDataModel::rowCount(const QModelIndex &parent) const {
    return m_data->size();
}

QVariant SceneDataModel::data(const QModelIndex &index, int role) const {
    switch (role) {
        case Qt::DisplayRole:
            return m_data->at(index.row()).name;
        case FullDisplayRole:
            return QVariant::fromValue(m_data->at(index.row()));
    }

    return QVariant();
}

bool SceneDataModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    m_data->replace(index.row(), value.value<SceneObjectData>());

    return true;
}

QModelIndex SceneDataModel::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column, (void *)(&m_data[row]));
}

QModelIndex SceneDataModel::parent(const QModelIndex &index) const {
    return QModelIndex();
}

void SceneDataModel::add(const SceneObjectData &data) {
    m_data->append(data);

    emit layoutChanged();
}

void SceneDataModel::add(const QVector<SceneObjectData> &other) {
    for (auto &item: other) {
        m_data->append(item);
    }

    emit layoutChanged();
}


SceneObjectInfoWidget::SceneObjectInfoWidget(QWidget * parent) :
    QWidget(parent) {
    m_mainLayout = new QVBoxLayout;
    m_formLayout = new QFormLayout;

    m_objectNameLabel = new QLabel("Light0");
    m_objectTypeLabel = new QLabel("light");

    m_xLineEdit = new QLineEdit(this);
    m_xLineEdit->setReadOnly(false);
    m_yLineEdit = new QLineEdit(this);
    m_yLineEdit->setReadOnly(false);
    m_zLineEdit = new QLineEdit(this);
    m_zLineEdit->setReadOnly(false);
    m_dLineEdit = new QLineEdit(this);
    m_dLineEdit->setReadOnly(false);
    m_sLineEdit = new QLineEdit(this);
    m_sLineEdit->setReadOnly(false);
    m_aLineEdit = new QLineEdit(this);
    m_aLineEdit->setReadOnly(false);

    m_lightEnabledCheckBox = new QCheckBox(this);

    m_errorLabel = new QLabel(this);
    m_errorLabel->setStyleSheet(QString("color: red;"));
    m_errorLabel->setVisible(false);

    m_saveButton = new QPushButton("Save", this);

    connect(m_saveButton, SIGNAL(clicked(bool)), this, SLOT(saveButtonClicked()));

    m_formLayout->addRow(QString("name:"), m_objectNameLabel);
    m_formLayout->addRow(QString("type:"), m_objectTypeLabel);
    m_formLayout->addRow(QString("enabled:"), m_lightEnabledCheckBox);
    m_formLayout->addRow(QString("x:"), m_xLineEdit);
    m_formLayout->addRow(QString("y:"), m_yLineEdit);
    m_formLayout->addRow(QString("z:"), m_zLineEdit);
    m_formLayout->addRow(QString("dif:"), m_dLineEdit);
    m_formLayout->addRow(QString("spec:"), m_sLineEdit);
    m_formLayout->addRow(QString("amb:"), m_aLineEdit);

    m_mainLayout->addWidget(m_saveButton);
    m_mainLayout->addLayout(m_formLayout, 1);
    m_mainLayout->addWidget(m_errorLabel);

    setLayout(m_mainLayout);
}

SceneObjectInfoWidget::~SceneObjectInfoWidget() {
    delete m_xLineEdit;
    delete m_yLineEdit;
    delete m_zLineEdit;

    delete m_dLineEdit;
    delete m_sLineEdit;
    delete m_aLineEdit;
}

void SceneObjectInfoWidget::updateInfo(QModelIndex index) {
    SceneObjectData object = index.data(FullDisplayRole).value<SceneObjectData>();

    modelIndex = index;
    objectData = object;

    m_objectNameLabel->setText(object.name);
    m_objectTypeLabel->setText(object.type);
    m_lightEnabledCheckBox->setChecked(object.enabled);

    m_xLineEdit->setText(QString::number(object.position.x()));
    m_yLineEdit->setText(QString::number(object.position.y()));
    m_zLineEdit->setText(QString::number(object.position.z()));

    m_dLineEdit->setText(QString::number(object.components.x()));
    m_sLineEdit->setText(QString::number(object.components.y()));
    m_aLineEdit->setText(QString::number(object.components.z()));
}

void SceneObjectInfoWidget::saveButtonClicked() {
    bool dOk = true;
    bool sOk = true;
    bool aOk = true;
    bool xOk = true;
    bool yOk = true;
    bool zOk = true;

    float d = m_dLineEdit->text().toFloat(&dOk);
    float s = m_sLineEdit->text().toFloat(&sOk);
    float a = m_aLineEdit->text().toFloat(&aOk);
    float x = m_xLineEdit->text().toFloat(&xOk);
    float y = m_yLineEdit->text().toFloat(&yOk);
    float z = m_zLineEdit->text().toFloat(&zOk);

    bool coordsOk = xOk && yOk && zOk;
    bool componentsOk = dOk && sOk && aOk;

    QString errString;

    if (!coordsOk) {
        errString += "***Incorrect coordinates***\n";
    }

    if (!componentsOk) {
        errString += "***Incorrect components***\n";
    }

    if (coordsOk && componentsOk) {
        m_errorLabel->setVisible(false);

        emit objectStateChanged(modelIndex, SceneObjectData(objectData.name,
                                                            objectData.type,
                                                            m_lightEnabledCheckBox->isChecked(),
                                                            QVector3D(x, y, z),
                                                            QVector3D(d, s, a)));
    }
    else {
        m_errorLabel->setText(errString.trimmed());
        m_errorLabel->setVisible(true);
    }
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->ui->mainToolBar->setVisible(false);
    this->setGeometry(QRect(20, 20, 1200, 700));

    m_centralWidget = new QWidget();
    setCentralWidget(m_centralWidget);

    m_sceneWidget = new SceneWidget(this);
    m_sceneWidget->setFocusPolicy(Qt::StrongFocus);
    m_sceneWidget->setGeometry(QRect(0, ui->mainToolBar->geometry().height(), 800, 600));
    m_sceneWidget->setMinimumSize(800, 600);

    connect(m_sceneWidget, SIGNAL(glInitialized()), this, SLOT(glInitializeHandler()));

    m_sceneObjectInfoWidget = new SceneObjectInfoWidget(this);

    connect(m_sceneObjectInfoWidget, SIGNAL(objectStateChanged(QModelIndex,SceneObjectData)),
            this, SLOT(updateObject(QModelIndex,SceneObjectData)));

    m_model = new SceneDataModel(this);

    m_listView = new QListView(this);
    m_listView->setModel(m_model);
    m_listView->setMinimumWidth(50);
    m_listView->setMaximumWidth(100);

    connect(m_listView, SIGNAL(clicked(QModelIndex)),
            m_sceneObjectInfoWidget, SLOT(updateInfo(QModelIndex)));


    m_perspectiveRadioButton = new QRadioButton("Perspective", this);
    m_orthogonalRadioButton  = new QRadioButton("Orthogonal", this);

    connect(m_perspectiveRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(setPerspectiveProjection()));
    connect(m_orthogonalRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(setOrthogonalProjection()));

    m_shadersCheckBox = new QCheckBox("shaders", this);
    m_styleCheckBox = new QCheckBox("dark", this);

    connect(m_shadersCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(shadersCheckBoxStateChanged(int)));

    connect(m_styleCheckBox, SIGNAL(stateChanged(int)),
            this, SLOT(styleCheckBoxStateChanged(int)));

    m_projectionLayout = new QVBoxLayout;
    m_projectionLayout->addWidget(m_styleCheckBox);
    m_projectionLayout->addWidget(m_shadersCheckBox);
    m_projectionLayout->addWidget(m_perspectiveRadioButton);
    m_projectionLayout->addWidget(m_orthogonalRadioButton);

    auto *objectInfoLayout = new QHBoxLayout;
    objectInfoLayout->addWidget(m_listView);
    objectInfoLayout->addWidget(m_sceneObjectInfoWidget, 1);

    m_optionsLayout = new QVBoxLayout;
    m_optionsLayout->addLayout(m_projectionLayout, 1);
    m_optionsLayout->addLayout(objectInfoLayout, 0);

    m_lineLayout = new QHBoxLayout;
    m_lineLayout->addLayout(m_optionsLayout);
    m_lineLayout->addWidget(m_sceneWidget, 1);

    m_centralWidget->setLayout(m_lineLayout);
}

void MainWindow::setPerspectiveProjection() {
    m_sceneWidget->setProjection(gl::Perspective);
}

void MainWindow::setOrthogonalProjection() {
    m_sceneWidget->setProjection(gl::Orthogonal);
}

void MainWindow::shadersCheckBoxStateChanged(int value) {
    m_sceneWidget->useShaders(static_cast<bool>(value));
}

void MainWindow::styleCheckBoxStateChanged(int value) {
    bool dark = static_cast<bool>(value);

    m_sceneWidget->setDark(dark);

    if (dark) {
        m_centralWidget->setStyleSheet(QString("background-color: #444444; color: white"));
    }
    else {
        m_centralWidget->setStyleSheet(QString("background-color: white; color: black"));
    }

}

void MainWindow::updateObject(QModelIndex index, SceneObjectData data) {
    m_model->setData(index, QVariant::fromValue<SceneObjectData>(data));
    m_sceneWidget->updateLight(data);
}

void MainWindow::glInitializeHandler() {
    m_model->add(m_sceneWidget->getLight());
}

MainWindow::~MainWindow()
{
    delete ui;
}
