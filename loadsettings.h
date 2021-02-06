#ifndef LOADSETTINGS_H
#define LOADSETTINGS_H

#include <QMainWindow>
#include <QTranslator>
#include <QSettings>
#include <QApplication>
#include <QScreen>
#include <iostream>

class LoadSettings
{
public:
    LoadSettings(QMainWindow *mainWindow, QTranslator *translator);
    void loadAllConfig();
    QString getPathFileForImg();

private:
    QMainWindow* mainWindow;
    QTranslator *translator;
    QSettings *settings;
    QString pathFileForImg = nullptr;
    void loadSizeOnTheMainWindow();
    void loadLanguageOnTheApp();
    void loadPathFileForImg();
};

#endif // LOADSETTINGS_H
