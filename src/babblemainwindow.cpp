#include "babblemainwindow.h"
#include "ui_babblemainwindow.h"
#include <cryptoutils.h>

BabbleMainWindow::BabbleMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BabbleMainWindow),
    settingsDialog(this) {
    ui->setupUi(this);
    CryptoUtils::init();
    connect(ui->encryptButton, SIGNAL(clicked()), this, SLOT(encryptClicked()));
    connect(ui->decryptButton, SIGNAL(clicked()), this, SLOT(decyrptClicked()));
    connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(settingsClicked()));
}

BabbleMainWindow::~BabbleMainWindow() {
    delete ui;
}

void BabbleMainWindow::encryptClicked() {
    ui->cipherText->setText(CryptoUtils::encrypt(ui->plainText->toPlainText().toUtf8(),
                                                 settingsDialog.passphrase.toUtf8(),
                                                 settingsDialog.base));
}

void BabbleMainWindow::decyrptClicked() {
    ui->plainText->setText(CryptoUtils::decrypt(ui->cipherText->toPlainText(),
                                                settingsDialog.passphrase.toUtf8(),
                                                settingsDialog.base));
}

void BabbleMainWindow::settingsClicked() {
    settingsDialog.show();
}
