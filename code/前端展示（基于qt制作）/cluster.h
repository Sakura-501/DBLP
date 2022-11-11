#ifndef CLUSTER_H
#define CLUSTER_H

#include <QDialog>

namespace Ui {
class Cluster;
}

class Cluster : public QDialog
{
    Q_OBJECT

public:
    explicit Cluster(QWidget *parent = nullptr);
    ~Cluster();

private:
    Ui::Cluster *ui;
};

#endif // CLUSTER_H
