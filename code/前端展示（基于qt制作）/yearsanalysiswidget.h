#ifndef YEARSANALYSISWIDGET_H
#define YEARSANALYSISWIDGET_H

#include <QWidget>

namespace Ui {
class yearsAnalysisWidget;
}

class yearsAnalysisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit yearsAnalysisWidget(QWidget *parent = nullptr);
    ~yearsAnalysisWidget();

signals:
    void goBack();

private:
    Ui::yearsAnalysisWidget *ui;
    QString YearsText;
    QImage *img;
};

#endif // YEARSANALYSISWIDGET_H
