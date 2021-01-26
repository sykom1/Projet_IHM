#include "chosecolor.h"
#include "ui_chosecolor.h"
#include "formsandcrop.h"
#include "drawcolormenu.h"
#include <QMouseEvent>
#include <QPainter>
#include <QtWidgets>
bool choseColor::isOpen;

choseColor::choseColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choseColor)
{


    ui->setupUi(this);
    createColorMenu();
    runEvents();
    QMainWindow w;
    this->setFixedSize(w.width()*.3,w.height()*0.3);



}

choseColor::~choseColor()
{
    delete ui;
}


void choseColor::createColorMenu()
{


    QGridLayout *layout = new QGridLayout;

    m_button = new QPushButton("Confirmer",this );
    m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    layout->addWidget(m_button);

    //this->layout()->addItem(conect_box);
    //setLayout(conect_box);

    QItemEditorFactory *factory = new QItemEditorFactory;

    QItemEditorCreatorBase *colorListCreator =
        new QStandardItemEditorCreator<drawColorMenu>();

    drawColorMenu *test;

    factory->registerEditor(QMetaType::QColor, colorListCreator);

    QItemEditorFactory::setDefaultFactory(factory);



    QColor *colorname = new QColor("Black");
    QTableWidget *table = new QTableWidget(1, 1);



    table->setHorizontalHeaderLabels({  tr("Color") });
    table->verticalHeader()->setVisible(true);
    table->setColumnWidth(0,table->columnWidth(0)+50);
    table->resize(table->columnWidth(0), 50);

    QTableWidgetItem *colorItem = new QTableWidgetItem;
    colorItem->setData(Qt::DisplayRole, *colorname);

    table->setItem(0, 0, colorItem);



    layout->addWidget(table);

    setLayout(layout);


}

void choseColor::runEvents(){

    connect(m_button, &QPushButton::clicked, this,[this]{handleButton();});

}


void choseColor::handleButton()
{
    color = drawColorMenu().colorStat.name();
    isOpen = false;
    close();


}
void choseColor::closeEvent(QCloseEvent *event)
{

    isOpen = false;
    QWidget::closeEvent(event);
}




