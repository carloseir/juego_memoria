//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//ERROR AL HACER CLIC EN UN BOTON ACTIVO
void error_boton(GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *ventanaError;
  ventanaError = gtk_message_dialog_new(GTK_WINDOW(elementos->ventana),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
  "El botón seleccionado es inválido");
  gtk_window_set_title (GTK_WINDOW(ventanaError), "Error");
  gtk_window_set_modal (GTK_WINDOW(ventanaError), TRUE);
  gtk_dialog_run (GTK_DIALOG(ventanaError));
  gtk_widget_destroy (ventanaError);
}

//SI NO SE PUEDE DESHACER POR SER EL PRIMER TIRO
void errorDeshacer (GtkWidget *widget,gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *ventanaError;
  ventanaError = gtk_message_dialog_new(GTK_WINDOW(elementos->ventana),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
  "No se puede regresar, este es el primer tiro.");
  gtk_window_set_title (GTK_WINDOW(ventanaError), "Error");
  gtk_window_set_modal (GTK_WINDOW(ventanaError), TRUE);
  gtk_dialog_run (GTK_DIALOG(ventanaError));
  gtk_widget_destroy (ventanaError);
}

//SI NO SE PUEDE REHACER
void errorRehacer (GtkWidget *widget,gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *ventanaError;
  ventanaError = gtk_message_dialog_new(GTK_WINDOW(elementos->ventana),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
  "No se puede avanzar, es el ultimo tiro.");
  gtk_window_set_title (GTK_WINDOW(ventanaError), "Error");
  gtk_window_set_modal (GTK_WINDOW(ventanaError), TRUE);
  gtk_dialog_run (GTK_DIALOG(ventanaError));
  gtk_widget_destroy (ventanaError);
}

//SI NO SE HA JUGADO NINGUNA PARTIDA
void errorRanking (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *ventanaError;
  ventanaError = gtk_message_dialog_new(GTK_WINDOW(elementos->ventana),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
  "Aún no hay ranking.\nEmpieza a jugar, los mejores tiempos aparecerán aquí");
  gtk_window_set_title (GTK_WINDOW(ventanaError), "Error");
  gtk_window_set_modal (GTK_WINDOW(ventanaError), TRUE);
  gtk_dialog_run (GTK_DIALOG(ventanaError));
  gtk_widget_destroy (ventanaError);
}
