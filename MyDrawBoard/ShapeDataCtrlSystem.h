#pragma once
#include "MidPointLineData.h"
#include"BresenhamLineData.h"
#include"MidPointCircleData.h"
#include"CircleArcData.h"
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
			std::vector<Point> allPoints;
			if (m_tailNode == nullptr) {
				return allPoints;
			}
			ShapeDataNode* p = m_tailNode;
			while (p != nullptr) {
				std::vector<Point> back = p->GetDrawPoints();
				allPoints.insert(allPoints.end(), back.begin(), back.end());
				p = p->next;
			}
			return allPoints;
		}
	private:
		ShapeDataCtrlSystem() {
			m_tailNode = nullptr;
			m_shapeCount = 0;
		}
		static ShapeDataCtrlSystem* m_instance;
		//
		int m_shapeCount;
		ShapeDataNode* m_tailNode;
	};
	ShapeDataCtrlSystem* ShapeDataCtrlSystem::m_instance = nullptr;
}