#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

int pseudoscalar(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - A.y) - (B.x - A.x) * (A.y - O.y);
}

bool isPointInsideTriangle(Point O, Point A, Point B, Point C) {
    int p1 = pseudoscalar(O, A, B);
    int p2 = pseudoscalar(O, B, C);
    int p3 = pseudoscalar(O, C, A);
    if (p1 > 0 && p2 > 0 && p3 > 0 || p1 < 0 && p2 < 0 && p3 < 0) {
        return true;
    }
    return false;
}

istream& operator>> (istream& in, Point& point) {
    in >> point.x >> point.y;
    return in;
}

int main()
{
    Point O, A, B, C;
    cin >> A >> B >> C;
    while (cin >> O) {
        cout << isPointInsideTriangle(O, A, B, C) << endl;
        cout << "pseudoscalar(O, A, B): " << pseudoscalar(O, A, B) << endl;
        cout << "pseudoscalar(O, B, C): " << pseudoscalar(O, B, C) << endl;
        cout << "pseudoscalar(O, C, A): " << pseudoscalar(O, C, A) << endl;
    }
}