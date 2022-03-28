//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

extern void ganador (GtkWidget *widget, gpointer user_data);

//VENTANA DE JUEGO DE UN JUGADOR
void unJugador (GtkWidget *widget, gpointer   user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  GtkWidget *label, *iniciar;

  gtk_widget_destroy (GTK_WIDGET (elementos->ventanaJugar));
  elementos->ventanaUno = gtk_dialog_new();
  label = gtk_label_new("Nombre del jugador:");
  elementos->nombre1 = gtk_entry_new();//Entry
  iniciar = gtk_button_new_with_label("Iniciar juego");//Botón

  //2b. Fijar atributos
  gtk_window_set_title (GTK_WINDOW(elementos->ventanaUno),"Jugador");
  gtk_widget_set_size_request (GTK_WIDGET (elementos->ventanaUno), 200, 100);
  gtk_window_set_modal(GTK_WINDOW(elementos->ventanaUno), TRUE);

  //3.- Registrar las llamadas a funciones
  g_signal_connect(G_OBJECT(iniciar), "clicked", G_CALLBACK(hideUnjugador), elementos);
  //4.-Definir la jerarquía
  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(elementos->ventanaUno)->vbox), label);
  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(elementos->ventanaUno)->vbox), elementos->nombre1);
  gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(elementos->ventanaUno)->action_area), iniciar);

  //5.-Mostrar widgets
  gtk_widget_show_all(elementos->ventanaUno);
}

//FUNCION PARA DESTRUIR LA VENTANA DE UN JUGADOR
void hideUnjugador (GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  elementos->modoJuego = 1;
  elementos->cargar=0;
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

  elementos->strJugador1=gtk_entry_get_text (GTK_ENTRY (elementos->nombre1));

  //TABLERO
  rand10 (elementos);
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

  for (int i = 0; i < 64; i++) {
    gtk_widget_show (GTK_WIDGET (elementos->botones [i]));
    gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
  }
  gtk_widget_show (elementos->eJugador1);
  gtk_widget_show (elementos->eJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->j1e),elementos->strJugador1);
  gtk_label_set_text (GTK_LABEL (elementos->j2e),"Computadora");

  //Iniciar timer
  elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
  elementos->juegoIniciado = 1;

  gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del primer jugador.");
  gtk_widget_hide (GTK_WIDGET (elementos->ventanaUno));
}

//FUNCION DE JUEGO DE DOS JUGADORES
void dosJugadores (GtkWidget *widget, gpointer user_data)
{
  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  gtk_widget_destroy (GTK_WIDGET (elementos->ventanaJugar));
  GtkWidget *label1, *label2, *iniciar1, *iniciar2;

  elementos->ventanaDos = gtk_dialog_new();
  label1 = gtk_label_new ("Nombre primer jugador:");
  label2 = gtk_label_new ("Nombre segundo jugador:");
  elementos->nombrej1 = gtk_entry_new ();
  elementos->nombrej2 = gtk_entry_new ();
  iniciar1=gtk_button_new_with_label ("Tira jugador 1\nprimero");
  iniciar2=gtk_button_new_with_label ("Tira jugador 2\nprimero");

  //2b. Fijar atributos
  gtk_window_set_title (GTK_WINDOW (elementos->ventanaDos),"Jugadores");
  gtk_widget_set_size_request (GTK_WIDGET (elementos->ventanaDos), 300, 200);
  gtk_window_set_modal(GTK_WINDOW(elementos->ventanaDos), TRUE);

  //3.- Registrar las llamadas a funciones
  g_signal_connect(G_OBJECT(iniciar1), "clicked", G_CALLBACK(hideDosjugadores_judador1), elementos);
  g_signal_connect(G_OBJECT(iniciar2), "clicked", G_CALLBACK(hideDosjugadores_judador2), elementos);

  //4.-Definir la jerarquía
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaDos)->vbox), label1);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaDos)->vbox), elementos->nombrej1);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaDos)->vbox), label2);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaDos)->vbox), elementos->nombrej2);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaDos)->action_area), iniciar1);
  gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(elementos->ventanaDos)->action_area), iniciar2);

  //5.-Mostrar widgets
  gtk_widget_show_all(elementos->ventanaDos);
}

