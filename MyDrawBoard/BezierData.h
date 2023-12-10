#pragma once
#include"ShapeData.h"
#include<qdebug.h>
namespace ComputerGraphics {
	class BezierData :public ShapeData {
	public:
		BezierData(vector<Point> clickPoints, int fillType, int fillLength, bool isSolidLine, int color = 2)
			:ShapeData(fillType, fillLength, isSolidLine,color) {
			m_points = clickPoints;

			//绘制点
			for (int i = 0; i < clickPoints.size(); i++) {
				CtrlPointData *circle = new CtrlPointData(clickPoints[i]);
				m_circles.push_back(circle);
			}
			//绘制直线
			for (int i = 0; i < clickPoints.size() - 1; i++) {
				BresenhamLineData* line = new BresenhamLineData(clickPoints[i], clickPoints[i + 1]);
				m_lines.push_back(line);
			}
			m_shapeType = ShapeType::Bezier;
			m_centerPointData = new CtrlPointData();
		}
		~BezierData() {

		}

		virtual void Set(const Point& move) {

		}

		//贝塞尔曲线不仅要绘制曲线，还要绘制控制多边形
		vector<Point> GetDrawPoints() override {
			vector<Point> bezierPoints = Algorithm::BezierLine(m_points);
			return bezierPoints;
		}

		//获取控制多边形
		vector<Point> GetCtrlPoints() override{
			return m_points;
		}
		Point GetCtrlPoint(int i) {
			return m_points[i];
		}

		//设置控制多边形
		void SetCtrlPoints(int i, const Point& point) {
			m_points[i] = point;
			qDebug() << point.x<<" "<< point.y << endl;
		}

		void SetCtrlPoints(const vector<Point>& points) {
			m_points = points;
		}

		//添加控制多边形的点
		void AddCtrlPoint(const Point& point) {
			m_points.push_back(point);
			CtrlPointData* circle = new CtrlPointData(point);
			m_circles.push_back(circle);
			BresenhamLineData* line = new BresenhamLineData();
			m_lines.push_back(line);
			//连接点与线
			AdjustShape();
		}

		//根据点来调整圆和线
		void AdjustShape() {
			for (int i = 0; i < m_points.size(); i++) {
				m_circles[i]->AdjustCircle(m_points[i]);
				if (i != m_points.size() - 1)
					m_lines[i]->AdjustLine(m_points[i], m_points[i + 1]);
			}
		}

		#pragma region 中心原点相关函数
		//更新中心原点
		void AdjustMyCenter(const Point& centerPoint)override {
			ShapeData::AdjustMyCenter(centerPoint);
			m_centerPointData->AdjustCircle(centerPoint);
		}
		//绘制中心原点
		vector<Point> DrawMyCenter() override {
			int x = 0;
			int y = 0;
			for (int i = 0; i < m_points.size(); i++) {
				x += m_points[i].x;
				y += m_points[i].y;
			}
			x = x / m_points.size();
			y = y / m_points.size();
			Point center = Point(x, y);
			AdjustMyCenter(center);
			vector<Point> bezierPoints = m_centerPointData->GetDrawPoints();
			for (int i = 0; i < m_circles.size(); i++) {
				vector<Point> add = m_circles[i]->GetDrawPoints();
				bezierPoints.insert(bezierPoints.end(), add.begin(), add.end());
				if (i != m_circles.size() - 1) {
					add = m_lines[i]->GetDrawPoints();
					bezierPoints.insert(bezierPoints.end(), add.begin(), add.end());
				}
			}
			return bezierPoints;
		}
#pragma endregion
		#pragma region 图形变换相关函数
		void Translation(int dff_x, int dff_y)override {
			vector<Point*> ctrlPoints;
			for (int i = 0; i < m_points.size(); i++) {
				ctrlPoints.push_back(&m_points[i]);
			}
			Algorithm::translation(ctrlPoints, dff_x, dff_y);
			AdjustShape();
		}
		void Rotation(double angle, const Point& axis) override {
			vector<Point*> ctrlPoints;
			for (int i = 0; i < m_points.size(); i++) {
				ctrlPoints.push_back(&m_points[i]);
			}
			Algorithm::rotate(ctrlPoints, angle, axis);
			AdjustShape();
		}
		void Rotation(double angle) override {
			vector<Point*> ctrlPoints;
			for (int i = 0; i < m_points.size(); i++) {
				ctrlPoints.push_back(&m_points[i]);
			}
			Algorithm::rotate(ctrlPoints, angle, m_centerPoint);
			AdjustShape();
		}
		void Scale(double rate, const Point& axis) override {
			vector<Point*> ctrlPoints;
			for (int i = 0; i < m_points.size(); i++) {
				ctrlPoints.push_back(&m_points[i]);
			}
			Algorithm::zoom(ctrlPoints, axis, rate);
			AdjustShape();
		}
		void Scale(double rate) override {
			vector<Point*> ctrlPoints;
			for (int i = 0; i < m_points.size(); i++) {
				ctrlPoints.push_back(&m_points[i]);
			}
			Algorithm::zoom(ctrlPoints, m_centerPoint, rate);
			AdjustShape();
		}
#pragma endregion	
		
		ShapeType GetShapeType() override {
			return m_shapeType;
		}
	private:
		CtrlPointData* m_centerPointData;

		vector<Point> m_points;
		//绘制控制多边形
		vector<BresenhamLineData*> m_lines;
		//绘制控制点
		vector<CtrlPointData*> m_circles;
	};
}