#include "imgserver_dialog.h"
#include "ui_imgserver_dialog.h"

ImgServer_Dialog::ImgServer_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImgServer_Dialog)
{
    ui->setupUi(this);
}

ImgServer_Dialog::~ImgServer_Dialog()
{
    delete ui;
}

QString ImgServer_Dialog::getIPAddress() {
    return ui->IPEdit->text();
}

uint ImgServer_Dialog::getPort() {
    return uint(ui->portSpinBox->value());
}

QString ImgServer_Dialog::getFileName() {
    return ui->fileNameEdit->text();
}
