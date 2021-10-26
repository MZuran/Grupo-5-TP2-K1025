#include <iostream>
#include <stdio.h>
#include <string.h>
#define caracteresCalle 25
#define caracteresNombres 15
#define caracteresPatente 7

using namespace std;

struct Incidente
{
    int codigoIncidente;
    int fechaHora; //AAAAMMDDHHmm
    int dniAsegurado;
    int dniOtroConductor;
    int nroPoliza;
    char calle[caracteresCalle]; //Acordarse que el caracter nulo es \0
    int altura;
};

struct polizaAsegurado
{
    int nroPoliza;
    int dni;
    char nombre[caracteresNombres];
    char apellido[caracteresNombres];
    bool cuotaAlDia;
    char patenteAuto[7];
    bool activa;
    int cdadIncidentes;
};

struct datospoliza
{
    polizaAsegurado info;
    datospoliza *sgte;
};

struct datoincidente
{
    Incidente info;
    Incidente *sgte;
};

//********************FUNCIONES ARCHIVO********************
void cargarPoliza(datospoliza *listas)
{
    system("CLS"); //Borra pantalla anterior

    //Se carga el archivo
    FILE* aseguradosFile;
    aseguradosFile = fopen("asegurados.bak", "r+b");
    listas = new datospoliza;
    datospoliza *paux=listas;


    cout << "Ingrese el número de poliza" << endl;
    cin >> paux->info.nroPoliza;
    cout << "Ingrese el número de DNI" << endl;
    cin >> paux->info.dni;
    cout << "Ingrese su nombre ("<< caracteresNombres <<" caracteres)" << endl;
    fflush(stdin);
    cin.getline(paux->info.nombre,caracteresNombres);
    cout << "Ingrese su apellido (" << caracteresNombres <<" caracteres)" << endl;
    fflush(stdin);
    cin.getline(paux->info.apellido,caracteresNombres);
    cout << "Está su cuota al día? 0: Sí, 1: No" << endl;
    cin >> paux->info.cuotaAlDia;
    cout << "Ingrese la patente de su auto (" << caracteresPatente <<" caracteres)" << endl;
    fflush(stdin);
    cin.getline(paux->info.patenteAuto,caracteresPatente);
    cout << "Está la poliza activa?" << endl;
    cin >> paux->info.activa;
    cout << "Ingrese la cantidad de incidentes" << endl;
    cin >> paux->info.cdadIncidentes;
    system("CLS");

    //Se guardan los nuevos datos en el archivo
    fseek(aseguradosFile,0,SEEK_END);
    fwrite(&paux->info,sizeof(datospoliza),1,aseguradosFile);
    paux=paux->sgte;

    //Se cierra el archivo
    fclose(aseguradosFile);
}


int main()
{

    FILE *aseguradosfile;
    int menuOption;
    datospoliza *lista;
    datospoliza *paux=lista;
    cout << "1: Cargar Poliza" << endl;
    cout << "2: Leer Polizas" << endl;
    cin >> menuOption;

    switch (menuOption)
    {
        case 1:
            cargarPoliza(lista);
        break;
        case 2:
        break;
    }
    return 0;
}


