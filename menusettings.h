#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <iostream>

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
    QComboBox *langueChoice = nullptr;
    QVBoxLayout *layoutGeneral = new QVBoxLayout();

    QHBoxLayout *layoutButton = nullptr;
    QPushButton *buttonApply = nullptr;
    QPushButton *buttonQuit = nullptr;

    void initAllTab();
    void initTabGeneral();
    void initTabShortcut();
    void setAllText();

    void createConnection();

};

#endif // MENUSETTINGS_H
