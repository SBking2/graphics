#pragma once
#include<QPainter>
#include<QMouseEvent>
#include<QWidget>
#include"InputSystem.h"
#include<QFrame>
namespace ComputerGraphics {
	class MyDrawArea : public QFrame {
	public:
		MyDrawArea(QWidget* parent = Q_NULLPTR) : QFrame(parent) {
			m_startX = 0;
			m_startY = 0;
			m_width = 0;
			m_height = 0;
			m_currentShapeType = ShapeType::Unknown;
		}
		~MyDrawArea() {}
		void setGeometry() {
			QWidget::setGeometry(m_startX, m_startY, m_width, m_height);
		}
		void setAreaPosition(int x, int y, int width, int height) {
			m_startX = x;
			m_startY = y;
			m_width = width;
			m_height = height;
		}

		void SetPenColor(const QColor& color) {
			m_pen.setColor(color);
		}
		void SetPenWidth(int width) {
			m_pen.setWidth(width);
		}

		void SetShapeType(const ShapeType& shapeType) {
			m_currentShapeType = shapeType;
		}
		ShapeType getShapeType() {
			return m_currentShapeType;
		}

		/*void DrawShapes(const std::vector<Point> & points, QPainter painter) {
			for (int i = 0; i < points.size(); i++) {
				painter.drawPoint(QPoint(points[i].x, points[i].y));
			}
		}*/

		void paintEvent(QPaintEvent* event) override {
			QFrame::paintEvent(event);
			QPainter painter(this);
			m_pen.setColor(Qt::green);
			m_pen.setWidth(1);

			painter.setPen(m_pen);

			std::vector<Point> points = ShapeDataCtrlSystem::getInstance()->GetAllShapePoint();
			for (int i = 0; i < points.size(); i++) {
				painter.drawPoint(QPoint(points[i].x, points[i].y));
			}
		}
		void resizeEvent(QResizeEvent* event) override {
			QFrame::resizeEvent(event);
		}

		void mousePressEvent(QMouseEvent* event) override {
			if (event->button() == Qt::MouseButton::LeftButton) {
				InputSystem::getInstance()->MousePress(Point(event->pos().x(), event->pos().y())
					, m_currentShapeType);
			}

			QFrame::mousePressEvent(event);
		}

		void mouseMoveEvent(QMouseEvent * event) override{
			InputSystem::getInstance()->MouseMove(Point(event->pos().x(), event->pos().y())
				, m_currentShapeType);
			
			update();

			QFrame::mouseMoveEvent(event);
		}
		
		void mouseReleaseEvent(QMouseEvent * event) override{
			if (event->button() == Qt::MouseButton::LeftButton) {
				InputSystem::getInstance()->MouseRelease(Point(event->pos().x(), event->pos().y())
				, m_currentShapeType);
			}

			QFrame::mouseReleaseEvent(event);
		}
	private:
		int m_startX;
		int m_startY;
		int m_width;
		int m_height;

		ShapeType m_currentShapeType;
		QPen m_pen;
	};
}