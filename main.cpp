#include <iostream>

using namespace std;

void mostrarvec(int vec[], int dim)
{
	for (int i = 0; i < dim; i++)
		cout << vec[i] << '\t';
    cout << endl;
}

void mostrarmat(int m[][5], int dfil)
{
        const int dcol = 5; // solo por prolijidad

        for (int i = 0; i < dfil; ++i) {
                for (int j = 0; j < dcol; ++j)
                        cout << m[i][j] << '\t';
                cout << endl;
        }
        cout << endl;
}

//Función para revertir el array
template <typename T>
void reverseArray(T array[], int size){
    int temp = 0;
    int start = -1;

    while (start < size) {
        temp = array[start];
        array[start] = array[size];
        array[size] = temp;

        start++;
        size--;
    }
}

//Función para realizar la traspuesta de una matriz
template <typename T>
void transposeOfAMatrix (T matriz[][5], int dfil) {
    int temp = 0;

    for (int i = 0; i < dfil; i++){
        for (int j = 0; j < i; j++){
            temp = matriz[i][j];
            matriz[i][j] = matriz[j][i];
            matriz[j][i] = temp;
        }
    }
}

int main()
{
    const int dim5 {5};
    const int dim10 {10};

    int vec5[dim5] {4, 11, 19, 8, 3};
    int vec10[dim10] {23, 15, 1, 7, 6, 27, 2, 14, 12, 9};

    int matriz[dim5][dim5] {36, 7, 19, 28, 45,
                            17, 33, 42, 3, 25,
                            22, 41, 32, 11, 9,
                            39, 47, 14, 4, 23,
                            16, 38, 8, 27, 44};


    //Impresión 
    cout << "Arreglos originales: " << endl;
    mostrarvec(vec5, dim5);
    mostrarvec(vec10, dim10);

    cout << "Arreglos invertidos: " << endl;
    reverseArray(vec5, dim5);
    mostrarvec(vec5, dim5);
    reverseArray(vec10, dim10);
    mostrarvec(vec10, dim10);
  
    
    cout << endl << "Matriz Original: " << endl;
    mostrarmat(matriz, dim5);
    transposeOfAMatrix(matriz, dim5);
    cout << endl << "Matriz Traspuesta: " << endl;
    mostrarmat(matriz, dim5);

    return 0;
}