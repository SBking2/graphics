#pragma once
#include"CtrlPointData.h"
#include "MidPointLineData.h"
#include"BresenhamLineData.h"
#include"MidPointCircleData.h"
#include"CircleArcData.h"
#include"CSCLineData.h"
#include"MidCLineData.h"
#include"SeedFillData.h"
#include"PolyFillData.h"
#include"BezierData.h"
namespace ComputerGraphics {

	class ShapeDataNode {
	public:
		ShapeDataNode(ShapeData* shapeData = nullptr) {
			m_shapeData = shapeData;
			next = nullptr;
		}
		ShapeType GetShapeType() {
			return m_shapeData->GetShapeType();
		}
		vector<Point> GetDrawPoints() {
		   return m_shapeData->GetDrawPoints();
		}
		vector<Point> DrawMyCenter() {
			return m_shapeData->DrawMyCenter();
		}
		ShapeData* GetShapeData() {
			return m_shapeData;
		}
		ShapeDataNode* next;
	private:
		ShapeData* m_shapeData;
	};
	class ShapeDataCtrlSystem {
	public:

		static ShapeDataCtrlSystem* getInstance() {
			if (m_instance == nullptr) {
				m_instance = new ShapeDataCtrlSystem();
			}
			return m_instance;
		}
		~ShapeDataCtrlSystem() {
			//Need Use to
			if (m_shapeCount == 0) {
				m_tailNode = nullptr;
				return;
			}
			ShapeDataNode* p = m_tailNode;
			while (p != nullptr) {
				m_tailNode = m_tailNode->next;
				delete p;
				p = m_tailNode;
			}
		}

		void AddShapeData(ShapeData* shapeData) {
			ShapeDataNode* newShapeNode = new ShapeDataNode(shapeData);
			if (m_tailNode == nullptr) {
				m_tailNode = newShapeNode;
			}
			else {
				newShapeNode->next = m_tailNode;
				m_tailNode = newShapeNode;
			}
			m_shapeCount++;
		}
		void DeleteShapeData() {
			if (m_tailNode == nullptr) {
				return;
			}
			ShapeDataNode* p = m_tailNode;
			m_tailNode = m_tailNode->next;
			m_shapeCount--;
			delete p;
		}

		int GetShapeCount() {
			return m_shapeCount;
		}


		//绘制所有图形的函数
		void GetAllShapePoint() {

			for (int i = 0; i < CANVASLENGTH; i++) {
				for (int j = 0; j < CANVASLENGTH; j++) {
					//Debug
					canvas[i][j] = 0;
					CtrlLayerCanvas[i][j] = 0;
				}
			}

			std::vector<Point> allPoints{};
			if (m_tailNode == nullptr) {
				return;
			}

			//根据栈的顺序获取点,注意此处需要先把点加到画布上，否则填充获取不到点
			ShapeDataNode* p = m_tailNode;
			/*while (p != nullptr) {
				std::vector<Point> back = p->GetDrawPoints();
				for (int i = 0; i < back.size(); i++) {
					canvas[back[i].x][back[i].y] = 1;
				}
				allPoints.insert(allPoints.end(), back.begin(), back.end());
				p = p->next;
			}*/

			//根据递归绘制
			DIGUIGetPoints(p);

			//仅绘制当前点
			//allPoints = m_tailNode->GetDrawPoints();
			//for (int i = 0; i < allPoints.size(); i++) {
			//	if (allPoints[i].x >= 0 && allPoints[i].y >= 0)
			//		copyCanvas[allPoints[i].x][allPoints[i].y] = 1;


			//	//for (int radius = 1; radius <= Length; radius++) {
			//	//	int x = 0, y = radius, e = 1 - radius;//圆形
			//	//	copyCanvas[allPoints[i].x + x][allPoints[i].y + y] = 1;
			//	//	copyCanvas[allPoints[i].x - x][allPoints[i].y - y] = 1;
			//	//	copyCanvas[allPoints[i].x - x][allPoints[i].y + y] = 1;
			//	//	copyCanvas[allPoints[i].x + x][allPoints[i].y - y] = 1;
			//	//	copyCanvas[allPoints[i].x + y][allPoints[i].y + x] = 1;
			//	//	copyCanvas[allPoints[i].x - y][allPoints[i].y - x] = 1;
			//	//	copyCanvas[allPoints[i].x - y][allPoints[i].y + x] = 1;
			//	//	copyCanvas[allPoints[i].x + y][allPoints[i].y - x] = 1;
			//	//	while (x <= y)
			//	//	{
			//	//		if (e < 0)
			//	//			e += 2 * x + 3;
			//	//		else
			//	//		{
			//	//			e += 2 * (x - y) + 5;
			//	//			y--;
			//	//		}
			//	//		x++;
			//	//		copyCanvas[allPoints[i].x + x][allPoints[i].y + y] = 1;
			//	//		copyCanvas[allPoints[i].x - x][allPoints[i].y - y] = 1;
			//	//		copyCanvas[allPoints[i].x - x][allPoints[i].y + y] = 1;
			//	//		copyCanvas[allPoints[i].x + x][allPoints[i].y - y] = 1;
			//	//		copyCanvas[allPoints[i].x + y][allPoints[i].y + x] = 1;
			//	//		copyCanvas[allPoints[i].x - y][allPoints[i].y - x] = 1;
			//	//		copyCanvas[allPoints[i].x - y][allPoints[i].y + x] = 1;
			//	//		copyCanvas[allPoints[i].x + y][allPoints[i].y - x] = 1;

			//	//	}
			//	//}
			//}
			//绘制控制点
			/*allPoints = m_tailNode->DrawMyCenter();
			for (int i = 0; i < allPoints.size(); i++) {
				if(allPoints[i].x>=0&& allPoints[i].y>=0)
					CtrlLayerCanvas[allPoints[i].x][allPoints[i].y] = 2;
			}*/

			//绘制轴心
			if (isDrawCtrlPoint) {
				m_axisPointData->AdjustCircle(m_axis);
				allPoints = m_axisPointData->GetDrawPoints();
				for (int i = 0; i < allPoints.size(); i++) {
					if (allPoints[i].x >= 0 && allPoints[i].y >= 0 && allPoints[i].x < CANVASLENGTH && allPoints[i].y < CANVASLENGTH)
						CtrlLayerCanvas[allPoints[i].x][allPoints[i].y] = 3;
				}
			}

			return;
		}

