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
    float fechaHora; //AAAAMMDDHHmm
    int dniAsegurado;
    int dniOtroConductor;
    int nroPoliza;
    char calle[caracteresCalle]; //Acordarse que el caracter nulo es \0
    int altura;
};

int inicializarIncidente(Incidente& y)
{
    y.codigoIncidente = 0;
    y.fechaHora = 0;
    y.dniAsegurado = 0;
    y.dniOtroConductor = 0;
    y.nroPoliza = 0;
    strncpy(y.calle, "", caracteresCalle);
    y.altura = 0;
    return 0;
}

int main()
{
    Incidente datos;
    FILE *F;
    bool stop = false;
    F = fopen("incidentes.bak","wb");

    do
    {
        inicializarIncidente(datos);

        cout << "Ingrese altura (Int)" << endl;
        cin >> datos.altura;

        cout << "Ingrese la calle (char[25])" << endl;
        fflush(stdin);
        cin.getline(datos.calle,caracteresCalle);

        cout << "Ingrese el codigo de incidente (Int)" << endl;
        cin >> datos.codigoIncidente;

        cout << "Ingrese el dni del asegurado (Int)" << endl;
        cin >> datos.dniAsegurado;

        cout << "Ingrese el dni del otro conductor (Int)" << endl;
        cin >> datos.dniOtroConductor;

        cout << "Ingrese la fecha y hora (Int) (AAAAMMDDHHmm)" << endl;
        cin >> datos.fechaHora;

        cout << "Ingrese el numero de poliza" << endl;
        cin >> datos.nroPoliza;

        fwrite(&datos,sizeof(datos),1,F);

        system("CLS");
        cout << "Seguir?" << endl << "0 = Si 1 = No" << endl;
        cin >> stop;
        system("CLS");
    } while (stop == false);

    fclose(F);
    return 0;
}
