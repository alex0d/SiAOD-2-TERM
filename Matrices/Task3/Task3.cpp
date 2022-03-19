#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

void fillVector(vector<Point>& v);
void printVector(const vector<Point>& v);

// Псевдоскалярное произведение векторов OA и AB
int pseudoscalar(Point O, Point A, Point B);

// Проверяет, принадлежит ли точка O треугольнику ABC
bool isPointInsideTriangle(Point O, Point A, Point B, Point C);

// Из первого множества выбирает три различные точки так, чтобы треугольник с вершинами в этих точках
// содержал (строго внутри себя) равное количество точек первого и второго множества.
// Результат записывает в вектор ans. Возвращает 0, если точки найдены, иначе -1.
int identicalTriangle(const vector<Point>& v1, const vector<Point>& v2, vector<Point>& ans);

istream& operator>> (istream& in, Point& P) {
    in >> P.x >> P.y;
    return in;
}

ostream& operator<< (ostream& out, const Point& P) {
    out << "(" << P.x << ", " << P.y << ")";
    return out;
}

bool operator== (const Point& A, const Point& B) {
    return A.x == B.x && A.y == B.y;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Работа #2 Двумерный массив. Денисов А.В. ИКБО-03-21. Вариант 7\n\n";

    int n;
    cout << "Введите количество точек в первом множестве: ";
    cin >> n;
    if (n < 1) {
        cout << "Введено недопустимое значение.";
        return 1;
    }
    vector<Point> v1(n);
    cout << "Введите точки первого множества (в формате x y)" << endl;
    fillVector(v1);

    cout << "Введите количество точек во втором множестве: ";
    cin >> n;
    if (n < 1) {
        cout << "Введено недопустимое значение.";
        return 1;
    }
    vector<Point> v2(n);
    cout << "Введите точки второго множества (в формате x y)" << endl;
    fillVector(v2);

    cout << "\nПоддерживаемые команды:\n" <<
        "0 - Выход\n1 - Вывести точки, принадлежащие множествам\n" <<
        "2 - Из первого множества выбрать три различные точки так, чтобы треугольник " << 
        "с вершинами в этих точках содержал (строго внутри себя) " << 
        "равное количество точек первого и второго множества\n";
    int cmd = 1;
    vector<Point> ans(3);
    while (cmd != 0) {
        cout << "\nВведите команду: ";
        cin >> cmd;
        switch (cmd) {
        case 1:
            cout << "Точки 1 множества: ";
            printVector(v1);
            cout << "\nТочки 2 множества: ";
            printVector(v2);
            break;

        case 2:
            if (identicalTriangle(v1, v2, ans) != 1) {
                cout << "Подходящие точки треугольника: ";
                printVector(ans);
            }
            else {
                cout << "Подходящий треугольник не найден.";
            }
            break;

        default:
            break;
        }
    }
    return 0;
}

void fillVector(vector<Point>& v) {
    for (int i = 0; i < v.size(); i++) {
        cin >> v.at(i);
    }
}

void printVector(const vector<Point>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

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

int identicalTriangle(const vector<Point>& v1, const vector<Point>& v2, vector<Point>& ans) {
    int points_in_v1 = 0;
    int points_in_v2 = 0;
    for (Point A : v1) {
        for (Point B : v1) {
            if (A == B) { break; }
            for (Point C : v1) {
                if (C == A || C == B) { break; }
                for (Point O : v1) {
                    if (isPointInsideTriangle(O, A, B, C)) {
                        points_in_v1++;
                    }
                }
                for (Point O : v2) {
                    if (isPointInsideTriangle(O, A, B, C)) {
                        points_in_v2++;
                    }
                }
                if (points_in_v1 != 0 && points_in_v1 == points_in_v2) {
                    ans[0] = A;
                    ans[1] = B;
                    ans[2] = C;
                    return 0;
                }
                points_in_v1 = points_in_v2 = 0;
            }
        }
    }
    return 1;
}