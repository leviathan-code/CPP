float Create(int stroka, int stolb) {//инициализация двоичноо диамичеакого массива
    float** tab = new float* [stroka];
    for (int i = 0; i <= stroka; i++)
    tab[i] = new float[stolb];
    return tab;
   
}


float** doavlenie(float** tab, int stroka, int stolb) {//создаем новую матрицу и вписываем в нее старую
    float** t = Create(stroka+1, stolb+1);//иницализация массива для копировавния в него элементов из tab, который больше на 1 строку и столбец
    
    for (int i = 0; i < stroka; i++) {
        for (int j = 0; j < stolb; j++) {
            t[i][j] = tab[i][j];//создаем новую матрицу и вписываем в нее старую
        }
    }
    
    stroka++, stolb++;
    return t; 
    for (int i = 0; i <stroka; i++)
        delete[] t[i];
    delete[] t;
}

int main(){

float** tab=Create( stroka,  stolb);//инициализация двоичного диамичеакого массива

doavlenie( tab, stroka, stolb);//создаем новую матрицу и вписываем в нее старую
}
