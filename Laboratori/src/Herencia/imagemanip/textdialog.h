#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class TextDialog : public QDialog
{
    Q_OBJECT

  QLineEdit *_text;
  QPushButton *_boto_ok, *_boto_cancel;
public:
    explicit TextDialog(QWidget *parent = 0);

signals:

public:
  QString text() const;
};

#endif // TEXTDIALOG_H
