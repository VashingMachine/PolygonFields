#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
	char name;
	double x;
	double y;
	double angleToMidPoint;
	Point(double x, double y, char z = '0') : x(x), y(y), name(z) {}
	double operator*(Point &p) {
		return x * p.x + y * p.y;
	}
};

std::ostream & operator<<(std::ostream &out, Point &p) {
	out << p.x << " " << p.y;
	return out;
}

double d(Point &a, Point &b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double getAngle(Point &a, Point &b) {
	Point OX = { 1, 0 };
	Point follower = { b.x - a.x, b.y - a.y };
	double cos_ab = OX * follower / (sqrt(OX * OX) * sqrt(follower * follower));
	return follower.y >= 0 ? acos(cos_ab) : 2 * M_PI - acos(cos_ab);
}

Point getMidPoint(vector<Point> &points) {
	Point p = { (points[0].x + points[1].x) / 2, (points[0].y + points[1].y) / 2 };
	for (int i = 1; i < points.size(); i++) {
		p.x = (p.x + points[i].x) / 2;
		p.y = (p.y + points[i].y) / 2;
	}
	return p;
}

double heronField(Point &a, Point &b, Point &c) {
	double ac = d(a, c);
	double ab = d(a, b);
	double bc = d(b, c);
	double p = (ab + ac + bc) / 2;
	return sqrt(p * (p - ab) * (p - ac) * (p - bc));
}

void sortByAngle(vector<Point> &points) {
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size() - i - 1; j++) {
			if (points[j].angleToMidPoint > points[j + 1].angleToMidPoint) {
				Point p = points[j];
				points[j] = points[j + 1];
				points[j + 1] = p;
			}
		}
	}
}

double fullField(vector<Point> &points) {
	Point mid = getMidPoint(points);
	for (int i = 0; i < points.size(); i++) {
		points[i].angleToMidPoint = getAngle(mid, points[i]);
	}
	sortByAngle(points);
	double sumField = 0;
	for (int i = 0; i < points.size() - 1; i++) {
		sumField += heronField(points[i], points[i + 1], mid);
	}
	sumField += heronField(points[points.size() - 1], points[0], mid);
	return sumField;
}

vector<Point> & readValues() {
	int n = 0, x = 0, y = 0; 
	char c = 'A';
	vector<Point> & points = *(new vector<Point>());
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points.push_back(*(new Point(x, y, c++)));
	}
	return points;

}

int main() {
	vector<Point> & points = readValues();
	cout << "Area: " << fullField(points) << endl;
	cout << "Order in polygon: " << endl;
	for (int i = 0; i < points.size(); i++){
		if (i != points.size() - 1)
			cout << points[i].name << "->";
		else
			cout << points[i].name;
	}
	delete &points;
}