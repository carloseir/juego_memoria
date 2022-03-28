//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//FUNCION DE LA COMPUTADORA
void computadora (GtkWidget *widget, gpointer user_data){
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  gint num;
  int i=0;
  int pares = 0;
  if (elementos->numTiros == 1) {
    //ESCONDE LAS IMAGENES CUANDO DAS CLIC EN EL TURNO SIGUIENTE
    if (elementos->primerTiro == 2) {
      gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta1]));
      gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta2]));
    }
    do {
      if (elementos->recordar [i] == 1 && elementos->recordar [32+i] == 1) {
        elementos->bCarta1 = i;
        elementos->bCarta2 = 32+i;
        elementos->igual = 1;
      }
      else{
        elementos->igual = 0;
        i++;
      }
    } while(elementos->igual == 0 && i < 32);
    if (elementos->igual == 0) {
      do {
        num=rand20 ();
        if (elementos->recordar [num] == 2) {
          pares = 1;
        }
        else{
          pares = 0;
          elementos->bCarta1 = num;
        }
      } while(pares == 1);
    }
    gtk_button_clicked (GTK_BUTTON (elementos->botones [elementos->bCarta1]));
  }
  else if (elementos->numTiros == 2) {
    if (elementos->igual == 1) {
      gtk_button_clicked (GTK_BUTTON (elementos->botones [elementos->bCarta2]));
    }
    else if (elementos->igual == 0) {
      do {
        num=rand20 ();
        if (elementos->recordar [num] == 2 || elementos->bCarta1 == num) {
          pares = 1;
        }
        else{
          pares = 0;
          elementos->bCarta2 = num;
        }
      } while(pares == 1);
    }
    gtk_button_clicked (GTK_BUTTON (elementos->botones [elementos->bCarta2]));
  }
}
