#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

const int mf = 500;
using namespace std;

typedef vector<double> Vector;

int main() {

    setlocale(LC_ALL, "Ru");
    int N;
    double a, lamda, ro, c, h, tau;
    double Tl, T0, Tr, L, t_end, time;
    Vector T(mf, 0.0), TT(mf, 0.0);

    cout << "������� ���������� ����� �� ���������������� ���������� (N): ";
    cin >> N;
    cout << "������� ��������� �� ������� (t_end): ";
    cin >> t_end;
    cout << "������� ������� �������� (L): ";
    cin >> L;
    cout << "������� ����������� ���������������� ��������� �������� (lamda): ";
    cin >> lamda;
    cout << "������� ��������� ��������� �������� (ro): ";
    cin >> ro;
    cout << "������� ������������ ��������� �������� (c): ";
    cin >> c;
    cout << "������� ��������� ����������� (T0): ";
    cin >> T0;
    cout << "������� ����������� �� ������� x=0 (Tl): ";
    cin >> Tl;
    cout << "������� ���������� �� ������� x=L (Tr): ";
    cin >> Tr;

    a = lamda / (ro * c);

    h = L / (N - 1);

    tau = 0.25 * h * h / a;

    for (int i = 1; i < N - 1; ++i) {
        T[i] = T0;
    }

    T[0] = Tl;
    T[N - 1] = Tr;

    time = 0.0;
    while (time < t_end) {
        time += tau;

        for (int i = 0; i < N; ++i) {
            TT[i] = T[i];
        }

        for (int i = 1; i < N - 1; ++i) {
            T[i] = TT[i] + a * tau / (h * h) * (TT[i + 1] - 2.0 * TT[i] + TT[i - 1]);
        }
    }

    ofstream f("res.txt");
    f << fixed << setprecision(4);
    f << "������� �������� L = " << L << endl;
    f << "����� ����� �� ���������������� ���������� N = " << N << endl;
    f << "����������� ���������������� ��������� �������� lamda = " << lamda << endl;
    f << "��������� ��������� �������� ro = " << ro << endl;
    f << "������������ ��������� �������� c = " << c << endl;
    f << "��������� ����������� T0 = " << T0 << endl;
    f << "����������� �� ������� x=0, Tl = " << Tl << endl;
    f << "����������� �� ������� x=L, Tr = " << Tr << endl;
    f << "��������� ������� � ����� �� ���������������� ���������� x, h = " << h << endl;
    f << "������������� ���� � ������ ������� tau = " << tau << endl;
    f << "������������� ���� � ������ ������� t = " << t_end << endl;
    f.close();

    ofstream g("tempr.txt");
    g << fixed << setprecision(5);
    for (int i = 0; i < N; ++i) {
        g << setw(10) << h * i << " " << setw(10) << T[i] << endl;
    }
    g.close();

    return 0;
}
