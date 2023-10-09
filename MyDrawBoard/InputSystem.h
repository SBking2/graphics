#pragma once
#include"ShapeDataCtrlSystem.h"
namespace ComputerGraphics {
	class InputSystem {
	public:
		static InputSystem* getInstance() {
			if (m_instance == nullptr) {
				m_instance = new InputSystem();
			}
			return m_instance;
		}
		~InputSystem() {}
		void MousePress(const Point& start, const ShapeType& currentShape, const Boarder & boarder) {
			switch (currentShape)
			{
			case ShapeType::MidPointLine:
			{
				m_MLisPressed = true;
				MidPointLineData* newLine = new MidPointLineData(start, start);
				m_currentShape = newLine;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
				m_OnPressed = start;
			}
			break;
			case ShapeType::BresenhamLine:
			{
				m_MLisPressed = true;
				BresenhamLineData* newLine = new BresenhamLineData(start, start);
				m_currentShape = newLine;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
				m_OnPressed = start;
			}
			break;
			case ShapeType::MidPointCircle:
			{
				m_MLisPressed = true;
				MidPointCircleData* newCircle = new MidPointCircleData(start, start);
				m_currentShape = newCircle;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newCircle);
				m_OnPressed = start;
			}
			break;
			case ShapeType::CircleArc:
			{
				if (m_isSetCenter) {
					m_isSetCenter = false;
					m_OnPressed = start;
					m_currentShape->SetStart(start);
					m_MLisPressed = true;
					break;
				}

				CircleArcData* newCircle = new CircleArcData(start, start, start);
				m_currentShape = newCircle;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newCircle);
				m_OnPressed = start;
				m_isSetCenter = true;
			}
			break;
			case ShapeType::CSCLine:
			{
				m_MLisPressed = true;
				CSCLineData* newLine = new CSCLineData(start, start, boarder);
				m_currentShape = newLine;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
				m_OnPressed = start;
			}
				break;
			case ShapeType::MidCLine:
			{
				m_MLisPressed = true;
				MidCLineData* newLine = new MidCLineData(start, start, boarder);
				m_currentShape = newLine;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
				m_OnPressed = start;
			}
			break;
			case ShapeType::SeedFill:
			{
				SeedFillData* newLine = new SeedFillData(start);
				m_currentShape = newLine;
				ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
			}
			break;
			case ShapeType::Unknown:
				break;
			default:
				break;
			}
		}

		void MouseMove(const Point& move, const ShapeType& currentShpae) {
			if (m_MLisPressed) {
				if (m_currentShape != nullptr) {
					m_currentShape->Set(move);
				}
				m_OnMoving = move;
			}
		}

		void MouseRelease(const Point& end, const ShapeType& currentShpae) {
			if (m_isSetCenter)
				return;
			if (m_MLisPressed) {
				if (m_currentShape != nullptr) {
					m_currentShape->Set(end);
				}
			}
			m_MLisPressed = false;
			
			ShapeDataCtrlSystem::getInstance()->GetAllShapePoint();
			m_currentShape = nullptr;
			m_OnReleased = end;
		}

		void BackSpace() {
			ShapeDataCtrlSystem::getInstance()->DeleteShapeData();
		}
	private:
		InputSystem() {
			m_MLisPressed = false;

			m_isSetCenter = false;

			m_currentShape = nullptr;

			m_OnPressed = Point(0, 0);

			m_OnMoving = Point(0, 0);

			m_OnReleased = Point(0, 0);
		}
		static InputSystem* m_instance;
		bool m_MLisPressed;

		ShapeData* m_currentShape;
		
		bool m_isSetCenter;

		Point m_OnPressed;

		Point m_OnMoving;

		Point m_OnReleased;
	};
	InputSystem* InputSystem::m_instance = nullptr;
}