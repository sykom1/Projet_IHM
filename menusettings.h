#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QComboBox>
#include <QLabel>

class MenuSettings : public QWidget
{
    Q_OBJECT
public:
    explicit MenuSettings(QStringList langues, QWidget *parent = nullptr);


private:
    QVBoxLayout *layoutSettings = nullptr;
    QTabWidget *tabWidget = nullptr;
    QWidget *tabGeneral = new QWidget();
    QWidget *tabShortcut = nullptr;
    QStringList langues;
    QLabel *labelLangue = new QLabel();
    QComboBox *langueChoice = new QComboBox;
    QVBoxLayout *layoutGeneral = new QVBoxLayout();

    void initAllTab();
    void initTabGeneral();
    void initTabShortcut();
    void setAllText();

};

#endif // MENUSETTINGS_H
