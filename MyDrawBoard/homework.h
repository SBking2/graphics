#pragma once
#include "MyUIList.h"
#include "MyDrawArea.h"
#include <QKeyEvent>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include<qDebug>
#include<QTimer>
#define SWidth 60
#define SLength 200
#define SMaxLength 500
namespace ComputerGraphics {

	//粒子
	class particle {
	public:
		particle(const vector<Point>& points, int color, int ttl) {
			m_polyFill = new PolyfillData(points, -1, 1, true, color);

			m_position = m_polyFill->GetCenterPoint();
			ShapeDataCtrlSystem::getInstance()->AddShapeData(m_polyFill);

			translation = Point(0, 0);
			angle = 0.0;
			scaleRate = 0.0;
			TTL = ttl;
			isLife = true;

		}
		~particle() {
			delete m_polyFill;
		}
		//设置变换参数
		void SetTransfromArg(const Point& delta, double angle, double rate) {
			translation = delta;
			this->angle = angle;
			scaleRate = rate;
		}
		//设置一次粒子的位置
		void SetPosition(Point position) {
			Point delta = position - m_position;
			vector<Point> ctrlPoints = m_polyFill->GetCtrlPoints();
			for (int i = 0; i < ctrlPoints.size(); i++) {
				ctrlPoints[i] = ctrlPoints[i] + delta;
			}
			m_polyFill->SetCtrlPoints(ctrlPoints);
			m_position = position;
		}
		bool GetLifeState() {
			return isLife;
		}
		void Update() {
			//TODO:运动
			m_polyFill->Translation(translation.x, translation.y);
			m_polyFill->Rotation(angle);
			m_polyFill->Scale(scaleRate);
			TTL -= 0.002;
			if (TTL <= 0) {
				isLife = false;
			}
		}
	private:
		PolyfillData* m_polyFill;
		Point m_position;

		bool isLife;
		int TTL;
		//变换参数
		Point translation;
		double angle;
		double scaleRate;

	};

