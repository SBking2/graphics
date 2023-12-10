#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class SeedFillData :public ShapeData {
	public:
		SeedFillData(const Point& start = Point(0, 0),int color = 2,int fillType = -1, int fillLength = 1, bool isSolidLine = true)
			:ShapeData(fillType, fillLength, isSolidLine, color) {
			m_start = start;
			m_shapeType = ShapeType::SeedFill;
		}
		~SeedFillData() {

		}
		virtual void Set(const Point& move) {
			m_start = move;
		}
		std::vector<Point> GetDrawPoints() override {
			vector<Point> result = {};
			Algorithm::seedFill(m_start,color);
			return result;
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}
	private:
		Point m_start;
	};
}