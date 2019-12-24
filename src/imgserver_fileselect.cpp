#include "imgserver_fileselect.h"
#include "ui_imgserver_fileselect.h"

StreamSelectDialog::StreamSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imgserver_fileselect)
{
    ui->setupUi(this);
}

StreamSelectDialog::~StreamSelectDialog()
{
    delete ui;
}

void StreamSelectDialog::on_buttonBox_accepted()
{
    emit fileSelected(ui->filePathEdit->text());
}
