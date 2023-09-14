#pragma once
#include"MyButton.h"
#define DEFAULT_MAXLISTLENGTH 10
namespace ComputerGraphics {
	class MyUIList : public QWidget {
	public:
		MyUIList(float startX = 0.0F, float startY = 0.0F
			, float iconSize = 0.0F, float buttonSize = 0.0F
			, int maxListLength = DEFAULT_MAXLISTLENGTH, bool isRight = false) {

			//Initialize list
			m_UIListLength = 0;
			m_maxListLength = maxListLength;
			m_UIListButtons = new MyButton*[m_maxListLength];

			for (int i = 0; i < m_maxListLength; i++) {
				m_UIListButtons[i] = nullptr;
			}

			//Setting the property
			m_startX = startX;
			m_startY = startY;
			m_iconSize = iconSize;
			m_buttonSize = buttonSize;
			m_isRight = isRight;
		}
		~MyUIList() {
			if (m_UIListButtons == nullptr)
				return;
			for (int i = 0; i < m_UIListLength; i++) {
				if(m_UIListButtons[i] != nullptr)
				delete m_UIListButtons[i];
			}
			delete[] m_UIListButtons;
		}

		template<typename Func2>
		void AddButton(QWidget* parent, QIcon icon, QString text
			, QString buttonName, const typename QtPrivate::FunctionPointer<Func2>::Object* receiver, Func2 slot
		, const ShapeType & shapeType) {
			if (m_UIListButtons == nullptr) {
				throw "UIList is NULL !";
				return;
			}
			if (m_UIListLength == m_maxListLength) {
				throw "UIList is Full";
				return;
			}
			MyButton *newButton = new MyButton(parent, icon, text, buttonName,receiver, slot
				, shapeType, m_iconSize);
			m_UIListButtons[m_UIListLength] = newButton;
			m_UIListLength++;
		}
		void DeleteButton() {
			if (m_UIListLength == 0) {
				throw "UIList is empty!";
				return;
			}
			MyButton* p = m_UIListButtons[--m_UIListLength];
			delete p;
			m_UIListButtons[m_UIListLength] = nullptr;
		}

		void DrawButtons() {
			for (int i = 0; i < m_UIListLength; i++) {
				if (!m_isRight) {
					m_UIListButtons[i]->setGeometry(m_startX, i * m_buttonSize + m_startY, m_buttonSize, m_buttonSize);
				}
				else {
					m_UIListButtons[i]->setGeometry(i * m_buttonSize + m_startX, m_startY, m_buttonSize, m_buttonSize);
				}
			}
		}

		void SetButtonSize(int buttonSize) {
			m_buttonSize = buttonSize;
		}
		void SetIconSize(int iconSize) {
			m_iconSize = iconSize;
		}
		
		void updateSelectedAllButton(const ShapeType & shapeType) {
		if (m_UIListButtons == nullptr)
			return;
			for (int i = 0; i < m_UIListLength; i++) {
				if(m_UIListButtons[i] == nullptr)
					continue;
				m_UIListButtons[i]->SetButtonState(false);
				if (m_UIListButtons[i]->GetShapeType() == shapeType) {
					m_UIListButtons[i]->SetButtonState(true);
				}
				m_UIListButtons[i]->updateButtonStyle();
			}
			update();
		}

	private:
		MyButton** m_UIListButtons;
		int m_UIListLength;
		int m_maxListLength;



		float m_startX;
		float m_startY;
		float m_iconSize;
		float m_buttonSize;

		bool m_isRight;
	};
}