	//香烟类
	class ciggrete {
	public:
		ciggrete() {
			clock = 0;
			//初始化直线
			topLine = new BresenhamLineData(m_endPoint, m_startPoint);
			bottomLine = new BresenhamLineData(Point(m_endPoint.x, m_endPoint.y + SWidth), Point(m_startPoint.x, m_startPoint.y + SWidth));
			length = SMaxLength;

			vector<Point> points;

			points.push_back(m_endPoint);
			points.push_back(m_endPoint - Point(5,0));
			points.push_back(m_endPoint - Point(20, -SWidth/2));
			points.push_back(m_endPoint - Point(5, -SWidth));
			points.push_back(m_endPoint - Point(0, -SWidth));
			endBezier = new BezierData(points, -1,1,true);
			points.clear();
			
			points.push_back(m_middlePoint);
			points.push_back(m_middlePoint - Point(5, 0));
			points.push_back(m_middlePoint - Point(20, -SWidth / 2));
			points.push_back(m_middlePoint - Point(5, -SWidth));
			points.push_back(m_middlePoint - Point(0, -SWidth));
			middleBezier = new BezierData(points, -1, 1, true);
			points.clear();

			points.push_back(m_startPoint);
			points.push_back(m_startPoint - Point(5, 0));
			points.push_back(m_startPoint - Point(20, -SWidth / 2));
			points.push_back(m_startPoint - Point(5, -SWidth));
			points.push_back(m_startPoint - Point(0, -SWidth));
			startBezier1 = new BezierData(points, -1, 1, true);
			points.clear();

			points.push_back(m_startPoint);
			points.push_back(m_startPoint + Point(5, 0));
			points.push_back(m_startPoint + Point(20, SWidth / 2));
			points.push_back(m_startPoint + Point(5, SWidth));
			points.push_back(m_startPoint + Point(0, SWidth));
			startBezier2 = new BezierData(points, -1, 1, true);
			points.clear();

			ciggreteHandle = new SeedFillData(m_endPoint + Point(0, SWidth / 2), 5);
			ciggreteHead = new SeedFillData(m_startPoint + Point(0, 10 + SWidth / 2), 1);

			
			ShapeDataCtrlSystem::getInstance()->AddShapeData(topLine);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(bottomLine);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(endBezier);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(middleBezier);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(startBezier1);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(startBezier2);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(ciggreteHandle);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(ciggreteHead);
		}
		~ciggrete(){}
		//设置香烟位置
		void SetPosition(const Point& point) {
			m_endPoint = point;
			m_middlePoint = Point(point.x + SLength, point.y);
			m_startPoint = Point(m_middlePoint.x + SMaxLength, m_middlePoint.y);
			UpdateShapePosition();
		}
		void SetLength(int length) {
			if (length <= 10)
				length = 10;
			m_startPoint = Point(m_middlePoint.x + length, m_middlePoint.y);
			this->length = length;
			UpdateShapePosition();
		}
		int GetLength() {
			return length;
		}
		//更新图形位置
		void UpdateShapePosition() {
			topLine->Set(m_endPoint, m_startPoint);
			bottomLine->Set(Point(m_endPoint.x, m_endPoint.y + SWidth), Point(m_startPoint.x, m_startPoint.y + SWidth));

			vector<Point> points;

			points.push_back(m_endPoint);
			points.push_back(m_endPoint - Point(5, 0));
			points.push_back(m_endPoint - Point(20, -SWidth / 2));
			points.push_back(m_endPoint - Point(5, -SWidth));
			points.push_back(m_endPoint - Point(0, -SWidth));
			endBezier->SetCtrlPoints(points);
			points.clear();

			points.push_back(m_middlePoint);
			points.push_back(m_middlePoint - Point(5, 0));
			points.push_back(m_middlePoint - Point(20, -SWidth / 2));
			points.push_back(m_middlePoint - Point(5, -SWidth));
			points.push_back(m_middlePoint - Point(0, -SWidth));
			middleBezier->SetCtrlPoints(points);
			points.clear();

			points.push_back(m_startPoint);
			points.push_back(m_startPoint - Point(5, 0));
			points.push_back(m_startPoint - Point(20, -SWidth / 2));
			points.push_back(m_startPoint - Point(5, -SWidth));
			points.push_back(m_startPoint - Point(0, -SWidth));
			startBezier1->SetCtrlPoints(points);
			points.clear();

			points.push_back(m_startPoint);
			points.push_back(m_startPoint + Point(5, 0));
			points.push_back(m_startPoint + Point(20, SWidth / 2));
			points.push_back(m_startPoint + Point(5, SWidth));
			points.push_back(m_startPoint + Point(0, SWidth));
			startBezier2->SetCtrlPoints(points);

			ciggreteHandle->Set(m_endPoint + Point(0, SWidth / 2));
			ciggreteHead->Set(m_startPoint + Point(0, SWidth / 2));
		}
		Point GetPosition() {
			return m_startPoint;
		}
		//更新
		void Update() {
			//TODO:管理所有的粒子
			clock++;
			if (clock < 13) {
				/*triangle->Translation(0, -3);
				triangle->Scale(1.1);
				triangle->Rotation(0.1);*/
			}
			if (clock > 13) {
				/*triangle->Translation(0, -3);
				triangle->Scale(0.92);
				triangle->Rotation(0.1);*/
			}
			if (clock == 30) {
				clock = 0;
				int j = (rand() % (5 - 3 + 1)) + 3;
				for (int i = 0; i < j; i++) {
					CreateParicle();
				}
			}

			vector<int> ints;

			for (int i = 0; i < m_particles.size(); i++) {
				m_particles[i]->Update();
				/*if (m_particles[i]->GetLifeState() == false) {
					ints.push_back(i);
				}*/
			}
			/*for (int i = 0; i < ints.size(); i++) {
				m_particles.erase(m_particles.begin()+ints[i]);
			}*/
		}

		void CreateParicle() {
			int size = (rand() % (5 - 3 + 1)) + 3;
			vector<Point> points;
			switch (size) {
			case 3:
				points.push_back(m_startPoint + Point(-30, -30));
				points.push_back(m_startPoint + Point(60, -30));
				points.push_back(m_startPoint + Point(12, 42));
				break;
			case 4:
				points.push_back(m_startPoint + Point(-30, -30));
				points.push_back(m_startPoint + Point(-30, 45));
				points.push_back(m_startPoint + Point(45, 45));
				points.push_back(m_startPoint + Point(45, -30));
				break;
			case 5:
				points.push_back(m_startPoint + Point(-30, -30));
				points.push_back(m_startPoint + Point(30, -30));
				points.push_back(m_startPoint + Point(60, 15));
				points.push_back(m_startPoint + Point(0, 60));
				points.push_back(m_startPoint + Point(-60, 15));
				break;
			}
			int ttl = (rand() % (300 - 100 + 1)) + 100;
			particle* newParticle = new particle(points, 12, ttl);

			int scaleArg = (rand() % (4 - 2 + 1)) + 2;
			double scale = 1 - (0.03 * scaleArg);

			int rotationArg = (rand() % (3 - 1 + 1)) + 1;
			double rotation = 0.05 * rotationArg;

			int TranslationArg = (rand() % (8 - 3 + 1)) + 3;
			int Translate = 1 * TranslationArg;

			int TranslationArg2 = (rand() % (3 - 1 + 1)) + 1;
			int Translate2 = 1 * TranslationArg2;

			Point delta = Point(Translate2, -Translate);

			newParticle->SetTransfromArg(delta, rotation, scale);
			m_particles.push_back(newParticle);
		}
	private:
		//Location
		Point m_endPoint;
		Point m_middlePoint;
		Point m_startPoint;

