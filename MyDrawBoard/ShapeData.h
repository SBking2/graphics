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
		SeedFill,
		PolyFill,
		Bezier,
		//设置抽心
		SetAxis,
		//控制信号
		BezierCtrl,
		PolyFillCtrl,
		CtrlPoint,
		RotateCtrl,
		//绕着自定点旋转
		RAPCtrl,
		ScaleCtrl,
		//绕着自定点缩放
		SAPCtrl
	};
	class ShapeData {
	public:
		ShapeData(int fillType, int fillLength, bool isSolidLine, int color = 2) {
			m_fillLength = fillLength;
			m_fillType = fillType;
			m_isSolidLine = isSolidLine;
			m_shapeType = ShapeType::Unknown;
			m_centerPoint = Point(0, 0);
			this->color = color;
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
		virtual vector<Point> GetCtrlPoints() {
			std::vector<Point> null;
			return null;
		}

		//图形的中心相关函数
		virtual void AdjustMyCenter(const Point & centerPoint) {
			m_centerPoint = centerPoint;
		}
		virtual vector<Point> DrawMyCenter() {
			vector<Point> result;
			return result;
		}

		//有关图形变换的函数
		 Point GetCenterPoint() {
			return m_centerPoint;
		}

		virtual void Translation(int dff_x, int dff_y) {

		}
		virtual void Rotation(double angle,const Point & axis) {

		}
		virtual void Rotation(double angle) {

		}
		virtual void Scale(double rate, const Point& axis) {

		}
		virtual void Scale(double rate) {

		}

		virtual int GetFillType() {
			return m_fillType;
		}
		virtual int GetFillLength() {
			return m_fillLength;
		}
		virtual bool GetIsSolidLine() {
			return m_isSolidLine;
		}

		int GetColor() {
			return color;
		}
	protected:
		ShapeType m_shapeType;
		Point m_centerPoint;

		bool m_isSolidLine;
		int m_fillType;
		int m_fillLength;

		int color;
	};
}