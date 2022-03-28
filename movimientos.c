//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//OPCION DE DESHACER
void deshacer (GtkWidget *widget,gpointer user_data){
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  if (elementos->tiro >= 1) {
    //REGRESA AL MOVIMIENTO ANTERIOR
    elementos->tiro = (elementos->tiro)-1;
    //OBTIENE LA INFORMACION DEL MOVIMIENTO ANTERIOR
    elementos->info = g_list_nth_data(elementos->lista,elementos->tiro);
    elementos->movimientos = (MOVIMIENTOS *) elementos->info;
    //OCULTA LAS IMAGENES Y MUESTRA LAS QUE ESTABAN ANTES
    for (int i = 0; i < 64; i++) {
      elementos->botonesActivos [i] = (elementos->movimientos)->botonesActiv [i];
    }
    for (int i = 0; i < 64; i++) {
      if (elementos->botonesActivos [i] == 1) {
        gtk_widget_show_all (GTK_WIDGET (elementos->imagenes [i]));
      }
      else {
        gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
      }
    }
    gtk_widget_show_all (GTK_WIDGET (elementos->imagenes [(elementos->movimientos)->carta]));
    //ESTABLECER LOS DATOS
    elementos->turno=(elementos->movimientos)->turnoM;
    elementos->numTiros = (elementos->movimientos)->numeroTiros;
    if (elementos->modoJuego == 1) {
      for (int i = 0; i < 64; i++) {
        elementos->recordar [i] = (elementos->movimientos)->recordarPC [i];
      }
    }
    //COLOCAR LA CARTA COMO ACTUAL
    if (elementos->numTiros == 1) {
      elementos->bCarta2 = (elementos->movimientos)->carta;
    }
    else if (elementos->numTiros == 2){
      elementos->bCarta1 = (elementos->movimientos)->carta;
    }
    elementos->paresJ1= (elementos->movimientos)->pares1J;
    sprintf(elementos->puntosJ1, "%d",elementos->paresJ1);
    gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),elementos->puntosJ1);
    elementos->paresJ2= (elementos->movimientos)->pares2J;
    sprintf(elementos->puntosJ2, "%d",elementos->paresJ2);
    gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),elementos->puntosJ2);
  }
  else if ((elementos->tiro) == 0){
    errorDeshacer(widget, user_data);
  }
}

//OPCION DE REHACER
void rehacer (GtkWidget *widget, gpointer user_data){
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  if (elementos->tiro >= 0 && elementos->tiro < g_list_length (elementos->lista)-1) {
    //AVANZA AL MOVIMIENTO SIGUIENTE
    elementos->tiro = (elementos->tiro)+1;
    //OBTIENE LA INFORMACION DEL MOVIMIENTO SIGUIENTE
    elementos->info = g_list_nth_data(elementos->lista,elementos->tiro);
    elementos->movimientos = (MOVIMIENTOS *) elementos->info;
    //OCULTA LAS IMAGENES Y MUESTRA LAS QUE ESTABAN ANTES
    for (int i = 0; i < 64; i++) {
      elementos->botonesActivos [i] = (elementos->movimientos)->botonesActiv [i];
    }
    for (int i = 0; i < 64; i++) {
      if (elementos->botonesActivos [i] == 1) {
        gtk_widget_show_all (GTK_WIDGET (elementos->imagenes [i]));
      }
      else {
        gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
      }
    }
    gtk_widget_show_all (GTK_WIDGET (elementos->imagenes [(elementos->movimientos)->carta]));
    //ESTABLECER LOS DATOS
    elementos->turno=(elementos->movimientos)->turnoM;
    elementos->numTiros = (elementos->movimientos)->numeroTiros;
    if (elementos->modoJuego == 1) {
      for (int i = 0; i < 64; i++) {
        elementos->recordar [i] = (elementos->movimientos)->recordarPC [i];
      }
    }
    //COLOCAR LA CARTA COMO ACTUAL
    if (elementos->numTiros == 1) {
      elementos->bCarta2 = (elementos->movimientos)->carta;
    }
    else if (elementos->numTiros == 2){
      elementos->bCarta1 = (elementos->movimientos)->carta;
    }
    elementos->paresJ1= (elementos->movimientos)->pares1J;
    sprintf(elementos->puntosJ1, "%d",elementos->paresJ1);
    gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),elementos->puntosJ1);
    elementos->paresJ2= (elementos->movimientos)->pares2J;
    sprintf(elementos->puntosJ2, "%d",elementos->paresJ2);
    gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),elementos->puntosJ2);
  }
  else if ((elementos->tiro) == g_list_length (elementos->lista)-1){
    errorRehacer (widget, user_data);
  }
}

//MOVIMIENTO
void movimiento (GtkWidget *widget, gpointer user_data){
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  if (elementos->tiro < g_list_length (elementos->lista)-1) {
    //AVANZA AL MOVIMIENTO SIGUIENTE
    elementos->tiro = (elementos->tiro)+1;
    //OBTIENE LA INFORMACION DEL MOVIMIENTO SIGUIENTE
    elementos->info = g_list_nth_data(elementos->lista,elementos->tiro);
    elementos->movimientos = (MOVIMIENTOS *) elementos->info;
    //OBITENE EL MODO DE JUEGO
    elementos->modoJuego = (elementos->movimientos)->modo;
    //OCULTA LAS IMAGENES Y MUESTRA LAS QUE ESTABAN ANTES
    for (int i = 0; i < 64; i++) {
      elementos->botonesActivos [i] = (elementos->movimientos)->botonesActiv [i];
    }
    for (int i = 0; i < 64; i++) {
      if (elementos->botonesActivos [i] == 1) {
        gtk_widget_show_all (GTK_WIDGET (elementos->imagenes [i]));
      }
      else {
        gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
      }
    }
    gtk_widget_show_all (GTK_WIDGET (elementos->imagenes [(elementos->movimientos)->carta]));
    //ESTABLECER LOS DATOS
    elementos->turno=(elementos->movimientos)->turnoM;
    elementos->numTiros = (elementos->movimientos)->numeroTiros;
    if (elementos->modoJuego == 1) {
      for (int i = 0; i < 64; i++) {
        elementos->recordar [i] = (elementos->movimientos)->recordarPC [i];
      }
    }
    //COLOCAR LA CARTA COMO ACTUAL
    if (elementos->numTiros == 1) {
      elementos->bCarta2 = (elementos->movimientos)->carta;
    }
    else if (elementos->numTiros == 2){
      elementos->bCarta1 = (elementos->movimientos)->carta;
    }
    elementos->paresJ1= (elementos->movimientos)->pares1J;
    sprintf(elementos->puntosJ1, "%d",elementos->paresJ1);
    gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),elementos->puntosJ1);
    elementos->paresJ2= (elementos->movimientos)->pares2J;
    sprintf(elementos->puntosJ2, "%d",elementos->paresJ2);
    gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),elementos->puntosJ2);
  }
  else if ((elementos->tiro) == g_list_length (elementos->lista)-1){
    errorRehacer (widget, user_data);
  }
}
