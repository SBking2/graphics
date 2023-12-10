#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class CircleArcData :public ShapeData {
	public:
		CircleArcData(int fillType, int fillLength, bool isSolidLine, const Point & center = Point(0,0), const Point& start = Point(0, 0), const Point& end = Point(0, 0))
			:ShapeData(fillType, fillLength, isSolidLine) {
			m_center = center;
			m_start = start;
			m_end = end;
			m_shapeType = ShapeType::CircleArc;

			m_centerPointData = new CtrlPointData();
		}
		~CircleArcData() {

		}

		virtual void Set(const Point& move) {
			m_end = move;
		}

		void SetStart(const Point& s) override {
			m_start = s;
		}
		

		std::vector<Point> GetDrawPoints() override {
			return Algorithm::CircleArc(m_center, m_start, m_end);
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}

		#pragma region ����ԭ����غ���
		//��������ԭ��
		void AdjustMyCenter(const Point& centerPoint)override {
			ShapeData::AdjustMyCenter(centerPoint);
			m_centerPointData->AdjustCircle(centerPoint);
		}
		//��������ԭ��
		vector<Point> DrawMyCenter() override {
			AdjustMyCenter(m_center);
			return m_centerPointData->GetDrawPoints();
		}
#pragma endregion

		#pragma region ͼ�α任��غ���
		void Translation(int dff_x, int dff_y)override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			ctrlPoints.push_back(&m_center);
			Algorithm::translation(ctrlPoints, dff_x, dff_y);
		}
		void Rotation(double angle, const Point& axis) override{
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			ctrlPoints.push_back(&m_center);
			Algorithm::rotate(ctrlPoints, angle, axis);
		}
		void Rotation(double angle) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			ctrlPoints.push_back(&m_center);
			Algorithm::rotate(ctrlPoints, angle, m_centerPoint);
		}
		void Scale(double rate, const Point& axis) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			ctrlPoints.push_back(&m_center);
			Algorithm::zoom(ctrlPoints, axis, rate);
		}
		void Scale(double rate) override {
			vector<Point*> ctrlPoints;
			ctrlPoints.push_back(&m_start);
			ctrlPoints.push_back(&m_end);
			ctrlPoints.push_back(&m_center);
			Algorithm::zoom(ctrlPoints, m_centerPoint, rate);
		}
#pragma endregion	
	private:

		Point m_center;
		Point m_start;
		Point m_end;

		//���Ƶ�
		CtrlPointData* m_centerPointData;
	};
}