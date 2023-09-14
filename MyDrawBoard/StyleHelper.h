#pragma once
#include<QToolButton>
class StyleHelper {
public:
	static QString button_normal;
	static QString button_selected;
	static QString drawArea;
};
QString StyleHelper::button_normal = QString("QToolButton{background-color:#FFFFFF;padding:0px;margin:2px;border:none;font-family:\"YouYuan\";font-size:14px;color:#222222;}"
	"QToolButton:hover{background-color:#1E90FF;}");
QString StyleHelper::button_selected = QString("QToolButton{background-color:#FFFFFF;border:2px solid #9932CC;padding:0px;margin:2px;font-family:\"YouYuan\";font-size:14px;color:#222222;}");
QString StyleHelper::drawArea = QString("MyDrawArea{background-color:#FFA500;padding:0px;margin:2px;border:2px;border-color: black;color:#222222; }");