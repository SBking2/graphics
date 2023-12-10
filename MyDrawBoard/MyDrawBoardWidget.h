#pragma once
#include "MyUIList.h"
#include "MyDrawArea.h"
#include <QKeyEvent>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include<qDebug>
namespace ComputerGraphics {
	class MyDrawBoardWidget : public QWidget {
	public:
		//Get the only one Instance
		static MyDrawBoardWidget* getDrawBoardInstance() {
			if (m_instance == nullptr) {
				m_instance = new MyDrawBoardWidget();
			}
			return m_instance;
		}

		~MyDrawBoardWidget() {
			//QWidget::~QWidget();???难道是由基类析构掉了？
			delete m_instance;
		}

		//Singleton can't be valued and copied
		MyDrawBoardWidget(MyDrawBoardWidget& other) = delete;
		void operator = (const MyDrawBoardWidget&) = delete;
		

		void keyPressEvent(QKeyEvent* event) override {
			if (event->key() == Qt::Key_Z) {
				InputSystem::getInstance()->BackSpace();
			}
			update();
			m_drawArea.update();
			QWidget::keyPressEvent(event);
		}
		void paintEvent(QPaintEvent* event) override {
			m_leftUIList.updateSelectedAllButton(m_drawArea.getShapeType());
			m_leftUIList2.updateSelectedAllButton(m_drawArea.getShapeType());
			QWidget::paintEvent(event);
		}
		void resizeEvent(QResizeEvent* event) override {
			m_leftUIList.DrawButtons();
			m_leftUIList2.DrawButtons();
			m_drawArea.setGeometry();
			QWidget::resizeEvent(event);
		}

		#pragma region Button Function
		void button_MidPointLine() {
			m_drawArea.SetShapeType(ShapeType::MidPointLine);
			m_drawArea.ResetInputSystem();
		}
		void button_BresenhamLine() {
			m_drawArea.SetShapeType(ShapeType::BresenhamLine);
			m_drawArea.ResetInputSystem();
		}
		void button_MidPointCircle() {
			m_drawArea.SetShapeType(ShapeType::MidPointCircle);
			m_drawArea.ResetInputSystem();
		}
		void button_CircleArc() {
			m_drawArea.SetShapeType(ShapeType::CircleArc);
			m_drawArea.ResetInputSystem();
		}
		void button_CSCLine() {
			m_drawArea.SetShapeType(ShapeType::CSCLine);
			m_drawArea.ResetInputSystem();
		}
		void button_MidCLine() {
			m_drawArea.SetShapeType(ShapeType::MidCLine);
			m_drawArea.ResetInputSystem();
		}
		void button_SeedFill() {
			m_drawArea.SetShapeType(ShapeType::SeedFill);
			m_drawArea.ResetInputSystem();
		}
		void button_PolyFill() {
			m_drawArea.SetShapeType(ShapeType::PolyFill);
			m_drawArea.ResetInputSystem();
		}
		void button_Bezier() {
			m_drawArea.SetShapeType(ShapeType::Bezier);
			m_drawArea.ResetInputSystem();
		}
		void button_BezierCtrl() {
			m_drawArea.SetShapeType(ShapeType::BezierCtrl);
			m_drawArea.ResetInputSystem();
		}
		void button_CtrlPoint() {
			m_drawArea.SetShapeType(ShapeType::CtrlPoint);
			m_drawArea.ResetInputSystem();
		}
		void button_RotationControl() {
			m_drawArea.SetShapeType(ShapeType::RotateCtrl);
			m_drawArea.ResetInputSystem();
		}
		void button_RAPCtrl() {
			m_drawArea.SetShapeType(ShapeType::RAPCtrl);
			m_drawArea.ResetInputSystem();
		}
		void button_SetAxis() {
			m_drawArea.SetShapeType(ShapeType::SetAxis);
			m_drawArea.ResetInputSystem();
		}
		void button_ScaleCtrl() {
			m_drawArea.SetShapeType(ShapeType::ScaleCtrl);
			m_drawArea.ResetInputSystem();
		}
		void button_SAPCtrl() {
			m_drawArea.SetShapeType(ShapeType::SAPCtrl);
			m_drawArea.ResetInputSystem();
		}
		void button_PolyCtrl() {
			m_drawArea.SetShapeType(ShapeType::PolyFillCtrl);
			m_drawArea.ResetInputSystem();
		}
		#pragma endregion
		#pragma region ValueChange Function
		void SetBoarder() {
			m_drawArea.SetBoarder(m_leftBoard->value(), m_rightBoard->value(), m_bottomBoard->value(), m_topBoard->value());
			m_drawArea.ResetInputSystem();
		}
		void Rotation() {
			m_drawArea.Rotation(m_rotation->value());
			m_drawArea.ResetInputSystem();
		}
		void Scale() {
			m_drawArea.Scale(m_scale->value());
			m_drawArea.ResetInputSystem();
		}
		void ChangeDrawMode() {
			m_drawArea.ChangeDrawMode();
			m_drawArea.ResetInputSystem();
		}
		void CreateBezier() {
			InputSystem::getInstance()->Bezier();
		}
		void CreatePolyFill() {
			InputSystem::getInstance()->Poly();
		}
		void Clear() {
			m_drawArea.Clear();
			m_drawArea.ResetInputSystem();
		}
		void ChangeLineToVirtual() {
			m_drawArea.SetLineType(false);
			m_drawArea.ResetInputSystem();
		}
		void ChangeLineToSolid() {
			m_drawArea.SetLineType(true);
			m_drawArea.ResetInputSystem();
		}
		void ChangeLineWidth() {
			m_drawArea.SetFillLength(m_lineWidth->value());
			m_drawArea.ResetInputSystem();
		}
		#pragma endregion



