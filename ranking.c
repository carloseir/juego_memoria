//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//CRREA ARCHIVO DONDE SE GUARDARAN LOS JUGADORES Y EL TIEMPO TOTAL DE PARTIDA
void listaRanking (GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  gint i = 0;
  FILE *fp;
  fp = fopen("ranking.bin", "ab");//Abrir archivo
  elementos->datosGandor = malloc(sizeof(RANKING));
  (elementos->datosGandor)->nombreGanador = g_strdup (elementos->ganador);
  (elementos->datosGandor)->tiempoTotal = elementos -> segundosTotales;
  elementos->listaRank = g_slist_append(elementos->listaRank, elementos->datosGandor);
  for (i=0; i<g_slist_length(elementos->listaRank); i++)
  {
    elementos->infoGanador = g_slist_nth_data(elementos->listaRank, i);
    elementos->datosGandor = (RANKING *)elementos->infoGanador;
    fwrite ((elementos->datosGandor)->nombreGanador, sizeof(RANKING), 1, fp);
    fwrite (&(elementos->datosGandor)->tiempoTotal, sizeof(RANKING), 1, fp);
  }
  fclose (fp);
}

void ventanaRanking(GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;

  GtkWidget *ok;
  GtkWidget *table;
  GtkWidget *num, *nombre, *tiempo;
  GtkWidget *uno, *dos, *tres, *cuatro, *cinco;
  elementos->ventanaRanking = gtk_dialog_new();
  table = gtk_table_new(6, 3, FALSE);
  num = gtk_label_new ("#");
  nombre = gtk_label_new ("Nombre");
  tiempo = gtk_label_new ("Tiempo");
  uno = gtk_label_new ("1");
  dos = gtk_label_new ("2");
  tres = gtk_label_new ("3");
  cuatro = gtk_label_new ("4");
  cinco = gtk_label_new ("5");
  ok = gtk_button_new_with_label ("Ok");

  //Parar timer
  if(elementos->juegoIniciado == 1)
  {
    gtk_timeout_remove(elementos->timer);
  }

  //2b. Fijar atributos
  gtk_window_set_title (GTK_WINDOW(elementos->ventanaRanking), "Ranking");
  gtk_widget_set_size_request (GTK_WIDGET (elementos->ventanaRanking), 500, 300);
  gtk_window_set_modal (GTK_WINDOW(elementos->ventanaRanking), TRUE);
  gtk_table_set_row_spacings (GTK_TABLE (elementos->tablero), 2);
  gtk_table_set_col_spacings (GTK_TABLE (elementos->tablero), 2);

  //3.- Registrar las llamadas a funciones
  g_signal_connect(G_OBJECT(ok), "clicked", G_CALLBACK(hideRanking), elementos);

  //4.-Definir la jerarquía
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaRanking)->vbox), table);

  gtk_table_attach_defaults(GTK_TABLE(table), num, 0, 1, 0, 1);
  gtk_table_attach_defaults(GTK_TABLE(table), nombre, 1, 2, 0, 1);
  gtk_table_attach_defaults(GTK_TABLE(table), tiempo, 2, 3, 0, 1);

  gtk_table_attach_defaults(GTK_TABLE(table), uno, 0, 1, 1, 2);
  gtk_table_attach_defaults(GTK_TABLE(table), dos, 0, 1, 2, 3);
  gtk_table_attach_defaults(GTK_TABLE(table), tres, 0, 1, 3, 4);
  gtk_table_attach_defaults(GTK_TABLE(table), cuatro, 0, 1, 4, 5);
  gtk_table_attach_defaults(GTK_TABLE(table), cinco, 0, 1, 5, 6);

  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaRanking)->action_area), ok);

  //5.-Mostrar widgets
  gtk_widget_show_all(elementos->ventanaRanking);
}

void hideRanking (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
	gtk_widget_hide (elementos->ventanaRanking);
	recuperarRanking(widget, user_data);
  //Reanudar timer
  if(elementos->juegoIniciado == 1)
  {
    elementos->timer =gtk_timeout_add(1000, cuenta, elementos);
  }
}

void recuperarRanking(GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
	FILE *fp;
	RANKING info, *data;
	gint i = 0;
  fp = fopen("ranking.bin", "rb");
  data = malloc(sizeof(RANKING));
  if(fp == NULL)
  {
  	errorRanking (widget, user_data);
  }

  else{

 		elementos->datosGandor = malloc(sizeof(RANKING));

  	while(fread(&info, sizeof(RANKING), 1, fp)==1)
		{
			(elementos->datosGandor)->nombreGanador = info.nombreGanador;
			(elementos->datosGandor)->tiempoTotal = info.tiempoTotal;
		}

		elementos->listaRank = g_slist_append(elementos->listaRank, elementos->datosGandor);


  	for (i=0; i<g_slist_length(elementos->listaRank); i++)
  	{
    	elementos->infoGanador = g_slist_nth_data(elementos->listaRank, i);
    	elementos->datosGandor = (RANKING *)elementos->infoGanador;
  	}
  	fclose (fp);
  }
}
