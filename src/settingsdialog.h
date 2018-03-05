#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
private:
    Ui::SettingsDialog *ui;
    QSettings settings;
    static const QString defaultBase;
public:
    QString passphrase;
    QString base;
private slots:
    void accept();
protected:
    void showEvent(QShowEvent*);
};

#endif // SETTINGSDIALOG_H
