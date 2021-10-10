#include <iostream>
#include <vector>

using namespace std;

void add(float** tab, int*c, int stroka, int stolb) {
	bool r = 0;//флаг для А0<0
	cout << "F(X)= ";
	//ввод 
	for (int j = 3; j < stolb - 1; j++) 
		cin >> tab[0][j];

	for (int i = 1; i < stroka; i++){
		cout << "Введите значения " << i << "неравенства" << endl;
		for (int j = 3; j < stolb; j++){
			if (j != stolb - 1){
				cout << "x" << "(" << j - 2 << ")";
				cin >> tab[i][j];
			}
			if (j == stolb - 1){
				cout << "<=";
				cin >> tab[i][2];
				if(tab[i][2]<0){
					c[i] = i;//фиксруем строку с отриц А0
					r = 1;//флаг для А0<0
				}
			}
		}
	}	
	// если свободные члены < 0
	if (r) {
		for (int i = 1; i < stroka; i++) {
			for (int j = 2; j < stolb; j++) {
				if (i == c[i]) 
					tab[i][j] *= -1;
			}
		}
	}
}

void show(float** tab,int* isc,int* ocen, int stroka, int stolb, bool n,bool iscustven,bool Dj1,bool Dj2) {
	//вывод
	cout << "cj" << " ";
	for (int j = 3; j < stolb; j++){
		if ((j == isc[j]) && (iscustven))
			cout << "-M" << "  ";
		else
			cout << tab[0][j] << "  ";
	}
	cout << endl;
	for (int j = 0; j < stolb; j++){
		if (j == 0){
			cout << "б" << " ";
			continue;
		}
		if (j == 1){
			cout << "сб" << " ";
			continue;
		}
		cout << "a" << j - 2 << " ";
	}
	cout << endl;
	for (int i = 1; i < stroka; i++) {
		for (int j = 0; j < stolb; j++) {
			if (j == 0) {
				cout << tab[i][j] - 2 << "  ";
				continue;
			}
			else if (j == 1) {
				if ((iscustven) && (ocen[i] == i))
					cout << "-M" << "  ";
				else {
					cout << tab[i][j] << "  ";
					continue;
				}
			}
			else if (j == 2) {
				cout << tab[i][j] << "  ";
				continue;
			}
			else
				cout << tab[i][j] << "  ";
		}
		cout << endl;
	}
	if (n && Dj1) {
		cout << "  dj'" << " ";
		for (int j = 2; j < stolb; j++)
			cout << tab[stroka][j] << "  ";
		cout << endl;
	}
	if (iscustven && Dj2) {
		cout << "  dj" << "\"" << " ";
		for (int j = 2; j < stolb; j++)
			cout << tab[stroka][j] << "  ";
		cout << endl;
	}
}

int FindBazzis(float** tab, float* bazisnyh, int stroka, int stolb) {
	int  bazis = 0, one = 0, zero = 0, str = -1;
	//находим базисные переменные в ограничения, smotrim po strokam
	for (int j = 3; j < stolb; j++) {
		for (int i = 1; i < stroka; i++) {
			if ((tab[i][j] != 0)) {
				if ((tab[i][j] == 1)) {
					one++;
					str = i;//ключевая строка
				}
				else one = 0;
			}
			else if (tab[i][j] == 0) zero++;
		}
		if ((one == 1) && (zero == stroka - 2)) {//нашел базис
			bazis++;//кол-во базисных переменных
			bazisnyh[str] = str;//для хранеия строк с базисными элементами
			tab[str][0] = j;//заполнение б
			tab[str][1] = tab[0][j];//заполнение сб
		}
		one = 0, zero = 0, str = -1;
	}
	return bazis;
}

int simplex(float** tab, float* bazisnyh,int*isc,int* ocen, int stroka, int stolb,bool iscust) {

	int stroka11, stolb11;
	float min = 9999999999999999.0, minDrob = 999, minn = 999999999999999999;
	float* mini = new float[stroka];//векор дл хранени отриц А0
	bool OtricOcen = 0, n = 1, Dj1=1, Dj2=1;

	//обнуляем оценки
	for (int j = 2; j < stolb; j++)
		tab[stroka][j] = 0;
	//считаем оценки
	for (int j = 2; j < stolb; j++) {
		for (int i = 1; i < stroka; i++)
			tab[stroka][j] += (tab[i][1] * tab[i][j]);
		if (j != 2)
			tab[stroka][j] -= tab[0][j];
	}
	show(tab,isc,ocen, stroka, stolb, n, iscust,Dj1,Dj2);
	//ищем мин оценку
	for (int j = 2; j < stolb; j++) {
		if (tab[stroka][j] < 0) {
			OtricOcen = 1;
			if (minn > tab[stroka][j]) {
				minn = tab[stroka][j];
				stolb11 = j;//ключевй столбец
			}
		}
	}
	if (OtricOcen) {
		for (int i = 1; i < stroka; i++) {// 
			if ((tab[i][stolb11] + 0.0) > 0)
				mini[i] = ((tab[i][2] + 0.0) / (tab[i][stolb11] + 0.0));//мин отношения к А0
		}
		for (int i = 1; i < stroka; i++) {// ключевой элемент
			if ((mini[i] < min) && ((mini[i]) + 0.0) > 0) {
				min = mini[i];//мин отношение к А0
				stroka11 = i;//ключевая строка
			}
		}
		bazisnyh[stroka11] = stroka11;//
		min = tab[stroka11][stolb11];//фиксируем ключ элемент
		//симплекс метод
		for (int i = 1; i < stroka; i++) {// 
			for (int j = 2; j < stolb; j++) {
				if ((j != stolb11) && (i != stroka11))
					tab[i][j] -= ((tab[stroka11][j] * tab[i][stolb11]) + 0.0) / min;
			}
		}
		for (int j = 2; j < stolb; j++)
			tab[stroka11][j] = (tab[stroka11][j] + 0.0) / min;

		tab[stroka11][stolb11] = 1;

		for (int i = 1; i < stroka; i++){
			if (i != stroka11)
				tab[i][stolb11] = 0;
		}
		FindBazzis(tab, bazisnyh, stroka, stolb);
	}
	for (int j = 2; j < stolb; j++) {
		if (tab[stroka][j] < 0) {
			OtricOcen = 1;
			break;
		}
	}
	delete mini;
	if (OtricOcen)
		return simplex(tab, bazisnyh,isc,ocen, stroka, stolb,iscust);
	else return 0;
}

