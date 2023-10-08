#pragma once
#include"ShapeData.h"
namespace ComputerGraphics {
	class CSCLineData :public ShapeData {
	public:
		CSCLineData(const Point& start = Point(0, 0), const Point& end = Point(0, 0),
			const Boarder & boarder = Boarder(0,0,0,0))
			:ShapeData() {
			m_start = start;
			m_end = end;
			m_boarder = boarder;
			m_shapeType = ShapeType::CSCLine;
		}
		~CSCLineData() {

		}

		virtual void Set(const Point& move) {
			m_end = move;
		}

		std::vector<Point> GetDrawPoints() override {
			return Algorithm::CSClipping(m_start, m_end, m_boarder);
		}
		ShapeType GetShapeType() override {
			return m_shapeType;
		}
	private:

		Point m_start;
		Point m_end;
		Boarder m_boarder;
	};
}