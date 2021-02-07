#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include <QEvent>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <iostream>

class MenuSettings : public QWidget
{
    Q_OBJECT
public:
    explicit MenuSettings(QStringList langues, QTranslator *translator, QWidget *parent = nullptr);


private:
    QSettings *settings = nullptr;

    QTranslator *translator = nullptr;
    QVBoxLayout *layoutSettings = nullptr;
    QTabWidget *tabWidget = new QTabWidget();
    QWidget *tabGeneral = new QWidget();
    QWidget *tabShortcut = new QWidget();
    QStringList languesDisplay;
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
    void changeLanguage();

    void createConnection();
    void undoLanguage();
    void changeEvent(QEvent *event) override;
    bool verifyLanguage();
    void verifyClose();
    void applyConfig();
};

#endif // MENUSETTINGS_H
