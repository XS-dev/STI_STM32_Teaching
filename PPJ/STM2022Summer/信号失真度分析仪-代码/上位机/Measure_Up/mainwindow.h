#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
#include <QUdpSocket>
#include "my_widget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udp_socket;
    my_widget* cart;

    bool is_started;
private slots:
    void onSocketReadyRead();
    void start_button_clicked(void);
signals:
    void update_points(QList <qint16> new_points,qint16 new_length,quint8 new_gears);
    void update_fft_points(QList <quint8> new_fft_points,quint32 new_fre_index2);
};
#endif // MAINWINDOW_H
