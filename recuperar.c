//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

//INICIA UNA PARTIDA DESDE UN JUEGO GUARDADO
void recuperar (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
	GtkWidget *recuperar;
	GtkFileFilter *filtro;
  elementos->cargar = 1;
	recuperar = gtk_file_chooser_dialog_new("Recuperar partida", GTK_WINDOW(elementos->ventana), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_OPEN, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	filtro = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filtro, "*.mem");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(recuperar), filtro);
  gtk_window_set_modal(GTK_WINDOW(recuperar), TRUE);
  gtk_widget_show_all(recuperar);
  gint resp = gtk_dialog_run(GTK_DIALOG(recuperar));
  if (resp == GTK_RESPONSE_OK)
  {
    g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(recuperar)));
    elementos->nombreArchivoRecuperar = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(recuperar));//Nombre del archivo de juego

    //recuperar el ARCHIVO
    recuperarArchivo(widget,user_data);
  }
  gtk_widget_destroy(recuperar);
}

//OPCION DE RECUPERAR ARCHIVO
void recuperarArchivo (GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  TABLERO tableroRecuperar;
  MOVIMIENTOS temporal;
  FILE *fp;

  //Primer paquete
  fp = fopen(elementos->nombreArchivoRecuperar, "rb");//Abrir archivo en modo lectura
  fread (&tableroRecuperar, sizeof(TABLERO), 1, fp);//Leer en el archivo

    elementos->segundosTotales = tableroRecuperar.tiempoJuego;//Tiempo en segundos
    for (int i = 0; i < 64; i++) {
      elementos->mapaimg[i] = tableroRecuperar.posicionTablero[i]; //TABLERO
    }
    elementos->strJugador1 = tableroRecuperar.nombreJ1;//nombre de los jugadores
    elementos->strJugador2 = tableroRecuperar.nombreJ2;

    //Recuperar TIMER
    elementos->timerHoras = elementos->segundosTotales / 3600;
    elementos->timerMinutos = (elementos->segundosTotales % 3600) / 60;
    elementos->timerSegundos = (elementos->segundosTotales % 3600) % 60;

  while (fread (&temporal, sizeof (MOVIMIENTOS),1,fp) == 1)
  {
    //GUARDAR MOVIMIENTO EN LA LISTA
    elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
    (elementos->movimientos)->turnoM = temporal.turnoM;  //2.- Llenar la informacion
    (elementos->movimientos)->numeroTiros = temporal.numeroTiros;
    (elementos->movimientos)->carta = temporal.carta;
    for (int i = 0; i < 64; i++) {
      (elementos->movimientos)->botonesActiv [i]= temporal.botonesActiv [i];
    }
    (elementos->movimientos)->pares1J = temporal.pares1J;
    (elementos->movimientos)->pares2J = temporal.pares2J;
    (elementos->movimientos)->modo = temporal.modo;
    elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
  }


  fclose (fp);//Cerrar archivo

  elementos->tiro = 0;
  //TABLERO
  gtk_table_set_row_spacings (GTK_TABLE (elementos->tablero), 5);
  gtk_table_set_col_spacings (GTK_TABLE (elementos->tablero), 5);
    for (int i = 0; i < 64; i++) {
      if (i == 8 || i== 16 || i== 24 || i==32 || i==40 || i==48 || i==56 || i==64){
        (elementos->filasArriba) = (elementos->filasAbajo);
        (elementos->filasAbajo) = (elementos->filasArriba+1);
        (elementos->columnasIzquierda) = 0;
        (elementos->columnasDerecha) = 1;
      }
      gtk_table_attach_defaults (GTK_TABLE (elementos->tablero),(elementos->botones [elementos->mapaimg [i]]),(elementos->columnasIzquierda),(elementos->columnasDerecha),(elementos->filasArriba),(elementos->filasAbajo));
      (elementos->columnasIzquierda)++;
      (elementos->columnasDerecha)++;
    }
    //TABLERO
    for (int i = 0; i < 64; i++) {
      gtk_container_add (GTK_CONTAINER (elementos->botones [i]), elementos->imagenes [i]);
    }
    elementos->cargar = 1;

    //MOSTRAR WIDGETS
    for (int i = 0; i < 64; i++) {
    gtk_widget_show (GTK_WIDGET (elementos->botones [i]));
    gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
  }


  //SENSIBILIDAD
  gtk_widget_set_sensitive (elementos->subGuardar, TRUE);//Activa botones de guardar una vez que la partida empieza
  gtk_widget_set_sensitive (GTK_WIDGET(elementos->saveItem), TRUE);

	gtk_widget_set_sensitive (elementos->subRecuperar, FALSE);//Desactiva la función recuperar si ya hay una partida en curso

  gtk_widget_set_sensitive (elementos->subDeshacer, TRUE);//Activa deshacer en la partida en curso
	gtk_widget_set_sensitive (GTK_WIDGET(elementos->undoItem), TRUE);

  gtk_widget_set_sensitive (elementos->subRehacer, TRUE);//Activa rehacer en la partida en curso
	gtk_widget_set_sensitive (GTK_WIDGET(elementos->redoItem), TRUE);

  gtk_widget_set_sensitive (elementos->subTerminar, TRUE); //Activa la función terminar para salir del juego en curso

  gtk_widget_set_sensitive (elementos->subJugar, FALSE);//Desactiva la función para jugar porque ya hay una partida en curso
  gtk_widget_set_sensitive (GTK_WIDGET(elementos->playItem), FALSE);

  //Mostrar jugadores, etiquetas
  gtk_widget_show (GTK_WIDGET (elementos->j1e));
	gtk_widget_show (GTK_WIDGET (elementos->j2e));
  gtk_widget_show (GTK_WIDGET (elementos->eJugador1));
	gtk_widget_show (GTK_WIDGET (elementos->eJugador2));
	gtk_widget_show (GTK_WIDGET (elementos->contadorJ1));
	gtk_widget_show (GTK_WIDGET (elementos->contadorJ2));
	gtk_widget_show (GTK_WIDGET (elementos->etiquetaJ1));
	gtk_widget_show (GTK_WIDGET (elementos->etiquetaJ2));
  gtk_widget_show (elementos->cajaPuntos);

	//Reanudar el timer
	elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
	elementos->juegoIniciado = 1;

  gtk_widget_show (GTK_WIDGET (elementos->avanzarM));
}
