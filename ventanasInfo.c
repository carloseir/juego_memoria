//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//FUNCION DE AYUDA
void funcionAyuda(GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *ventanaAyuda;

  //Parar timer
  if(elementos->juegoIniciado == 1)
  {
    gtk_timeout_remove(elementos->timer);
  }

  ventanaAyuda = gtk_message_dialog_new(GTK_WINDOW(elementos->ventana),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
  "1.Presiona jugar o play para iniciar el juego.\n2.Para voltear las cartas presiona sobre ellas.\n3.Debes encontrar el par de la carta que volteaste.\n4.Si deseas deshacer un movimiento, presiona deshacer.\n5.Para rehacer movimiento, presiona rehacer.\n6.Para guardar partida preiona guardar.\n7.Si deseas terminar el juego presiona terminar o salir");
  gtk_window_set_title (GTK_WINDOW(ventanaAyuda), "Ayuda");
  gtk_dialog_run (GTK_DIALOG(ventanaAyuda));
  gtk_widget_destroy (ventanaAyuda);
  //Reanudar timer
  if(elementos->juegoIniciado == 1)
  {
    elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
  }
}

//FUNCION DE ACERCA DE...
void funcionAcercade(GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *)user_data;

  //ESTRUCTURA DE VENTANA
  GtkWidget *ventanaAcerca, *content_area;

  GtkWidget *infoA, *infoB, *infoC, *vbox, *hboxA, *hboxB, *hboxC, *ok;

  GtkWidget *alejandro, *barbara, *carlos;  //FOTOS

  //Parar timer
  if(elementos->juegoIniciado == 1)
  {
    gtk_timeout_remove(elementos->timer);
  }

  //2a. Crear widget
  ventanaAcerca = gtk_dialog_new_with_buttons("Acerca de...", GTK_WINDOW(elementos->ventana), GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (ventanaAcerca));
  vbox = gtk_vbox_new (FALSE, 5);
  hboxA = gtk_hbox_new (FALSE, 5);
  hboxB = gtk_hbox_new (FALSE, 5);
  hboxC = gtk_hbox_new (FALSE, 5);
  ok = gtk_button_new_with_label ("Ok");

  //INFORMACION DE PROGRAMADORES

  infoA = gtk_label_new ("Alejandro Solorzano Santos\nEstudiante de Universidad Iberoamericana CDMX\nIngeniería en Tecnologí­as de Cómputo y Telecomunicaciones\n2do semestre");
  infoC = gtk_label_new ("Carlos Emilio Ibarra Rodriguez\nEstudiante de Universidad Iberoamericana CDMX\nIngeniería en Tecnologías de Cómputo y Telecomunicaciones\n2do semestre");
  infoB = gtk_label_new ("Bárbara Mondragón Herrada\nEstudiante de Universidad Iberoamericana CDMX\nIngeniería Biomédica\n2do semestre");

  //FOTOS DE PROGRAMADORES

  alejandro = gtk_image_new_from_file("alejandro.jpeg");
  barbara = gtk_image_new_from_file("barbara.jpeg");
  carlos = gtk_image_new_from_file("carlos.jpeg");

  //2b. Fijar atributos
  gtk_widget_set_size_request (ventanaAcerca, 600, 300);
  gtk_window_set_modal(GTK_WINDOW(ventanaAcerca), TRUE);

  //3.- Registrar las llamadas a funciones
  g_signal_connect(G_OBJECT(ok), "clicked", G_CALLBACK(hideAcerca), ventanaAcerca);

  //4.-Definir la jerarqui­a
  gtk_container_add(GTK_CONTAINER (content_area), vbox);
  gtk_box_pack_start_defaults (GTK_BOX(vbox), hboxA);
  gtk_box_pack_start_defaults (GTK_BOX(vbox), hboxB);
  gtk_box_pack_start_defaults (GTK_BOX(vbox), hboxC);
  gtk_box_pack_start_defaults (GTK_BOX(vbox), ok);
  gtk_box_pack_start_defaults (GTK_BOX(hboxA), alejandro);
  gtk_box_pack_start_defaults (GTK_BOX(hboxA), infoA);
  gtk_box_pack_start_defaults (GTK_BOX(hboxB), barbara);
  gtk_box_pack_start_defaults (GTK_BOX(hboxB), infoB);
  gtk_box_pack_start_defaults (GTK_BOX(hboxC), carlos);
  gtk_box_pack_start_defaults (GTK_BOX(hboxC), infoC);

  //5.-Mostrar widgets
  gtk_widget_show_all (ventanaAcerca);
}

//FUNCION PARA DESTRUIR LA VENTANA DE ACERCA DE
void hideAcerca (GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *)user_data;
  GtkWidget *ventanaAcerca = (GtkWidget *) user_data;
  gtk_widget_destroy (ventanaAcerca);
  //Reanudar timer
  if(elementos->juegoIniciado == 1)
  {
    elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
  }
}

//VENTANA DEL GANADOR
void ganador(GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
	GtkWidget *ventanaGanador, *label, *labelGanador, *ok;
  ventanaGanador = gtk_dialog_new();
  label = gtk_label_new ("El ganador es:");
  labelGanador = gtk_label_new ("");
  gtk_label_set_text(GTK_LABEL (labelGanador), elementos->ganador);
  ok = gtk_button_new_with_label ("Aceptar");

  //Parar timer
	if(elementos->juegoIniciado == 1)
	{
  	gtk_timeout_remove(elementos->timer);
	}

  //2b. Fijar atributos
  gtk_window_set_title (GTK_WINDOW (ventanaGanador),"Ganador");
  gtk_widget_set_size_request (GTK_WIDGET (ventanaGanador), 300, 200);
  gtk_window_set_modal (GTK_WINDOW(ventanaGanador), TRUE);

  //3.- Registrar las llamadas a funciones
  g_signal_connect_swapped (G_OBJECT(ok), "clicked", G_CALLBACK(gtk_widget_hide) , ventanaGanador);

  //4.-Definir la jerarquía
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(ventanaGanador)->vbox), label);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(ventanaGanador)->vbox), labelGanador);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(ventanaGanador)->action_area), ok);

  //5.-Mostrar widgets
  gtk_widget_show_all(ventanaGanador);
}
