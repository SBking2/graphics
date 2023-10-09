#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class SeedFillData :public ShapeData {
	public:
		SeedFillData(const Point& start = Point(0, 0))
			:ShapeData() {
			m_start = start;
			m_shapeType = ShapeType::SeedFill;
		}
		~SeedFillData() {

		}

		virtual void Set(const Point& move) {
		}

		std::vector<Point> GetDrawPoints() override {
			vector<Point> result = {};
			Algorithm::seedFill(m_start, 's', 'b');
			return result;
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}
	private:
		Point m_start;
	};
}