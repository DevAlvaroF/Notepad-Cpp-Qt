#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    setWindowTitle("Super Cool Notepad"); // Set window name
    setWindowIcon(QIcon(":/Imgs/Icons/appicon.png")); // Set Window Icon (.qrc path)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // Object to open file
    QFile file(fileName);
    currentFile = fileName;

    // Open file as Read Only
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warnig","Cannot open file: "+file.errorString());
        return;
    }

    setWindowTitle(fileName); // Set window name to the filename
    QTextStream in(&file); // A Reading object
    QString text = in.readAll(); // Extract text from file
    ui->textEdit->setText(text); // Place text from file in UI

    // Close File
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // Object to save file
    QFile file(fileName);

    // Open file as Write Only
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warnig","Cannot save file: "+file.errorString());
        return;
    }

    currentFile = fileName; // Update Curret File Variable
    setWindowTitle(fileName); // Set window name to the filename
    QTextStream out(&file); // A Writing object

    QString text = ui->textEdit->toPlainText(); // Getting data from widget
    out << text;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");

    // Print Dialog
    QPrintDialog pDialog(&printer, this);

    // Error manager
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning","Cannot Access Printer");
        return;
    }

    // Send textEdit text to printer
    ui->textEdit->print(&printer);



}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();

}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

