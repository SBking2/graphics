#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include <math.h>
#include<qDebug>
#include<stack>
#include <cmath>
#define CANVASLENGTH 1501
using namespace std;
namespace ComputerGraphics {
    //初始化像素点画布
    static int** canvas;
    //控制点层
    static int** CtrlLayerCanvas;


    //点变量
    struct Point {
        int x;
        int y;
        Point(int X = 0, int Y = 0) {
            x = X;
            y = Y;
        }
        ~Point(){}
        Point& operator=(const Point& point) {
            this->Set(point.x, point.y);
            return *this;
        }
        Point operator+(Point point) {
            return { this->x + point.x, this->y + point.y };
        }
        Point operator-(Point point) {
            return { this->x - point.x, this->y - point.y };
        }
        Point operator*(const int& value) {
            return Point(this->x * value, this->y * value);
        }
        void Set(int X, int Y) {
            x = X;
            y = Y;
        }
    };
    //边框变量
    struct Boarder {
        int left;
        int right;
        int bottom;
        int top;
        Boarder(int left = 0, int right = 100, int bottom = 0, int top = 100) {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
        }
        ~Boarder() {

        }
        Boarder& operator=(const Boarder& boarder) {
            left = boarder.left;
            right = boarder.right;
            bottom = boarder.bottom;
            top = boarder.top;
            return *this;
        }
        void Set(int left, int right, int bottom, int top) {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
        }
    };
    typedef struct Edge
    {
        int ymax;
        float x, deltax;
        struct Edge* nextEdge = NULL;
    } Edge;

    void InsertEdge(Edge*& headpoint, Edge* p) {
        Edge* e = new Edge;
        e->deltax = p->deltax;
        e->nextEdge = NULL;
        e->x = p->x;
        e->ymax = p->ymax;
        if (headpoint == NULL) {
            headpoint = e;
            return;
        }
        if (e->x < headpoint->x || (e->x == headpoint->x && e->deltax < headpoint->deltax)) {
            e->nextEdge = headpoint;
            headpoint = e;
            return;
        }
        if (e->x == headpoint->x) {
            e->nextEdge = headpoint->nextEdge;
            headpoint->nextEdge = e;
            return;
        }
        Edge* temp = headpoint;
        while (temp->nextEdge != NULL && e->x > temp->nextEdge->x) {
            temp = temp->nextEdge;
        }
        if (temp->nextEdge != NULL && e->x == temp->nextEdge->x && e->deltax > headpoint->deltax) {
            temp = temp->nextEdge;
        }
        e->nextEdge = temp->nextEdge;
        temp->nextEdge = e;
    }
    class Algorithm {
    public:
        #pragma region 线形线宽部分
        static vector<Point> LineWidth(const vector<Point>& allPoints, int Length) {
            vector<Point> result;
            for (int i = 0; i < allPoints.size(); i++) {
                for (int radius = 1; radius <= Length; radius++) {
                    int x = 0, y = radius, e = 1 - radius;//圆形
                    result.push_back(Point(allPoints[i].x + x, allPoints[i].y + y));
                    result.push_back(Point(allPoints[i].x - x, allPoints[i].y - y));
                    result.push_back(Point(allPoints[i].x - x, allPoints[i].y + y));
                    result.push_back(Point(allPoints[i].x + x, allPoints[i].y - y));
                    result.push_back(Point(allPoints[i].x + y, allPoints[i].y + x));
                    result.push_back(Point(allPoints[i].x - y, allPoints[i].y - x));
                    result.push_back(Point(allPoints[i].x - y, allPoints[i].y + x));
                    result.push_back(Point(allPoints[i].x + y, allPoints[i].y - x));
                    while (x <= y)
                    {
                        if (e < 0)
                            e += 2 * x + 3;
                        else
                        {
                            e += 2 * (x - y) + 5;
                            y--;
                        }
                        x++;
                        result.push_back(Point(allPoints[i].x + x, allPoints[i].y + y));
                        result.push_back(Point(allPoints[i].x - x, allPoints[i].y - y));
                        result.push_back(Point(allPoints[i].x - x, allPoints[i].y + y));
                        result.push_back(Point(allPoints[i].x + x, allPoints[i].y - y));
                        result.push_back(Point(allPoints[i].x + y, allPoints[i].y + x));
                        result.push_back(Point(allPoints[i].x - y, allPoints[i].y - x));
                        result.push_back(Point(allPoints[i].x - y, allPoints[i].y + x));
                        result.push_back(Point(allPoints[i].x + y, allPoints[i].y - x));
                    }
                }
            }
            return result;
        }
        static vector<Point> VirtualLine(const vector<Point>& allPoints) {
            vector<Point> result;
            int count = 0;
            for (int i = 0; i < allPoints.size(); i++) {
                if (count < 15) {
                    result.push_back(Point(allPoints[i].x, allPoints[i].y));
                }
                count++;
                if (count > 30)
                    count = 0;
            }
            return result;
        }
        static vector<Point> cubeWidth(const vector<Point>& allPoints, int Length) {
            vector<Point> result;
            for (int i = 0; i < allPoints.size(); i++) {
                for (int j = 1 - Length; j <= Length - 1; j++)//正方形    
                    for (int k = 1 - Length; k <= Length - 1; k++)
                    {
                        result.push_back(Point(allPoints[i].x + j, allPoints[i].y + k));
                    }

                for (int j = 1 - Length, k = 0; j <= 0; j++, k++)//菱形
                    for (int k1 = -k; k1 <= k; k1++)
                    {
                        if (j != 0) {
                            result.push_back(Point(allPoints[i].x + j, allPoints[i].y + k1));
                            result.push_back(Point(allPoints[i].x - j, allPoints[i].y + k1));
                        }
                        else {
                            result.push_back(Point(allPoints[i].x, allPoints[i].y + k1));
                        }
                    }
            }
            return result;
        }
        #pragma endregion

