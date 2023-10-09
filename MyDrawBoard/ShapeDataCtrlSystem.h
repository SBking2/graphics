#pragma once
#include "MidPointLineData.h"
#include"BresenhamLineData.h"
#include"MidPointCircleData.h"
#include"CircleArcData.h"
#include"CSCLineData.h"
#include"MidCLineData.h"
#include"SeedFillData.h"
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
		std::vector<Point> GetDrawPoints() {
		   return m_shapeData->GetDrawPoints();
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

		std::vector<Point> GetAllShapePoint() {

			for (int i = 0; i < CANVASLENGTH; i++) {
				for (int j = 0; j < CANVASLENGTH; j++) {
					canvas[i][j] = 0;
				}
			}

			std::vector<Point> allPoints;
			if (m_tailNode == nullptr) {
				return allPoints;
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
			allPoints = DIGUIGetPoints(p);

			return allPoints;
		}
	private:
		ShapeDataCtrlSystem() {
			m_tailNode = nullptr;
			m_shapeCount = 0;
			canvas = new int* [CANVASLENGTH];
			for (int i = 0; i < CANVASLENGTH; i++) {
				canvas[i] = new int[CANVASLENGTH];
				for (int j = 0; j < CANVASLENGTH; j++) {
					canvas[i][j] = 0;
				}
			}
		}
		//递归函数
		vector<Point> DIGUIGetPoints(ShapeDataNode* p) {
			vector<Point> result{};
			if (p == nullptr)
				return result;
			vector<Point> tail = DIGUIGetPoints(p->next);
			result = p->GetDrawPoints();
			for (int i = 0; i < result.size(); i++) {
				canvas[result[i].x][result[i].y] = 1;
			}
			result.insert(result.end(), tail.begin(), tail.end());
			return result;
		}

		static ShapeDataCtrlSystem* m_instance;

		
		int m_shapeCount;
		ShapeDataNode* m_tailNode;
	};
	ShapeDataCtrlSystem* ShapeDataCtrlSystem::m_instance = nullptr;
}