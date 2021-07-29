#include "filewindow.h"
#include "ui_filewindow.h"

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    // 初始化构造函数
    isSave = false;
    fileName = tr("untitled.txt");
    setWindowTitle(fileName);

}

FileWindow::~FileWindow()
{
    delete ui;
}
// 创建文件
void FileWindow::new_file()
{
    // 当前编辑文件已保存>>创建新文件
    if (maybe_save())
    {
        isSave = false;
        fileName = "untitled.txt";
        setWindowTitle(fileName);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true); //是否可见
    }
}

//判断编辑区域文件是否有修改未保存
bool FileWindow::maybe_save()
{
    qDebug() << "test maybe save";
    // 文档被编辑过 则提醒保存
    if(ui->textEdit->document()->isModified())
    {
        // 提醒未保存
        QMessageBox msg_box;
        msg_box.setWindowTitle(tr("警告"));
        msg_box.setIcon(QMessageBox::Warning);
        msg_box.setText(fileName + tr("未保存，是否需要保存？"));
        msg_box.addButton(tr("是"), QMessageBox::YesRole);
        msg_box.addButton(tr("否"), QMessageBox::NoRole);
        msg_box.addButton(tr("取消"), QMessageBox::RejectRole);
        int result = msg_box.exec();
        if(!result)
        {
            qDebug() << "YES";
            //执行保存
            return save();
        } else
        {
            qDebug() << "NO";
            return false;
        }
    }
    return true;
}

// 当前文件已经保存过 >> 保存文件 未保存过则另存为，保存提供保存文件名
bool FileWindow::save()
{
    if(isSave)
    {
        return saveFile(fileName);
    }else {
        return saveAs();
    }
}

// 另存为
bool FileWindow::saveAs()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("另存为"), fileName);
    if (file_name.isEmpty()) return false;
    return saveFile(file_name);
}

// 已保存过再次保存
bool FileWindow::saveFile(QString fileName)
{
    QFile file(fileName);

    // 打开失败
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("编辑器"),
                             tr("无法写入文件 %1: /n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    // 鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    // 鼠标指针恢复状态
    QApplication::restoreOverrideCursor();
    isSave = true;
    fileName = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(fileName);
    return true;
}

bool FileWindow::loadFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("警告"),
                             tr("读取文件失败 %1 /n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    fileName = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(fileName);
    return true;
}


void FileWindow::on_action_new_triggered()
{
    new_file();
}

void FileWindow::on_action_save_triggered()
{
    save();
}

void FileWindow::on_action_saveAs_triggered()
{
    saveAs();
}

void FileWindow::on_action_open_triggered()
{
    if (maybe_save())
    {
        qDebug() << "test ave";
        QString fileName = QFileDialog::getOpenFileName(this);

        if (!fileName.isEmpty())
        {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }

    }
}

