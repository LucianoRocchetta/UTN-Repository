#include <iostream>
#include <fstream>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "rwstring.hpp"

using namespace std;

struct Registro {
	string producto;
	int fecha;
	double precio;
};
const int cantProducto = 20;

struct Producto {
	int mes = 0;
	int cantidadPorMes = 0;
	double precioTotal = 0;
	double promedio = 0;
};

struct porProducto {
	string producto;
	int cantidad = 0;
	Nodo<Producto>* listaProductos = nullptr;
};

fstream &operator >> (fstream &fs, Registro &est) {
  est.producto = readstring(fs, cantProducto);
  fs.read((char *)&est.fecha, sizeof(est.fecha));
	 fs.read((char *)&est.precio, sizeof(est.precio));
  return fs;
}

ostream& operator << (ostream& o, Registro& est) {
	o << est.producto << "\t" << est.fecha << "\t" << est.precio;
	return o;
}

ostream& operator << (ostream& o, porProducto& est) {
	o << est.producto << "\t" << est.cantidad;
	return o;
}

ostream& operator << (ostream& o, Producto& est) {
	o << est.mes << "\t" << est.promedio;
	return o;
}

//El criterio que utilizo es en forma: Ascendente.
int criterio (porProducto a, porProducto b) {
	return a.producto.compare(b.producto);
}

int criterio2 (Producto a, Producto b) {
	return a.mes > b.mes;
}

void mostrarLista (Nodo<Producto>* lista) {
	while (lista != nullptr) {
		cout << lista->dato << endl;
		lista = lista->sig;
	}
}

int main() {
 	fstream miArchivo;
	miArchivo.open("Datos.bin", ios::in | ios::binary);
	(miArchivo.fail()) ? cout << "Error al abrir el archivo" << endl : cout << "Abierto correctamente" << endl;

	//Leer datos
	Registro aux;
	Nodo<porProducto>* lista = nullptr;
	Nodo<porProducto>* listaAux = nullptr;
	Nodo<Producto>* elemento = nullptr;
	porProducto producto;
	Producto productoAux;
	while (miArchivo >> aux) {
		cout << aux << endl;

		//Punto 2
		producto.producto = aux.producto;
		//El criterio que utilizo es en forma: Ascendente.
		listaAux = insertar_unico(producto, lista, criterio);
		listaAux->dato.cantidad++;

		//Punto 3
		productoAux.mes = (aux.fecha / 100) % 100;
		
		elemento = insertar_unico(productoAux, listaAux->dato.listaProductos, criterio2);
		elemento->dato.cantidadPorMes++;
		elemento->dato.precioTotal += aux.precio;
	}

	//Calculo los promedios
	elemento, listaAux = nullptr;
	listaAux = lista;
	while (listaAux != nullptr) {
		elemento = listaAux->dato.listaProductos;
	while (elemento != nullptr) {
		elemento->dato.promedio = (elemento->dato.precioTotal / double(elemento->dato.cantidadPorMes));
		elemento = elemento->sig;
	}
	listaAux = listaAux->sig;
}
	
	//Imprimo ListaAux
	cout << endl;
	mostrar(lista);
	cout << endl;

	listaAux = nullptr;
	//Punto 3
	producto.producto = "";
	while (true) {
		cout << "Ingrese un producto: ";
		getline(cin, producto.producto);
		listaAux = buscar(producto, lista, criterio);
		if (listaAux != nullptr) {
			cout << "Mes" << "\t" << "Promedio" << endl;
			mostrarLista(listaAux->dato.listaProductos);
		} else {
			cout << "No se encontro el producto" << endl;
		}
	}

	//COMENTARIO: LA LISTA DE SEGUNDO NIVEL SALTEA ALGUNOS MESES (EN LOS DISTINTOS PRODUCTOS) QUE TENDRIAN QUE APARECER, NO PUDE ENCONTRAR CUAL SERIA EL PROBLEMA!
}