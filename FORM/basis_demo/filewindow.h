#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = nullptr);
    ~FileWindow();

    void new_file(); // 创建文件
    bool maybe_save(); // 判断是否已保存文件
    bool save(); //文件保存，判断直接保存还是另存为
    bool saveAs(); // 文件另存
    bool saveFile(QString); // 文件直接保存
    bool loadFile(QString); // 读取文件



private slots:
    void on_action_new_triggered(); //创建
    void on_action_save_triggered(); // 保存
    void on_action_saveAs_triggered(); //另存
    void on_action_open_triggered(); // 打开

private:
    Ui::FileWindow *ui;

    bool isSave; //当前文件是否已经保存过
    QString fileName;

};

#endif // FILEWINDOW_H
