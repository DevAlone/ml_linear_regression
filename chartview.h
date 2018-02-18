#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QWidget>

class ChartView : public QtCharts::QChartView {
    Q_OBJECT
public:
    explicit ChartView(QWidget* parent = nullptr);

signals:

public slots:
    void resetZoom();
    void resetDataset();

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent* event);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QtCharts::QScatterSeries* series;
    QtCharts::QLineSeries* series2;
    QVector<QPointF> points;
    QPointF minPoint = QPointF(0, 0);
    QPointF maxPoint = QPointF(0, 0);
};

#endif // CHARTVIEW_H