        #pragma region 变换算法部分
        /// 平移任意图形，控制点以std::vector<Points> 传入传出
        static void translation(vector<Point*> points, int x_diff, int y_diff) {
            for (int i = 0; i < points.size(); i++) {
                translation(points[i], x_diff, y_diff);
            }
        }

        /// 图形绕指定点旋转
        static void rotate(vector<Point*> points, double angle,const Point & axis) {
            for (int i = 0; i < points.size(); i++) {
                rotate(points[i], angle, axis);
            }
        }

        //图形缩放
        /// 图形以指定点为中心放缩
        static void zoom(vector<Point*> points, Point center, double rate) {
            for (int i = 0; i < points.size(); i++) {
                zoom(points[i], center, rate);
            }
        }
        #pragma endregion

        //de Caste贝塞尔曲线
        static vector<Point> BezierLine(vector<Point> Points) {          //Bezier曲线
            vector<Point> base;
            vector<Point> result;
            for (float t = 0; t <= 1.01; t += 0.05) {
                Point p = Bezier(Points, t);
                p.x = int(p.x + 0.5);
                p.y = int(p.y + 0.5);
                base.push_back(p);
            }
            for (int i = 0; i < base.size() - 1; i++)
            {
                Point start = base[i];
                Point end = base[i + 1];

                auto x1 = start.x, x2 = end.x, y1 = start.y, y2 = end.y;
                int x = x1;
                int y = y1;
                int dx = abs(x2 - x1);
                int dy = abs(y2 - y1);
                int s1 = x2 > x1 ? 1 : -1;
                int s2 = y2 > y1 ? 1 : -1;
                result.reserve(max(dx, dy));

                bool interchange = false; // 默认不互换 dx、dy
                if (dy > dx)              // 当斜率大于 1 时，dx、dy 互换
                {
                    int temp = dx;
                    dx = dy;
                    dy = temp;
                    interchange = true;
                }

                int p = 2 * dy - dx;
                for (int i = 0; i < dx; i++) {
                    result.push_back({ x, y });
                    if (p >= 0) {
                        if (!interchange) // 当斜率 < 1 时，选取上下象素点
                            y += s2;
                        else // 当斜率 > 1 时，选取左右象素点
                            x += s1;
                        p -= 2 * dx;
                    }
                    if (!interchange)
                        x += s1; // 当斜率 < 1 时，选取 x 为步长
                    else
                        y += s2; // 当斜率 > 1 时，选取 y 为步长
                    p += 2 * dy;
                }
                result.push_back(p);
            }
            return result; 
        }
        static Point Bezier(vector<Point> points, double t) {
            int n = points.size() - 1;
            Point result = { 0, 0 };

            for (int i = 0; i <= n; i++) {
                float binomial_coefficient = 1;
                for (int j = 1; j <= i; j++) {
                    binomial_coefficient *= (double)(n - j + 1) / j;
                }

                float factor = binomial_coefficient * pow(t, i) * pow(1 - t, n - i);
                result.x += factor * points[i].x;
                result.y += factor * points[i].y;
            }
            return result;
        }

