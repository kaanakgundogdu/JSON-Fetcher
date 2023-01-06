#include "widget.h"
#include "./ui_widget.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , network_manager(new QNetworkAccessManager(this))
    ,network_reply(nullptr)
    ,m_data_buffer(new QByteArray)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete m_data_buffer;
    delete ui;
}


void Widget::on_fetch_button_clicked()
{
    const QUrl API_ENDPOINT("https://jsonplaceholder.typicode.com/posts");
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);
    network_reply=network_manager->get(request);

    connect(network_reply,&QIODevice::readyRead,this,&Widget::data_ready_read);
    connect(network_reply,&QNetworkReply::finished,this,&Widget::data_read_finished);


}

void Widget::data_ready_read()
{
    m_data_buffer->append(network_reply->readAll());
}

void Widget::data_read_finished()
{
    if (network_reply->error()) {
        qDebug()<<"Error: "<< network_reply->errorString();
    }
    else {
        qDebug()<<"Data fetch finished!";

        QJsonDocument doc= QJsonDocument::fromJson(*m_data_buffer);

        QJsonArray arr=doc.array();

        for (int i = 0; i < arr.size(); ++i) {
            QJsonObject obj=arr.at(i).toObject();
            QVariantMap map= obj.toVariantMap();
            QString title=map["title"].toString();

            ui->json_content_list->addItem("[" + QString::number(i+1) + "] " + title);
        }

    }
}













