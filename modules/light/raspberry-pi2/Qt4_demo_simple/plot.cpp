#include <QtGui>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include "plot.h"
#include "avaspec.h"

Plot::Plot(QWidget *parent):
    QwtPlot(parent)
{
    extern double m_pLambda[MAX_NR_PIXELS];
    extern double l_pSpectrum[MAX_NR_PIXELS];

    setAxisTitle(xBottom, "Wavelength [nm]");
    setAxisTitle(yLeft, "Counts");
    setAxisScale(xBottom, 300.0, 900.0);
    setAxisScale(yLeft, -100.0, 17000.0);

    curve = new QwtPlotCurve("Testcurve");
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setPen(QPen(Qt::black));
    curve->setSamples(m_pLambda,l_pSpectrum,MAX_NR_PIXELS);
    curve->attach(this);

    // LeftButton for the zooming
    // MidButton for the panning
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size

    QwtPlotZoomer* zoomer = new QwtPlotZoomer(canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);

    QwtPlotPanner *panner = new QwtPlotPanner(canvas());  
    panner->setMouseButton(Qt::MidButton);
    zoomer->setRubberBandPen(QColor(Qt::black));
    zoomer->setTrackerPen(QColor(Qt::black));
//  this->resize(600,400); // does not work, use sizeHint and minimumSizeHint
    this->show();
}

QSize Plot::minimumSizeHint() const
{
    return QSize(600, 400);
}

QSize Plot::sizeHint() const
{
    return QSize(600, 400);
}

void Plot::update_plot()
{
    extern double m_pLambda[MAX_NR_PIXELS];
    extern double l_pSpectrum[MAX_NR_PIXELS];
    extern unsigned short m_NrPixels;

    curve->setSamples(m_pLambda,l_pSpectrum,m_NrPixels);
    replot();
}

