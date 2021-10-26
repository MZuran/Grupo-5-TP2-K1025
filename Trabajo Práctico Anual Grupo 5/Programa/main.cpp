#include <iostream>
#include <stdio.h>
#include <string.h>
#define caracteresCalle 25
#define caracteresNombres 15
#define caracteresPatente 7

using namespace std;

//********************DECLARACIÓN STRUCTS********************
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

struct polizaAsegurado
{
    int nroPoliza;
    int dni;
    char nombre[caracteresNombres];
    char apellido[caracteresNombres];
    bool cuotaAlDia;
    char patenteAuto[caracteresPatente];
    bool activa;
    int cdadIncidentes;
};

struct nodoListaSE
{
    polizaAsegurado polizaLista;
    nodoListaSE *sgte;
};

struct nodoListaSEIncidentes
{
    Incidente incidenteLista;
    nodoListaSEIncidentes *sgte;
};

//********************FUNCIONES********************
void cargarPolizas(nodoListaSE*& inicio, int &contador)
{
    nodoListaSE *paux=inicio;

    cout << "Primero en la lista: " << endl << paux->polizaLista.nombre << endl << endl;

    //Se mueve hasta el final de la lista SE
    for (int i=0; i < contador-1; i = i + 1)
    {
        paux=paux->sgte;
    }

    cout << "Ultimo en la lista: " << endl << paux->polizaLista.nombre << endl << endl;
    paux->sgte=new nodoListaSE();
    paux = paux->sgte;
    paux->sgte = NULL;

    contador = contador + 1;

    //Ingresa datos uno por uno
    cout << "Ingrese el numero de poliza" << endl;
    cin >> paux ->polizaLista.nroPoliza;
    cout << "Ingrese el numero de DNI" << endl;
    cin >> paux ->polizaLista.dni;
    cout << "Ingrese su nombre ("<< caracteresNombres <<" caracteres)" << endl;
    fflush(stdin);
    cin.getline(paux ->polizaLista.nombre,caracteresNombres);
    cout << "Ingrese su apellido (" << caracteresNombres <<" caracteres)" << endl;
    fflush(stdin);
    cin.getline(paux ->polizaLista.apellido,caracteresNombres);
    cout << "Está su cuota al dia? 0: Si, 1: No" << endl;
    cin >> paux ->polizaLista.cuotaAlDia;
    cout << "Ingrese la patente de su auto (" << caracteresPatente <<" caracteres)" << endl;
    fflush(stdin);
    cin.getline(paux ->polizaLista.patenteAuto,caracteresPatente);
    cout << "Esta la poliza activa(1=true 0=false)?" << endl;
    cin >> paux ->polizaLista.activa;
    cout << "Ingrese la cantidad de incidentes" << endl;
    cin >> paux ->polizaLista.cdadIncidentes;
    system("CLS");

    cout << "Datos de " << paux->polizaLista.nombre << " cargados con exito" << endl << endl;
}

bool validarDatos(nodoListaSE*& paux)
{
    bool a = paux->polizaLista.nroPoliza;
    bool b = paux->polizaLista.dni;
    bool c = paux->polizaLista.nombre[0];
    bool d = paux->polizaLista.apellido[0];
    bool e = paux->polizaLista.patenteAuto[0];
    return a*b*c*d*e;
}

void finalizarJornada(nodoListaSE*& inicio)
{
    nodoListaSE *paux = inicio;

    FILE* aseguradosFile;
    aseguradosFile = fopen("asegurados.bak", "w");

    //Se mueve hasta el final de la lista SE
    while (paux)
    {
        if (validarDatos(paux))
        {
            //cout << "Escribio una poliza" << endl;
            fwrite(&paux->polizaLista,sizeof(paux->polizaLista),1,aseguradosFile);
            fseek(aseguradosFile,0,SEEK_END);
        }
        paux=paux->sgte;
    }

    fclose(aseguradosFile);
    cout << "Fin";
}

