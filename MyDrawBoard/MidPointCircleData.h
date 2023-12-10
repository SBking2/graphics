#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class MidPointCircleData :public ShapeData {
	public:
		MidPointCircleData(int fillType, int fillLength, bool isSolidLine, const Point& start = Point(0, 0), const Point& end = Point(0, 0))
			:ShapeData(fillType, fillLength, isSolidLine) {
			m_start = start;
			m_end = end;
			m_shapeType = ShapeType::MidPointCircle;
			m_centerPointData = new CtrlPointData();
		}
		~MidPointCircleData() {

		}

		virtual void Set(const Point& move) {
			m_end = move;
		}

		std::vector<Point> GetDrawPoints() override {
			return Algorithm::MidPointCircle(m_start, m_end);
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}

		//辅助函数，Bezier相关
		void AdjustCircle(const Point& center, const Point& end) {
			m_start = center;
			m_end = end;
		}
		#pragma region 中心原点相关函数
		//更新中心原点
		void AdjustMyCenter(const Point& centerPoint)override {
			ShapeData::AdjustMyCenter(centerPoint);
			m_centerPointData->AdjustCircle(centerPoint);
		}
		//绘制中心原点
		vector<Point> DrawMyCenter() override {
			AdjustMyCenter(m_start);
			return m_centerPointData->GetDrawPoints();
		}
#pragma endregion

		#pragma region 图形变换相关函数
		void Translation(int dff_x, int dff_y)override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::translation(ctrlPoints, dff_x, dff_y);
		}
		void Rotation(double angle, const Point& axis) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::rotate(ctrlPoints, angle, axis);
		}
		void Rotation(double angle) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::rotate(ctrlPoints, angle, m_centerPoint);
		}
		void Scale(double rate, const Point& axis) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::zoom(ctrlPoints, axis, rate);
		}
		void Scale(double rate) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::zoom(ctrlPoints, m_centerPoint, rate);
		}
#pragma endregion	
	private:

		CtrlPointData* m_centerPointData;
		Point m_start;
		Point m_end;
	};
}