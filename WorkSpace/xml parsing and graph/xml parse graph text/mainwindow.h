// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>  // Include QTextEdit
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void appendToOutput(const QString &text);  // Add this line

    void on_userdialog_clicked();

private:
    Ui::MainWindow *ui;
    QTextEdit *outputTextEdit;  // Add this line
};

#endif // MAINWINDOW_H
