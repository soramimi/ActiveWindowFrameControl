#include "MainWindow.h"
#include "ui_MainWindow.h"

void winActivateWindowFrame(WId wid);

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onActivateWindow()
{
	winActivateWindowFrame(ui->dockWidget->winId());
	activateWindow();
}
