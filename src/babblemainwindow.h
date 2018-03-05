#ifndef BABBLEMAINWINDOW_H
#define BABBLEMAINWINDOW_H

#include <QWidget>
#include "settingsdialog.h"

namespace Ui {
    class BabbleMainWindow;
}

class BabbleMainWindow : public QWidget {
    Q_OBJECT
public:
    explicit BabbleMainWindow(QWidget *parent = 0);
    ~BabbleMainWindow();
private:
    Ui::BabbleMainWindow *ui;
    SettingsDialog settingsDialog;
private slots:
    void encryptClicked();
    void decyrptClicked();
    void settingsClicked();
};

#endif // BABBLEMAINWINDOW_H
