#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class CircleArcData :public ShapeData {
	public:
		CircleArcData(const Point & center = Point(0,0), const Point& start = Point(0, 0), const Point& end = Point(0, 0))
			:ShapeData() {
			m_center = center;
			m_start = start;
			m_end = end;
			m_shapeType = ShapeType::CircleArc;
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
	private:

		Point m_center;
		Point m_start;
		Point m_end;
	};
}