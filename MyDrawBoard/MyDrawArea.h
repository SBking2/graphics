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

		void Rotation(double angle) {
			InputSystem::getInstance()->Rotation(angle);
			update();
		}

		void Scale(double rate) {
			InputSystem::getInstance()->Scale(rate);
			update();
		}
		void SetT(float t) {
			m_t = t;
		}

		void SetBoarder(int left, int right, int bottom, int top) {
			m_boarder.Set(left, right, bottom, top);
		}

		/*void DrawShapes(const std::vector<Point> & points, QPainter painter) {
			for (int i = 0; i < points.size(); i++) {
				painter.drawPoint(QPoint(points[i].x, points[i].y));
			}
		}*/

		void paintEvent(QPaintEvent* event) override {
			QFrame::paintEvent(event);
			QPainter painter(this);
			m_pen.setColor(Qt::red);
			m_pen.setWidth(1);
			painter.setPen(m_pen);

			QPen BlackPen;
			BlackPen.setColor(Qt::black);
			BlackPen.setWidth(1);

			QPen BluePen;
			BluePen.setColor(Qt::blue);
			BluePen.setWidth(1);

			QPen yellowPen;
			QColor yellowC(237, 159, 90);
			yellowPen.setColor(yellowC);
			yellowPen.setWidth(1);

			QPen lungPen;
			lungPen.setWidth(1);
			//lung
			QColor lungColor(255 * m_t, 0, 0);
			lungPen.setColor(lungColor);

			//粒子
			QPen GrayPen;
			GrayPen.setColor(Qt::gray);
			GrayPen.setWidth(1);

			//10为肺部专属变色
			ShapeDataCtrlSystem::getInstance()->GetAllShapePoint();
			//for (int i = 0; i < points.size(); i++) {
			//	//painter.drawPoint(QPoint(points[i].x, points[i].y));
			//}
			for (int i = 0; i < CANVASLENGTH; i++) {
				for (int j = 0; j < CANVASLENGTH; j++) {
					if (CtrlLayerCanvas[i][j] == 2) {
						//黑色为图形
						painter.setPen(BlackPen);
						painter.drawPoint(QPoint(i,j));
					}
					else if (CtrlLayerCanvas[i][j] == 3) {
						//绿色为轴心
						painter.setPen(BluePen);
						painter.drawPoint(QPoint(i, j));
					}
					else if (canvas[i][j] == 1) {
						//红色为控制多边形
						painter.setPen(m_pen);
						painter.drawPoint(QPoint(i, j));
					}
					else if (canvas[i][j] == 2) {
						//黑色为图形
						painter.setPen(BlackPen);
						painter.drawPoint(QPoint(i, j));
					}
					else if (canvas[i][j] == 5) {
						painter.setPen(yellowPen);
						painter.drawPoint(QPoint(i, j));
					}
					else if (canvas[i][j] == 4) {
						//black
						painter.setPen(BlackPen);
						painter.drawPoint(QPoint(i, j));
					}
					else if (canvas[i][j] == 10) {
						painter.setPen(lungPen);
						painter.drawPoint(QPoint(i, j));
					}
					else if (canvas[i][j] == 12) {
						painter.setPen(GrayPen);
						painter.drawPoint(QPoint(i, j));
					}
					
				}
			}
		}

		void resizeEvent(QResizeEvent* event) override {
			QFrame::resizeEvent(event);
		}

		void mousePressEvent(QMouseEvent* event) override {
			if (event->button() == Qt::MouseButton::LeftButton) {
				InputSystem::getInstance()->MousePress(Point(event->pos().x(), event->pos().y())
					, m_currentShapeType, m_boarder);
				update();
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

		void ChangeDrawMode() {
			ShapeDataCtrlSystem::getInstance()->ChangeDrawMode();
			update();
		}

		void ResetInputSystem() {
			InputSystem::getInstance()->ResetInputSystem();
		}

		void Clear() {
			InputSystem::getInstance()->Clear();
			ShapeDataCtrlSystem::getInstance()->Clear();
			update();
		}
		void SetFillType(int x) {
			InputSystem::getInstance()->SetFillType(x);
		}
		void SetFillLength(int length) {
			InputSystem::getInstance()->SetFillLength(length);
		}
		void SetLineType(bool value) {
			InputSystem::getInstance()->SetLineType(value);
		}
	private:
		int m_startX;
		int m_startY;
		int m_width;
		int m_height;


		Boarder m_boarder;
		ShapeType m_currentShapeType;
		QPen m_pen;
		float m_t;
	};
}