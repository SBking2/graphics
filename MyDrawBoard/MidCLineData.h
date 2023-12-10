#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class MidCLineData :public ShapeData {
	public:
		MidCLineData(int fillType, int fillLength, bool isSolidLine,const Point& start = Point(0, 0), const Point& end = Point(0, 0),
			const Boarder& boarder = Boarder(0, 0, 0, 0))
			:ShapeData(fillType, fillLength, isSolidLine) {
			m_start = start;
			m_end = end;
			m_boarder = boarder;
			m_shapeType = ShapeType::MidCLine;
			m_centerPointData = new CtrlPointData();
		}
		~MidCLineData() {

		}

		virtual void Set(const Point& move) {
			m_end = move;
		}

		std::vector<Point> GetDrawPoints() override {
			return Algorithm::MidPointClipping(m_start, m_end, m_boarder);
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}

		#pragma region 中心原点相关函数
		//更新中心原点
		void AdjustMyCenter(const Point & centerPoint)override {
			ShapeData::AdjustMyCenter(centerPoint);
			m_centerPointData->AdjustCircle(centerPoint);
		}
		//绘制中心原点
		vector<Point> DrawMyCenter() override {
			Point center = Point(((m_start.x + m_end.x) / 2), ((m_start.y + m_end.y) / 2));
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
		Boarder m_boarder;
	};
}