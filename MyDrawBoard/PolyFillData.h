#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class PolyfillData :public ShapeData {
	public:
		PolyfillData(vector<Point> clickPoints, int fillType, int fillLength, bool isSolidLine,int color)
			:ShapeData(fillType, fillLength, isSolidLine, color) {
			m_points = clickPoints;
			m_shapeType = ShapeType::PolyFill;
			//绘制点
			for (int i = 0; i < clickPoints.size(); i++) {
				CtrlPointData* circle = new CtrlPointData(clickPoints[i]);
				m_circles.push_back(circle);
			}
			m_centerPointData = new CtrlPointData();
		}
		~PolyfillData() {

		}

		virtual void Set(const Point& move) {

		}

		//添加控制多边形的点
		void AddCtrlPoint(const Point& point) {
			m_points.push_back(point);
			CtrlPointData* circle = new CtrlPointData(point);
			m_circles.push_back(circle);
			//更新控制点图案
			AdjustShape();
		}
		void AdjustShape() {
			for (int i = 0; i < m_points.size(); i++) {
				m_circles[i]->AdjustCircle(m_points[i]);
			}
		}

		std::vector<Point> GetDrawPoints() override {
			return Algorithm::PolyFill(m_points);
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}

		vector<Point> GetCtrlPoints() override {
			return m_points;
		}

		void UpdateCenter() {
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
		}

		//设置控制多边形
		void SetCtrlPoints(int i, const Point& point) {
			m_points[i] = point;
		}
		void SetCtrlPoints(const vector<Point> & points) {
			m_points = points;
		}

		#pragma region 中心原点相关函数
		//更新中心原点
		void AdjustMyCenter(const Point & centerPoint)override {
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
			vector<Point> polyPoints = m_centerPointData->GetDrawPoints();
			for (int i = 0; i < m_circles.size(); i++) {
				vector<Point> add = m_circles[i]->GetDrawPoints();
				polyPoints.insert(polyPoints.end(), add.begin(), add.end());
			}
			return polyPoints;
		}
#pragma endregion
		#pragma region 图形变换相关函数
		void Translation(int dff_x, int dff_y)override {
			UpdateCenter();
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
			UpdateCenter();
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
			UpdateCenter();
			vector<Point*> ctrlPoints;
			for (int i = 0; i < m_points.size(); i++) {
				ctrlPoints.push_back(&m_points[i]);
			}
			Algorithm::zoom(ctrlPoints, m_centerPoint, rate);
			AdjustShape();
		}
#pragma endregion	

	private:
		CtrlPointData* m_centerPointData;

		vector<CtrlPointData*> m_circles;

		vector<Point> m_points;
	};
}