//FUNCION PARA DESTRUIR LA VENTANA DE DOS JUGADORES SI JUGADOR 1 TIRA PRIMERO
void hideDosjugadores_judador1 (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  elementos->modoJuego = 2;
  elementos->cargar=0;
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

	elementos -> turno = 1;
  gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del primer jugador.");

  elementos->strJugador1=gtk_entry_get_text (GTK_ENTRY (elementos->nombrej1));
  elementos->strJugador2=gtk_entry_get_text (GTK_ENTRY (elementos->nombrej2));
  //TABLERO
  rand10 (elementos);
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
  for (int i = 0; i < 64; i++) {
    gtk_widget_show (GTK_WIDGET (elementos->botones [i]));
    gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
  }
  gtk_widget_show (GTK_WIDGET (elementos->eJugador1));
  gtk_widget_show (GTK_WIDGET (elementos->eJugador2));
  gtk_widget_show (elementos->cajaPuntos);
  gtk_label_set_text (GTK_LABEL (elementos->j1e),elementos->strJugador1);
  gtk_widget_set_name (GTK_WIDGET (elementos->j1e),elementos->strJugador1);
  gtk_widget_set_name (GTK_WIDGET (elementos->j2e),elementos->strJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->j2e),elementos->strJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->etiquetaJ1),elementos->strJugador1);
  gtk_label_set_text (GTK_LABEL (elementos->etiquetaJ2),elementos->strJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),"0");
  gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),"0");

  //Iniciar timer
  elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
  elementos->juegoIniciado = 1;

  gtk_widget_hide (GTK_WIDGET (elementos->ventanaDos));
}

//FUNCION PARA DESTRUIR LA VENTANA DE DOS JUGADORES SI JUGADOR 2 TIRA PRIMERO
void hideDosjugadores_judador2 (GtkWidget *widget, gpointer user_data)
{
	ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  elementos->modoJuego = 2;
  elementos->cargar=0;
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

	elementos->turno = 2;
  gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado),elementos->idEstado, "Turno del segundo jugador.");

  elementos->strJugador2=gtk_entry_get_text (GTK_ENTRY (elementos->nombrej1));
  elementos->strJugador1=gtk_entry_get_text (GTK_ENTRY (elementos->nombrej2));

  //TABLERO
  rand10 (elementos);
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
  for (int i = 0; i < 64; i++) {
    gtk_widget_show (GTK_WIDGET (elementos->botones [i]));
    gtk_widget_hide (GTK_WIDGET (elementos->imagenes [i]));
  }
  gtk_widget_show (GTK_WIDGET (elementos->eJugador1));
  gtk_widget_show (GTK_WIDGET (elementos->eJugador2));
  gtk_widget_show (elementos->cajaPuntos);
  gtk_label_set_text (GTK_LABEL (elementos->j1e),elementos->strJugador1);
  gtk_widget_set_name (GTK_WIDGET (elementos->j1e),elementos->strJugador1);
  gtk_widget_set_name (GTK_WIDGET (elementos->j2e),elementos->strJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->j2e),elementos->strJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->etiquetaJ1),elementos->strJugador1);
  gtk_label_set_text (GTK_LABEL (elementos->etiquetaJ2),elementos->strJugador2);
  gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),"0");
  gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),"0");

  //Iniciar timer
  elementos->timer = gtk_timeout_add (1000, cuenta, elementos);
  elementos->juegoIniciado = 1;

  gtk_widget_hide (GTK_WIDGET (elementos->ventanaDos));
}

