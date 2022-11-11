#ifndef AUTHORCOUNT_H
#define AUTHORCOUNT_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class AuthorCount;
}

class AuthorCount : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorCount(QWidget *parent = nullptr);
    ~AuthorCount();

private:
    Ui::AuthorCount *ui;
};

#endif // AUTHORCOUNT_H
