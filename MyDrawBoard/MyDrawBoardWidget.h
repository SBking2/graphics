#pragma once
#include "MyUIList.h"
#include "MyDrawArea.h"
#include <QKeyEvent>
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
		#pragma endregion


	private:
		MyDrawBoardWidget(QWidget* parent = Q_NULLPTR) : QWidget(parent) {
			setWindowTitle(QStringLiteral("Draw Board"));

			//private awake function
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

			m_drawArea.setParent(this);
			m_drawArea.setAreaPosition(100, 100, 500, 500);
			m_drawArea.setStyleSheet("border:1px solid black");
		}

		static MyDrawBoardWidget* m_instance;
		MyUIList m_leftUIList;
		MyDrawArea m_drawArea;
	};
	MyDrawBoardWidget* MyDrawBoardWidget::m_instance = nullptr;
}