	private:
		MyDrawBoardWidget(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
			setWindowTitle(QStringLiteral("Draw Board"));

			//Button UIList 初始化
			m_leftUIList.SetButtonSize(100);
			m_leftUIList.SetIconSize(60);

			m_leftUIList2.SetButtonSize(100);
			m_leftUIList2.SetIconSize(60);
			m_leftUIList2.setPosition(105, 0, 80, 400);

			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/StraightLine.png"))
				, QString("MidPoint Line"), QString("Line Button"), this, &MyDrawBoardWidget::button_MidPointLine
			, ShapeType::MidPointLine);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/StraightLine.png"))
				, QString("Bresenham Line"), QString("Line Button"), this, &MyDrawBoardWidget::button_BresenhamLine
			, ShapeType::BresenhamLine);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/Circle.png"))
				, QString("MidPoint Circle"), QString("Circle Button"), this, &MyDrawBoardWidget::button_MidPointCircle
				, ShapeType::MidPointCircle);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/line2arc.png"))
				, QString("Circle Arc"), QString("Circle Button"), this, &MyDrawBoardWidget::button_CircleArc
				, ShapeType::CircleArc);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/StraightLine.png"))
				, QString("CSC Line"), QString("CSC Line Button"), this, &MyDrawBoardWidget::button_CSCLine
				, ShapeType::CSCLine);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/translation.png"))
				, QString("Transform Ctrl"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_CtrlPoint
				, ShapeType::CtrlPoint);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/Axis.png"))
				, QString("Set Axis"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_SetAxis
				, ShapeType::SetAxis);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/Scale.png"))
				, QString("Scale"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_ScaleCtrl
				, ShapeType::ScaleCtrl);
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/PolyCtrl.png"))
				, QString("PolyFillCtrl"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_PolyCtrl
				, ShapeType::PolyFillCtrl);
			
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/StraightLine.png"))
				, QString("MidC Line"), QString("Mid Line Button"), this, &MyDrawBoardWidget::button_MidCLine
				, ShapeType::MidCLine);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/Fill.png"))
				, QString("Seed Fill"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_SeedFill
				, ShapeType::SeedFill);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/Poly.png"))
				, QString("Ploy Fill"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_PolyFill
				, ShapeType::PolyFill);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/Bezier.png"))
				, QString("Bezier"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_Bezier
				, ShapeType::Bezier);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/BezierCtrl.png"))
				, QString("Bezier Ctrl"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_BezierCtrl
				, ShapeType::BezierCtrl);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/rotate.png"))
				, QString("Rotate Ctrl"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_RotationControl
				, ShapeType::RotateCtrl);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/RotationAroundPoint.png"))
				, QString("RAP Ctrl"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_RAPCtrl
				, ShapeType::RAPCtrl);
			m_leftUIList2.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/SAP.png"))
				, QString("SAP Ctrl"), QString("Seed Fill Button"), this, &MyDrawBoardWidget::button_SAPCtrl
				, ShapeType::SAPCtrl);

			//变换输入框初始化
			QLabel* rotationLable = new QLabel("Rotation", this);
			rotationLable->setGeometry(220, 5, 72, 24);
			m_rotation = new QDoubleSpinBox(this);
			m_rotation->setGeometry(280, 5, 64, 24);
			m_rotation->setRange(0, 9999);


			QLabel* scaleLable = new QLabel("Scale", this);
			scaleLable->setGeometry(360, 5, 72, 24);
			m_scale = new QDoubleSpinBox(this);
			m_scale->setGeometry(395, 5, 64, 24);
			m_scale->setRange(0, 9999);

			//旋转确定按钮
			QToolButton* RotationButton = new QToolButton(this);
			RotationButton->setText("Rotation");
			RotationButton->setGeometry(465, 5, 100, 25);
			QObject::connect(RotationButton, &QToolButton::clicked, this, &MyDrawBoardWidget::Rotation, Qt::ConnectionType::DirectConnection);

			//缩放确定按钮
			QToolButton* ScaleButton = new QToolButton(this);
			ScaleButton->setText("Scale");
			ScaleButton->setGeometry(570, 5, 100, 25);
			QObject::connect(ScaleButton, &QToolButton::clicked, this, &MyDrawBoardWidget::Scale, Qt::ConnectionType::DirectConnection);

			//贝塞尔确定按钮
			QToolButton* BezierButton = new QToolButton(this);
			BezierButton->setText("CreateBezier");
			BezierButton->setGeometry(675, 5, 100, 25);
			QObject::connect(BezierButton, &QToolButton::clicked, this, &MyDrawBoardWidget::CreateBezier, Qt::ConnectionType::DirectConnection);


			//多边形确定按钮
			QToolButton* PolyFillButton = new QToolButton(this);
			PolyFillButton->setText("CreatePoly");
			PolyFillButton->setGeometry(780, 5, 100, 25);
			QObject::connect(PolyFillButton, &QToolButton::clicked, this, &MyDrawBoardWidget::CreatePolyFill, Qt::ConnectionType::DirectConnection);

			//更改渲染模式按钮
			QToolButton* CDMButton = new QToolButton(this);
			CDMButton->setText("ChangeDrawMode");
			CDMButton->setGeometry(885, 5, 120, 25);
			QObject::connect(CDMButton, &QToolButton::clicked, this, &MyDrawBoardWidget::ChangeDrawMode, Qt::ConnectionType::DirectConnection);

			//Reset绘画板
			QToolButton* ResetButton = new QToolButton(this);
			ResetButton->setText("Reset");
			ResetButton->setGeometry(1010, 5, 120, 25);
			QObject::connect(ResetButton, &QToolButton::clicked, this, &MyDrawBoardWidget::Clear, Qt::ConnectionType::DirectConnection);

			//输入框初始化
			QLabel* leftLable = new QLabel("left Boarder",this);
			leftLable->setGeometry(220, 50, 72, 24);
			m_leftBoard = new QSpinBox(this);
			m_leftBoard->setGeometry(300, 50, 64, 24);
			m_leftBoard->setRange(0, 9999);


			QLabel* rightLable = new QLabel("right Boarder", this);
			rightLable->setGeometry(380, 50, 72, 32);
			m_rightBoard = new QSpinBox(this);
			m_rightBoard->setGeometry(460, 50, 64, 24);
			m_rightBoard->setRange(0, 9999);


			QLabel* buttonLable = new QLabel("button Boarder", this);
			buttonLable->setGeometry(540, 50, 72, 24);
			m_bottomBoard = new QSpinBox(this);
			m_bottomBoard->setGeometry(620, 50, 64, 24);
			m_bottomBoard->setRange(0, 9999);
			

			QLabel* topLable = new QLabel("top Boarder", this);
			topLable->setGeometry(700, 50, 72, 24);
			m_topBoard = new QSpinBox(this);
			m_topBoard->setGeometry(780, 50, 64, 24);
			m_topBoard->setRange(0, 9999);


			//确定按钮
			QToolButton* button = new QToolButton(this);
			button->setText("Apply Change!");
			button->setGeometry(420, 80, 150, 30);
			QObject::connect(button, &QToolButton::clicked, this, &MyDrawBoardWidget::SetBoarder, Qt::ConnectionType::DirectConnection);

			QLabel* lineWidth = new QLabel("Line Width", this);
			lineWidth->setGeometry(850, 50, 80, 24);

			//线宽输入框初始化
			m_lineWidth = new QSpinBox(this);
			m_lineWidth->setGeometry(950, 50, 64, 24);

			m_lineWidth->setValue(1);

			//修改线宽按钮
			QToolButton* LineWidthButton = new QToolButton(this);
			LineWidthButton->setText("Change Line Width");
			LineWidthButton->setGeometry(1020, 47, 180, 30);
			QObject::connect(LineWidthButton, &QToolButton::clicked, this, &MyDrawBoardWidget::ChangeLineWidth, Qt::ConnectionType::DirectConnection);

			QLabel* lineType = new QLabel("Line Type", this);
			lineType->setGeometry(1220, 50, 72, 24);

			//实线按钮
			QToolButton* SolidLineButton = new QToolButton(this);
			SolidLineButton->setText("Solid");
			SolidLineButton->setGeometry(1300, 40, 70, 70);
			QObject::connect(SolidLineButton, &QToolButton::clicked, this, &MyDrawBoardWidget::ChangeLineToSolid, Qt::ConnectionType::DirectConnection);

			//虚线按钮
			QToolButton* VirtualLineButton = new QToolButton(this);
			VirtualLineButton->setText("Virtual");
			VirtualLineButton->setGeometry(1375, 40, 70, 70);
			QObject::connect(VirtualLineButton, &QToolButton::clicked, this, &MyDrawBoardWidget::ChangeLineToVirtual, Qt::ConnectionType::DirectConnection);

			//绘画区域初始化
			m_drawArea.setParent(this);
			m_drawArea.setAreaPosition(220, 120, 1500, 800);
			m_drawArea.setStyleSheet("border:1px solid black");

			ChangeLineWidth();
		}

		static MyDrawBoardWidget* m_instance;
		MyUIList m_leftUIList;
		MyUIList m_leftUIList2;
		MyDrawArea m_drawArea;

		//存储边框数据
		QSpinBox* m_leftBoard;
		QSpinBox* m_rightBoard;
		QSpinBox* m_bottomBoard;
		QSpinBox* m_topBoard;

		//存放旋转数据
		QDoubleSpinBox* m_rotation;
		QDoubleSpinBox* m_scale;

		//线宽数据
		QSpinBox* m_lineWidth;
	};
	MyDrawBoardWidget* MyDrawBoardWidget::m_instance = nullptr;
}