void desactivar(nodoListaSE *&lista)
{



    cout << "Ingrese el numero de poliza a desactivar: " << endl;
    int poliza;
    cin >> poliza;

    bool encontrado=false;
    nodoListaSE *paux=lista;
    while (paux && encontrado!=true)
    {
        if (paux->polizaLista.nroPoliza==poliza)
        {
            encontrado=true;
            //cout << paux->polizaLista.activa << endl;
        }
        else
            paux=paux->sgte;
    }
    if (encontrado==true)
    {

        if (paux->polizaLista.activa==false)
        {
            cout << "La poliza ya esta desactivada" << endl << endl;
            //cout << paux->polizaLista.activa << endl;
        }
        if (paux->polizaLista.activa==true)
        {
            paux->polizaLista.activa=false;
            //cout << paux->polizaLista.activa << endl;
            cout << "Se desactivo la poliza de " << paux->polizaLista.nombre << " " << paux->polizaLista.apellido << endl << endl;
        }
    }
    else
        cout << "No se encontro la poliza buscada" << endl << endl;

}
void buscarpol(nodoListaSE *&lista)
{



    cout << "Buscar poliza por nro de poliza(1) o por dni(0)" << endl;
    int dato;
    cin >> dato;
    bool encontrado=false;
    nodoListaSE *paux=lista;
    if (dato==1)
    {
        cout << endl << "ingrese nro. de poliza:" << endl;
        int poliza;
        cin >> poliza;
        system("CLS");
        while (paux)
        {
            if (paux->polizaLista.nroPoliza==poliza)
            {
                encontrado=true;
                cout << "Se encontro la poliza de: " << paux->polizaLista.nombre << ", "<< paux->polizaLista.apellido << endl;
                cout << "Dni: " << paux->polizaLista.dni << endl;
                cout << "Cantidad de incidentes: " << paux->polizaLista.cdadIncidentes << endl;
                cout << "Patente del auto: " <<paux->polizaLista.patenteAuto << endl;
                cout << "Cuota al dia?: " <<paux->polizaLista.cuotaAlDia << endl;
                cout << "Estado de poliza (1=Activada, 0=Desactivada): " << paux->polizaLista.activa << endl << endl;
                paux=paux->sgte;
            }
            else
                paux=paux->sgte;
        }
        if (encontrado==false)
            cout << "no se pudo encontrar la poliza buscada" << endl << endl;
    }
    if(dato==0)
    {
        cout << endl << "ingrese dni:" << endl;
        int dni;
        cin >> dni;
        system("CLS");
        while (paux)
        {
            if (paux->polizaLista.dni == dni)
            {
                encontrado=true;
                cout << endl;
                cout << "Se encontro la poliza de: " << paux->polizaLista.nombre << ", "<< paux->polizaLista.apellido << endl;
                cout << "Numero de poliza: " << paux->polizaLista.nroPoliza << endl;
                cout << "Cantidad de incidentes: " << paux->polizaLista.cdadIncidentes << endl;
                cout << "Patente del auto: " <<paux->polizaLista.patenteAuto << endl;
                cout << "Cuota al dia?: " <<paux->polizaLista.cuotaAlDia << endl;
                cout << "Estado de poliza(1=activa o 0=desactiva): " << paux->polizaLista.activa << endl << endl;
                paux=paux->sgte;
            }
            else
                paux=paux->sgte;
        }
        if (encontrado==false)
            cout << "No se pudo encontrar la poliza buscada" << endl << endl;
    }
}
void ordsaldo (nodoListaSE *&lista)
{



    nodoListaSE *paux=lista;
    nodoListaSE *paux2=lista->sgte;
    polizaAsegurado info1;
    polizaAsegurado info2;
    for (int j=0; j<8; j++)
    {
        paux=lista;
        paux2=lista->sgte;
        while (paux2)
        {
            if((paux->polizaLista.cdadIncidentes)<(paux2->polizaLista.cdadIncidentes))
            {
                info1= paux->polizaLista;
                info2= paux2->polizaLista;
                paux->polizaLista=info2;
                paux2->polizaLista=info1;
                paux=paux->sgte;
                paux2=paux2->sgte;
            }
            else
            {
                paux=paux->sgte;
                paux2=paux2->sgte;
            }
        }
    }
    paux=lista;
    while (paux)
    {
        if (paux->polizaLista.activa==1)
        {
            cout << endl;
            cout <<"*************************************************************************************************" << endl;
            cout << "la poliza de: " << paux->polizaLista.nombre << ", "<< paux->polizaLista.apellido << endl;
            cout << "numero de poliza: " << paux->polizaLista.nroPoliza << endl;
            cout << "cantidad de incidentes: " << paux->polizaLista.cdadIncidentes << endl;
            cout << "patente del auto: " <<paux->polizaLista.patenteAuto << endl;
            cout << "cuota al dia?: " <<paux->polizaLista.cuotaAlDia << endl;
            cout << "estado de poliza(1=activa o 0=desactiva): " << paux->polizaLista.activa << endl;
            cout << "dni: " << paux->polizaLista.dni << endl << endl;
            paux=paux->sgte;
        }
        else
            paux=paux->sgte;
    }
}

