#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class MidPointCircleData :public ShapeData {
	public:
		MidPointCircleData(const Point& start = Point(0, 0), const Point& end = Point(0, 0))
			:ShapeData() {
			m_start = start;
			m_end = end;
			m_shapeType = ShapeType::MidPointCircle;
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
	private:

		Point m_start;
		Point m_end;
	};
}