#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   
    int n, m;
    if (!(cin >> n >> m))
        return 0;
    vector<vector<pair<int, int>>> matrix(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        vector<pair<int, int>> row;
        for (int k = 0; k < c; k++) {
            int j, a;
            cin >> j >> a;
            row.push_back(make_pair(j, a));
        }
        matrix[i] = row;
    }
    vector<double> v(n, 1.0);
    double norm_v = 0.0;
    for (int i = 0; i < n; i++) {
        norm_v += v[i] * v[i];
    }
    norm_v = sqrt(norm_v);
    if (norm_v == 0) norm_v = 1.0;
    for (int i = 0; i < n; i++) {
        v[i] /= norm_v;
    }
    int iterations = 1200;
    for (int iter = 0; iter < iterations; iter++) {
        vector<double> w(n, 0.0);
        for (int i = 0; i < n; i++) {
            for (const auto &p : matrix[i]) {
                int j = p.first;
                int a = p.second;
                w[i] += a * v[j];
            }
        }
        double norm_w = 0.0;
        for (int i = 0; i < n; i++) {
            norm_w += w[i] * w[i];
        }
        norm_w = sqrt(norm_w);
        if (norm_w == 0) break;
        for (int i = 0; i < n; i++) {
            v[i] = w[i] / norm_w;
        }
    }
    vector<double> Av(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (const auto &p : matrix[i]) {
            int j = p.first;
            int a = p.second;
            Av[i] += a * v[j];
        }
    }
    double eigenvalue = 0.0;
    for (int i = 0; i < n; i++) {
        eigenvalue += v[i] * Av[i];
    }
    double abs_eigenvalue = (eigenvalue >= 0) ? eigenvalue : -eigenvalue;
    double rounded = round(abs_eigenvalue * 10000) / 10000.0;
    cout << fixed << setprecision(4) << rounded;
    return 0;
}