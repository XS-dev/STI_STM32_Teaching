#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QList>
#include <math.h>



#define WIDGET_WIDTH  942       //窗口的宽度
#define WIDGET_HEIGHT 300       //信号窗口的高度
#define BASE_X  20      //统计图绘制开始的位置
#define BASE_Y  20


class my_widget : public QWidget
{
Q_OBJECT
public:
    my_widget (QWidget* parent=nullptr);
    ~my_widget(void)override{}
protected:
    void paintEvent(QPaintEvent* event)override;

private:

    void draw_back(QPainter& painter);

    quint32 fre_index2;
    QList <quint8> fft_points;
    QList <qint16> points;
    qint16 length;
    quint8 gears;

private slots:
    void update_points(QList <qint16> new_points,qint16 new_length,quint8 new_gears);
    void update_fft_points(QList <quint8> new_fft_points,quint32 new_fre_index2);
};


#endif // MY_WIDGET_H
