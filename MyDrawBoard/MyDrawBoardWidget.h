#pragma once
#include "MyUIList.h"
#include "MyDrawArea.h"
#include <QKeyEvent>
#include <QSpinBox>
#include <QLabel>
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
			QWidget::paintEvent(event);
		}
		void resizeEvent(QResizeEvent* event) override {
			m_leftUIList.DrawButtons();
			m_drawArea.setGeometry();

			QWidget::resizeEvent(event);
		}

		#pragma region Button Function
		void button_MidPointLine() {
			m_drawArea.SetShapeType(ShapeType::MidPointLine);
		}
		void button_BresenhamLine() {
			m_drawArea.SetShapeType(ShapeType::BresenhamLine);
		}
		void button_MidPointCircle() {
			m_drawArea.SetShapeType(ShapeType::MidPointCircle);
		}
		void button_CircleArc() {
			m_drawArea.SetShapeType(ShapeType::CircleArc);
		}
		void button_CSCLine() {
			m_drawArea.SetShapeType(ShapeType::CSCLine);
		}
		void button_MidCLine() {
			m_drawArea.SetShapeType(ShapeType::MidCLine);
		}
		#pragma endregion
		#pragma region ValueChange Function
		void SetBoarder() {
			m_drawArea.SetBoarder(m_leftBoard->value(), m_rightBoard->value(), m_bottomBoard->value(), m_topBoard->value());
		}
		#pragma endregion



	private:
		MyDrawBoardWidget(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
			setWindowTitle(QStringLiteral("Draw Board"));

			//Button UIList 初始化
			m_leftUIList.SetButtonSize(96);
			m_leftUIList.SetIconSize(48);
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
			m_leftUIList.AddButton(this, QIcon(QString(":/Icon/Resource/Icon/StraightLine.png"))
				, QString("MidC Line"), QString("Mid Line Button"), this, &MyDrawBoardWidget::button_MidCLine
				, ShapeType::MidCLine);

			/*
			TODO：目前改变框内的值无法调节边框的范围
			*/

			//输入框初始化
			QLabel* leftLable = new QLabel("left Boarder",this);
			leftLable->setGeometry(100, 0, 72, 24);
			m_leftBoard = new QSpinBox(this);
			m_leftBoard->setGeometry(180, 0, 64, 24);
			m_leftBoard->setRange(0, 9999);

			connect(m_leftBoard, SIGNAL(valueChanged(int)), this, SLOT(SetBoarder(int)));

			QLabel* rightLable = new QLabel("right Boarder", this);
			rightLable->setGeometry(260, 0, 72, 32);
			m_rightBoard = new QSpinBox(this);
			m_rightBoard->setGeometry(340, 0, 64, 24);
			m_rightBoard->setRange(0, 9999);

			connect(m_rightBoard, SIGNAL(valueChanged(int)), this, SLOT(SetBoarder(int)));

			QLabel* buttonLable = new QLabel("button Boarder", this);
			buttonLable->setGeometry(420, 0, 72, 24);
			m_bottomBoard = new QSpinBox(this);
			m_bottomBoard->setGeometry(500, 0, 64, 24);
			m_bottomBoard->setRange(0, 9999);

			connect(m_bottomBoard, SIGNAL(valueChanged(int)), this, SLOT(SetBoarder(int)));

			QLabel* topLable = new QLabel("top Boarder", this);
			topLable->setGeometry(580, 0, 72, 24);
			m_topBoard = new QSpinBox(this);
			m_topBoard->setGeometry(660, 0, 64, 24);
			m_topBoard->setRange(0, 9999);

			connect(m_topBoard, SIGNAL(valueChanged(int)), this, SLOT(SetBoarder(int)));

			//绘画区域初始化
			m_drawArea.setParent(this);
			m_drawArea.setAreaPosition(100, 100, 500, 500);
			m_drawArea.setStyleSheet("border:1px solid black");
		}

		static MyDrawBoardWidget* m_instance;
		MyUIList m_leftUIList;
		MyDrawArea m_drawArea;

		//存储边框数据
		QSpinBox* m_leftBoard;
		QSpinBox* m_rightBoard;
		QSpinBox* m_bottomBoard;
		QSpinBox* m_topBoard;
	};
	MyDrawBoardWidget* MyDrawBoardWidget::m_instance = nullptr;
}