#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

// <decl>
class TextDialog : public QDialog {
  // Q_OBJECT
  QLineEdit *_edit;
  QPushButton *_ok, *_cancel;
public:
  TextDialog(QString titol, QWidget *parent = 0);
  QString text() const;
};
// </decl>

#endif // TEXTDIALOG_H