int main(){
	setlocale(LC_ALL, "Russian");

	int stroka, stl, stolb, stroka11;
	cout << " введите кол-во ограничений:";
	cin >> stroka;
	stroka++;
	cout << " введите кол-во переменных:";
	cin >> stolb;

	stolb += 4;//кол-во столбцов с базисом,С-базисным,А0
	stl = stolb - 1;//фиксируем кол-во переменных

	float** tab = new float* [stroka];
	for (int i = 0; i <= stroka; i++)
		tab[i] = new float[stolb];
	float* bazisnyh = new float[stroka];//фиксируем сторку с базисной переменной
	int* c = new int[stroka];//фиксируем сторку с базисной переменной

	add(tab,c, stroka, stolb);

	//вывод введенных значений
	cout << "введенные значения:" << endl;
	cout << "F(X)= ";
	for (int j = 3; j < stolb; j++)
		cout << tab[0][j] << "  ";
	cout << endl;
	for (int i = 1; i < stroka; i++){
		cout << "      ";
		for (int j = 3; j < stolb; j++){
			if (j == stolb - 1)
				cout << "= " << tab[i][2];
			if (j != stolb - 1)
				cout << tab[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	stolb--;//убираем лишний столбец

	FindBazzis(tab, bazisnyh, stroka, stolb);

	int* isc = new int(stroka);// № столба с искусственным базисом
	int* ocen = new int(stroka);//хранение № строки для базиса
	bool n = 0, iscust=0;
	int bazis = FindBazzis(tab, bazisnyh, stroka, stolb), Dj1=0, Dj2=0,o;

	//если есть базис 
	if (bazis == stroka - 1){
		show(tab, isc, ocen, stroka, stolb, n, iscust, Dj1, Dj2);
		n = 1, Dj1 = 1;
	}
	//добавляем базис
	else{//удлиняем массив:
		o = stl;//фиксируем № последнего столбца в матрице до добавления новых 
		stolb = stl + stroka - bazis - 1; //кол-во столбцов после резайза
		float q = -3.1409 * 7777;//число М для искусственного базиса
		//если НЕТ базиса
		if (bazis == 0){
			for (int i = 1; i < stroka; i++){
				for (int j = o; j < stolb; j++){
					if (i == j - stl + 1){
						tab[i][j] = 1;
						tab[i][0] = j;//заполняем базис
						tab[i][1] = tab[0][j];//заполняем с-базисное
					}
				}
			}
		}
		//если есть хотя бы ОДИН базис
		else{
			int k, kol = 0, l = 0;
			//ищем базис в ограничениях до ресайз
			for (int i = 1; i < stroka; i++){
				for (int j = 0; j < o; j++){
					//через этот массив смотрим,куда можно добавить базис в уже добавленные столбцах
					for (int k = o; k < stolb; k++){
						//проверка,чтобы не добавить новую единицу в новом базисе
						if (k == l) {
							tab[i][j] = 0;
							continue;
						}
						else if (bazisnyh[i] != i) {
							tab[i][k] = 1;
							l = k;//флаг,чтобы пропустить столбец,который уже заполнили
							bazisnyh[i] = i;
							isc[k] = k;
							tab[i][0] = k;
							tab[i][1] = tab[0][k];
							ocen[i] = i;
						}
					}
				}
			}
		}
		cout << endl;
		show(tab, isc, ocen, stroka, stolb, n, iscust, Dj1, Dj2);
		Dj2 = 1,iscust = 1;
	}
	//начинается симплекс 
	simplex(tab, bazisnyh, isc, ocen, stroka, stolb, iscust);

	float* x = new float(stolb);
	iscust = 0, Dj1=0, Dj2=0,n=0;

	show(tab, isc, ocen, stroka, stolb, n, iscust, Dj1, Dj2);

	for (int i = 1; i < stroka; i++) {
		for (int j = 2; j < stolb; j++) {
			if (tab[i][0] == j)
				x[j] = tab[i][2];
		}
	}
	float l = tab[stroka][2];//допустимое решение задачи
	//допустимое множество 
	cout << endl << "X*( ";
	for (int j = 3; j < stolb; j++) {
		if (j == 3)
			cout << x[j] << " ,";
		else if (j == stolb - 1)
			cout << " " << x[j];
		else
			cout << " " << x[j] << " ,";
	}
	cout << " )" << endl << "L*=" << l << endl << endl;

	system("pause");
	return 0;
}
