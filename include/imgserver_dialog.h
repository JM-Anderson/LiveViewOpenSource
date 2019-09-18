#ifndef IMGSERVER_DIALOG_H
#define IMGSERVER_DIALOG_H

#include <QDialog>

namespace Ui {
class ImgServer_Dialog;
}

class ImgServer_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImgServer_Dialog(QWidget *parent = 0);
    ~ImgServer_Dialog();

    QString getIPAddress();
    uint getPort();
    QString getFileName();

private:
    Ui::ImgServer_Dialog *ui;

};

#endif // IMGSERVER_DIALOG_H