        //多边形填充算法
        static vector<Point> PolyFill(vector<Point> p) {          //扫描线填充
            vector<Point> result;
            if (p.size() == 0) {
                return result;
            }
            int Ymax = p[0].y, Ymin = p[0].y;
            for (int i = 1; i < p.size(); i++) {
                if (p[i].y > Ymax) {
                    Ymax = p[i].y;
                }
                if (p[i].y < Ymin) {
                    Ymin = p[i].y;
                }
            }
            Edge** NET = new Edge * [Ymax - Ymin + 1];      //初始化NET
            for (int i = 0; i < Ymax - Ymin + 1; i++) {
                NET[i] = NULL;
            }
            for (int i = 0; i < p.size() - 1; i++) {
                Edge* edge = new Edge;
                int ymin = p[i].y > p[i + 1].y ? p[i + 1].y : p[i].y;
                edge->ymax = p[i].y > p[i + 1].y ? p[i].y : p[i + 1].y;
                edge->x = p[i].y > p[i + 1].y ? p[i + 1].x : p[i].x;
                if ((p[i].y - p[i + 1].y) != 0) {
                    edge->deltax = float(p[i].x - p[i + 1].x) / float(p[i].y - p[i + 1].y);
                    edge->nextEdge = NET[ymin - Ymin];
                    NET[ymin - Ymin] = edge;
                }
                if (i + 1 == p.size() - 1) {
                    Edge* edge1 = new Edge;
                    int ymin = p[0].y > p[i + 1].y ? p[i + 1].y : p[0].y;
                    edge1->ymax = p[0].y > p[i + 1].y ? p[0].y : p[i + 1].y;
                    edge1->x = p[0].y > p[i + 1].y ? p[i + 1].x : p[0].x;
                    if ((p[0].y - p[i + 1].y) != 0) {
                        edge1->deltax = float(p[0].x - p[i + 1].x) / float(p[0].y - p[i + 1].y);
                        edge1->nextEdge = NET[ymin - Ymin];
                        NET[ymin - Ymin] = edge1;
                    }
                }
            }
            Edge* AET = NULL;        //建立活性边表
            for (int i = 0; i < Ymax - Ymin + 1; i++) {
                Edge* p1 = AET;                                 //从AET删除过期的边
                while (p1 != NULL && p1->ymax == i + Ymin) {
                    AET = AET->nextEdge;
                    delete p1;
                    p1 = AET;
                }
                if (p1 != NULL && p1->nextEdge != NULL) {
                    Edge* p2 = p1;
                    p1 = p1->nextEdge;
                    while (p1 != NULL) {
                        int k = p1->ymax;
                        if (p1->ymax == i + Ymin) {
                            p2->nextEdge = p1->nextEdge;
                            delete p1;
                            p1 = p2->nextEdge;
                        }
                        else {
                            p2 = p1;
                            p1 = p1->nextEdge;
                        }
                    }
                }
                for (Edge* p = AET; p != NULL; p = p->nextEdge) {   //更新x
                    p->x += p->deltax;
                }

                for (Edge* p = NET[i]; p != NULL; p = p->nextEdge) {   //向AET加入新的边
                    InsertEdge(AET, p);
                }

                for (Edge* p = AET; p != NULL; p = p->nextEdge->nextEdge) {     //填充
                    for (int j = int(p->x + 0.5); j <= int(p->nextEdge->x + 0.5); j++) {
                        result.push_back({ j , i + Ymin });
                    }
                }
            }
            return result;
        }

        //Bre直线
        static vector<Point> BresenhamLining(Point start, Point end) {
            vector<Point> result{};
            auto x1 = start.x, x2 = end.x, y1 = start.y, y2 = end.y;
            int x = x1;
            int y = y1;
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);
            int s1 = x2 > x1 ? 1 : -1;
            int s2 = y2 > y1 ? 1 : -1;
            result.reserve(max(dx, dy));

            bool interchange = false; // 默认不互换 dx、dy
            if (dy > dx)              // 当斜率大于 1 时，dx、dy 互换
            {
                int temp = dx;
                dx = dy;
                dy = temp;
                interchange = true;
            }

