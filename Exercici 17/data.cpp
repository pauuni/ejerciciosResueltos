#include <stdio.h>
#include <iostream>
using namespace std;
#include "data.h"


void llegeixDia(Data& diaCalendari)
{
     cin>>diaCalendari.dia;
     cin>>diaCalendari.mes;
     cin>>diaCalendari.any;
}


bool getTraspasYear(int any){
    return any%4==0 && any%100!=0 && any%400==0; 
}
bool esValida(Data& diaCalendari)
{   //considerando las absurdeces de año o mes imposibles && 
    if(diaCalendari.any < 0 || diaCalendari.mes > 12 || diaCalendari.mes < 1 || diaCalendari.dia < 1 || diaCalendari.dia > 31 || (diaCalendari.mes == 2 && getTraspasYear(diaCalendari.any))){
        return false;
    }
    return true;
}

bool hasSameDate(int date1, int date2){
    return date1==date2;
}

int comparaDates(Data& data1, Data& data2)
{if(hasSameDate(data1.dia + data1.mes + data1.any, data2.dia+data2.mes+data2.any))
return 0;
    else if(data1.any>data2.any) return 1;
            else if(data1.any<data2.any)return -1;
        
       else if(data1.mes>data2.mes) return 1;
            else if(data1.mes<data2.mes)return -1;
            
             else if(data1.dia>data2.dia) return 1;
            else if(data1.dia<data2.dia)return -1;
}

int getDiesMes(int mes, bool isTraspas){
    if (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) return 31;
        else if (mes==2) 
                if (isTraspas) return 29; 
                    else return 28;
        else return 30;}

Data sumaDies(Data& diaOriginal, int nDies)
{   
   bool traspas=getTraspasYear(diaOriginal.any); //aqui sabemos si es any de traspas o no
    int diasDelAny = traspas ? 366 : 365;       //aqui guardamos en variable el numero de dias del anyo acorde a lo anterior
    int diesMes= getDiesMes( diaOriginal.mes,  traspas);
    int x;

   
     if(nDies==0){return diaOriginal;}
    
    while(nDies>=31){
        diesMes= getDiesMes( diaOriginal.mes,  traspas);    //,miras dias mes
        x=diesMes-diaOriginal.dia;                      //calculas lo que te queda para llegar a fin de mes, el dia maximo del mes - el dia en el que ya estas 31-10=21
        diaOriginal.dia+=(x+1);                         //actualizas tu dia de forma precisa para acabar en el dia 1 del mes siguiente. ej: 10+22=32 lo que equivale a 1 del mes siguiente
        nDies-=(x+1);                                   //actualizamos ndies lo mismo que sumamos a dias lo mismo que restamos a ndies. nDies=31-(21+1)=9
        
        if(diaOriginal.dia > diesMes){diaOriginal.mes++;} // 2
        diaOriginal.dia-=diesMes; // Confirmamos y actualizamos el dia de forma que se quede como el dia 1 del mes siguiente 32-31=1
        if(diaOriginal.mes==13){    //unas lineas para considerar el caso hipotetico de que debamos sumar año
            diaOriginal.mes=1;
            diaOriginal.any++;
        }
     
    }
      if(nDies>0){  
           diesMes= getDiesMes( diaOriginal.mes,  traspas);
        x=diesMes-diaOriginal.dia;  
        if(nDies < x){
            diaOriginal.dia +=nDies;
        } else{
            
            diaOriginal.dia+=nDies;
            
            diaOriginal.dia-x;
            if(diaOriginal.dia!= diesMes){
            diaOriginal.mes ++;}
            }
         
         
      }
    return diaOriginal;
   
    
}

int DiasTranscurridosAnyo(Data Fecha)
{
 // Variables a utilizar   
  int contador=0;
  int suma=0;
  int dia=Fecha.dia;
  int mes=Fecha.mes;
  int any=Fecha.any;
  // Crear una matriz numerica con los dias
  // correspondientes a cada mes
  int Meses_Anyo[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  // Contar los dias transcurridos segun los meses pasados
  for (contador=0;contador<mes-1;contador++)
  {
     suma+= Meses_Anyo[contador];
  }
  //  sumar los dias correspondientes al mes actual
  suma+= dia;
  // si el año es bisiesto sumar 1 dia mas al total
  if(getTraspasYear(any) && mes>2) 
     suma++;
  // devolver el numero de dias transcurridos de la fecha pasada
  return suma;
}



int restaDates(Data& data1, Data& data2)
{
    // Variables a utilizar
     int anyoiniciocuantos=0;
     int anyofinalcuantos=0;
     long sumadias=0;
     int cuentaanyos=0;
     // Dias transcurridos de la primera fecha, en caso de ser años iguales
     // la diferencia en dias de la primera fecha es 0
     bool traspas = getTraspasYear(data1.any);
     int diasDelAny = traspas ? 366 : 365;
     anyoiniciocuantos = data1.any==data2.any? 0: diasDelAny - DiasTranscurridosAnyo(data1);
     // dias transcurridos del año de la segunda fecha
     anyofinalcuantos = DiasTranscurridosAnyo(data2);
     
     // Contar los años transcurridos entre una fecha y otra sumando
     // los dias correspondientes por año
     for(cuentaanyos=data1.any+1;cuentaanyos<data2.any;cuentaanyos)
     {
         traspas=getTraspasYear(cuentaanyos);
         diasDelAny = traspas ? 366 : 365;
        sumadias+=diasDelAny;
     }
     // sumar los dias correspondientes al total de dias transcurridos
     sumadias+=anyoiniciocuantos+anyofinalcuantos;
     // devolver la suma de dias transcurridos
     if(data1.any==data2.any){
         sumadias-=10;
     }
     return sumadias;
}

bool terminiValid(Data& diaOriginal, int nDies, Data& dataActual)
{
    diaOriginal=sumaDies(diaOriginal,nDies);
    
if(diaOriginal.dia<=dataActual.dia && diaOriginal.mes<=dataActual.mes && diaOriginal.any<=dataActual.any){
return false;
    }
    return true;
}

