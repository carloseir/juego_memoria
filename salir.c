//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//FUNCION PARA CERRAR EL EVENTO DE LA VENTANA PRINCIPAL
gboolean deleteEventHandler(GtkWidget *widget, GdkEvent *event,gpointer  user_data)
{
  return FALSE;
}

//FUNCION PARA SALIR DEL PROGRAMA AL CERRAR
void salir (GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  //Liberar memoria
  g_list_free(elementos->lista);
  g_slist_free(elementos->listaRank);

  gtk_main_quit ();//Salir
}

//FUNCION PARA LA OPCION DE TERMINAR, PREGUNTA SI DESEAS GUARDAR
void terminar (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *guarda, *noGuardar, *label;

  //Parar timer
	if(elementos->juegoIniciado == 1)
	{
  	gtk_timeout_remove(elementos->timer);
	}

  elementos->terminar = gtk_dialog_new();
  label = gtk_label_new ("¿Deseas guardar la partida actual?");
  guarda = gtk_button_new_with_label("Guardar");//button
  noGuardar = gtk_button_new_with_label("No\nguardar");//button

  //2b. Fijar atributos
  gtk_window_set_title (GTK_WINDOW(elementos->terminar),"Terminar");
  gtk_widget_set_size_request (GTK_WIDGET (elementos->terminar), 265, 100);
  gtk_window_set_modal(GTK_WINDOW(elementos->terminar), TRUE);

  //3.- Registrar las llamadas a funciones
  g_signal_connect(G_OBJECT(guarda), "clicked", G_CALLBACK(guardar), elementos);
  g_signal_connect(G_OBJECT(noGuardar), "clicked", G_CALLBACK(salir), elementos);
  g_signal_connect_swapped (G_OBJECT(guarda), "clicked", G_CALLBACK(gtk_widget_hide) , elementos->terminar);
  g_signal_connect_swapped (G_OBJECT(noGuardar), "clicked", G_CALLBACK(gtk_widget_hide) , elementos->terminar);

  //4.-Definir la jerarquía
  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(elementos->terminar)->vbox), label);
  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(elementos->terminar)->action_area), guarda);
  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(elementos->terminar)->action_area), noGuardar);

  //5.-Mostrar widgets
  gtk_widget_show_all(elementos->terminar);
}
