#pragma once
#include "algorithm.h"
namespace ComputerGraphics {
	enum class ShapeType
	{
		Unknown,
		BresenhamLine,
		MidPointLine,
		MidPointCircle,
		CircleArc,
		CSCLine,
		MidCLine,
		SeedFill
	};
	class ShapeData {
	public:
		ShapeData() {
			m_shapeType = ShapeType::Unknown;
		}
		~ShapeData() {}

		virtual void Set(const Point & move){}
		virtual void SetStart(const Point & s){}
		virtual ShapeType GetShapeType() {
			return m_shapeType;
		}
		//
		virtual std::vector<Point> GetDrawPoints() {
			std::vector<Point> null;
			return null;
		}
	protected:
		ShapeType m_shapeType;
	};
}