void levantarPolizas(nodoListaSE*& inicio, int &contador)
{
    FILE *F;
    if (F = fopen("asegurados.bak","rb"))
    {
        F = fopen("asegurados.bak","rb");
    }
    else
    {
        F = fopen("asegurados.bak","wb");
        fclose(F);
        F = fopen("asegurados.bak","rb");

        cout << "Se ha creado el archivo" << endl;
    }

    cout << "Nombres de las polizas aseguradas" << endl << endl;

    nodoListaSE *paux;

    inicio=new nodoListaSE();
    paux= inicio;

    while (!feof(F))
    {
        fread(&paux -> polizaLista, sizeof(polizaAsegurado), 1, F);
        if (!feof(F))
        {
            cout << paux -> polizaLista.nombre << " " << paux -> polizaLista.apellido << endl;
            paux->sgte=new nodoListaSE();
            paux = paux->sgte;
            contador = contador + 1;
        }
        else
        {
            paux->sgte = NULL;
        }
    };
    cout << "Cantidad de polizas levantadas: " << contador << endl << endl;
    fclose(F);
}

void informeHTML(nodoListaSE *&lista)
{
    nodoListaSE *paux=lista;

    FILE *f1;
    f1 = fopen("informe.html", "wt");
    fprintf(f1,"<html><body>\n");
    fprintf(f1,"<h2>Informe de patentes no al día</h2>\n");
    fprintf(f1,"<table border=2>\n");
    fprintf(f1,"<th>Numero Poliza</th><th>DNI</th><th>Nombres</th><th>Apellido</th><th>Patente</th><th>Poliza Activa?</th><th>Cantidad Incidentes</th>\n");

    while (paux)
    {
        if (validarDatos(paux) && paux -> polizaLista.cuotaAlDia == 1)
        {
            fprintf(f1,"<tr>\n");
            //%s es para strings
            //%d es para decimales
            fprintf(f1,"<td>%d</td><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%d</td><td>%d</td>\n",paux -> polizaLista.nroPoliza ,paux -> polizaLista.dni ,paux -> polizaLista.nombre ,paux -> polizaLista.apellido ,paux -> polizaLista.patenteAuto ,paux -> polizaLista.activa ,paux -> polizaLista.cdadIncidentes);
            fprintf(f1,"</tr>\n");
        }
        paux = paux -> sgte;
    }
    fprintf(f1, "</table>");
    fprintf(f1, "</body>");
    fprintf(f1, "</html>");
    fclose(f1);

    cout << "Informe HTML creado con exito" << endl << endl;
    return;
}

void informeCSV(nodoListaSE *&lista)
{
    FILE *f1;
    f1 = fopen("informe.csv", "wt");
    nodoListaSE *paux=lista;

    fprintf(f1,"Numero Poliza;DNI;Nombres;Apellido;Patente;Poliza Activa?;Cantidad Incidentes\n");

    while (paux)
    {
        if (validarDatos(paux) && paux -> polizaLista.cuotaAlDia == 1)
        {
            //%s es para strings
            //%d es para decimales
            fprintf(f1,"%d;%d;%s;%s;%s;%d;%d\n",paux -> polizaLista.nroPoliza ,paux -> polizaLista.dni ,paux -> polizaLista.nombre ,paux -> polizaLista.apellido ,paux -> polizaLista.patenteAuto ,paux -> polizaLista.activa ,paux -> polizaLista.cdadIncidentes);
        }
        paux = paux -> sgte;
    }
    fclose(f1);

    cout << "Informe CSV creado con exito" << endl << endl;
    return;
}

