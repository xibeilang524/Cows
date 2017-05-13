#include "stdafx.h"

#include "tablewidget.h"
#include "customtablemodel.h"

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    // create simple model for storing data
    // user's table data model
    //! [1]
	m_pModel = new CustomTableModel;
    //! [1]

    //! [2]
    // create table view and add model to it
	m_pTableView = new QTableView;
	m_pTableView->setModel(m_pModel);
	m_pTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //! [2]

    //! [3]
	m_pChart = new QChart;
	m_pChart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

	initAxis();

    //! [8]
	m_pChart->createDefaultAxes();
	m_pChartView = new QChartView(m_pChart);
	m_pChartView->setRenderHint(QPainter::Antialiasing);
	m_pChartView->setMinimumSize(640, 480);
    //! [8]

    //! [9]
    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(m_pTableView, 1, 0);
	mainLayout->addWidget(m_pChartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
    //! [9]
}

void TableWidget::initAxis()
{
	// X����
	m_pSeriesX = new QSplineSeries;
	m_pSeriesX->setName("X");
	QVXYModelMapper *mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(1);
	mapper->setSeries(m_pSeriesX);
	mapper->setModel(m_pModel);
	m_pChart->addSeries(m_pSeriesX);

	QString seriesColorHex = "#000000";

	// get the color of the series and use it for showing the mapped area
	seriesColorHex = "#" + QString::number(m_pSeriesX->pen().color().rgb(), 16).right(6).toUpper();
	m_pModel->addMapping(seriesColorHex, QRect(1, 0, 1, m_pModel->rowCount()));

	// Y����
	m_pSeriesY = new QSplineSeries;
	m_pSeriesY->setName("Y");

	mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(2);
	mapper->setSeries(m_pSeriesY);
	mapper->setModel(m_pModel);
	m_pChart->addSeries(m_pSeriesY);

	seriesColorHex = "#" + QString::number(m_pSeriesY->pen().color().rgb(), 16).right(6).toUpper();
	m_pModel->addMapping(seriesColorHex, QRect(2, 0, 1, m_pModel->rowCount()));

	// Z����
	m_pSeriesZ = new QSplineSeries;
	m_pSeriesZ->setName("Z");

	mapper = new QVXYModelMapper(this);
	mapper->setXColumn(0);
	mapper->setYColumn(3);
	mapper->setSeries(m_pSeriesZ);
	mapper->setModel(m_pModel);
	m_pChart->addSeries(m_pSeriesZ);

	seriesColorHex = "#" + QString::number(m_pSeriesZ->pen().color().rgb(), 16).right(6).toUpper();
	m_pModel->addMapping(seriesColorHex, QRect(3, 0, 1, m_pModel->rowCount()));
}