            int p = 2 * dy - dx;
            for (int i = 0; i < dx; i++) {
                result.push_back({ x, y });
                if (p >= 0) {
                    if (!interchange) // 当斜率 < 1 时，选取上下象素点
                        y += s2;
                    else // 当斜率 > 1 时，选取左右象素点
                        x += s1;
                    p -= 2 * dx;
                }
                if (!interchange)
                    x += s1; // 当斜率 < 1 时，选取 x 为步长
                else
                    y += s2; // 当斜率 > 1 时，选取 y 为步长
                p += 2 * dy;
            }
            return result;
        }
        //中点算法直线
        static vector<Point> MidPointLining(Point start, Point end) {
            int dx, dy, d, UpIncre, DownIncre, x, y;
            auto x0 = start.x, x1 = end.x, y0 = start.y, y1 = end.y;
            vector<Point> result{};
            if (x0 > x1) {
                x = x1;
                x1 = x0;
                x0 = x;
                y = y1;
                y1 = y0;
                y0 = y;
            }
            x = x0;
            y = y0;
            dx = x1 - x0;
            dy = y1 - y0;
            result.reserve(max(dx, dy));
            // 0 <= k <= 1
            if (dy >= 0 && dy < dx) {
                d = dx - 2 * dy;
                UpIncre = 2 * dx - 2 * dy;
                DownIncre = -2 * dy;
                while (x <= x1) {
                    result.push_back({ x, y });
                    x++;
                    if (d < 0) {
                        y++;
                        d += UpIncre;
                    }
                    else
                        d += DownIncre;
                }
            }
            // k > 1
            else if (dy >= 0 && dy > dx) {
                d = -dy + 2 * dx;
                UpIncre = 2 * dx;
                DownIncre = 2 * dx - 2 * dy;
                while (y <= y1) {
                    result.push_back({ x, y });
                    y++;
                    if (d < 0) {
                        d += UpIncre;
                    }
                    else {
                        x++;
                        d += DownIncre;
                    }
                }
            }

            // -1 <= k < 0
            else if (dy < 0 && dy >= -dx) {
                d = -dx - 2 * dy;
                UpIncre = -2 * dy;
                DownIncre = -2 * dx - 2 * dy;

                while (x <= x1) {
                    result.push_back({ x, y });
                    x++;
                    if (d < 0) {
                        d += UpIncre;
                    }
                    else {
                        y--;
                        d += DownIncre;
                    }
                }
            }
            // k < -1
            else if (dy < 0 && dy < -dx) {
                d = -2 * dx - dy;
                UpIncre = -2 * dx - 2 * dy;
                DownIncre = -2 * dx;

                while (y >= y1) {
                    result.push_back({ x, y });
                    y--;
                    if (d < 0) {
                        x++;
                        d += UpIncre;
                    }
                    else {
                        d += DownIncre;
                    }
                }
            }
            return result;
        }
        //DDA直线
        static vector<Point> DDALine(const Point & start, const Point& end)
        {
            vector<Point> result;
            //以下是直线段的绘制
            int x1, x2, y1, y2;
            if (start.x > end.x) x1 = end.x, x2 = start.x, y1 = end.y, y2 = start.y;
            else x1 = start.x, x2 = end.x, y1 = start.y, y2 = end.y;
            int a = y1 - y2, b = x2 - x1;
            int xbase = x1, ybase = y1;
            int s1 = 1, s2 = (a < 0 ? 1 : -1);
            if (abs(b) >= abs(a))//dx>dy
            {
                int d = ((a << 1) + (a < 0 ? 1 : -1) * b), deta1 = a << 1, deta2 = (a + (a < 0 ? 1 : -1) * b) << 1;
                while (xbase <= x2)
                {
                    if ((a < 0) ^ (d >= 0))
                    {
                        xbase += s1, ybase += s2;
                        result.push_back(Point(xbase, ybase));
                        d += deta2;
                    }
                    else
                    {
                        xbase += s1;
                        result.push_back(Point(xbase, ybase));
                        d += deta1;
                    }
                }
            }
            else
            {
                int d = ((a < 0 ? 1 : -1) * (b << 1)) + a, deta1 = (a < 0 ? 1 : -1) * (b << 1), deta2 = (a + (a < 0 ? 1 : -1) * b) << 1;
                while (ybase != y2)
                {
                    if ((a < 0) ^ (d >= 0))
                    {
                        ybase += s2;
                        result.push_back(Point(xbase, ybase));
                        d += deta1;
                    }
                    else
                    {
                        xbase += s1; ybase += s2;
                        result.push_back(Point(xbase, ybase));
                        d += deta2;
                    }
                }
                result.push_back(Point(xbase, ybase));
            }
            return result;
        }

