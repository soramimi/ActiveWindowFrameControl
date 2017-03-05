#include "MainWindow.h"
#include <windows.h>
#include <QAbstractNativeEventFilter>
#include <QApplication>
#include <QDebug>

void winActivateWindowFrame(WId wid)
{
	DefWindowProc((HWND)wid, WM_NCACTIVATE, TRUE, 0);
}

class WindowsEventHandler : public QAbstractNativeEventFilter {
private:
	MainWindow *mainwindow;
	bool active = true;
public:
	WindowsEventHandler(MainWindow *mainwindow)
		: mainwindow(mainwindow)
	{
	}

	bool nativeEventFilter(const QByteArray &eventType, void *message, long *result)
	{
		MSG *msg = (MSG *)message;
		if (msg) {
			if (msg->message == WM_ACTIVATEAPP) {
				active = msg->wParam != FALSE;
				if (active) {
					mainwindow->onActivateWindow();
				} else {
					DefWindowProc(msg->hwnd, WM_NCACTIVATE, FALSE, 0);
				}
			} else if (msg->message == WM_NCACTIVATE) {
				if (active) {
					*result = DefWindowProc(msg->hwnd, WM_NCACTIVATE, TRUE, 0);
					return true;
				}
			}
		}
		return false;
	}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	WindowsEventHandler win(&w);
	w.show();
	a.installNativeEventFilter(&win);

	return a.exec();
}
