#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void show(vector<vector<float>>& a, int n, int m, bool b) {

	if (b == 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << a[i][j] << "  ";
			cout << "\n";
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++)
				cout << a[i][j] << "  ";
			cout << "| " << a[i][m - 1] << "  ";
			cout << "\n";
		}
	}
}

int main() {

	int n = 0, m = 0;
	ifstream read;

	read.open("D:\\SLAU++\\SLAU\\text.txt");

	char s;
	int k = 0;

	while (!read.eof()) {
		read >> s;
		k++;
	}

	read.close();
	read.open("D:\\SLAU++\\SLAU\\text.txt");

	while (!read.eof()) {
		read.get(s);
		if (s == '/n')
			break;
		if (s == ' ')
			m++;
	}

	n = k / (m + 1) + 1;
	m = n + 1;

	vector<vector<float>> a(n, vector<float>(m, 0));

	read.close();
	read.open("D:\\SLAU++\\SLAU\\text.txt");

	ifstream read_o;
	read_o.open("D:\\SLAU++\\SLAU\\oott.txt");

	if (read.is_open()) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++)
				read >> a[i][j];
			read_o >> a[i][m - 1];
		}
	}
	read_o.close();
	read.close();

	bool trans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) {
			if (a[i][j] > a[i][i]) {
				trans = 1;
				break;
			}
		}
	}
	bool b;

	if (trans == 1) {
		vector<vector<float>> aa(n, vector<float>(n, 0));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				aa[i][j] = a[j][i];
			}
		}

		show(a, n, m, b = 0);
		vector<vector<float>> b(n, vector<float>(n, 0));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					b[i][j] += a[i][k] * aa[k][j];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = b[i][j];
			}
		}
	}

	read.close();
	float e = 0.001;

	show(a, n, m, b = 1);

	//получим ситему подготовленную к релоксации
	for (int i = 0; i < n; i++) {
		float aii = a[i][i];
		for (int j = 0; j < m; j++)
			a[i][j] = (a[i][j] / (aii * (-1)));
		a[i][m - 1] *= -1;
	}

	//начальное приближение

	vector<float> x0(n, 0);
	vector<float> R(n, 0);
	vector<vector<float>> mirr(n, vector<float>(m, 0));
	vector<float> Rnext(n, 0);
	vector<float> otvet(n, 0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++)
			mirr[i][j] = a[i][j];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++)
			a[i][j] *= x0[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			R[i] += a[i][j];
	}

	float max = 0.;
	int jj;

	for (int i = 0; i < n; i++) {
		if (max <= abs(R[i])) {
			max = abs(R[i]);
			jj = i;
		}
	}

	bool cont = 0;

	while (cont != 1) {

		otvet[jj] += R[jj];

		for (int i = 0; i < n; i++) {
			R[i] = R[i] + (mirr[i][jj] * max);
		}

		max = 0;

		for (int i = 0; i < n; i++) {
			if (max <= abs(R[i])) {
				max = abs(R[i]);
				jj = i;
			}
		}

		for (int j = 0; j < n; j++) {
			if (R[j] != 0) {
				if (R[j] <= e)
					cont = 1;
				else {
					cont = 0;
					break;
				}
			}
		}
	}

	ofstream write;

	write.open("D:\\SLAU++\\SLAU\\vivod.txt");

	cout << "\n";
	for (int j = 0; j < n; j++) {
		cout << setprecision(2) << otvet[j] << " ";
		write << setprecision(2) << otvet[j] << " ";
	}
	cout << "\n";
	write.close();

	system("pause");
	return 0;
}
