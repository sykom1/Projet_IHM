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
#include <QScrollArea>
#include <QScrollBar>
#include <QAction>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <iostream>

#define WIDTHLABELSHORTCUT 150

class MenuSettings : public QWidget
{
    Q_OBJECT
public:
    explicit MenuSettings(QStringList langues, QTranslator *translator,
                          QVector<QVector<QAction*>*> *listOfListQAction, QWidget *parent = nullptr);


private:
    QSettings *settings = nullptr;

    QVector<QVector<QAction*>*> *listOfListQAction = nullptr;

    QTranslator *translator = nullptr;
    QVBoxLayout *layoutSettings = nullptr;
    QTabWidget *tabWidget = new QTabWidget();
    QWidget *tabGeneral = new QWidget();
    QWidget *tabWindow = new QWidget;

    QLabel *lblInfoSizeWindow = new QLabel;
    QVBoxLayout *layoutWindow = new QVBoxLayout;
    QGroupBox *boxForSizeSettings = nullptr;
    QRadioButton *buttonForDefault = new QRadioButton;
    QRadioButton *buttonForMaximize = new QRadioButton;
    QRadioButton *buttonForFullscreen = new QRadioButton;
    QRadioButton *buttonForPersonalize = new QRadioButton;
    QVBoxLayout *layoutQRadioButton = nullptr;

    QGroupBox *boxForPersonalizationLength = nullptr;
    QLabel *lblForHeight = new QLabel;
    QLineEdit *editForHeight = nullptr;
    QLabel *lblForWidth = new QLabel;
    QLineEdit *editForWidth = nullptr;
    QVBoxLayout *layoutPersonalization = nullptr;

    QWidget *tabShortcut = new QWidget();
    QScrollArea *scrollAreaShortcut = new QScrollArea();
    QVBoxLayout *layoutShortcut = new QVBoxLayout;
    QWidget *widgetScroll = nullptr;
    QVBoxLayout *layoutScroll = nullptr;
    QStringList languesDisplay;
    QLabel *labelLangue = new QLabel();
    QComboBox *langueChoice = nullptr;
    QVBoxLayout *layoutGeneral = new QVBoxLayout();

    QHBoxLayout *layoutButton = nullptr;
    QPushButton *buttonApply = nullptr;
    QPushButton *buttonQuit = nullptr;

    void initAllTab();
    void initTabGeneral();
    void initTabWindow();
    void initTabShortcut();
    void setAllText();
    void changeLanguage();

    void createConnection();
    void undoLanguage();
    void changeEvent(QEvent *event) override;
    bool verifyLanguage();
    void verifyClose();
    void applyConfig();
    void loadShortcut(int indOfThePartOfTheShortcut);
};

#endif // MENUSETTINGS_H
