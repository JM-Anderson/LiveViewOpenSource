#ifndef IMGSERVER_FILESELECT_H
#define IMGSERVER_FILESELECT_H

#include <QDialog>

namespace Ui {
class imgserver_fileselect;
}

class StreamSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StreamSelectDialog(QWidget *parent = 0);
    ~StreamSelectDialog();

signals:
    void fileSelected(QString filePath);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::imgserver_fileselect *ui;
};

#endif // IMGSERVER_FILESELECT_H
