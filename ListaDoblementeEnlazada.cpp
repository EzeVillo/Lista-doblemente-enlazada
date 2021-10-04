#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class Nodo
{
public:
	Nodo *Ant;
	Nodo *Sig;
	Nodo(char *);
	~Nodo();
	char Nombre[20];
};

class Lista
{
public:
	Nodo *Inicio;
	Nodo *Final;
	Lista();
	~Lista();
	void Insertar(char *);
	void Mostrar();
	void MostrarAlReves();
	Nodo *Sacar(char *);

private:
	void Insert(Nodo *);
};

Nodo::Nodo(char *N)
{
	strcpy(Nombre, N);
}

Nodo::~Nodo()
{
	cout << "Matando a " << Nombre << "\n\n";
}

Lista::Lista()
{
	Inicio = NULL;
	Final = NULL;
}

Lista::~Lista()
{
	if (!Inicio)
		return;

	Nodo *N = Inicio;

	cout << "\t\t MATANDO: \n\n";

	while (N->Sig)
	{
		N = N->Sig;
		delete N->Ant;
	}
	delete N;
}

void Lista::Insertar(char *Nombre)
{
	Nodo *NodoN = new Nodo(Nombre);
	Insert(NodoN);
}

void Lista ::Insert(Nodo *NodoN)
{
	if (!Inicio)
	{
		// si la lista esta vacia
		Inicio = NodoN;
		Final = NodoN;
		NodoN->Sig = NULL;
		NodoN->Ant = NULL;
		return;
	}

	if (strcmp(NodoN->Nombre, Inicio->Nombre) < 0)
	{
		// si es el primer nodo
		Inicio->Ant = NodoN;
		NodoN->Sig = Inicio;
		NodoN->Ant = NULL;
		Inicio = NodoN;
		return;
	}

	Nodo *Aux = Inicio->Sig;
	while (Aux)
	{
		// si esta en el medio
		if (strcmp(NodoN->Nombre, Aux->Nombre) < 0)
		{
			Aux->Ant->Sig = NodoN;
			NodoN->Sig = Aux;
			NodoN->Ant = Aux->Ant;
			Aux->Ant = NodoN;
			return;
		}
		Aux = Aux->Sig;
	}
	// ultimo nodo
	NodoN->Sig = NULL;
	NodoN->Ant = Final;
	Final->Sig = NodoN;
	Final = NodoN;
}

Nodo *Lista::Sacar(char *Nombre)
{
	if (!Inicio)
		return NULL;

	Nodo *Nodo;
	Nodo = Inicio;

	if (strcmp(Inicio->Nombre, Nombre) == 0 && Inicio->Sig == NULL)
	{
		// si es el unico elemento en la lista
		Nodo = Inicio;
		Inicio = NULL;
		Final = NULL;
		return Nodo;
	}

	if (strcmp(Inicio->Nombre, Nombre) == 0)
	{
		// si es el primero
		Nodo = Inicio;
		Inicio = Inicio->Sig;
		Inicio->Ant = NULL;
		return Nodo;
	}

	if (strcmp(Final->Nombre, Nombre) == 0)
	{
		// si es el ultimo
		Nodo = Final;
		Final = Final->Ant;
		Final->Sig = NULL;
		return Nodo;
	}

	while (Nodo)
	{
		if (strcmp(Nodo->Nombre, Nombre) == 0)
		{
			// si esta en el medio
			Nodo->Ant->Sig = Nodo->Sig;
			Nodo->Sig->Ant = Nodo->Ant;
			return Nodo;
		}
		Nodo = Nodo->Sig;
	}
	return NULL;
}

void Lista::Mostrar()
{
	if (!Inicio)
		return;

	Nodo *Nodo = Inicio;

	cout << "\t\t MOSTRANDO: \n\n";

	while (Nodo)
	{
		cout << "Nombre " << Nodo->Nombre << "\n\n";
		Nodo = Nodo->Sig;
	}
}

void Lista::MostrarAlReves()
{
	if (!Final)
		return;
	Nodo *Nodo = Final;

	cout << "\t\t MOSTRANDO AL REVES: \n\n";

	while (Nodo)
	{
		cout << "Nombre " << Nodo->Nombre << "\n\n";
		Nodo = Nodo->Ant;
	}
}

char *GenerarNombre()
{
	static int I = 0;
	static char Nombre[][20] = {"Franco", "Agustin", "Lautaro", "Camila",
								"Pepe", "Larry", "Leo", "Pipo",
								"Luis", "Cristian", "Ezequiel", "Beatriz", "FIN"};
	return Nombre[I++];
}

int main()
{

	Lista Nombres;

	char Nombre[20];
	strcpy(Nombre, GenerarNombre());
	cout << "\t\t INGRESO: \n\n";
	cout << "Nombre " << Nombre << "\n\n";

	while (strcmp(Nombre, "FIN") != 0)
	{
		Nombres.Insertar(Nombre);
		strcpy(Nombre, GenerarNombre());
		cout << "Nombre " << Nombre << "\n\n";
	}

	Nombres.Mostrar();
	Nombres.MostrarAlReves();

	cout << "Ingrese un nombre para Eliminar: ";
	cin >> Nombre;
	cout << "\n\n";
	Nodo *Nodo = Nombres.Sacar(Nombre);
	if (Nodo)
	{
		delete Nodo;
		Nombres.Mostrar();
		Nombres.MostrarAlReves();
	}
	else
	{
		cout << "Ingreso un nombre invalido \n\n";
	}
}