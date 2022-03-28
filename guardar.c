//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

void guardar (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
	GtkWidget *guardar;
	GtkFileFilter *filtro;

  //Parar timer
	if(elementos->juegoIniciado == 1)
	{
  	gtk_timeout_remove(elementos->timer);
	}

	guardar = gtk_file_chooser_dialog_new("Guardar", GTK_WINDOW(elementos->ventana), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_SAVE, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	filtro = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filtro, "*.mem");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(guardar), filtro);

  gtk_window_set_modal(GTK_WINDOW(guardar), TRUE);

  gtk_widget_show_all(guardar);
  gint resp = gtk_dialog_run(GTK_DIALOG(guardar));
  if (resp == GTK_RESPONSE_OK)
  {
    g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(guardar)));
    elementos->nombreArchivoGuardar = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(guardar));//Nombre del archivo de juego

    //guardar en ARCHIVO
    guardarArchivo(widget,user_data);
  }

  gtk_widget_destroy(guardar);
  //Reanudar timer
  if(elementos->juegoIniciado == 1)
  {
    elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
  }
}

void guardarArchivo(GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  FILE *fp;

  //Primer paquete
  elementos->tableroGuardar = malloc(sizeof(TABLERO));

  (elementos->tableroGuardar)->tiempoJuego = elementos->segundosTotales;//Tiempo en segundos
  for (int i = 0; i < 64; i++) {
    (elementos->tableroGuardar)->posicionTablero[i] = elementos->mapaimg[i]; //TABLERO
  }
  (elementos->tableroGuardar)->nombreJ1 = g_strdup(elementos->strJugador1);//nombre de los jugadores
  (elementos->tableroGuardar)->nombreJ2 = g_strdup(elementos->strJugador2);

  fp = fopen(elementos->nombreArchivoGuardar, "wb");//Abrir archivo en modo escritura

  fwrite (elementos->tableroGuardar, sizeof(TABLERO), 1, fp);//Escribir en el archivo
  fclose (fp);//Cerrar archivo
  fp = fopen (elementos->nombreArchivoGuardar, "ab");
  //PAQUETES CON LISTA DE MOVIMIENTOS DE LOS JUGADORES
  for (int i = 0; i < g_list_length (elementos->lista); i++) {
    elementos->info = g_list_nth_data(elementos->lista,i);
    elementos->movimientos = (MOVIMIENTOS *) elementos->info;
    fwrite (elementos->movimientos,sizeof (MOVIMIENTOS),1,fp);
  }
  fclose (fp);
}
