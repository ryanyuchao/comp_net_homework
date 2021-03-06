#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QMessageBox>
#include "assert.h"
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QtNetwork>


//#include<stdio.h>

ChatDialog::ChatDialog(QString id, QWidget *parent) :
    QMainWindow(parent),
    id(id),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    //QKeyEvent *ev;
    connect(ui->msgTxtEdit, SIGNAL(send_text()), this, SLOT(on_sendBtn_clicked()));
    //this->eventFilter(ui->msgTxtEdit,ev);
     //this->msgTxtEdit::keyPressEvent ( ev );
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::rec_msg(QString id, QString msg)
{
    if ( id == this->id )
        QMessageBox::information(this, "get msg!", "from" + id + " " + msg);
    qDebug() << "id" << id << "this->id" << this->id << "msg" << msg;
}

void ChatDialog::on_fontCbx_currentFontChanged(const QFont &f)
{
    ui->msgTxtEdit->setCurrentFont(f);
    ui->msgTxtEdit->setFocus();
}

void ChatDialog::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
    ui->msgTxtEdit->setFontPointSize(arg1.toDouble());
    ui->msgTxtEdit->setFocus();
}

void ChatDialog::on_sendBtn_clicked()
{
   if( ui->msgTxtEdit->toPlainText()== "") { QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok); return;}
   msg_tobesent=ui->msgTxtEdit->toPlainText();
   ui->usrNumLbl->setText(msg_tobesent);
   ui->msgTxtEdit->clear();
   emit send_msg(id, msg_tobesent);
  // QMessageBox::warning(0,tr("显示"),tr(msg_tobesent),QMessageBox::Ok);
  // printf("%s",msg_tobesent.toStdString());
}


