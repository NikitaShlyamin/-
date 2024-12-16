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

    cout << "Введите количество узлов по пространственной координате (N): ";
    cin >> N;
    cout << "Введите окончание по времени (t_end): ";
    cin >> t_end;
    cout << "Введите толщину пластины (L): ";
    cin >> L;
    cout << "Введите коэффициент теплопроводности материала пластины (lamda): ";
    cin >> lamda;
    cout << "Введите плотность материала пластины (ro): ";
    cin >> ro;
    cout << "Введите теплоемкость материала пластины (c): ";
    cin >> c;
    cout << "Введите начальную температуру (T0): ";
    cin >> T0;
    cout << "Введите температуру на границе x=0 (Tl): ";
    cin >> Tl;
    cout << "Введите темературу на границе x=L (Tr): ";
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
    f << "Толщина пластины L = " << L << endl;
    f << "Число узлов по пространственной координате N = " << N << endl;
    f << "Коэффициент теплопроводности материала пластины lamda = " << lamda << endl;
    f << "Плотность материала пластины ro = " << ro << endl;
    f << "Теплоемкость материала пластины c = " << c << endl;
    f << "Начальная температура T0 = " << T0 << endl;
    f << "Температура на границе x=0, Tl = " << Tl << endl;
    f << "Температура на границе x=L, Tr = " << Tr << endl;
    f << "Результат получен с шагом по пространственной координате x, h = " << h << endl;
    f << "Температурное поле в момент времени tau = " << tau << endl;
    f << "Температурное поле в момент времени t = " << t_end << endl;
    f.close();

    ofstream g("tempr.txt");
    g << fixed << setprecision(5);
    for (int i = 0; i < N; ++i) {
        g << setw(10) << h * i << " " << setw(10) << T[i] << endl;
    }
    g.close();

    return 0;
}
