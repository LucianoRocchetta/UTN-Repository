#include <iostream>
#include <fstream>

using namespace std;

//Files
fstream info("./Files/Datos.txt");

const int numSucursales = 8; //Cambio nombre de la variable
const int numGustos = 6;     //Cambio nombre de la variable

string arraySucursales[numSucursales]{"uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho"};         //Cambio nombre de la variable
string arrayGustos[numGustos]{"Muzzarella", "Fugazza", "Anchoas", "Fugazzeta", "Pizzaiola", "Jamón y Morrones"}; //Cambio nombre de la variable

//Se debe declarar la estructura despues de los arrays (Generan problemas).
struct Pizza
{
    int idSucursal;
    int idTaste;
    int count;
};

Pizza myData[] = {};

//Aquí van las funciones auxiliares que necesite programar
int readData()
{
    Pizza tempPizza;
    int i = 0;

    while (info >> tempPizza.idSucursal >> tempPizza.idTaste >> tempPizza.count)
    {
        myData[i] = tempPizza;
        i++;
    }
    return i;
}

int mostSellestPizza(int count)
{
    string sucursal = "";
    string taste = "";
    int numberOfSucursal;

    int max = myData[0].count;
    for (int i = 1; i < count - 1; i++)
    {
        if (max < myData[i].count)
        {
            max = myData[i].count;
            sucursal = arraySucursales[myData[i].idSucursal];
            taste = arrayGustos[myData[i].idTaste];

            numberOfSucursal = myData[i].idSucursal;
        }
    }
    cout << "the most sellest pizza was " + taste + " in " + sucursal + " with " + to_string(max) + " sells" << endl;
    return numberOfSucursal;
}

string theLeastSoldPizza(int numberOfSucursal, int count)
{
    int nextSucursal = numberOfSucursal, sucursal, taste = 0, temporal = 0;
    int countArray[numGustos] = {};

    (numberOfSucursal == 7) ? nextSucursal = 0 : nextSucursal++;

    for (int i = 0; i < numGustos; i++){
        for (int j = 0; j < count; j++){
            if (myData[j].idSucursal == nextSucursal && taste == myData[j].idTaste){
                countArray[i] += myData[j].count;
            }
        }
        taste++;
    }

    int min = countArray[0];
    for (int i = 0; i < numGustos; i++){
        if (min > countArray[i]){
            min = countArray[i];
            sucursal = i;
        }
    }

    return "the least sold pizza was " + arrayGustos[sucursal] + " with " + to_string(min) + " pizzas";
}

void sortMyData (int numberOfSucursal, int count) {
    int newArray[numGustos][2] = {};

    for (int i = 0; i < numGustos; i++){
        for (int j = 0; j < count; j++){
            if (i == myData[j].idTaste && numberOfSucursal == myData[j].idSucursal){
                newArray[i][0] = myData[j].idTaste;
                newArray[i][1] += myData[j].count;
            }
        }
    }

    int temporalCount, temporalTaste;
    for (int i = 0; i < numGustos; i++){
        for (int j = 0; j < numGustos - 1; j++){
            if (newArray[j][1] > newArray[j+1][1]){
                
                //Count
                temporalCount = newArray[j][1];
                newArray[j][1] = newArray[j+1][1];
                newArray[j+1][1] = temporalCount;

                //Taste
                temporalTaste = newArray[j][0];
                newArray[j][0] = newArray[j+1][0];
                newArray[j+1][0] = temporalTaste;
            }
        }
    cout << "Pizza: " << arrayGustos[newArray[i][0]] << " Count: " << newArray[i][1] << endl;
    }

}

int main()
{
    //Some variables
    int count = 0;
    int numberOfSucursal = 0;
    //punto 1
    count = readData();

    //punto 2
    //La mayor cantidad de pizzas se pidió en la sucursal cinco del gusto Fugazzeta
    numberOfSucursal = mostSellestPizza(count);

    //punto3
    //Mínima cantidad de pizzas vendidas en sucursal seis: 5 correspondiente al gusto Jamón y Morrones
    cout << theLeastSoldPizza(numberOfSucursal, count);

    //punto4
    sortMyData(numberOfSucursal, count);
    /*
	Gusto		Cantidad
	Muzzarella	10
	Fugazza		25
	Jamón y Morrones26
	Anchoas		27
	Pizzaiola	40
	Fugazzeta	42
	*/

    return 0;
}