#pragma once
#include"ShapeData.h"
#include<QToolButton>
#include"StyleHelper.h"
namespace ComputerGraphics {
	class MyButton : public QToolButton {
	public:
		template<typename Func2>
		MyButton(QWidget* parent, QIcon icon, QString text
			, QString buttonName, const typename QtPrivate::FunctionPointer<Func2>::Object* receiver, Func2 slot
			,const ShapeType & shapeType, int iconSize = 0): QToolButton(parent) {
			m_shapeType = ShapeType::Unknown;
			m_isSelected = false;
			m_shapeType = shapeType;

			setParent(parent);
			setIcon(icon);
			setText(text);
			setObjectName(buttonName);
			setIconSize(QSize(iconSize, iconSize));
			setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
			updateButtonStyle();

			MyButton::Connect(receiver, slot);
		}

		~MyButton() {
			//m_button.~QToolButton();QT类由父级析构
		}
		
		ShapeType GetShapeType() {
			return m_shapeType;
		}

		bool GetButtonState() {
			return m_isSelected;
		}
		void SetButtonState(bool is) {
			m_isSelected = is;
		}

		template<typename Func2>
		void Connect(const typename QtPrivate::FunctionPointer<Func2>::Object* receiver, Func2 slot) {
			QObject::connect(this, &QToolButton::clicked, receiver, slot, Qt::ConnectionType::DirectConnection);
		}

		//button style
		void updateButtonStyle() {
			if (!m_isSelected) {
				setStyleSheet(StyleHelper::button_normal);
			}
			else
			{
				setStyleSheet(StyleHelper::button_selected);
			}
		}
		
		
	private:
		/*template<typename Func2>
		void copy(QWidget* parent, QIcon icon, QString text
			, QString buttonName, int iconSize, int buttonSize
			, const typename QtPrivate::FunctionPointer<Func2>::Object* receiver, Func2 slot) {
			m_parent = parent;
			m_icon = icon;
			m_text = text;
			m_buttonName = buttonName;
			m_iconSize = iconSize;
			m_buttonSize = buttonSize;


			m_button.setParent(m_parent);
			m_button.setObjectName(m_buttonName);
			m_button.setText(m_text);
			m_button.setIcon(m_icon);
			m_button.setIconSize(QSize(m_iconSize, m_iconSize));
			m_button.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

			m_isSelected = false;

			Connect(receiver, slot);
			Connect(this), &QToolButton::updateButtonStyle);
		}*/

		//QToolButton m_button;

		//
		//QWidget* m_parent;
		//QIcon m_icon;
		//QString m_text;
		//QString m_buttonName;
		//int m_iconSize;
		//int m_buttonSize;

		bool m_isSelected;

		ShapeType m_shapeType;

	};
}