        //圆形
        static vector<Point> MidPointCircle(const Point& start, const Point& end) {
            vector<Point> result{};
            int radius =(int) sqrt((end.y - start.y) * (end.y - start.y) + (end.x - start.x) * (end.x - start.x));

            vector<Point> temp = CircleArc1stRange(radius);


            for (int i = 0; i < 8; i++) {
                vector<Point> temp2 = CircleArcCompletRange(temp, i);
                result.insert(result.end(), temp2.begin(), temp2.end());
            }

            

            for (int i = 0; i < result.size(); i++) {
                result[i].x += start.x;
                result[i].y += start.y;
            }
            return result;
        }

        //任意段圆弧
        static vector<Point> CircleArc(const Point & center, const Point& start,const Point& end) {
            vector<Point> result{};
            
            int radius =(int) round(sqrt((start.y - center.y) * (start.y - center.y) + (start.x - center.x) * (start.x - center.x)));
            if (radius == 0)
                return result;
            if (end.x == center.x && end.y == center.y)
                return result;
            int dx = end.x - center.x;
            int dy = end.y - center.y;

            double t1 = (radius * radius) / (double)(dx * dx + dy * dy);
            double t2 = -t1;


            Point endP;
            endP.x = center.x + t1 * dx;
            endP.y = center.y + t1 * dy;



            Point startP = Point(start.x - center.x, start.y - center.y);
            endP = Point(endP.x - center.x, endP.y - center.y);


            int startID = FindRangeofArc(startP);
            int endID = FindRangeofArc(endP);


            vector<Point> temp = CircleArc1stRange(radius);

            //仅绘制一个区间内的圆弧
            if (startID == endID) {
                if ((startP.y >= 0 && startP.x < endP.x)
                    || (startP.y < 0 && startP.x > endP.x)) {
                    result = CircleArc1Range(startP, endP, radius);
                    for (int i = 0; i < result.size(); i++) {
                        result[i] = result[i] + center;
                    }
                    return result;
                }
                else if((startP.y > 0 && startP.x > endP.x)
                    || (startP.y <= 0 && startP.x < endP.x))
                {
                    for (int i = 1; i <= 7; i++) {
                        vector<Point> temp2 = CircleArcCompletRange(temp, (startID + i) % 8);
                        result.insert(result.end(), temp2.begin(), temp2.end());
                    }
                }

            }



            if (startID < endID) {
                for (int i = startID + 1; i < endID; i++) {
                    vector<Point> temp2 = CircleArcCompletRange(temp, i);
                    result.insert(result.end(), temp2.begin(), temp2.end());
                }
            }
            else if(startID > endID)
            {
                for (int i = startID + 1; i < endID + 8; i++) {
                    int p = i;
                    if (p >= 8)
                        p-=8;
                    vector<Point> temp2 = CircleArcCompletRange(temp, p);
                    result.insert(result.end(), temp2.begin(), temp2.end());
                }
            }

            //顺时针绘制起点区间
            vector<Point> startTemp = CircleArc1Range(startP, GetNextSidePoint(startID, true, radius), radius);
            result.insert(result.end(), startTemp.begin(), startTemp.end());

            vector<Point> endTemp = CircleArc1Range(GetNextSidePoint(endID, false, radius), endP, radius);
            result.insert(result.end(), endTemp.begin(), endTemp.end());

            for (int i = 0; i < result.size(); i++) {
                result[i] = result[i] + center;
            }
            return result;
        }
        
