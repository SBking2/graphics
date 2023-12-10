#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class BresenhamLineData :public ShapeData {
	public:
		BresenhamLineData( const Point& start = Point(0, 0), const Point& end = Point(0, 0), int color = 2, int fillType = -1, int fillLength = 1, bool isSolidLine = true)
			:ShapeData(fillType, fillLength, isSolidLine, color) {
			m_start = start;
			m_end = end;
			m_shapeType = ShapeType::BresenhamLine;
			m_centerPointData = new CtrlPointData();
		}
		~BresenhamLineData() {

		}

		virtual void Set(const Point& move) {
			m_end = move;
		}
		void Set(const Point& start, const Point& end) {
			m_start = start;
			m_end = end;
		}

		std::vector<Point> GetDrawPoints() override {
			return Algorithm::BresenhamLining(m_start, m_end);
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}

		//辅助函数，Bezier相关
		void AdjustLine(const Point& start, const Point& end) {
			m_start = start;
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
			Point center = Point((int)((m_start.x + m_end.x) / 2.0 + 0.5), (int)((m_start.y + m_end.y) / 2.0 + 0.5));
			AdjustMyCenter(center);
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
		void Rotation(double angle, const Point& axis) override{
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
		void Scale(double rate, const Point& axis) override{
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::zoom(ctrlPoints, axis, rate);
		}
		void Scale(double rate) override{
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			Algorithm::zoom(ctrlPoints, m_centerPoint, rate);
		}
		#pragma endregion	

	private:
		Point m_start;
		Point m_end;

		//控制点
		CtrlPointData* m_centerPointData;
	};
}