void procesarIncidentes(nodoListaSE *&lista)
{

    nodoListaSE *pauxPersonas=lista;
    //Incidente aux;
    int i = 0;

    FILE *fIncidentes;

    if (fIncidentes = fopen("incidentes.bak","rb"))
    {
        fIncidentes = fopen("incidentes.bak","rb");

        nodoListaSEIncidentes *inicioIncidentes = NULL;
        nodoListaSEIncidentes *pauxIncidentes;

        inicioIncidentes =new nodoListaSEIncidentes();
        pauxIncidentes= inicioIncidentes;

        while (!feof(fIncidentes))
        {
            fread(&pauxIncidentes -> incidenteLista, sizeof(Incidente), 1, fIncidentes);

            if (!feof(fIncidentes))
            {
                //cout << pauxIncidentes -> incidenteLista.calle << endl;
                pauxIncidentes -> sgte = new nodoListaSEIncidentes();
                pauxIncidentes = pauxIncidentes -> sgte;

                /*cout << "Codigo de incidente: " << aux.codigoIncidente << endl;
                cout << "Fecha y hora: " << aux.fechaHora << endl;
                cout << "Dni del asegurado: " << aux.dniAsegurado << endl;
                cout << "Dni del otro conductor: " << aux.dniOtroConductor << endl;
                cout << "Numero de poliza: " << aux.nroPoliza << endl;
                cout << "Calle: " << aux.calle << endl;
                cout << "Altura de calle: " << aux.altura << endl;
                cout << endl;*/
            }
        }

        pauxIncidentes = inicioIncidentes;

        nodoListaSE *pauxPersonas=lista;
        FILE *fProcesados;
        fProcesados = fopen("procesados.bak","wb");

        while (pauxPersonas)
        {
            while (pauxIncidentes)
            {
                //cout << "**********************" << endl;

                if (pauxPersonas -> polizaLista.nroPoliza == pauxIncidentes -> incidenteLista.nroPoliza)
                {
                    pauxPersonas -> polizaLista.cdadIncidentes = pauxPersonas -> polizaLista.cdadIncidentes + 1;
                    fwrite(&pauxIncidentes -> incidenteLista,sizeof(Incidente),1,fProcesados);
                }
                pauxIncidentes = pauxIncidentes -> sgte;
            }
            pauxIncidentes = inicioIncidentes;
            pauxPersonas = pauxPersonas -> sgte;
        }
        fclose(fProcesados);

        cout << "Incidentes procesados con exito" << endl << endl;
    }
    else
    {
        cout << "No hay archivo de incidentes!" << endl << endl;
    }

    fclose(fIncidentes);
}
//********************MAIN********************
int main()
{
    nodoListaSE *inicio = NULL;
    int contador = 0;
    int menuOption = 0;

    levantarPolizas(inicio, contador);

    while (menuOption != 8)
    {
        cout << "1: Cargar Poliza" << endl;
        cout << "2: Desactivar una poliza existente " << endl;
        cout << "3: Buscar una poliza por dni o por su numero " << endl;
        cout << "4: Mostrar todas las polizas activas ordenadas por saldo " << endl;
        cout << "5: Crear informe HTML de polizas sin cuota al dia" << endl;
        cout << "6: Crear informe CSV de polizas sin cuota al dia" << endl;
        cout << "7: Procesamiento de incidentes de archivo externo" << endl;
        cout << "8: Finalizar Jornada (Sobreescribir)" << endl;

        cin >> menuOption;
        system("CLS");

        switch (menuOption)
        {
        case 1:
            cargarPolizas(inicio, contador);
            break;

        case 2:
            desactivar(inicio);
            break;

        case 3:
            buscarpol(inicio);
            break;

        case 4:
            ordsaldo(inicio);
            break;

        case 5:
            informeHTML(inicio);
            break;

        case 6:
            informeCSV(inicio);
            break;

        case 7:
            procesarIncidentes(inicio);
            break;

        case 8:
            finalizarJornada(inicio);
            break;
        }
    }
    return 0;
}