		//获取当前控制的贝塞尔曲线指针
		BezierData* GetCtrlBezier(const Point& clickPoint, int & index) {
			ShapeDataNode* p = m_tailNode;
			while (p != nullptr) {
				if (p->GetShapeType() == ShapeType::Bezier) {
					vector<Point> points = p->GetShapeData()->GetCtrlPoints();
					for (int i = 0; i < points.size(); i++) {
						if (GetDistance(clickPoint, points[i]) <= PR) {
							index = i;
							BezierData* bezier = dynamic_cast<BezierData*>(p->GetShapeData());
							return bezier;
						}
					}
				}
				p = p->next;
			}
			return nullptr;
		}

		//获取当前控制的多边形矩阵指针
		PolyfillData* GetCtrlPoly(const Point& clickPoint, int& index) {
			ShapeDataNode* p = m_tailNode;
			while (p != nullptr) {
				if (p->GetShapeType() == ShapeType::PolyFill) {
					vector<Point> points = p->GetShapeData()->GetCtrlPoints();
					for (int i = 0; i < points.size(); i++) {
						if (GetDistance(clickPoint, points[i]) <= PR) {
							index = i;
							PolyfillData* polyfill = dynamic_cast<PolyfillData*>(p->GetShapeData());
							return polyfill;
						}
					}
				}
				p = p->next;
			}
			return nullptr;
		}

		//获取当前控制的图形
		ShapeData* GetCtrlShape(const Point& clickPoint) {
			ShapeDataNode* p = m_tailNode;
			while (p != nullptr) {
				Point centerPoint = p->GetShapeData()->GetCenterPoint();
				if (GetDistance(clickPoint, centerPoint) <= PR) {
					return p->GetShapeData();
				}
				p = p->next;
			}
			return nullptr;
		}

		void ChangeDrawMode() {
			isDrawCtrlPoint = !isDrawCtrlPoint;
		}
		//获取控制点
		Point GetAxisPoint() {
			return m_axis;
		}
		void SetAxisPoint(Point point) {
			m_axis = point;
		}

		void Clear() {
			ShapeDataNode* p;
			while (m_tailNode != nullptr) {
				p = m_tailNode;
				m_tailNode = m_tailNode->next;
				delete p;
			}
			m_tailNode = nullptr;
		}



	private:
		ShapeDataCtrlSystem() {

			m_axis = Point(0, 0);
			m_tailNode = nullptr;
			m_shapeCount = 0;
			m_axisPointData = new CtrlPointData(m_axis);
			canvas = new int* [CANVASLENGTH];
			for (int i = 0; i < CANVASLENGTH; i++) {
				canvas[i] = new int[CANVASLENGTH];
				for (int j = 0; j < CANVASLENGTH; j++) {
					canvas[i][j] = 0;
				}
			}

			CtrlLayerCanvas = new int* [CANVASLENGTH];
			for (int i = 0; i < CANVASLENGTH; i++) {
				CtrlLayerCanvas[i] = new int[CANVASLENGTH];
				for (int j = 0; j < CANVASLENGTH; j++) {
					CtrlLayerCanvas[i][j] = 0;
				}
			}

			isDrawCtrlPoint = true;
		}

		//辅助函数，求两点距离
		int GetDistance(const Point& p1, const Point& p2) {
			int x = p1.x - p2.x;
			int y = p1.y - p2.y;
			int distance = sqrt(x * x + y * y);
			return distance;
		}

		//递归函数
		void DIGUIGetPoints(ShapeDataNode* p) {
			vector<Point> result{};
			if (p == nullptr)
				return;
			DIGUIGetPoints(p->next);
			result = p->GetDrawPoints();
			//绘制图形点
			if (p->GetShapeData()->GetIsSolidLine()) {
				
			}
			else {
				result = Algorithm::VirtualLine(result);
			}
			int length = p->GetShapeData()->GetFillLength();
			if (length != 1) {
				result = Algorithm::cubeWidth(result, p->GetShapeData()->GetFillLength());
			}
			int color = p->GetShapeData()->GetColor();
			for (int i = 0; i < result.size(); i++) {
				if (result[i].x >= 0 && result[i].y >= 0 && result[i].x < CANVASLENGTH && result[i].y < CANVASLENGTH) {
					canvas[result[i].x][result[i].y] = color;
				}
			}
			//绘制控制点
			if (isDrawCtrlPoint) {
				result = p->DrawMyCenter();
				for (int i = 0; i < result.size(); i++) {
					if (result[i].x >= 0 && result[i].y >= 0 && result[i].x < CANVASLENGTH && result[i].y < CANVASLENGTH)
						CtrlLayerCanvas[result[i].x][result[i].y] = 2;
				}
			}
		}

		static ShapeDataCtrlSystem* m_instance;

		Point m_axis;

		CtrlPointData* m_axisPointData;
		
		int m_shapeCount;
		ShapeDataNode* m_tailNode;

		bool isDrawCtrlPoint;

	};
	ShapeDataCtrlSystem* ShapeDataCtrlSystem::m_instance = nullptr;
}