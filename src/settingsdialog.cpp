#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QMessageBox>

const QString SettingsDialog::defaultBase("的一是了人在有我他这为之来以个们到说和地也子时而要于就下得可你年生自会那后能对着事其里所去行过十用发如然方成者多都三二同么当起与好看学进将还分此心前面又定见只从现因开些长明样已月正想实把相两力等外它并间手应全门点身由何向至物被五及入先己或很最书美山什名曰合加世水果位度马给数次今表原各才几解则气再听提万更比百尔即白许系且光路接结题指感量取场电空边件住放风求形望传笑叫往区达设记字故品象花七服据云像飞远收石类程转千式流每该始术格运怎步让识拉若备造快集布尽称确呢节注存具甚容吃算坐早引似视尚轻况留照写足余星居技属找食");

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    settings("yvbbrjdr", "Babble"),
    passphrase(settings.value("passphrase", QString()).toString()),
    base(settings.value("base", defaultBase).toString()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::accept() {
    if (ui->baseLineEdit->text().length() != 256) {
        QMessageBox::critical(this, "错误", "基底必须为256个汉字长。");
        return;
    }
    passphrase = ui->passphraseLineEdit->text();
    base = ui->baseLineEdit->text();
    settings.setValue("passphrase", passphrase);
    settings.setValue("base", base);
    hide();
}

void SettingsDialog::showEvent(QShowEvent*) {
    ui->passphraseLineEdit->setText(passphrase);
    ui->baseLineEdit->setText(base);
    ui->passphraseLineEdit->setFocus();
}
