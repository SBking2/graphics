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
		//��갴��ִ�еĺ���
		void MousePress(const Point& start, const ShapeType& currentShape, const Boarder & boarder) {
			switch (currentShape)
			{
			case ShapeType::MidPointLine:
				{
					m_MLisPressed = true;
					MidPointLineData* newLine = new MidPointLineData(fillType, fillLength, isSolidLine, start, start);
					m_currentShape = newLine;
					ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
					m_OnPressed = start;
				}
				break;
			case ShapeType::BresenhamLine:
				{
					m_MLisPressed = true;
					BresenhamLineData* newLine = new BresenhamLineData(start, start, fillType, fillLength, isSolidLine);
					m_currentShape = newLine;
					ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
					m_OnPressed = start;
				}
				break;
			case ShapeType::MidPointCircle:
				{
					m_MLisPressed = true;
					MidPointCircleData* newCircle = new MidPointCircleData(fillType, fillLength, isSolidLine, start, start);
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

					CircleArcData* newCircle = new CircleArcData(fillType, fillLength, isSolidLine, start, start, start);
					m_currentShape = newCircle;
					ShapeDataCtrlSystem::getInstance()->AddShapeData(newCircle);
					m_OnPressed = start;
					m_isSetCenter = true;
				}
				break;
			case ShapeType::CSCLine:
				{
					m_MLisPressed = true;
					CSCLineData* newLine = new CSCLineData(fillType, fillLength, isSolidLine, start, start, boarder);
					m_currentShape = newLine;
					ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
					m_OnPressed = start;
				}
				break;
			case ShapeType::MidCLine:
				{
					m_MLisPressed = true;
					MidCLineData* newLine = new MidCLineData(fillType, fillLength, isSolidLine, start, start, boarder);
					m_currentShape = newLine;
					ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
					m_OnPressed = start;
				}
				break;
			case ShapeType::SeedFill:
				{
					SeedFillData* newLine = new SeedFillData(start, 2,fillType, fillLength, isSolidLine);
					m_currentShape = newLine;
					ShapeDataCtrlSystem::getInstance()->AddShapeData(newLine);
				}
				break;
			case ShapeType::PolyFill:
				{
					if (isCreatePoly) {
						m_currentPoly->AddCtrlPoint(start);
						break;
					}
					PolyPoints.push_back(start);
					PolyfillData* polyfill = new PolyfillData(PolyPoints, fillType, fillLength, isSolidLine,2);
					ShapeDataCtrlSystem::getInstance()->AddShapeData(polyfill);
					m_currentPoly = polyfill;
					isCreatePoly = true;
				}
				break;
			case ShapeType::Bezier:
				{
				if (isCreateBezier) {
					m_currentBezier->AddCtrlPoint(start);
					break;
					}
					BezierPoints.push_back(start);
					BezierData* bezier = new BezierData(BezierPoints,fillType, fillLength, isSolidLine);
					ShapeDataCtrlSystem::getInstance()->AddShapeData(bezier);
					m_currentBezier = bezier;
					isCreateBezier = true;
				}
				break;
			//�˴�����Bezier���߿���ģʽ
			case ShapeType::BezierCtrl:
				m_currentBezier = ShapeDataCtrlSystem::getInstance()->GetCtrlBezier(start, m_bezierIndex);
				if (m_currentBezier != nullptr) {
					m_currentBezier->SetCtrlPoints(m_bezierIndex, start);
					isBezierCtrl = true;
					//����Bezier���º���
					m_currentBezier->AdjustShape();
				}
				break;
				//�˴��������Ŀ���ģʽ
			case ShapeType::CtrlPoint:
				m_currentCtrlShapeData = ShapeDataCtrlSystem::getInstance()->GetCtrlShape(start);
				if (m_currentCtrlShapeData != nullptr) {
					//TODO:����ͼ��
					isTransformCtrl = true;
				}
				break;
			case ShapeType::RotateCtrl:
				m_currentCtrlShapeData = ShapeDataCtrlSystem::getInstance()->GetCtrlShape(start);
				if (m_currentCtrlShapeData != nullptr) {
					//TODO:����ͼ��
					isRotateCtrl = true;
					m_OnMoving = start;
				}
				break;
			case ShapeType::RAPCtrl:
				m_currentCtrlShapeData = ShapeDataCtrlSystem::getInstance()->GetCtrlShape(start);
				if (m_currentCtrlShapeData != nullptr) {
					//TODO:����ͼ��
					isRAPCtrl = true;
					m_OnMoving = start;
				}
				break;
			case ShapeType::ScaleCtrl:
				m_currentCtrlShapeData = ShapeDataCtrlSystem::getInstance()->GetCtrlShape(start);
				if (m_currentCtrlShapeData != nullptr) {
					//TODO:����ͼ��
					isScaleCtrl = true;
					m_OnMoving = start;
				}
				break;
			case ShapeType::SAPCtrl:
				m_currentCtrlShapeData = ShapeDataCtrlSystem::getInstance()->GetCtrlShape(start);
				if (m_currentCtrlShapeData != nullptr) {
					//TODO:����ͼ��
					isSAPCtrl = true;
					m_OnMoving = start;
				}
				break;
			case ShapeType::SetAxis:
				ShapeDataCtrlSystem::getInstance()->SetAxisPoint(start);
				isSettingAxis = true;
				break;
			//����εĿ���ģʽ
			case ShapeType::PolyFillCtrl:
				m_currentPoly = ShapeDataCtrlSystem::getInstance()->GetCtrlPoly(start, m_polyfillIndex);
				if (m_currentPoly != nullptr) {
					m_currentPoly->SetCtrlPoints(m_polyfillIndex, start);
					isPolyCtrl = true;
					//����Bezier���º���
					m_currentPoly->AdjustShape();
				}
				break;
			case ShapeType::Unknown:
				break;
			default:
				break;
			}
		}
		//����ƶ�ִ�еĺ���
		void MouseMove(const Point& move, const ShapeType& currentShpae) {
			if (isCreateBezier) {
				return;
			}
			if (isCreatePoly) {
				return;
			}
			if (isSettingAxis) {
				ShapeDataCtrlSystem::getInstance()->SetAxisPoint(move);
			}
			if (isTransformCtrl) {
				Point center = m_currentCtrlShapeData->GetCenterPoint();
				Point delta = Point(move.x-center.x, move.y - center.y);
				m_currentCtrlShapeData->Translation(delta.x, delta.y);
				return;
			}
			if (isRotateCtrl) {
				int delta = move.x - m_OnMoving.x;
				double angle = delta*0.01;
				m_currentCtrlShapeData->Rotation(angle);
				m_OnMoving = move;
				return;
			}
			if (isScaleCtrl) {
				int delta = move.x - m_OnMoving.x;
				double rate = delta > 0 ? 1.1 : 0.9;
				m_currentCtrlShapeData->Scale(rate);
				m_OnMoving = move;
				return;
			}
			if (isSAPCtrl) {
				int delta = move.x - m_OnMoving.x;
				double rate = delta > 0 ? 1.1 : 0.9;
				Point axis = ShapeDataCtrlSystem::getInstance()->GetAxisPoint();
				m_currentCtrlShapeData->Scale(rate, axis);
				m_OnMoving = move;
				return;
			}
			if (isRAPCtrl) {
				int delta = move.x - m_OnMoving.x;
				double angle = delta*0.01;
				Point axis = ShapeDataCtrlSystem::getInstance()->GetAxisPoint();
				m_currentCtrlShapeData->Rotation(angle, axis);
				m_OnMoving = move;
				return;
			}
			if (isBezierCtrl) {
				m_currentBezier->SetCtrlPoints(m_bezierIndex, move);
				m_currentBezier->AdjustShape();
			}
			if (isPolyCtrl) {
				m_currentPoly->SetCtrlPoints(m_polyfillIndex, move);
				m_currentPoly->AdjustShape();
			}
			if (m_MLisPressed) {
				if (m_currentShape != nullptr) {
					m_currentShape->Set(move);
				}
				m_OnMoving = move;
			}
		}
		//����ɿ�ִ�еĺ���
		void MouseRelease(const Point& end, const ShapeType& currentShpae) {
			if (isCreateBezier) {
				return;
			}
			if (isCreatePoly) {
				return;
			}
			if (isSettingAxis) {
				isSettingAxis = false;
			}
			if (isBezierCtrl) {
				m_bezierIndex = -1;
				m_currentBezier = nullptr;
				isBezierCtrl = false;
			}
			if (isPolyCtrl) {
				m_polyfillIndex = -1;
				m_currentPoly = nullptr;
				isPolyCtrl = false;
			}
			//ƽ���ź�����
			if (isTransformCtrl) {
				isTransformCtrl = false;
			}
			//��ת�ź�����
			if (isRotateCtrl) {
				isRotateCtrl = false;
			}
			if (isRAPCtrl) {
				isRAPCtrl = false;
			}
			///�����ź�����
			if (isScaleCtrl) {
				isScaleCtrl = false;
			}
			if (isSAPCtrl) {
				isSAPCtrl = false;
			}
			//
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
		void Poly() {
			PolyPoints.clear();
			isCreatePoly = false;
		}
		void Bezier() {
			BezierPoints.clear();
			isCreateBezier = false;
		}

		void Rotation(double angle) {
			if (m_currentCtrlShapeData != nullptr) {
				m_currentCtrlShapeData->Rotation(angle);
			}
		}
		void Scale(double rate) {
			if (m_currentCtrlShapeData != nullptr) {
				m_currentCtrlShapeData->Scale(rate);
			}
		}
		void BackSpace() {
			ShapeDataCtrlSystem::getInstance()->DeleteShapeData();
		}

		void ResetInputSystem() {
			isPolyCtrl = false;
			m_MLisPressed = false;
			m_isSetCenter = false;
			m_currentShape = nullptr;
			m_currentBezier = nullptr;
			m_currentPoly = nullptr;
			m_OnPressed = Point(0, 0);
			m_OnMoving = Point(0, 0);
			m_OnReleased = Point(0, 0);
			isBezierCtrl = false;
			m_bezierIndex = -1;
			m_polyfillIndex = -1;
			isTransformCtrl = false;
			isRotateCtrl = false;
			isSettingAxis = false;
			isRAPCtrl = false;
			isCreateBezier = false;
			isCreatePoly = false;
			PolyPoints.clear();
			BezierPoints.clear();
			isScaleCtrl = false;
			isSAPCtrl = false;
		}
		void Clear() {
			PolyPoints.clear();
			BezierPoints.clear();
			isPolyCtrl = false;
			m_MLisPressed = false;
			m_isSetCenter = false;
			m_currentShape = nullptr;
			m_currentBezier = nullptr;
			m_currentCtrlShapeData = nullptr;
			m_currentPoly = nullptr;
			m_OnPressed = Point(0, 0);
			m_OnMoving = Point(0, 0);
			m_OnReleased = Point(0, 0);
			isBezierCtrl = false;
			m_bezierIndex = -1;
			m_polyfillIndex = -1;
			isTransformCtrl = false;
			isRotateCtrl = false;
			isSettingAxis = false;
			isRAPCtrl = false;
			isCreateBezier = false;
			isCreatePoly = false;

			isScaleCtrl = false;
			isSAPCtrl = false;
		}

		void SetFillType(int x) {
			fillType = x;
		}
		void SetFillLength(int length) {
			if (length >= 1) {
				fillLength = length;
			}
			else {

			}
		}
		void SetLineType(bool value) {
			isSolidLine = value;
		}
	private:
		InputSystem() {
			isPolyCtrl = false;
			m_MLisPressed = false;
			m_isSetCenter = false;
			m_currentShape = nullptr;
			m_currentBezier = nullptr;
			m_currentCtrlShapeData = nullptr;
			m_currentPoly = nullptr;
			m_OnPressed = Point(0, 0);
			m_OnMoving = Point(0, 0);
			m_OnReleased = Point(0, 0);
			isBezierCtrl = false;
			m_bezierIndex = -1;
			m_polyfillIndex = -1;
			isTransformCtrl = false;
			isRotateCtrl = false;
			isSettingAxis = false;
			isRAPCtrl = false;
			isCreateBezier = false;
			isCreatePoly = false;

			isScaleCtrl = false;
			isSAPCtrl = false;
		}
		static InputSystem* m_instance;
		bool m_MLisPressed;
		ShapeData* m_currentShape;	
		bool m_isSetCenter;
		Point m_OnPressed;
		Point m_OnMoving;
		vector<Point> PolyPoints;
		vector<Point> BezierPoints;
		Point m_OnReleased;
		//���ƶ����
		bool isCreatePoly;

		//���������
		bool isCreateBezier;
		BezierData* m_currentBezier;
		PolyfillData* m_currentPoly;
		ShapeData* m_currentCtrlShapeData;
		int m_bezierIndex;
		int m_polyfillIndex;

		//�任���
		bool isRotateCtrl;
		bool isTransformCtrl;
		bool isBezierCtrl;
		bool isSettingAxis;
		bool isRAPCtrl;

		bool isPolyCtrl;
		bool isScaleCtrl;
		bool isSAPCtrl;

		int fillType;
		int fillLength;
		bool isSolidLine;

	};
	InputSystem* InputSystem::m_instance = nullptr;
}