        //Cohen-Sutherland算法裁剪直线
        static vector<Point> CSClipping(Point&start, Point&end, Boarder boarder) {
            constexpr int LEFT = 1 << 0;
            constexpr int RIGHT = 1 << 1;
            constexpr int BOTTOM = 1 << 2;
            constexpr int TOP = 1 << 3;
            auto encode = [=](Point p) {
                int c{ 0 };
                if (p.x < boarder.left)
                    c |= LEFT;
                if (p.x > boarder.right)
                    c |= RIGHT;
                if (p.y < boarder.bottom)
                    c |= BOTTOM;
                if (p.y > boarder.top)
                    c |= TOP;
                return c;
            };
            auto code_start = encode(start);
            auto code_end = encode(end);
            if ((code_start | code_end) == 0)
                return BresenhamLining(start, end);
            if ((code_start & code_end) != 0)
                return {};
            while (code_start != 0 || code_end != 0) {
                int x{}, y{};
                auto code = code_start;
                if (code_start == 0)
                    code = code_end;
                if ((LEFT & code) != 0) {
                    x = boarder.left;
                    y = start.y + (float)(end.y - start.y) * (float)(boarder.left - start.x) /
                        (float)(end.x - start.x);
                }
                else if ((RIGHT & code) != 0) {
                    x = boarder.right;
                    y = start.y + (float)(end.y - start.y) *
                        (float)(boarder.right - start.x) /
                        (float)(end.x - start.x);
                }
                else if ((BOTTOM & code) != 0) {
                    y = boarder.bottom;
                    x = start.x + (float)(end.x - start.x) *
                        (float)(boarder.bottom - start.y) /
                        (float)(end.y - start.y);
                }
                else if ((TOP & code) != 0) {
                    y = boarder.top;
                    x = start.x + (float)(end.x - start.x) * (float)(boarder.top - start.y) /
                        (float)(end.y - start.y);
                }
                if (code == code_start) {
                    start = { x, y };
                    code_start = encode(start);
                }
                else {
                    end = { x, y };
                    code_end = encode(end);
                }
            }
            return BresenhamLining(start, end);
        }
        
