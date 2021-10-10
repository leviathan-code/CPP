// Программа Искусственный базис//
/////////////////////////////////

#include <iostream>
#include <vector>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	int n, stl, m, stroka;
	cout << " введите кол-во ограничений:";
	cin >> n;
	n++;
	cout << " введите кол-во переменных:";
	cin >> m;

	m += 4;//кол-во столбцов с базисом,С-базисным,А0
	stl = m - 1;//фиксируем кол-во переменных

	vector< vector<float> > tab(n);// хранит все элементы задачи
	vector<int> c(m);// используем для нахождениия строки с отриц А0 ()
	vector <float> bazisnyh(n);//фиксируем сторку с базисной переменной
	vector<float> a0(n);//фиксируем А0
	vector<string> cb(m);//фиксируем столбец с баз переменной
	vector<float> ocen(m);//для фиксации оценок
	vector<float> isc(m);//№ столбов искусственного базисов

	// Заполнение нулями, чтобы был инициализирован в любом случае
	for (int i = 0; i < n; i++)
	{
		tab[i].resize(m);
		for (int j = 0; j < m - 1; j++)
		{
			tab[i][j] = 0;
			bazisnyh[i] = 0;
		}
	}

	bool r = 0;//флаг для А0<0
	cout << "F(X)= ";
	//ввод 
	for (int j = 3; j < m - 1; j++) {
		cin >> tab[0][j];
	}

	for (int i = 1; i < n; i++)
	{
		cout << "Введите значения " << i << "неравенства" << endl;
		for (int j = 3; j < m; j++)
		{
			if (j != m - 1)
			{
				cout << "x" << "(" << j - 2 << ")";
				cin >> tab[i][j];
			}

			if (j == m - 1)
			{
				cout << "<=";
				cin >> a0[i];
				if (a0[i] < 0)
				{
					c[i] = i;//фиксруем строку с отриц А0
					r = 1;//флаг для А0<0
				}
			}
		}
	}
	//вывод введенных значений
	cout << "введенные значения:" << endl;
	cout << "F(X)= ";
	for (int j = 3; j < m; j++)
	{
		cout << tab[0][j] << "  ";
	}
	cout << endl;
	for (int i = 1; i < n; i++)
	{
		cout << "      ";
		for (int j = 3; j < m; j++)
		{
			if (j == m - 1)
				cout << "= " << a0[i];
			if (j != m - 1)
			{
				cout << tab[i][j] << "  ";
			}
		}
		cout << endl;
	}
	cout << endl;
	// если свободные члены < 0
	if (r)
	{
		for (int i = 1; i < n; i++)
		{
			for (int j = 3; j < m; j++)
			{
				if (i == c[i])
				{
					tab[i][j] *= -1;
					a0[i] *= -1;
				}
			}
		}
	}
	m = m - 1;

	int  bazis = 0, one = 0, zero = 0, str = -1;

	//находим базисные переменные в ограничениях,смотрим по строкам
	for (int j = 3; j < m; j++)
	{
		for (int i = 1; i < n; i++)
		{
			if ((tab[i][j] != 0))
			{
				if ((tab[i][j] == 1))
				{
					one++;
					str = i;                      //ключевая строка
				}
				else
				{
					one = 0;
				}
			}
			else
				if (tab[i][j] == 0)
				{
					zero++;
				}
		}
		//находим кол-во базисных переменных
		if ((one == 1) && (zero == n - 2))
		{
			bazis++;                      //кол-во базисных переменных
			bazisnyh[str] = str;          //для хранеия строк с базисными элементами
			c[j] = j;                     //хранение столбов с базисными переными  
			tab[str][0] = c[j];           //заполнение базиса
			tab[str][1] = tab[0][c[j]];   //заполнение с-базисного 
		}
		one = 0;
		zero = 0;
		str = -1;
	}

	int o;
	int iscust = 0;

	//если есть базис 
	if (bazis == n - 1)
	{
		tab.resize(m);
		//заполнение пустых ячеек:
		float b = -1;
		//инициализация
		for (int i = n - 1; i <= n; i++)
		{
			tab[i].resize(m);
			for (int j = 0; j < m; j++) {
				if ((i == 0) && (bazis != 0)) {
					tab[i][j] = b;
				}
			}
		}
		cout << endl;
		//вывод
		cout << "cj" << " ";
		for (int j = 3; j < m; j++)
		{
			cout << tab[0][j] << "  ";
		}
		cout << endl;
		for (int j = 0; j < m; j++)
		{
			if (j == 0)
			{
				cout << "б" << " ";
				continue;
			}
			if (j == 1)
			{
				cout << "cб" << " ";
				continue;
			}
			cout << "a" << j - 2 << " ";
		}
		cout << endl;

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (j == 0)
				{
					cout << tab[i][j] - 2 << "  ";
					continue;
				}
				else if (j == 1)
				{
					cout << tab[i][j] << "  ";
					continue;
				}

				else
					if (j == 2)
					{
						tab[i][j] = a0[i];
						cout << tab[i][j] << "  ";
						continue;
					}
					else
						cout << tab[i][j] << "  ";
			}
			cout << endl;
		}

	}
	//добавляем базис
	else
	{   //удлиняем массив:

		o = stl;                 //фиксируем последний столец в матрице до добавления новых столбцов 
		m = stl + n - bazis - 1; //кол-во столбцов после резайза

		tab.resize(m);
		bazisnyh.resize(m);
		a0.resize(m);
		ocen.resize(m);
		c.resize(m);
		isc.resize(m);
		/////////////////

		//заполнение пустых ячеек после ресайз 
		float a = 0;
		float b = -1;
		int p = -1;
		//инициализация
		for (int i = 0; i <= n + 1; i++)
		{
			tab[i].resize(m);
			for (int j = o; j < m; j++) {
				if ((i == 0) && (bazis != 0)) {
					tab[i][j] = b;
				}
				else
					tab[i][j] = a;
				c[j] = p;
				isc[j] = a;
				ocen[j] = p;
			}
		}
		float q = -3.1409 * 7777;//число М для искусственного базиса
		//если НЕТ базиса
		if (bazis == 0)
		{
			for (int i = 1; i < n; i++)
			{
				for (int j = o; j < m; j++)
				{
					if (i == j - stl + 1)
					{
						tab[i][j] = 1;
						tab[i][0] = j;          //заполняем базис
						tab[i][1] = tab[0][j];  //заполняем с-базисное
					}
				}
			}
		}
		//если есть хотя бы ОДИН базис
		else
		{
			int k, kol = 0, l = 0;
			//ищем базис в ограничениях до ресайз
			for (int i = 1; i < n; i++)
			{
				for (int j = 0; j < o; j++)
				{
					//через этот массив смотрим,куда можно добавить базис в уже добавленные столбцах
					for (int k = o; k < m; k++)
					{
						//проверка,чтобы не добавить новую единицу в новом базисе
						if (k == l)
							continue;
						else
						{
							if (bazisnyh[i] != i)
							{
								tab[i][k] = 1;
								l = k;               //флаг,чтобы пропустить столбец,который уже заполнили
								bazisnyh[i] = i;
								isc[k] = k;          // № столба с искусственным базисом
								tab[i][0] = k;
								tab[i][1] = tab[0][k];
								iscust = 1;
								ocen[i] = i;         //хранение № строки для базиса
							}
						}
					}
				}
			}
		}
		cout << endl;
		//вывод
		cout << "cj" << " ";
		for (int j = 3; j < m; j++)
		{
			if ((j == isc[j]) && (iscust))
			{
				cout << "-M" << "  ";
			}
			else
			{
				cout << tab[0][j] << "  ";
			}
		}
		cout << endl;
		for (int j = 0; j < m; j++)
		{
			if (j == 0)
			{
				cout << "б" << " ";
				continue;
			}
			if (j == 1)
			{
				cout << "сб" << " ";
				continue;
			}
			cout << "a" << j - 2 << " ";
		}
		cout << endl;

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (j == 0)
				{
					cout << tab[i][j] - 2 << "  ";
					continue;
				}
				else
					if (j == 1)
					{
						if ((iscust) && (ocen[i] == i))
						{
							cout << "-M" << "  ";
						}
						else
						{
							cout << tab[i][j] << "  ";
							continue;
						}
					}
					else
						if (j == 2)
						{
							tab[i][j] = a0[i];
							cout << tab[i][j] << "  ";
							continue;
						}
						else
							cout << tab[i][j] << "  ";
			}
			cout << endl;
		}
	}

	//начинается симплекс 
	bool OtricOcen = 0;
	float min = 9999999999999999.0;
	vector<float> mini(n);      //векор для хранения отриц-ых А0
	float v = 0;
	//новая инициализация
	for (int j = 0; j < n; j++)
	{
		mini[j] = v;
	}

	bool reshaem = 1;
	//решаем
	int stolb;
	if (iscust == 0)
	{
		//ОБЫЧНЫЙ симплекс-метод
		for (int j = 2; j < m; j++)
		{
			//считаем ОЦЕНКИ
			for (int i = 1; i < n; i++)
			{
				tab[n][j] += (tab[i][1] * tab[i][j]);
			}
			tab[n][j] -= tab[0][j];
		}
		cout << endl << endl;
		///////////////////////////
		//вывод
		cout << "cj" << " ";
		for (int j = 3; j < m; j++)
		{
			cout << tab[0][j] << "  ";
			c[j] = zero;      //переинициализация
		}
		cout << endl;
		for (int j = 0; j < m; j++)
		{
			if (j == 0)
			{
				cout << "б" << " ";
				continue;
			}
			if (j == 1)
			{
				cout << "сб" << " ";
				continue;
			}
			cout << "a" << j - 2 << " ";
		}
		cout << endl;

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (j == 0)
				{
					cout << tab[i][j] - 2 << "  ";
					continue;
				}
				else
					if (j == 1)
					{
						cout << tab[i][j] << "  ";
						continue;
					}
					else
						if (j == 2)
						{
							cout << tab[i][j] << "  ";
							continue;
						}
						else
							cout << tab[i][j] << "  ";
			}
			cout << endl;
		}
		//////////////
		cout << "dj'" << "  ";
		for (int j = 2; j < m; j++)
		{
			cout << tab[n][j] << "  ";
		}
		cout << endl;

		float minn;
		minn = 999999999999999999;

		for (int j = 2; j < m; j++)
		{
			//ПОИСК МИНИМАЛЬНОЙ ОЦЕНКИ
			if (tab[n][j] < 0)
			{
				OtricOcen = 1;
				if (minn > tab[n][j])
				{
					minn = tab[n][j];
					stolb = j;        //ключевой столбец
				}
			}
		}
		for (int j = 2; j < m; j++)
		{
			//обнуляем оценки 
			tab[n][j] = 0;
		}

		float Zero = 0;
		//начало симплекса 
		while (OtricOcen)
		{
			//решает пока есть оценки<0 и ДРОБНЫЕ А0
			min = 9999999999999.0;
			if (OtricOcen)
			{
				for (int i = 1; i < n; i++)
				{
					if ((tab[i][stolb] + 0.0) > 0)
					{
						mini[i] = ((tab[i][2] + 0.0) / (tab[i][stolb] + 0.0));    //мин отношения к А0
					}
				}

				for (int i = 1; i < n; i++)
				{
					// ключевой элемент
					if ((mini[i] < min) && ((mini[i]) + 0.0) > 0)
					{
						min = mini[i];
						stroka = i;                  //ключевая строка
					}
				}
			}
			bazisnyh[stroka] = stroka;
			min = tab[stroka][stolb];                //фиксируем ключ элемент

			//симплекс метод
			for (int i = 1; i < n; i++)
			{
				for (int j = 2; j < m; j++)
				{
					if (j != stolb)
					{
						if ((i != stroka))
						{
							tab[i][j] -= ((tab[stroka][j] * tab[i][stolb]) + 0.0) / min;
						}
					}
				}
			}

			for (int j = 2; j < m; j++)
			{
				tab[stroka][j] = (tab[stroka][j] + 0.0) / min;
			}

			tab[stroka][stolb] = 1;

			for (int i = 1; i < n; i++)
			{
				if (stroka != i)
				{
					tab[i][stolb] = 0;
				}
			}
			/////////////



			//находим базисные переменные 
			for (int j = 3; j < m - 1; j++)
			{
				for (int i = 1; i < n; i++)
				{
					if ((tab[i][j] != 0))
					{
						if ((tab[i][j] == 1))
						{
							one++;
							str = i;
						}

						else
						{
							one = 0;
						}
					}

					else
						if (tab[i][j] == 0)
						{
							zero++;
						}
				}
				//найден базис
				if ((one == 1) && (zero == n - 2))
				{
					bazisnyh[str] = str;
					c[j] = j;
					tab[str][0] = c[j];
					tab[str][1] = tab[0][c[j]];
				}
				one = 0;
				zero = 0;
				str = -1;
			}
			//оценки считаем 
			for (int j = 2; j < m; j++)
			{
				for (int i = 1; i < n; i++)
				{
					tab[n][j] += (tab[i][1] * tab[i][j]);
				}
				tab[n][j] -= tab[0][j];
			}
			cout << endl;

			//вывод
			cout << "cj" << " ";
			for (int j = 3; j < m; j++)
			{
				cout << tab[0][j] << "  ";
				c[j] = zero;    //переинициализация
			}
			cout << endl;
			for (int j = 0; j < m; j++)
			{
				if (j == 0)
				{
					cout << "б" << " ";
					continue;
				}
				if (j == 1)
				{
					cout << "сб" << " ";
					continue;
				}
				cout << "a" << j - 2 << " ";
			}
			cout << endl;

			for (int i = 1; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					mini[i] = 0;    //переинициализация
					if (j == 0)
					{
						cout << tab[i][j] - 2 << "  ";
						continue;
					}
					else
						if (j == 1)
						{
							cout << tab[i][j] << "  ";
							continue;
						}

						else
							if (j == 2)
							{
								cout << tab[i][j] << "  ";
								continue;
							}
							else
								cout << tab[i][j] << "  ";
				}
				cout << endl;
			}
			///////////////////////////
			cout << "dj'" << "  ";
			for (int j = 2; j < m; j++)
			{
				cout << tab[n][j] << "  ";
			}
			cout << endl;

			OtricOcen = 0;     // для отрицательных оценок 
			minn = 999999999999999999;
			min = 9999999999999999;
			//если min оценка
			for (int j = 2; j < m; j++)
			{
				if (tab[n][j] < 0)
				{
					OtricOcen = 1;
					if (minn > tab[n][j])
					{
						minn = tab[n][j];
						stolb = j;            //ключевой стобец
					}
				}
			}

			//обнуляем dj
			if (OtricOcen)
			{
				for (int j = 2; j < m; j++)
				{
					tab[n][j] = Zero;
				}
			}
		}
	}
	//КОНЕЦ симплекс метода 
	else
	{
		//симплекс метод с искусственным базисом
		for (int j = 2; j < m; j++)
		{
			for (int i = 1; i < n; i++)
			{
				if ((ocen[i] == i))
				{
					tab[n + 1][j] += (tab[i][1] * tab[i][j]);           //счиаем dj'
				}
				else
					if (ocen[i] != i)
						tab[n][j] += (tab[i][1] * tab[i][j]);
			}
			if (isc[j] != j)
				//считаем dj''
				tab[n][j] -= tab[0][j];
			if ((isc[j] == j))
			{
				tab[n + 1][j] -= tab[0][j];
			}
		}

		bool OtricOcen = 0;
		float min = 9999999999999999.0;
		vector<float> mini(n);               //вектор для мин отношения элемента к А0 

		//инициализация
		float v = 0;
		for (int j = 0; j < n; j++)
		{
			mini[j] = v;
		}
		///
		int stolb;
		cout << endl;
		//вывод
		for (int j = 0; j < m; j++)
		{
			if ((j == isc[j]))
			{
				cout << "-M" << "  ";
			}
			else
			{
				cout << tab[0][j] << "  ";
			}
		}
		cout << endl;
		for (int j = 0; j < m - 1; j++)
		{
			if (j == 0)
			{
				cout << "б" << " ";
				continue;
			}
			if (j == 1) {
				cout << "сб" << " ";
				continue;
			}
			cout << "a" << j - 2 << " ";
		}
		cout << endl;

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (j == 0)
				{
					cout << tab[i][j] - 2 << "  ";
					continue;
				}
				else
				if (j == 1)
				{
					if ((iscust) && (ocen[i] == bazisnyh[i]))
					{
						cout << "-M" << "  ";
					}
					else
					{
						cout << tab[i][j] << "  ";
						continue;
					}
				}
				else if (j == 2)
				{
					cout << tab[i][j] << "  ";
					continue;
				}
				else
					cout << tab[i][j] << "  ";
			}
			cout << endl;
		}
		//вывод оценок в искусственном базисе 
		cout << " dj'" << "   ";
		for (int j = 2; j < m; j++) {
			cout << tab[n][j] << "  ";
		}
		cout << endl;
		cout << " dj''" << "   ";
		for (int j = 2; j < m; j++) {
			cout << tab[n + 1][j] << "  ";
		}
		cout << endl;
		////конец вывода

		float minn;
		minn = 999999999999999999;
		bool IscustOcen = 0;
		int otriciscust = 0;

		//решаем
		for (int j = 2; j < m; j++)
		{
			//находим мин оцеку для dj''
			if (tab[n + 1][j] < 0)
			{
				IscustOcen = 1;
				if ((minn > tab[n + 1][j]) && (j != 2))
				{
					minn = tab[n + 1][j];
					stolb = j;   
					cout << "tab[n + 1][j]=" << tab[n + 1][j] << endl;
					//столбец с мин оценкой
				}
				otriciscust = 1;
				//флаг для искусствен базиса
			}
			else if ((tab[n][j] < 0) && (otriciscust == 0) && (j != 2)) {
				OtricOcen = 1;
				m = o+1;
				if (minn > tab[n][j])
				{
					minn = tab[n][j];
					stolb = j;            //столбец с мин оценкой
				}
			}
		}
		//обнуляем все оценки
		for (int j = 2; j < m; j++)
		{
			tab[n][j] = 0;
			tab[n + 1][j] = 0;
		}
		float Zero = 0;

		bool stopIsc = 0;

		//решает пока план неоптимален
		while ((OtricOcen) || (IscustOcen))
		{
			min = 9999999999999.0;
			
			if ((IscustOcen) && stopIsc == 0) {
				for (int i = 1; i < n; i++)
				{
					if (ocen[i] == i)
					{
						if ((tab[ocen[i]][stolb] + 0.0) > 0)
						{
							mini[ocen[i]] = ((tab[ocen[i]][2] + 0.0) / (tab[ocen[i]][stolb] + 0.0));     //мин отношение к a0 в dj''
						}
					}
				}
			}

			if ((IscustOcen == 0) && OtricOcen) {
				for (int i = 1; i < n; i++)
				{
					if ((tab[i][stolb] + 0.0) > 0)
					{
						mini[i] = ((tab[i][2] + 0.0) / (tab[i][stolb] + 0.0));             //мин отношение к a0 в dj'
					}
				}
			}
				
			// находим ключевую строку
			for (int i = 1; i < n; i++)
			{
				if ((mini[i] < min) && ((mini[i]) + 0.0) > 0)
				{
					min = mini[i];
					stroka = i;
				}
			}
			bazisnyh[stroka] = stroka;
			min = tab[stroka][stolb];      //фиксируем ключевой элемент

			//симплекс-метод
			for (int i = 1; i < n; i++)
			{
				for (int j = 2; j < m; j++)
				{
					if (j != stolb) {
						if ((i != stroka))
						{
							tab[i][j] -= ((tab[stroka][j] * tab[i][stolb]) + 0.0) / min;
						}
					}
				}
			}

			for (int j = 2; j < m; j++)
			{
				tab[stroka][j] = (tab[stroka][j] + 0.0) / min;          //делим все элемты ключевой строки на ключ элемент
			}
			tab[stroka][stolb] = 1;   //сам ключевой элемент
			for (int i = 1; i < n; i++)
			{
				if (stroka != i)
				{
					tab[i][stolb] = 0;  //элементы в ключевом толбце приравнием к 0
				}
			}
			////////////////////конец

			//находим базисные переменные 
			for (int j = 3; j < m - 1; j++)
			{
				for (int i = 1; i < n; i++)
				{
					if ((tab[i][j] != 0))
					{
						if ((tab[i][j] == 1))
						{
							one++;
							str = i;
						}
						else
						{
							one = 0;
						}
					}

					else
						if (tab[i][j] == 0)
						{
							zero++;
						}
				}
				//если найден базис
				if ((one == 1) && (zero == n - 2))
				{
					bazisnyh[str] = str;           //фиксируем ключевую строку
					if (ocen[str] == bazisnyh[str]) {//заменяем строку с исскуственным базисом(вектор ocen[] используем повторно)
						ocen[str] = 0;
					}
					c[j] = j;                      //фиксирем столбы с базисными переменными 
					tab[str][0] = c[j];            //заполняем столб б
					tab[str][1] = tab[0][c[j]];    //заполняем столб сб
				}
				one = 0;
				zero = 0;
				str = -1;
			}


		
			if ((OtricOcen) || (IscustOcen))
			{
				for (int j = 2; j < m; j++)
				{
					tab[n][j] = Zero;
					tab[n + 1][j] = Zero;
				}
			}

			for (int j = 2; j < m; j++)
			{
				for (int i = 1; i < n; i++)
				{
					if ((ocen[i] == i)&& IscustOcen)
					{
						tab[n + 1][j] += (tab[i][1] * tab[i][j]);           //счиаем dj'
					}
					else
							tab[n][j] += (tab[i][1] * tab[i][j]);
				}
				if (isc[j] != j)
					//считаем dj''
					tab[n][j] -= tab[0][j];
				if ((isc[j] == j)&& IscustOcen)
				{
					tab[n + 1][j] -= tab[0][j];
				}
			}


			OtricOcen = 0;
			IscustOcen = 0;
			otriciscust = 0;
			minn = 999999999999999999;
			min = 9999999999999999;
			//int PoloshDj = 0;

			for (int j = 2; j < m; j++) {
				if ((tab[n + 1][j] < 0)&&stopIsc==0) {
					IscustOcen = 1;
					break;
				}
			}

			//находим мин оцеку для dj''
			
			if (IscustOcen) {
				for (int j = 2; j < m; j++) {//находим мин оцеку для dj''
					if ((minn > tab[n + 1][j]) && (j != 2)&& tab[n + 1][j]<0) {
						minn = tab[n + 1][j];
						stolb = j;///столб самой мин оценки
					}
					otriciscust = 1; // флаг для искусствен базиса
				}
			}
			else if ((otriciscust == 0) && IscustOcen == 0) {
				for (int j = 2; j < m; j++)
				{
					if ((minn > tab[n][j]) && (j != 2)&& tab[n][j]<0) {
						OtricOcen = 1;
						stopIsc = 1;
						m = o+1;
						if (minn > tab[n][j]) {
							minn = tab[n][j];
							stolb = j;///столб самой мин оценки
						}
						cout << "minn " << minn << endl;
					}
				}
			}
	
			cout << endl;
			//вывод
			cout << "cj" << " ";
			for (int j = 3; j < m; j++)
			{
				if ((j == isc[j]))
				{
					cout << "-M" << "  ";
				}
				else {
					cout << tab[0][j] << "  ";
				}
				c[j] = zero;//переинициализфция
			}
			cout << endl;
			for (int j = 0; j < m; j++)
			{
				if (j == 0)
				{
					cout << "б" << " ";
					continue;
				}
				if (j == 1) {
					cout << "сб" << " ";
					continue;
				}
				cout << "a" << j - 2 << " ";
			}
			cout << endl;

			for (int i = 1; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					mini[i] = 0;//переинициализфция

					if (j == 0)
					{
						cout << tab[i][j] - 2 << "  ";
						continue;
					}
					else if (j == 1)
					{
						if ((ocen[i] == bazisnyh[i]))
						{
							cout << "-M" << "  ";
						}
						else
						{
							cout << tab[i][j] << "  ";
							continue;
						}
					}

					else
						if (j == 2)
						{
							cout << tab[i][j] << "  ";
							continue;
						}
						else
							cout << tab[i][j] << "  ";
				}
				cout << endl;
			}
			//////////////////////
			cout << " dj'" << "  ";
			for (int j = 2; j < m; j++)
			{
				cout << tab[n][j] << "  ";
			}
			cout << endl;
			
				cout << " dj''" << " ";
				for (int j = 2; j < m; j++)
				{
					cout << tab[n + 1][j] << "  ";
				}
				cout << endl;
			


				for (int j = 2; j < m; j++)
				{
					tab[n][j] = Zero;
					tab[n + 1][j] = Zero;
				}
			
		}
		
	}
	//конец симплекс метода с искусственым базисом
	cout << endl;
	//СЧИТАЕМ ОЦЕНКИ
	for (int j = 2; j < m; j++)
	{
		for (int i = 1; i < n; i++)
		{
			tab[n][j] += (tab[i][1] * tab[i][j]);
		}
		tab[n][j] -= tab[0][j];
	}
	cout << endl;
	//вывод
	cout << "Оптимальный план:" << endl;
	cout << "cj" << " ";
	for (int j = 3; j < m; j++)
	{
		cout << tab[0][j] << "  ";
	}
	cout << endl;
	for (int j = 0; j < m; j++)
	{
		if (j == 0)
		{
			cout << "б" << " ";
			continue;
		}
		if (j == 1) {
			cout << "сб" << " ";
			continue;
		}
		cout << "a" << j - 2 << " ";
	}
	cout << endl;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (j == 0)
			{
				cout << tab[i][j] - 2 << "  ";
				continue;
			}
			else
				if (j == 1)
				{
					cout << tab[i][j] << "  ";
					continue;
				}

				else
					if (j == 2)
					{
						cout << tab[i][j] << "  ";
						continue;
					}
					else
						cout << tab[i][j] << "  ";
		}
		cout << endl;
	}
	////////////////////
	cout << " dj'" << "  ";
	for (int j = 2; j < m; j++)
	{
		cout << tab[n][j] << "  ";
	}

	system("pause");
	return 0;
}