//FUNCION DE TIROS
void tiros (GtkWidget *widget, gpointer user_data)
{

  ELEMENTOS *elementos = (ELEMENTOS *) user_data;
  //JUEGO JUGADOR VS COMPUTADORA
  if (elementos->modoJuego == 1) {
    //TURNO DEL PRIMER JUGADOR
    if (elementos->turno == 1) {
      //SI ES EL PRIMER TIRO
      if (elementos->numTiros == 1) {
        //ESCONDE LAS IMAGENES CUANDO DAS CLIC EN EL TURNO SIGUIENTE
        if (elementos->primerTiro == 2) {
          gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta1]));
          gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta2]));
        }
        //OBTENER EL NOMBRE DE LA PRIMER CARTA
        elementos->carta1 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta1 = atoi (elementos->carta1);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta1] == 1) {
          //VENTANA DE ERROR AL OPRIMIR EL BOTON
          error_boton (widget, user_data);
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 1;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
        }
        else {
          //MOSTRAR LA CARTA
          gtk_widget_show_all (widget);
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta1] = 1;
          //ASIGNAR EL SIGUIENTE TIRO COMO ULTIMO DEL TURNO
          elementos->numTiros =  2;
          //GUARDAR MOVIMIENTO EN LA LISTA
          elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
          (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
          (elementos->movimientos)->numeroTiros = elementos->numTiros;
          (elementos->movimientos)->carta = elementos->bCarta2;
          for (int i = 0; i < 64; i++) {
            (elementos->movimientos)->recordarPC [i]= elementos->recordar [i];
          }
          for (int i = 0; i < 64; i++) {
            (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
          }
          (elementos->movimientos)->pares1J = elementos->paresJ1;
          (elementos->movimientos)->pares2J = elementos->paresJ2;
          (elementos->movimientos)->modo = elementos->modoJuego;
          elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
          elementos->tiro = g_list_length(elementos->lista);
        }
      }
      else if (elementos->numTiros == 2){
        //OBTENER EL NOMBRE DE LA SEGUNDA CARTA
        elementos->carta2 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta2 = atoi (elementos->carta2);
        //MOSTRAR LA CARTA
        gtk_widget_show_all (widget);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta2] == 1) {
          //VENTANA DE ERROR AL OPRIMIR EL BOTON
          error_boton (widget, user_data);
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 2;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
        }
        else {
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta2] = 1;
          //SI LAS CARTAS SON IGUALES
          if ((((elementos->bCarta1)+32) == elementos->bCarta2) || (((elementos->bCarta2)+32) == elementos->bCarta1)) {
            //SUMAR UN PAR AL JUGADOR 1
            elementos->paresJ1 = (elementos->paresJ1)+1;
            elementos->totalPuntos = elementos->paresJ1 + elementos->paresJ2;
           sprintf(elementos->puntosJ1, "%d",elementos->paresJ1);
           gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),elementos->puntosJ1);
           //SI YA SE VOLTEARON TODAS LAS CARTAS
           if(elementos->totalPuntos == 32)
           {
             if (elementos->paresJ1 > elementos->paresJ2)
             {
               elementos->ganador = g_strdup(elementos->strJugador1);
               ganador (widget, user_data);
             }
             else if (elementos->paresJ2 > elementos->paresJ1)
             {
               elementos->ganador = g_strdup("Computadora");
               ganador (widget, user_data);
             }
             else
             {
               elementos->ganador = g_strdup("Empate");
               ganador (widget, user_data);
             }
           }
          else {
            //ASIGNAR EL PRIMER TIRO DEL SIGUIENTE TURNO
            elementos->numTiros = 1;
            //ASIGNAR EL TURNO PARA EL JUGADOR 1
            elementos->turno = 1;
            //ASIGNAR QE EL TURNO SERA EL SEGUNDO
            elementos->primerTiro = 1;
            //RECORDAR LOS PARES
            elementos->recordar [elementos->bCarta1] = 2;
            elementos->recordar [elementos->bCarta2] = 2;
            //GUARDAR MOVIMIENTO EN LA LISTA
            elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
            (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
            (elementos->movimientos)->numeroTiros = elementos->numTiros;
            (elementos->movimientos)->carta = elementos->bCarta2;
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->recordarPC [i]= elementos->recordar [i];
            }
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
            }
            (elementos->movimientos)->pares1J = elementos->paresJ1;
            (elementos->movimientos)->pares2J = elementos->paresJ2;
            (elementos->movimientos)->modo = elementos->modoJuego;
            elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
            elementos->tiro = g_list_length(elementos->lista);
            gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del primer jugador.");
          }
          }
          //SI LAS CARTAS NO SON IGUALES
          else if ((((elementos->bCarta1)+32) != elementos->bCarta2) || (((elementos->bCarta2)+32) != elementos->bCarta1)){
            //ASGINAR EL PRIMER TIRO DEL SIGUIENTE TURNO
            elementos->numTiros = 1;
            //ASIGNAR EL TURNO DEL SIGUIENTE JUGADOR
            elementos->turno = 2;
            //ASIGNAR LAS CARTAS COMO INACTIVAS
            elementos->botonesActivos [elementos->bCarta1] = 0;
            elementos->botonesActivos [elementos->bCarta2] = 0;
            //ASIGNAR LA SEGUNDA VEZ QUE SE TIRA
            elementos->primerTiro = 2;
            //RECORDAR LOS BOTONES PARA LA COMPUTADORA
            elementos->recordar [elementos->bCarta1] = 1;
            elementos->recordar [elementos->bCarta2] = 1;
            //GUARDAR MOVIMIENTO EN LA LISTA
            elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
            (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
            (elementos->movimientos)->numeroTiros = elementos->numTiros;
            (elementos->movimientos)->carta = elementos->bCarta2;
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->recordarPC [i]= elementos->recordar [i];
            }
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
            }
            (elementos->movimientos)->pares1J = elementos->paresJ1;
            (elementos->movimientos)->pares2J = elementos->paresJ2;
            (elementos->movimientos)->modo = elementos->modoJuego;
            elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
            elementos->tiro = g_list_length(elementos->lista);
            gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del segundo jugador.");
            //LLAMAR A QUE TIRE LA COMPUTADORA
            computadora (widget,user_data);
          }
        }
      }
    }
    //TURNO DE LA COMPUTADORA
    else if (elementos->turno == 2) {
      //SI ES EL PRIMER TIRO
      if (elementos->numTiros == 1) {
        //OBTENER EL NOMBRE DE LA PRIMER CARTA
        elementos->carta1 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta1 = atoi (elementos->carta1);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta1] == 1) {
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 1;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
          //LLAMAR A LA COMPUTADORA
          computadora (widget, user_data);
        }
        else {
          //MOSTRAR LA CARTA
          gtk_widget_show_all (widget);
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta1] = 1;
          //ASIGNAR EL SIGUIENTE TIRO COMO ULTIMO DEL TURNO
          elementos->numTiros =  2;
          //AGREGAR EL MOVIMIENTO A LA LISTA
          elementos->movimientos = malloc(sizeof(MOVIMIENTOS)); // 1.- Crear espacio
          (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
          (elementos->movimientos)->numeroTiros = elementos->numTiros;
          (elementos->movimientos)->carta = elementos->bCarta1;
          (elementos->movimientos)->modo = elementos->modoJuego;
          elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
          elementos->tiro = g_list_length(elementos->lista);
          //LLAMAR A LA COMPUTADORA
          computadora (widget, user_data);
        }
        }
        else if (elementos->numTiros == 2){
          //OBTENER EL NOMBRE DE LA SEGUNDA CARTA
          elementos->carta2 = gtk_widget_get_name (widget);
          //CONVERTIR EL NOMBRE EN ENTERO
          elementos->bCarta2 = atoi (elementos->carta2);
          //MOSTRAR LA CARTA
          gtk_widget_show_all (widget);
          //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
          if (elementos->botonesActivos [elementos->bCarta2] == 1) {
            //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
            elementos->numTiros = 2;
            //ASIGNAR EL TURNO AL MISMO JUGADOR
            elementos->turno = 1;
            //LLAMAR A LA COMPUTADORA
            computadora (widget,user_data);
          }
          else {
            //ESTABLECER LA CARTA COMO ACTIVA
            elementos->botonesActivos [elementos->bCarta2] = 1;
            //SI LAS CARTAS SON IGUALES
            if ((((elementos->bCarta1)+32) == elementos->bCarta2) || (((elementos->bCarta2)+32) == elementos->bCarta1)) {
              //SUMAR UN PAR AL JUGADOR 2
              elementos->paresJ2 = (elementos->paresJ2)+1;
              elementos->totalPuntos = elementos->paresJ2 + elementos->paresJ1;
             sprintf(elementos->puntosJ2, "%d",elementos->paresJ2);
             gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),elementos->puntosJ2);
             //SI YA SE VOLTEARON TODAS LAS CARTAS
             if(elementos->totalPuntos == 32)
             {
               if (elementos->paresJ1 > elementos->paresJ2)
               {
                 elementos->ganador = g_strdup(elementos->strJugador1);
                 ganador (widget, user_data);
               }
               else if (elementos->paresJ2 > elementos->paresJ1)
               {
                 elementos->ganador = g_strdup("Computadora");
                 ganador (widget, user_data);
               }
               else
               {
                 elementos->ganador = g_strdup("Empate");
                 ganador (widget, user_data);
               }
             }
            else {
              //ASIGNAR EL PRIMER TIRO DEL SIGUIENTE TURNO
              elementos->numTiros = 1;
              //ASIGNAR EL TURNO PARA EL JUGADOR 1
              elementos->turno = 2;
              //ASIGNAR QE EL TURNO SERA EL SEGUNDO
              elementos->primerTiro = 1;
              //RECORDAR LOS PARES
              elementos->recordar [elementos->bCarta1] = 2;
              elementos->recordar [elementos->bCarta2] = 2;
              //GUARDAR MOVIMIENTO EN LA LISTA
              elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
              (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
              (elementos->movimientos)->numeroTiros = elementos->numTiros;
              (elementos->movimientos)->carta = elementos->bCarta2;
              (elementos->movimientos)->recordarPC [elementos->bCarta1] = 2;
              (elementos->movimientos)->recordarPC [elementos->bCarta2] = 2;
              (elementos->movimientos)->modo = elementos->modoJuego;
              elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
              elementos->tiro = g_list_length(elementos->lista);
              //LLAMAR A LA COMPUTADORA
              computadora (widget,user_data);
              gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno de la computadora.");
            }
            }
            //SI LAS CARTAS NO SON IGUALES
            else if ((((elementos->bCarta1)+32) != elementos->bCarta2) || (((elementos->bCarta2)+32) != elementos->bCarta1)){
              //ASGINAR EL PRIMER TIRO DEL SIGUIENTE TURNO
              elementos->numTiros = 1;
              //ASIGNAR EL TURNO DEL SIGUIENTE JUGADOR
              elementos->turno = 1;
              //ASIGNAR LAS CARTAS COMO INACTIVAS
              elementos->botonesActivos [elementos->bCarta1] = 0;
              elementos->botonesActivos [elementos->bCarta2] = 0;
              //ASIGNAR LA SEGUNDA VEZ QUE SE TIRA
              elementos->primerTiro = 2;
              //RECORDAR LOS BOTONES PARA LA COMPUTADORA
              elementos->recordar [elementos->bCarta1] = 1;
              elementos->recordar [elementos->bCarta2] = 1;
              //GUARDAR EL MOVIMIENTO EN LA LISTA
              elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
              elementos->movimientos->turnoM = elementos->turno;  //2.- Llenar la informacion
              (elementos->movimientos)->numeroTiros = elementos->numTiros;
              (elementos->movimientos)->carta = elementos->bCarta2;
              (elementos->movimientos)->recordarPC [elementos->bCarta1] = 1;
              (elementos->movimientos)->recordarPC [elementos->bCarta2] = 1;
              (elementos->movimientos)->botonesActiv [elementos->bCarta1] = 0;
              (elementos->movimientos)->botonesActiv [elementos->bCarta2] = 0;
              (elementos->movimientos)->modo = elementos->modoJuego;
              elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
              elementos->tiro = g_list_length(elementos->lista);
              gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del primer jugador.");

            }
          }
        }
      }
    }
  //JUEGO JUGADOR VS JUGADOR
  else if (elementos->modoJuego == 2) {
    //TIRO DEL PRIMER JUGADOR
    if (elementos->turno == 1) {
      //SI ES EL PRIMER TIRO
      if (elementos->numTiros == 1) {
        //ESCONDE LAS IMAGENES CUANDO DAS CLIC EN EL TURNO SIGUIENTE
        if (elementos->primerTiro == 2) {
          gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta1]));
          gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta2]));
        }
        //OBTENER EL NOMBRE DE LA PRIMER CARTA
        elementos->carta1 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta1 = atoi (elementos->carta1);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta1] == 1) {
          //VENTANA DE ERROR AL OPRIMIR EL BOTON
          error_boton (widget, user_data);
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 1;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
        }
        else {
          //MOSTRAR LA CARTA
          gtk_widget_show_all (widget);
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta1] = 1;
          //ASIGNAR EL SIGUIENTE TIRO COMO ULTIMO DEL TURNO
          elementos->numTiros =  2;
          //GUARDAR MOVIMIENTO EN LA LISTA
          elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
          (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
          (elementos->movimientos)->numeroTiros = elementos->numTiros;
          (elementos->movimientos)->carta = elementos->bCarta1;
          for (int i = 0; i < 64; i++) {
            (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
          }
          (elementos->movimientos)->pares1J = elementos->paresJ1;
          (elementos->movimientos)->pares2J = elementos->paresJ2;
          (elementos->movimientos)->modo = elementos->modoJuego;
          elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
          elementos->tiro = g_list_length(elementos->lista);
        }
      }
      else if (elementos->numTiros == 2){
        //OBTENER EL NOMBRE DE LA SEGUNDA CARTA
        elementos->carta2 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta2 = atoi (elementos->carta2);
        //MOSTRAR LA CARTA
        gtk_widget_show_all (widget);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta2] == 1) {
          //VENTANA DE ERROR AL OPRIMIR EL BOTON
          error_boton (widget, user_data);
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 2;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
        }
        else {
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta2] = 1;
          //SI LAS CARTAS SON IGUALES
          if ((((elementos->bCarta1)+32) == elementos->bCarta2) || (((elementos->bCarta2)+32) == elementos->bCarta1)) {
            //SUMAR UN PAR AL JUGADOR 1
            elementos->paresJ1 = (elementos->paresJ1)+1;
            elementos->totalPuntos = elementos->paresJ1 + elementos->paresJ2;
           sprintf(elementos->puntosJ1, "%d",elementos->paresJ1);
           gtk_label_set_text (GTK_LABEL (elementos->contadorJ1),elementos->puntosJ1);
           //SI YA SE VOLTEARON TODAS LAS CARTAS
           if(elementos->totalPuntos == 32)
           {
             if (elementos->paresJ1 > elementos->paresJ2)
             {
               elementos->ganador = g_strdup(elementos->strJugador1);
               ganador (widget, user_data);//Muestra el ganador en pantalla
               listaRanking(widget, user_data);//Guarda los datos del ganador en una lista
             }
             else if (elementos->paresJ2 > elementos->paresJ1)
             {
               elementos->ganador = g_strdup(elementos->strJugador2);
               ganador (widget, user_data);//Muestra el ganador en pantalla
               listaRanking(widget, user_data);//Guarda los datos del ganador en una lista
             }
             else
             {
               elementos->ganador = g_strdup("Empate"); //Muestra que hubo un empate
               ganador (widget, user_data);
             }
           }
          else {
            //ASIGNAR EL PRIMER TIRO DEL SIGUIENTE TURNO
            elementos->numTiros = 1;
            //ASIGNAR EL TURNO PARA EL JUGADOR 1
            elementos->turno = 1;
            //ASIGNAR QE EL TURNO SERA EL SEGUNDO
            elementos->primerTiro = 1;
            //GUARDAR MOVIMIENTO EN LA LISTA
            elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
            (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
            (elementos->movimientos)->numeroTiros = elementos->numTiros;
            (elementos->movimientos)->carta = elementos->bCarta2;
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
            }
            (elementos->movimientos)->pares1J = elementos->paresJ1;
            (elementos->movimientos)->pares2J = elementos->paresJ2;
            (elementos->movimientos)->modo = elementos->modoJuego;
            elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
            elementos->tiro = g_list_length(elementos->lista);
            gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del primer jugador.");
          }
          }
          //SI LAS CARTAS NO SON IGUALES
          else if ((((elementos->bCarta1)+32) != elementos->bCarta2) || (((elementos->bCarta2)+32) != elementos->bCarta1)){
            //ASGINAR EL PRIMER TIRO DEL SIGUIENTE TURNO
            elementos->numTiros = 1;
            //ASIGNAR EL TURNO DEL SIGUIENTE JUGADOR
            elementos->turno = 2;
            //ASIGNAR LAS CARTAS COMO INACTIVAS
            elementos->botonesActivos [elementos->bCarta1] = 0;
            elementos->botonesActivos [elementos->bCarta2] = 0;
            //ASIGNAR LA SEGUNDA VEZ QUE SE TIRA
            elementos->primerTiro = 2;
            //GUARDAR MOVIMIENTO EN LA LISTA
            elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
            (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
            (elementos->movimientos)->numeroTiros = elementos->numTiros;
            (elementos->movimientos)->carta = elementos->bCarta2;
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
            }
            (elementos->movimientos)->pares1J = elementos->paresJ1;
            (elementos->movimientos)->pares2J = elementos->paresJ2;
            (elementos->movimientos)->modo = elementos->modoJuego;
            elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
            elementos->tiro = g_list_length(elementos->lista);
            gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del segundo jugador.");

          }
        }
      }
    }
    //SI ES EL TURNO DEL SEGUNDO JUGADOR
    else if (elementos->turno == 2) {
      //SI ES EL PRIMER TIRO
      if (elementos->numTiros == 1) {
        //ESCONDE LAS IMAGENES CUANDO DAS CLIC EN EL TURNO SIGUIENTE
        if (elementos->primerTiro == 2) {
          gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta1]));
          gtk_widget_hide (GTK_WIDGET (elementos->imagenes [elementos->bCarta2]));
        }
        //OBTENER EL NOMBRE DE LA PRIMER CARTA
        elementos->carta1 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta1 = atoi (elementos->carta1);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta1] == 1) {
          //VENTANA DE ERROR AL OPRIMIR EL BOTON
          error_boton (widget, user_data);
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 1;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
        }
        else {
          //MOSTRAR LA CARTA
          gtk_widget_show_all (widget);
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta1] = 1;
          //ASIGNAR EL SIGUIENTE TIRO COMO ULTIMO DEL TURNO
          elementos->numTiros =  2;
          //GUARDAR MOVIMIENTO EN LA LISTA
          elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
          (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
          (elementos->movimientos)->numeroTiros = elementos->numTiros;
          (elementos->movimientos)->carta = elementos->bCarta1;
          for (int i = 0; i < 64; i++) {
            (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
          }
          (elementos->movimientos)->pares1J = elementos->paresJ1;
          (elementos->movimientos)->pares2J = elementos->paresJ2;
          (elementos->movimientos)->modo = elementos->modoJuego;
          elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
        }
        elementos->tiro = g_list_length(elementos->lista);
      }
      else if (elementos->numTiros == 2){
        //OBTENER EL NOMBRE DE LA SEGUNDA CARTA
        elementos->carta2 = gtk_widget_get_name (widget);
        //CONVERTIR EL NOMBRE EN ENTERO
        elementos->bCarta2 = atoi (elementos->carta2);
        //MOSTRAR LA CARTA
        gtk_widget_show_all (widget);
        //VERIFICAR QUE NO HAYA DADO CLIC EN EL MISMO BOTON
        if (elementos->botonesActivos [elementos->bCarta2] == 1) {
          //VENTANA DE ERROR AL OPRIMIR EL BOTON
          error_boton (widget, user_data);
          //ASGINAR LOS NUMEROS DE TIROS AL PRIMERO
          elementos->numTiros = 2;
          //ASIGNAR EL TURNO AL MISMO JUGADOR
          elementos->turno = 1;
        }
        else {
          //ESTABLECER LA CARTA COMO ACTIVA
          elementos->botonesActivos [elementos->bCarta2] = 1;
          //SI LAS CARTAS SON IGUALES
          if ((((elementos->bCarta1)+32) == elementos->bCarta2) || (((elementos->bCarta2)+32) == elementos->bCarta1)) {
            //SUMAR UN PAR AL JUGADOR 2
            elementos->paresJ2 = (elementos->paresJ2)+1;
            elementos->totalPuntos = elementos->paresJ2 + elementos->paresJ1;
            sprintf(elementos->puntosJ2, "%d",elementos->paresJ2);
            gtk_label_set_text (GTK_LABEL (elementos->contadorJ2),elementos->puntosJ2);
            if(elementos->totalPuntos == 32)
            {
            	if (elementos->paresJ1 > elementos->paresJ2)
            	{
            		elementos->ganador = g_strdup(elementos->strJugador1);
            		ganador (widget, user_data);
            	}
            	else if (elementos->paresJ2 > elementos->paresJ1)
            	{
            		elementos->ganador = g_strdup(elementos->strJugador2);
            		ganador (widget, user_data);
            	}
            	else
            	{
            		elementos->ganador = g_strdup("Empate");
            		ganador (widget, user_data);
            	}
            }
            else {
              //ASIGNAR EL PRIMER TIRO DEL SIGUIENTE TURNO
              elementos->numTiros = 1;
              //ASIGNAR EL TURNO PARA EL JUGADOR 2
              elementos->turno = 2;
              //ASIGNAR QUE EL TIRO SERA EL PRIMERO
              elementos->primerTiro = 1;
              //GUARDAR MOVIMIENTO EN LA LISTA
              elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
              (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
              (elementos->movimientos)->numeroTiros = elementos->numTiros;
              (elementos->movimientos)->carta = elementos->bCarta2;
              for (int i = 0; i < 64; i++) {
                (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
              }
              (elementos->movimientos)->pares1J = elementos->paresJ1;
              (elementos->movimientos)->pares2J = elementos->paresJ2;
              (elementos->movimientos)->modo = elementos->modoJuego;
              elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
              elementos->tiro = g_list_length(elementos->lista);
              gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del segundo jugador.");
            }
          }
          //SI LAS CARTAS NO SON IGUALES
          else if ((((elementos->bCarta1)+32) != elementos->bCarta2) || (((elementos->bCarta2)+32) != elementos->bCarta1)){
            //ASGINAR EL PRIMER TIRO DEL SIGUIENTE TURNO
            elementos->numTiros = 1;
            //ASIGNAR EL TURNO DEL SIGUIENTE JUGADOR
            elementos->turno = 1;
            //ASIGNAR LAS CARTAS COMO INACTIVAS
            elementos->botonesActivos [elementos->bCarta1] = 0;
            elementos->botonesActivos [elementos->bCarta2] = 0;
            //ASIGNAR LA SEGUNDA VEZ QUE SE TIRA
            elementos->primerTiro = 2;
            //GUARDAR MOVIMIENTO EN LA LISTA
            elementos->movimientos = malloc (sizeof (MOVIMIENTOS)); //1.- Crear el espacio
            (elementos->movimientos)->turnoM = elementos->turno;  //2.- Llenar la informacion
            (elementos->movimientos)->numeroTiros = elementos->numTiros;
            (elementos->movimientos)->carta = elementos->bCarta2;
            for (int i = 0; i < 64; i++) {
              (elementos->movimientos)->botonesActiv [i]= elementos->botonesActivos [i];
            }
            (elementos->movimientos)->pares1J = elementos->paresJ1;
            (elementos->movimientos)->pares2J = elementos->paresJ2;
            (elementos->movimientos)->modo = elementos->modoJuego;
            elementos->lista = g_list_append(elementos->lista,elementos->movimientos); // 3.- Encadenar
            elementos->tiro = g_list_length(elementos->lista);
            gtk_statusbar_push (GTK_STATUSBAR (elementos->barraEstado), elementos->idEstado, "Turno del primer jugador.");
          }
        }
      }
    }
  }

}
