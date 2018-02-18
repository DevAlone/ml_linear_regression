#include "chartview.h"

#include <QtCharts/QLegendMarker>
#include <QtCharts/QScatterSeries>
#include <QtCore/QtMath>
#include <QtGui/QImage>
#include <QtGui/QPainter>

#include <QDebug>
#include <QLineSeries>

#include "ml/linear_regression.h"

using namespace QtCharts;

ChartView::ChartView(QWidget* parent)
    : QtCharts::QChartView(parent)
{
    series = new QScatterSeries();
    series->setName("points");
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(15.0);

    series2 = new QLineSeries();

    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series);
    chart()->addSeries(series2);

    chart()->setTitle("Linear regression example(Just click to add point)");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);

    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}

void ChartView::resetZoom()
{
    chart()->zoomReset();
}

void ChartView::wheelEvent(QWheelEvent* event)
{
    qreal factor = event->angleDelta().y() < 0 ? 0.5 : 2.0;
    chart()->zoom(factor);
    event->accept();
    QChartView::wheelEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent* event)
{
}

void ChartView::mouseReleaseEvent(QMouseEvent* event)
{
    auto point = chart()->mapToValue(event->pos());
    points.append(point);
    series->append(point);

    if (points.size() == 1) {
        minPoint = point;
        maxPoint = point;
    } else {
        maxPoint = QPointF(
            qMax(maxPoint.x(), point.x()),
            qMax(maxPoint.y(), point.y()));

        minPoint = QPointF(
            qMin(minPoint.x(), point.x()),
            qMin(minPoint.y(), point.y()));
    }

    if (points.size() > 1) {

        auto dataSet = std::vector<std::pair<float, float> >();

        for (const auto& point : points) {
            dataSet.push_back(std::make_pair(point.x(), point.y()));
        }

        auto result = ml::getLineFitsToPoints(dataSet);

        float theta0 = result.first;
        float theta1 = result.second;

        auto minX = minPoint.x();
        auto maxX = maxPoint.x();

        series2->clear();
        series2->append(QPointF(minX, theta0 + minX * theta1));
        series2->append(QPointF(maxX, theta0 + maxX * theta1));
    }
}
