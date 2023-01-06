#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_fetch_button_clicked();
    void data_ready_read();
    void data_read_finished();

private:
    Ui::Widget *ui;
    QNetworkAccessManager* network_manager;
    QNetworkReply* network_reply;
    QByteArray* m_data_buffer;

};
#endif // WIDGET_H
