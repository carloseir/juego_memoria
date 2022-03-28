//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//FUNCION DEL TIEMPO
gint cuenta(gpointer user_data)
{
    ELEMENTOS *elementos = (ELEMENTOS *) user_data;
    gchar cadena[20];

    elementos->segundosTotales +=1;//Contador del tiempo total en segundos

    elementos->timerSegundos +=1;

    if(elementos->timerSegundos > 60)
    {
      elementos->timerSegundos = 0;
      elementos->timerMinutos++;
    }

    if(elementos->timerMinutos > 60)
    {
      elementos->timerHoras++;
    }

    sprintf(cadena, "%2d:%2d:%2d", elementos->timerHoras, elementos->timerMinutos, elementos->timerSegundos);
    gtk_label_set_text (GTK_LABEL(elementos->labelTimer),cadena);
    gtk_widget_set_tooltip_text (elementos->labelTimer, "Tiempo transcurrido en la partida");
    return 1;
}

//ACOMODA ALEATORIAMENTE LAS CARTAS
void rand10(ELEMENTOS *elementos)
{
  srand(time(0)); // iniciando la semilla aleatoria
  int vector [64];
  int i,j;

  for(i=0;i<63;i++)
  {
    // Genera numero aleatorio
    int num = 1 + rand()%63;

   if(i>0)
   {
      // Verifica si no se ha generado antes
      for(j=0; j < i; j++)
          if(num==vector[j])
          {
             num = 1 + rand()%63;
             j=-1;
          }
    }

    vector [ i ] =num;
  }
  for ( i = 0; i < 63; i++) {
    elementos->mapaimg [i] = vector [i];
  }

}

//Genera un tiro aleatorio para la computadora
int rand20(void)
{
    static int firstcall=1;
    if (firstcall)
    {
    srand((unsigned int)time(NULL));
    firstcall = 0;
    }
    return ( rand()%63 +1);
}
