//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//FUNCION QUE INICIA UN JUEGO NUEVO

void funcionJugar (GtkWidget *widget, gpointer user_data)
{
  //DESEMPAQUETAR LA ESTRUCTURA Y CREAR LA VENTANA
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *instrucciones;//label
  GtkWidget *botonUnJugador, *botonDosJugadores;

  //2. CREAR LOS WIDGETS DE LA VENTANA

  elementos->ventanaJugar = gtk_dialog_new();

  instrucciones = gtk_label_new("\nEn el modo un jugador se jugará vs. la computadora\nEn el modo dos jugadores se alternarán\nlos jugadores");
  botonUnJugador = gtk_button_new_with_label("Un jugador");
  botonDosJugadores = gtk_button_new_with_label("Dos jugadores");

  //2b. FIJAR ATRIBUTOS
  gtk_window_set_title (GTK_WINDOW(elementos->ventanaJugar),"Modo de juego");
  gtk_widget_set_size_request (GTK_WIDGET (elementos->ventanaJugar), 300, 150);
  gtk_window_set_modal(GTK_WINDOW(elementos->ventanaJugar), TRUE);

  //3.- Registrar las llamadas a funciones
  g_signal_connect(G_OBJECT(botonUnJugador), "clicked", G_CALLBACK(unJugador), elementos);
  g_signal_connect(G_OBJECT(botonDosJugadores), "clicked", G_CALLBACK(dosJugadores), elementos);

  //4.-Definir la jerarquia
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaJugar)->vbox), instrucciones);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaJugar)->action_area), botonUnJugador);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaJugar)->action_area), botonDosJugadores);

  //5.-Mostrar widgets
  gtk_widget_show_all(elementos->ventanaJugar);

}
