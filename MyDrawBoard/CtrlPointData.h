#pragma once
#include"ShapeData.h"
#define PR 5
//使用中点算法绘制的控制点
namespace ComputerGraphics {
	class CtrlPointData :public ShapeData {
	public:
		CtrlPointData(const Point& center = Point(0, 0), int fillType = -1, int fillLength = 1, bool isSolidLine = true)
			:ShapeData(fillType, fillLength, isSolidLine) {
			m_start = center;
			m_shapeType = ShapeType::CtrlPoint;
		}
		~CtrlPointData() {

		}

		virtual void Set(const Point& move) {
			m_start = move;
		}

		std::vector<Point> GetDrawPoints() override {
			vector<Point> result = Algorithm::MidPointCircle(m_start, Point(m_start.x + PR, m_start.y));
			return result;
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}

		void AdjustCircle(const Point& center) {
			m_start = center;
		}

		#pragma region 图形变换相关函数
		/*void Translation(int dff_x, int dff_y)override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			Algorithm::translation(ctrlPoints, dff_x, dff_y);
		}
		void Rotation(double angle, const Point& axis) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			Algorithm::rotate(ctrlPoints, angle, axis);
		}
		void Rotation(double angle) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			Algorithm::rotate(ctrlPoints, angle, m_centerPoint);
		}*/
#pragma endregion	
	private:
		Point m_start;
	};
}