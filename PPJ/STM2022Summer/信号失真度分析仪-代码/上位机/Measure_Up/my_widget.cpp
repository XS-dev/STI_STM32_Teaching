#include "my_widget.h"

void my_widget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)             //标记不使用这个参数

    QPainter painter(this);     //创建一个绘画元件
    painter.setViewport(0,0,WIDGET_WIDTH,WIDGET_HEIGHT);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(130,151,165));
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    draw_back(painter);

    pen.setColor(QColor(0xff,0x61,0x00));
    painter.setPen(pen);


    if(length==0)
    {
        return;
    }
    else
    {
        qint16 max_point=0,min_point=qint16(0x01<<14);
        float div_h;

        for(int i=0;i<150;i++)
        {
            if(points[i]>max_point)
            {
                max_point=points[i];
            }
            if(points[i]<min_point)
            {
                min_point=points[i];
            }
        }

        if(max_point-min_point==0)
        {
            return;
        }
        else
        {
            div_h=240.0f/float(max_point-min_point);
            if(div_h!=0)
            {
                qint16 tmp_max=0,tmp_min=0x7fff;
                for(int i=0;i<150;i++)
                {
                    if(points[i]<tmp_min)
                    {
                        tmp_min=points[i];
                    }
                    if(points[i]>tmp_max)
                    {
                        tmp_max=points[i];
                    }
                }
                float peek_voltage=1.0f;

                switch(gears)
                {
                case 1:
                    peek_voltage= float(tmp_max-tmp_min)/0x3fff*3.3f/5.0f*1000.0f ;
                    painter.drawText(90,20,QString("档位:x5   Vpp=")+QString::number(peek_voltage,'f',2)+QString(" mV") );
                    break;
                case 2:
                    peek_voltage= float(tmp_max-tmp_min)/0x3fff*3.3f/20.0f*1000.0f ;
                    painter.drawText(90,20,QString("档位:x20  Vpp=")+QString::number(peek_voltage,'f',2)+QString(" mV") );
                    break;
                case 3:
                    peek_voltage= float(tmp_max-tmp_min)/0x3fff*3.3f/80.0f*1000.0f ;
                    painter.drawText(90,20,QString("档位:x80  Vpp=").QString::number(peek_voltage,'f',2)+QString(" mV") );
                    break;
                }
                painter.drawText(330,20,QString("频率=")+QString::number(float(length)/0x3fff*200.0f,'f',2)+QString(" kHz"));
                painter.drawText(5,20,QString("X/")+QString::number(50.0f/240.0f*peek_voltage,'f',1)+QString(" mV"));

                QPoint last_point=QPoint(0,270-(points[0]-min_point)*div_h);
                QPoint this_point;



                pen.setColor(QColor(250,128,114));
                painter.setPen(pen);
                for(int i=1;i<150;i++)
                {
                    this_point=QPoint(i*8/3,270-(points[i]-min_point)*div_h);
                    painter.drawLine(last_point,this_point);
                    last_point=this_point;
                }
                pen.setColor(QColor(0xff,0x61,0x00));
                painter.setPen(pen);



                float time_div=250.0f/(1000.0f/length);
                for(int i=0;i<4;i++)
                {
                    painter.drawText(100*i+60,295,QString::number((1+i)*time_div,'f',1)+QString("us"));
                }
            }
        }



        if(fft_points.size()!=0)
        {
            //painter.drawText(100,100,QString("%1").arg(12000000.0f/(12000000/fre_index2)));

            if(fre_index2!=0)
            {
                float delta_fre=(12000.0f/(12000000/fre_index2))*50.0f/512.0f;
                for(int i=0;i<5;i++)
                {
                    painter.drawText(i*100+460,20,QString::number((i+1)*delta_fre,'f',3)+QString(" kHz"));
                }
            }

            QPoint last_point(440,300-300.0f*sqrt(fft_points[0])/11.269);
            QPoint this_point;

            pen.setColor(QColor(250,128,114));
            painter.setPen(pen);
            for(int i=1;i<fft_points.size();i++)
            {
                this_point=QPoint(i+440,300-300.0f*sqrt(fft_points[i])/11.269);
                painter.drawLine(last_point,this_point);
                last_point=this_point;
            }

        }
    }
}

my_widget::my_widget(QWidget* parent):
    QWidget(parent)
{
    points.clear();
    length=0;
}

void my_widget::update_points(QList <qint16> new_points,qint16 new_length,quint8 new_gears)
{
    points=new_points;
    length=new_length;
    gears=new_gears;
    this->update();
}

void my_widget::update_fft_points(QList <quint8> new_fft_points,quint32 new_fre_index2)
{
    fft_points=new_fft_points;
    fre_index2=new_fre_index2;
    this->update();
}



void my_widget::draw_back(QPainter& painter)
{
    painter.drawLine(1,0,1,300);
    for(int i=1;i<5;i++)
    {
        painter.drawLine(i*100,0,i*100,300);
    }

    painter.drawLine(0,1,400,1);
    for(int i=1;i<7;i++)
    {
        painter.drawLine(0,i*50,400,i*50);
    }

    for(int i=0;i<6;i++)
    {
        painter.drawLine(i*100+440,0,i*100+440,300);
    }

    for(int i=0;i<7;i++)
    {
        painter.drawLine(0+440,i*50,512+440,i*50);
    }
}