        //中点分割裁剪算法
        static vector<Point> MidPointClipping(Point&start, Point&end, Boarder boarder) {
            constexpr int LEFT = 1 << 0;
            constexpr int RIGHT = 1 << 1;
            constexpr int BOTTOM = 1 << 2;
            constexpr int TOP = 1 << 3;
            auto encode = [=](Point p) {
                int c{ 0 };
                if (p.x < boarder.left)
                    c |= LEFT;
                if (p.x > boarder.right)
                    c |= RIGHT;
                if (p.y < boarder.bottom)
                    c |= BOTTOM;
                if (p.y > boarder.top)
                    c |= TOP;
                return c;
            };
            auto code_start = encode(start);
            auto code_end = encode(end);
            if ((code_start | code_end) == 0)
                return BresenhamLining(start, end);
            if ((code_start & code_end) != 0) {
                start = { boarder.left - 1, boarder.bottom - 1 };
                end = start;
                return {};
            }
            auto midp = [](Point p1, Point p2) -> Point {
                return { (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 };
            };
            if (code_end != 0) {
                auto p11 = start;
                auto p22 = end;
                auto pmid = midp(p11, p22);
                while (std::abs(p11.x - pmid.x) > 1 || std::abs(p11.y - pmid.y) > 1) {
                    auto cmid = encode(pmid);
                    if (cmid == 0)
                        p11 = pmid;
                    else
                        p22 = pmid;
                    pmid = midp(p11, p22);
                }
                end = pmid;
            }
            if (code_start != 0) {
                auto p11 = start;
                auto p22 = end;
                auto pmid = midp(p11, p22);
                while (std::abs(p11.x - pmid.x) > 1 || std::abs(p11.y - pmid.y) > 1) {
                    auto cmid = encode(pmid);
                    if (cmid == 0)
                        p22 = pmid;
                    else
                        p11 = pmid;
                    pmid = midp(p11, p22);
                }
                start = pmid;
            }
            return BresenhamLining(start, end);
        }

        //填充算法
        static void seedFill(const Point & clickPosition, int color) {
            // 如果当前像素不是目标颜色，或者已经填充过，返回
            if (clickPosition.x < 0 || clickPosition.y < 0 || clickPosition.x >= CANVASLENGTH || clickPosition.y >= CANVASLENGTH || canvas[clickPosition.x][clickPosition.y] == 1)
                return;

            stack<Point> stack;

            // 将当前像素填充为目标颜色
            canvas[clickPosition.x][clickPosition.y] = 1;
            stack.push(Point(clickPosition.x, clickPosition.y));

            while (!stack.empty()) {
                Point top = stack.top();
                stack.pop();
                if(top.x >= 0&& top.x < CANVASLENGTH && top.y >=0 && top.y < CANVASLENGTH)
                    canvas[top.x][top.y] = color;
                else {
                    continue;
                }

                if (top.x + 1 < CANVASLENGTH &&  canvas[top.x + 1][top.y] == 0) {
                    stack.push(Point(top.x + 1, top.y));
                }
                if (top.x - 1 >= 0 && canvas[top.x - 1][top.y] == 0) {
                    stack.push(Point(top.x - 1, top.y));
                }
                if (top.y + 1 < CANVASLENGTH && canvas[top.x][top.y+1] == 0) {
                    stack.push(Point(top.x, top.y+1));
                }
                if (top.y - 1 >= 0 && canvas[top.x][top.y-1] == 0) {
                    stack.push(Point(top.x, top.y-1));
                }
            }

        }
        
    private:

        //平移辅助函数
        static void translation(Point* p, int x_diff, int y_diff) {
            p->x = p->x + x_diff;
            p->y = p->y + y_diff;
        }
        /// 旋转辅助函数，点以另一个点为中心旋转
        static void rotate(Point* p, double angle,const Point & axis) {
            p->x = p->x - axis.x;
            p->y = p->y - axis.y;
            rotate(p, angle);
            p->x = p->x + axis.x;
            p->y = p->y + axis.y;
        }
        //旋转辅助函数，以原点为中心旋转
        static void rotate(Point* p, double angle) {
            double cos_v = std::cos(angle);
            double sin_v = std::sin(angle);
            int x = p->x;
            int y = p->y;
            p->x = (int)round(((double)x * cos_v - (double)y * sin_v));
            p->y = (int)round(((double)x * sin_v + (double)y * cos_v));
        }
        //缩放函数
        static void zoom(Point* p, Point center, double rate) {
            int x = p->x;
            int y = p->y;
            double k = (double)(y - center.y) / (double)(x - center.x);
            if (std::isfinite(k)) {
                int new_x = (int)round(rate * (double)(x - center.x)) + center.x;
                int new_y = (int)round(k * double(new_x - center.x)) + center.y;
                p->x = new_x;
                p->y = new_y;
            }
            else {
                    p->x = (int)round(rate * (double)(x - center.x)) + center.x;
                    p->y = (int)round(rate * (double)(y - center.y)) + center.y;
            }
        }

        //绘制第一区间的完整圆弧
        static vector<Point> CircleArc1stRange(const int& radius) {
            vector<Point> result{};
            int dx, dy, e;
            dx = 0;
            dy = radius;
            e = 1 - radius;
            //vector<Point> temp = CirclePoints(Point(dx, dy));
            //result.insert(result.end(), temp.begin(), temp.end());
            result.push_back(Point(dx, dy));
            while (dx <= dy) {
                if (e < 0)
                    e += 2 * dx + 3;
                else
                {
                    e += 2 * (dx - dy) + 5;
                    dy--;
                }
                dx++;
                result.push_back(Point(dx, dy));
                //vector<Point> temp = CirclePoints(Point(dx, dy));
                //result.insert(result.end(), temp.begin(), temp.end());
            }
            return result;
        }//Get The fir range points

        //Circle Arc Clockwise
        static int FindRangeofArc(const Point& point) {
            int x = point.x, y = point.y;
            if (x > 0 && y >= 0) {
                if (x < y)
                    return 0;
                else
                    return 1;
            }
            else if (x >= 0 && y < 0) {
                if (x > -y)
                    return 2;
                else
                    return 3;
            }
            else if (x < 0 && y <= 0) {
                if (x > y)
                    return 4;
                else
                    return 5;
            }
            else
            {
                if (-x > y)
                    return 6;
                else
                    return 7;
            }
        }

        //绘制第一区间的部分圆弧
        static vector<Point> CircleArcOn1stRange(const Point& start, const Point& end, const int & radius) {
            vector<Point> result{};

            Point startP = start;
            Point endP = end;

            int x, y, e;
            x = 0;
            y = radius;
            e = 1 - radius;
            if (x >= startP.x) {
                result.push_back(Point(x, y));
            }
            while (x <= y) {
                if (e < 0)
                    e += 2 * x + 3;
                else {
                    e += 2 * (x - y) + 5; y--;
                }
                x++;
                if (x >= startP.x && x <= endP.x) {
                    result.push_back(Point(x, y));
                }
            }
            return result; 
        }
        //绘制一个区间内的部分圆弧
        static vector<Point> CircleArc1Range(const Point & start, const Point & end, const int & radius) {
            vector<Point> result{};
            int x = (int)((start.x + end.x)+0.5)/2;
            int y = (int)((start.y + end.y) + 0.5) / 2;
            int id = FindRangeofArc(Point(x, y));

            //首先需要根据区间ID转换起点和终点的坐标
            switch (id)//********************* border?
            {
            case 0:
                //如果在第一区间，则不需要转换坐标，直接代入两点获得
                result = CircleArcOn1stRange(start, end, radius);
                break;
            case 1: {
                Point startP = Point(start.y, start.x);
                Point endP = Point(end.y, end.x);
                result = CircleArcOn1stRange(endP, startP,radius);
            }
                break;
            case 2:
            {
                Point startP = Point(-start.y, start.x);
                Point endP = Point(-end.y, end.x);
                result = CircleArcOn1stRange(startP, endP,radius);
            }
                break;
            case 3:
            {
                Point startP = Point(start.x, -start.y);
                Point endP = Point(end.x, -end.y);
                result = CircleArcOn1stRange(endP, startP, radius);
            }
                break;
            case 4:
            {
                Point startP = Point(-start.x, -start.y);
                Point endP = Point(-end.x, -end.y);
                result = CircleArcOn1stRange(startP, endP, radius);
            }
                break;
            case 5:
            {
                Point startP = Point(-start.y, -start.x);
                Point endP = Point(-end.y, -end.x);
                result = CircleArcOn1stRange(endP, startP, radius);
            }
                break;
            case 6:
            {
                Point startP = Point(start.y, -start.x);
                Point endP = Point(end.y, -end.x);
                result = CircleArcOn1stRange(startP, endP, radius);
            }
                break;
            case 7:
            {
                Point startP = Point(-start.x, start.y);
                Point endP = Point(-end.x, end.y);
                result = CircleArcOn1stRange(endP, startP, radius);
            }
                break;
            default:
                throw "Out of Range !!";
                break;
            }
            //将获得的第一区间的圆弧转换回原来区间
            result = CircleArcCompletRange(result, id);
            return result;            
        }
        //根据第一区间内的圆弧，将其转换为其他区间的圆弧
        static vector<Point> CircleArcCompletRange(const vector<Point> & firPoints,const int & id) {
            vector<Point> result{};
            result = firPoints;
            switch (id)
            {
            case 0:
                break;
            case 1:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(result[i].y, result[i].x);
                }
                break;
            case 2:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(result[i].y, -1 * result[i].x);
                }
                break;
            case 3:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(result[i].x, -1 * result[i].y);
                }
                break;
            case 4:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(-1 * result[i].x, -1 * result[i].y);
                }
                break;
            case 5:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(-1*result[i].y, -1 * result[i].x);
                }
                break;
            case 6:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(-1 * result[i].y, result[i].x);
                }
                break;
            case 7:
                for (int i = 0; i < result.size(); i++) {
                    result[i] = Point(-1*result[i].x, result[i].y);
                }
                break;
            default:
                throw 1;
                break;
            }
            return result;
        }
           
        //获取区间下个边界点或者上个边界点
        static Point GetNextSidePoint(const int& id, bool isNext, const int & radius) {
            Point result(0,0);
            int value = (int)1.41 * radius;

            switch (id)
            {
            case 0:
                if (isNext) {
                    result = Point(value, value);
                }
                else
                {
                    result = Point(0, radius);
                }
                break;
            case 1:
                if (isNext) {
                    result = Point(radius, 0);
                }
                else
                {
                    result = Point(value, value);
                }
                break;
            case 2:
                if (isNext) {
                    result = Point(value, -value);
                }
                else
                {
                    result = Point(radius, 0);
                }
                break;
            case 3:
                if (isNext) {
                    result = Point(0, -radius);
                }
                else
                {
                    result = Point(value, -value);
                }
                break;
            case 4:
                if (isNext) {
                    result = Point(-value, -value);
                }
                else
                {
                    result = Point(0, -radius);
                }
                break;
            case 5:
                if (isNext) {
                    result = Point(-radius, 0);
                }
                else
                {
                    result = Point(-value, -value);
                }
                break;
            case 6:
                if (isNext) {
                    result = Point(-value, value);
                }
                else
                {
                    result = Point(-radius, 0);
                }
                break;
            case 7:
                if (isNext) {
                    result = Point(0, radius);
                }
                else
                {
                    result = Point(-value, value);
                }
                break;
            default:
                throw "Out of Range !!";
                break;
            }

            return result;
        }


    };

}