		//ShapeData
		BresenhamLineData* topLine;
		BresenhamLineData* bottomLine;

		BezierData* endBezier;
		BezierData* startBezier1;
		BezierData* startBezier2;
		BezierData* middleBezier;

		SeedFillData* ciggreteHandle;

		vector<particle*> m_particles;

		SeedFillData* ciggreteHead;

		int clock;

		int length;
	};
	//肺类
	class lung {
	public:
		lung(const Point & position) {
			m_position = position;
			maxRange = 50;
			minRange = -30;
			currentRange = 0;
			isOut = true;

			vector<Point> points;
			Point EPoint1;
			Point SPoint1;

			points.push_back(m_position - Point(40, 0));
			SPoint1 = points[0];
			points.push_back(points[0] + Point(0, -80));
			points.push_back(points[0] + Point(-40, -40));
			points.push_back(points[2] + Point(-170, 210));
			tempRange1 = points[3];
			points.push_back(points[3] + Point(80, 170));
			points.push_back(points[4] + Point(50, -50));
			bezier1 = new BezierData(points, -1, 1, true,1);
			EPoint1 = points[5];
			points.clear();

			points.push_back(EPoint1);
			points.push_back(points[0] + Point(30, -20));
			points.push_back(points[1] + Point(40, -40));
			bezier3 = new BezierData(points, -1, 1, true,1);
			EPoint1 = points[2];
			points.clear();

			line1 = new BresenhamLineData(SPoint1 - Point(0, 2), EPoint1 - Point(0, -2), 1);

			points.push_back(m_position + Point(40, 0));
			SPoint1 = points[0];
			points.push_back(points[0] + Point(0, -80));
			points.push_back(points[0] + Point(40, -40));
			points.push_back(points[2] + Point(170, 210));
			tempRange2 = points[3];
			points.push_back(points[3] + Point(-80, 170));
			points.push_back(points[4] + Point(-50, -50));
			bezier2 = new BezierData(points, -1,1, true,1);
			EPoint1 = points[5];
			points.clear();

			points.push_back(EPoint1);
			points.push_back(points[0] + Point(-30, -20));
			points.push_back(points[1] + Point(-40, -40));
			bezier4 = new BezierData(points, -1, 1, true,1);
			EPoint1 = points[2];
			points.clear();

			Branch0 = new BresenhamLineData(m_position + Point(10, 0), m_position + Point(10, -120), 4, 1, 2);
			Branch1 = new BresenhamLineData(m_position + Point(-10, 0), m_position + Point(-10, -120), 4, 1, 2);
			Branch2 = new BresenhamLineData(m_position + Point(10, 0), m_position + Point(42, 30), 4, 1, 2);
			Branch3 = new BresenhamLineData(m_position + Point(-10, 0), m_position + Point(-42, 30), 4, 1, 2);
			Branch4 = new BresenhamLineData(m_position + Point(0, 20), m_position + Point(45, 60), 4, 1, 2);
			Branch5 = new BresenhamLineData(m_position + Point(0, 20), m_position + Point(-45, 60), 4, 1, 2);
			///
			Branch6 = new BresenhamLineData(m_position + Point(-42, 30), m_position + Point(-92, 108), 4, 1, 2);
			Branch7 = new BresenhamLineData(m_position + Point(-45, 60), m_position + Point(-90, 120), 4, 1, 2);
			Branch8 = new BresenhamLineData(m_position + Point(-90, 120), m_position + Point(-70, 180), 4, 1, 2);
			Branch9 = new BresenhamLineData(m_position + Point(-95, 130), m_position + Point(-70, 180), 4, 1, 2);
			Branch10 = new BresenhamLineData(m_position + Point(-95, 130), m_position + Point(-100, 220), 4, 1, 2);
			Branch11 = new BresenhamLineData(m_position + Point(-100, 125), m_position + Point(-100, 220), 4, 1, 2);
			Branch12 = new BresenhamLineData(m_position + Point(-100, 125), m_position + Point(-135, 170), 4, 1, 2);
			Branch13 = new BresenhamLineData(m_position + Point(-98, 113), m_position + Point(-135, 170), 4, 1, 2);
			Branch14 = new BresenhamLineData(m_position + Point(-98, 113), m_position + Point(-120, 100), 4, 1, 2);
			Branch15 = new BresenhamLineData(m_position + Point(-92, 108), m_position + Point(-120, 100), 4, 1, 2);
			Branch16 = new BresenhamLineData(m_position + Point(-42, 30), m_position + Point(-92, 108), 4, 1, 2);
			///
			Branch17 = new BresenhamLineData(m_position + Point(45, 60), m_position + Point(90, 120), 4, 1, 2);
			Branch18 = new BresenhamLineData(m_position + Point(90, 120), m_position + Point(70, 180), 4, 1, 2);
			Branch19 = new BresenhamLineData(m_position + Point(95, 130), m_position + Point(70, 180), 4, 1, 2);
			Branch20 = new BresenhamLineData(m_position + Point(95, 130), m_position + Point(100, 220), 4, 1, 2);
			Branch21 = new BresenhamLineData(m_position + Point(100, 125), m_position + Point(100, 220), 4, 1, 2);
			Branch22 = new BresenhamLineData(m_position + Point(100, 125), m_position + Point(135, 170), 4, 1, 2);
			Branch23 = new BresenhamLineData(m_position + Point(98, 113), m_position + Point(135, 170), 4, 1, 2);
			Branch24 = new BresenhamLineData(m_position + Point(98, 113), m_position + Point(120, 100), 4, 1, 2);
			Branch25 = new BresenhamLineData(m_position + Point(92, 108), m_position + Point(120, 100), 4, 1, 2);
			Branch26 = new BresenhamLineData(m_position + Point(42, 30), m_position + Point(92, 108), 4, 1, 2);
			///
			Branch27 = new BresenhamLineData(m_position + Point(10, -120), m_position + Point(-10, -120), 4, 1, 2);


			line2 = new BresenhamLineData(SPoint1 + Point(0, -2), EPoint1 + Point(0, 2), 1);

			lung1 = new SeedFillData(m_position - Point(80, -100), 10);
			lung2 = new SeedFillData(m_position + Point(80, 100), 10);
			//branch = new SeedFillData(m_position + Point(0, 0), 4);

			

			ShapeDataCtrlSystem::getInstance()->AddShapeData(bezier1);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(bezier2);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(bezier3);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(bezier4);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(line1);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(line2);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(lung1);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(lung2);


			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch0);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch1);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch2);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch3);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch4);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch5);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch6);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch7);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch8);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch9);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch10);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch11);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch12);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch13);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch14);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch15);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch16);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch17);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch18);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch19);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch20);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch21);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch22);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch23);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch24);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch25);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch26);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Branch27);

			//ShapeDataCtrlSystem::getInstance()->AddShapeData(branch);
		}
		~lung() {

		}

		void SetPosition(const Point& point) {
			m_position = point;
			UpdateShape();
		}
		void UpdateShape() {
			vector<Point> points;
			Point EPoint1;
			Point SPoint1;

			points.push_back(m_position - Point(40, 0));
			SPoint1 = points[0];
			points.push_back(points[0] + Point(0, -80));
			points.push_back(points[0] + Point(-40, -40));
			points.push_back(points[2] + Point(-170, 210));
			tempRange1 = points[3];
			points.push_back(points[3] + Point(80, 170));
			points.push_back(points[4] + Point(50, -50));
			bezier1->SetCtrlPoints(points);
			EPoint1 = points[5];
			points.clear();

			points.push_back(EPoint1);
			points.push_back(points[0] + Point(30, -20));
			points.push_back(points[1] + Point(40, -40));
			bezier3->SetCtrlPoints(points);
			EPoint1 = points[2];
			points.clear();

			line1->Set(SPoint1, EPoint1);

			points.push_back(m_position + Point(40, 0));
			SPoint1 = points[0];
			points.push_back(points[0] + Point(0, -80));
			points.push_back(points[0] + Point(40, -40));
			points.push_back(points[2] + Point(170, 210));
			tempRange2 = points[3];
			points.push_back(points[3] + Point(-80, 170));
			points.push_back(points[4] + Point(-50, -50));
			bezier2->SetCtrlPoints(points);
			EPoint1 = points[5];
			points.clear();

			points.push_back(EPoint1);
			points.push_back(points[0] + Point(-30, -20));
			points.push_back(points[1] + Point(-40, -40));
			bezier4->SetCtrlPoints(points);
			EPoint1 = points[2];
			points.clear();

			line2->Set(SPoint1, EPoint1);
		}
		//肺的动态呼吸
		void Update(float t) {
			float maxRangeT = maxRange *t;
			float minRangeT = minRange * t;
			bezier1->SetCtrlPoints(3, tempRange1 - Point(currentRange, 0));
			bezier2->SetCtrlPoints(3, tempRange2 + Point(currentRange, 0));
			if (isOut) {
				currentRange = lerp(currentRange, maxRangeT, 0.1);
			}
			else {
				currentRange = lerp(currentRange, minRangeT, 0.1);
			}
			if (maxRangeT - currentRange < 1 && isOut) {
				isOut = false;
			}
			else if (currentRange - minRangeT < 1 && !isOut) {
				isOut = true;
			}
		}
		template<typename T>
		T lerp(const T& start, const T& end, double t) {
			return start + t * (end - start);
		}

	private:
		Point m_position;

		BezierData* bezier1;
		BezierData* bezier2;
		BezierData* bezier3;
		BezierData* bezier4;
		BresenhamLineData* line1;
		BresenhamLineData* line2;
		SeedFillData* lung1;
		SeedFillData* lung2;
		SeedFillData* branch;
		Point tempRange1;
		Point tempRange2;
		float minRange;
		float maxRange;
		float currentRange;
		bool isOut;

		BresenhamLineData* Branch0;
		BresenhamLineData* Branch1;
		BresenhamLineData* Branch2;
		BresenhamLineData* Branch3;
		BresenhamLineData* Branch4;
		BresenhamLineData* Branch5;
		BresenhamLineData* Branch6;
		BresenhamLineData* Branch7;
		BresenhamLineData* Branch8;
		BresenhamLineData* Branch9;
		BresenhamLineData* Branch10;
		BresenhamLineData* Branch11;
		BresenhamLineData* Branch12;
		BresenhamLineData* Branch13;
		BresenhamLineData* Branch14;
		BresenhamLineData* Branch15;
		BresenhamLineData* Branch16;
		BresenhamLineData* Branch17;
		BresenhamLineData* Branch18;
		BresenhamLineData* Branch19;
		BresenhamLineData* Branch20;
		BresenhamLineData* Branch21;
		BresenhamLineData* Branch22;
		BresenhamLineData* Branch23;
		BresenhamLineData* Branch24;
		BresenhamLineData* Branch25;
		BresenhamLineData* Branch26;
		BresenhamLineData* Branch27;
	};
	//烟雾类
	class smoke {
	public:
		smoke(const Point& point){
			t = 0;
			isOut = true;

			m_position = point;

			vector<Point> points;
			points.push_back(Point(m_position));
			points.push_back(Point(m_position + Point(-25, -100)));
			points.push_back(Point(points[1] + Point(-25, -100)));
			points.push_back(Point(points[2] + Point(-25, -100)));
			B11 = points[1];
			B12 = points[2];
			B13 = points[3];
			Bezier1 = new BezierData(points, -1, 1, true);
			points.clear();

			points.push_back(Point(m_position));
			points.push_back(Point(points[0] + Point(25, -100)));
			points.push_back(Point(points[1] + Point(25, -100)));
			points.push_back(Point(points[2] + Point(25, -100)));
			Bezier2 = new BezierData(points, -1, 1, true);
			B21 = points[1];
			B22 = points[2];
			B23 = points[3];
			points.clear();

			ShapeDataCtrlSystem::getInstance()->AddShapeData(Bezier1);
			ShapeDataCtrlSystem::getInstance()->AddShapeData(Bezier2);
		}
		~smoke(){

		}
		void SetPosition(const Point& point) {
			m_position = point;
			UpdateShapePosition();
		}
		void UpdateShapePosition() {

			vector<Point> points;
			points.push_back(Point(m_position));
			points.push_back(Point(m_position + Point(-25, -100)));
			points.push_back(Point(points[1] + Point(-25, -100)));
			points.push_back(Point(points[2] + Point(-25, -100)));
			B11 = points[1];
			B12 = points[2];
			B13 = points[3];
			Bezier1 ->SetCtrlPoints(points);
			points.clear();

			points.push_back(Point(m_position));
			points.push_back(Point(points[0] + Point(25, -100)));
			points.push_back(Point(points[1] + Point(25, -100)));
			points.push_back(Point(points[2] + Point(25, -100)));
			Bezier2->SetCtrlPoints(points);
			B21 = points[1];
			B22 = points[2];
			B23 = points[3];
			points.clear();
		}
		void Update() {
			//更新参数t
			if (isOut) {
				t = t + 0.03;
				if (t > 1) {
					t = 1;
					isOut = false;
				}
			}
			else {
				t = t - 0.03;
				if (t < -1) {
					t = -1;
					isOut = true;
				}
			}


			//调整Bezier曲线
			Bezier1->SetCtrlPoints(1, B11 + Point(100, 0));
			Bezier1->SetCtrlPoints(2, B12 + Point(-100 *t, 0));
			Bezier1->SetCtrlPoints(3, B13 + Point(30 * t, 0));

			Bezier2->SetCtrlPoints(1, B21 + Point(100, 0));
			Bezier2->SetCtrlPoints(2, B22 + Point(-100 * t, 0));
			Bezier2->SetCtrlPoints(3, B23 + Point(30* t, 0));
		}
	private:
		Point m_position;
		Point B11, B12, B13, B21, B22, B23;
		float t;
		bool isOut;

		BezierData* Bezier1;
		BezierData* Bezier2;
	};
	class homework : public QWidget {
	public:
		//获取单例函数
		static homework* GetInstance() {
			if (m_instance == nullptr) {
				m_instance = new homework();
			}
			return m_instance;
		}
		//析构函数
		~homework() {
			//TODO:析构
		}
		void resizeEvent(QResizeEvent* event)override {
			m_dreaArea.setGeometry();
			QWidget::resizeEvent(event);
		}
		void mousePressEvent(QMouseEvent* event)override {
			if (event->button() == Qt::MouseButton::LeftButton) {
				isSomking = true;
				qDebug() << event->pos().x() << " " << event->pos().y() << endl;
			}
			QWidget::mousePressEvent(event);
		}
		void mouseReleaseEvent(QMouseEvent* event)override {
			if (event->button() == Qt::MouseButton::LeftButton) {
				isSomking = false;
			}
			QWidget::mouseReleaseEvent(event);
		}
		//更新函数
		void Update() {
			//TODO:刷新画面
			if (isSomking) {
				m_ciggrete->SetLength(m_ciggrete->GetLength() - 3);
			}
			t = (float)m_ciggrete->GetLength() / SMaxLength;
			m_lung->Update(t);
			m_smoke->SetPosition(m_ciggrete->GetPosition());
			m_smoke->Update();
			m_ciggrete->Update();
			m_dreaArea.update();
			m_dreaArea.SetT(t);
			update();
		}
		float GetT() {
			return t;
		}
	private:
		homework() {
			//TODO:默认构造函数
			
			//初始化
			isSomking = false;
		    timer = new QTimer(this);
			connect(timer, &QTimer::timeout, this, &homework::Update);
			timer->start(1);

			//构造画布
			m_dreaArea.setParent(this);
			m_dreaArea.setAreaPosition(10,10,1180,780);
			m_dreaArea.setStyleSheet("border:1px solid black");
			//屏蔽绘画区域的交互
			m_dreaArea.SetShapeType(ShapeType::Unknown);
			//取消绘制控制点
			m_dreaArea.ChangeDrawMode();

			setFixedSize(1200, 800);
			
			m_ciggrete = new ciggrete();
			m_ciggrete->SetPosition(Point(200, 600));

			m_lung = new lung(Point(600, 200));

			m_smoke = new smoke(m_ciggrete->GetPosition());

			t = m_ciggrete->GetLength() / SMaxLength;
		}
		static homework* m_instance;
		MyDrawArea m_dreaArea;
		ciggrete* m_ciggrete;
		lung* m_lung;
		smoke* m_smoke;
		QTimer* timer;
		bool isSomking;

		//烟的长度参数
		float t;
	};
	homework* homework::m_instance = nullptr;
}