//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

#include "tipos.h"//Archivos de inclusión, estructuras y declaración de funciones

extern void funcionAyuda(GtkWidget *widget, gpointer user_data);
extern void funcionAcercade(GtkWidget *widget, gpointer user_data);

//PRINCIPAL
gint main (gint argc, gchar *argv [])
{
  ELEMENTOS *elementos;
  gchar *rutaImagenes [32]= {"Imagenes/1.png","Imagenes/2.png","Imagenes/3.png","Imagenes/4.png","Imagenes/5.png","Imagenes/6.png","Imagenes/7.png","Imagenes/8.png","Imagenes/9.png","Imagenes/10.png","Imagenes/11.png","Imagenes/12.png","Imagenes/13.png","Imagenes/14.png","Imagenes/15.png","Imagenes/16.png","Imagenes/17.png","Imagenes/18.png","Imagenes/19.png","Imagenes/20.png","Imagenes/21.png","Imagenes/22.png","Imagenes/23.png","Imagenes/24.png","Imagenes/25.png","Imagenes/26.png","Imagenes/27.png","Imagenes/28.png","Imagenes/29.png","Imagenes/30.png","Imagenes/31.png","Imagenes/32.png"};
  gchar *nombrech;

  //1. Inicializar el ambiente
  gtk_init (&argc, &argv);

  //Reservar espacio en memoria
  nombrech = malloc(sizeof(elementos->nombre));
  elementos = malloc(sizeof(ELEMENTOS));

  elementos->lista = NULL;
  elementos->listaRank = NULL;

  elementos->juegoIniciado = 0;//El timer está en 00:00:00

  //Inicializar contadores
  elementos->numTiros=1;

  elementos->timerSegundos=0;
  elementos->timerMinutos=0;
  elementos->timerHoras=0;

  elementos->filasArriba = 0;
  elementos->filasAbajo = 1;
  elementos->columnasIzquierda = 0;
  elementos->columnasDerecha = 1;

  elementos->nombre = 0;
  elementos->paresJ2=0;
  elementos->paresJ1=0;
  elementos->turno=1;
  elementos->primerTiro = 1;

  for (int i = 0; i < 64; i++) {
    elementos->botonesActivos [i] = 0;
  }

  elementos->bCarta1 = 0;
  elementos->bCarta2 = 0;
  elementos->igual = 0;
  elementos->tiro = 0;

  //INICIALIZAR ARREGLO BOTONES DE COMPUTADORA
  for(int i = 0; i < 64; i++){
    elementos->recordar[i] = 0;
  }

  //2a. Crear widgets

  //VENTANA DEL JUEGO
  elementos->ventana = gtk_window_new (GTK_WINDOW_TOPLEVEL);  //GtkWidget *gtk_window_new (GtkWindowType WindowType);

  //CAJA PRINCIPAL
  elementos->cajaVertical = gtk_vbox_new (FALSE, 1);   //GtkWidget *gtk_vbox_new (gboolean homogeneo, gint separacion);

  //BARRA DE MENU
  elementos->barraMenu = gtk_menu_bar_new ();

  //SUBMENUS
  elementos->menuJuego = gtk_menu_new ();
  elementos->menuHerramientas = gtk_menu_new ();
  elementos->menuAyuda = gtk_menu_new ();
  elementos->menuAcercade = gtk_menu_new ();
  elementos->menuRanking = gtk_menu_new ();

  //ITEMS
  elementos->itemAyuda = gtk_menu_item_new_with_label ("Ayuda");
  elementos->itemAcercade = gtk_menu_item_new_with_label ("Acerca de ...");

  elementos->itemJuego = gtk_menu_item_new_with_label("Juego");
  elementos->itemHerramientas = gtk_menu_item_new_with_label ("Herramientas");
  elementos->itemRanking = gtk_menu_item_new_with_label("Ranking");
  elementos->subJugar = gtk_menu_item_new_with_mnemonic ("_Jugar");
  elementos->separadorItem1 = gtk_menu_item_new();
  elementos->subGuardar = gtk_menu_item_new_with_mnemonic("_Guardar");
  elementos->separadorItem2 = gtk_menu_item_new();
  elementos->subRecuperar = gtk_menu_item_new_with_mnemonic ("_Recuperar");
  elementos->separadorItem3 = gtk_menu_item_new();
  elementos->subTerminar = gtk_menu_item_new_with_mnemonic ("_Terminar");
  elementos->subDeshacer = gtk_menu_item_new_with_mnemonic ("_Deshacer");
  elementos->separadorItem4 = gtk_menu_item_new();
  elementos->subRehacer = gtk_menu_item_new_with_mnemonic ("Reha_cer");

  //TOOLBAR
  elementos->toolbar = gtk_toolbar_new ();
  elementos->playItem = gtk_tool_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
  elementos->stopItem = gtk_tool_button_new_from_stock (GTK_STOCK_QUIT);
  elementos->undoItem = gtk_tool_button_new_from_stock (GTK_STOCK_UNDO);
  elementos->redoItem = gtk_tool_button_new_from_stock (GTK_STOCK_REDO);
  elementos->saveItem = gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
  elementos->avanzarM = gtk_tool_button_new_from_stock (GTK_STOCK_GOTO_BOTTOM);

  //CAJA DE LA BARRA DE ESTADO
  elementos->cajaHorizontal = gtk_hbox_new (FALSE,5);

  //BARRA DE ESTADO
  elementos->barraEstado = gtk_statusbar_new ();
  elementos->idEstado = gtk_statusbar_get_context_id (GTK_STATUSBAR (elementos->barraEstado), "");//Id de barra de estado, regresa el id

  //TABLERO

  for (int i = 0; i < 64; i++) {
    elementos->botones [i] = gtk_button_new ();
  }
  elementos->tablero = gtk_table_new (8,8,TRUE);
  for (int i = 0; i < 32; i++) {
    elementos->imagenes [i] = gtk_image_new_from_file (rutaImagenes [i]);
    elementos->imagenes [32+i] = gtk_image_new_from_file (rutaImagenes [i]);
  }

  //TIEMPO Y JUGADORES
  elementos->eJugador1 = gtk_label_new ("Jugador 1:");
  elementos->eJugador2 = gtk_label_new ("Jugador 2:");
  elementos->cajaTiempo = gtk_hbox_new (FALSE, 2);
  elementos->labelTimer = gtk_label_new ("00:00:00");
  elementos->j1e = gtk_label_new ("");
  elementos->j2e = gtk_label_new ("");

  //CONTADOR CARTAS CORRECTAS
  elementos->cajaPuntos = gtk_hbox_new (FALSE, 1);
  elementos->etiquetaJ1 = gtk_label_new ("");
  elementos->etiquetaJ2 = gtk_label_new ("");
  elementos->contadorJ1 = gtk_label_new ("");
  elementos->contadorJ2 = gtk_label_new ("");

  //2b. Fijar atributos
  gtk_window_set_title (GTK_WINDOW(elementos->ventana),"Memoria");  //gtk_*_set_* ();
  gtk_window_set_default_size (GTK_WINDOW (elementos->ventana), 1366, 768);
  gtk_widget_set_size_request (GTK_WIDGET (elementos->tablero), 535, 535);

  for (int i = 0; i < 64; i++) {
    gtk_widget_set_size_request (GTK_WIDGET (elementos->botones[i]), 93, 93);
  }

  //Asignar nombre a los botones
  for (int i = 0; i < 64; i++) {
    sprintf (nombrech,"%d",i);
    gtk_widget_set_name (elementos->botones [i],nombrech);
  }

  //BARRA MENU
  gtk_widget_set_size_request (elementos->barraMenu, 5, 5);

  //TOOLBAR
  gtk_toolbar_set_orientation (GTK_TOOLBAR (elementos->toolbar), GTK_ORIENTATION_HORIZONTAL);
  gtk_toolbar_set_style(GTK_TOOLBAR(elementos->toolbar), GTK_TOOLBAR_BOTH);
  gtk_container_set_border_width (GTK_CONTAINER (elementos->toolbar), 2);
  gtk_widget_set_size_request (elementos->toolbar, 40, 40);
  gtk_toolbar_set_icon_size (GTK_TOOLBAR (elementos->toolbar), 1);

  //BARRA DE ESTADO
  gtk_widget_set_size_request (GTK_WIDGET (elementos->barraEstado), 2, 2);

  //TIEMPO Y JUGADORES
  gtk_widget_set_size_request (GTK_WIDGET (elementos->cajaTiempo), 2, 2);

  //CONTADOR DE CARTAS CORRECTAS
  gtk_widget_set_size_request (GTK_WIDGET (elementos->cajaPuntos), 2, 2);

  //ACELERADORES
  elementos->grupoAceleradores = gtk_accel_group_new();
  gtk_window_add_accel_group ((GTK_WINDOW(elementos->ventana)), elementos->grupoAceleradores);

  gtk_widget_add_accelerator((elementos->subJugar), "activate", elementos->grupoAceleradores, 'J', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator((elementos->subGuardar), "activate", elementos->grupoAceleradores, 'G', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator((elementos->subRecuperar), "activate", elementos->grupoAceleradores, 'R', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator((elementos->subTerminar), "activate", elementos->grupoAceleradores, 'T', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator((elementos->subDeshacer), "activate", elementos->grupoAceleradores, 'D', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_add_accelerator((elementos->subRehacer), "activate", elementos->grupoAceleradores, 'A', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  //SENSIBILIDAD DE BOTONES AL INICIAR EL JUEGO
  gtk_widget_set_sensitive (elementos->subGuardar, FALSE);//Desactiva guardar al inicio pues no hay partida en curso
  gtk_widget_set_sensitive (GTK_WIDGET(elementos->saveItem), FALSE);

	gtk_widget_set_sensitive (elementos->subDeshacer, FALSE);//Desactiva deshacer al inicio pues no hay partida en curso
	gtk_widget_set_sensitive (GTK_WIDGET(elementos->undoItem), FALSE);

	gtk_widget_set_sensitive (elementos->subRehacer, FALSE);//Desactiva rehacer al inicio pues no hay partida en curso
	gtk_widget_set_sensitive (GTK_WIDGET(elementos->redoItem), FALSE);

  gtk_widget_set_sensitive (elementos->subTerminar, FALSE); //Desactiva la función terminar pues no hay partida por terminar en curso


  //TOOLTIPS
  gtk_widget_set_tooltip_text (elementos->itemAyuda, "Instrucciones de juego");
  gtk_widget_set_tooltip_text (elementos->subJugar, "Iniciar nueva partida");
  gtk_widget_set_tooltip_text (GTK_WIDGET(elementos->playItem), "Iniciar nueva partida");
  gtk_widget_set_tooltip_text (elementos->itemAcercade, "Información sobre los programadores");
  gtk_widget_set_tooltip_text (elementos->subDeshacer, "Deshacer jugada");
  gtk_widget_set_tooltip_text (GTK_WIDGET(elementos->undoItem), "Deshacer jugada");
  gtk_widget_set_tooltip_text (elementos->subRehacer, "Rehacer jugada");
  gtk_widget_set_tooltip_text (GTK_WIDGET(elementos->redoItem), "Rehacer jugada");
  gtk_widget_set_tooltip_text (elementos->subGuardar, "Guardar la partida en curso");
  gtk_widget_set_tooltip_text (GTK_WIDGET(elementos->saveItem), "Guardar la partida en curso");
  gtk_widget_set_tooltip_text (elementos->subRecuperar, "Jugar partida guardada");

  //3. Registrar llamadas a las funciones.
  g_signal_connect (G_OBJECT (elementos->ventana), "delete_event", G_CALLBACK(deleteEventHandler), NULL); //DESTRUIR el proceso
  g_signal_connect (G_OBJECT (elementos->ventana), "destroy", G_CALLBACK(salir), elementos); //Cerrar el programa cuando se cierre la ventana
  g_signal_connect (G_OBJECT (elementos->subJugar), "activate", G_CALLBACK (funcionJugar),elementos);
  g_signal_connect (G_OBJECT (elementos->itemAyuda), "activate", G_CALLBACK(funcionAyuda), elementos); //Ventana de ayuda
  g_signal_connect (G_OBJECT (elementos->itemAcercade), "activate", G_CALLBACK(funcionAcercade), elementos); //Ventana de acerca de
  g_signal_connect (G_OBJECT (elementos->playItem), "clicked", G_CALLBACK(funcionJugar), elementos); // Ventana de jugar
  g_signal_connect (G_OBJECT (elementos->itemRanking), "activate", G_CALLBACK (ventanaRanking), elementos);//Ventana de ranking
  g_signal_connect (G_OBJECT (elementos->subTerminar), "activate", G_CALLBACK(terminar), elementos); //Ventana pregunta si desea guardar el juego
  g_signal_connect (G_OBJECT (elementos->subGuardar), "activate", G_CALLBACK(guardar), elementos); //funciones para seleccionar archivo en interfaz
  g_signal_connect (G_OBJECT (elementos->saveItem), "clicked", G_CALLBACK(guardar), elementos);
  g_signal_connect (G_OBJECT (elementos->stopItem), "clicked", G_CALLBACK (terminar), elementos); //Opcion salir
  for (int i = 0; i < 64; i++) {
    g_signal_connect (G_OBJECT (elementos->botones [i]), "clicked", G_CALLBACK (tiros),elementos); //Botones del tablero
  }
  g_signal_connect (G_OBJECT (elementos->undoItem), "clicked", G_CALLBACK (deshacer),elementos);  //Opcion de rehacer
  g_signal_connect (G_OBJECT (elementos->redoItem), "clicked", G_CALLBACK (rehacer), elementos); //Opcion de rehacer
  g_signal_connect (G_OBJECT (elementos->subRecuperar), "activate", G_CALLBACK (recuperar), elementos); //Opcion de cargar
  g_signal_connect (G_OBJECT (elementos->avanzarM), "clicked", G_CALLBACK (movimiento), elementos);

  //4.Definir la jerarquia.

  /*Agregar elementos a una ventana (container ->  bin)
  void gtk_container_add(GtkContainer *container, GtkWidget *widget)

  Agregar elementos a una caja (container -> box)
  void gtk_box_pack_start_defaults (GtkBox *box, GtkWidget *widget);
  void gtk_box_pack_end_defaults (GtkBox *box, GtkWidget *widget);*/

  gtk_container_add (GTK_CONTAINER (elementos->ventana), elementos->cajaVertical);

  //BARRA MENU
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaVertical), elementos->barraMenu);

  //TOOLBAR
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaVertical), elementos->toolbar);

  //MENU JUEGO
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->subJugar);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->separadorItem1);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->subGuardar);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->separadorItem2);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->subRecuperar);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->separadorItem3);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuJuego), elementos->subTerminar);

  gtk_menu_item_set_submenu (GTK_MENU_ITEM (elementos->itemJuego), elementos->menuJuego);

  gtk_menu_bar_append (GTK_MENU_BAR (elementos->barraMenu), elementos->itemJuego);

  //MENU HERRAMIENTAS
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuHerramientas),elementos-> subDeshacer);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuHerramientas), elementos->separadorItem4);
  gtk_menu_shell_append (GTK_MENU_SHELL (elementos->menuHerramientas), elementos->subRehacer);

  gtk_menu_item_set_submenu (GTK_MENU_ITEM (elementos->itemHerramientas), elementos->menuHerramientas);

  gtk_menu_bar_append (GTK_MENU_BAR (elementos->barraMenu), elementos->itemHerramientas);

  //MENU AYUDA
  gtk_menu_bar_append (GTK_MENU_BAR (elementos->barraMenu), elementos->itemAyuda);

  //MENU RANKING
  gtk_menu_bar_append (GTK_MENU_BAR (elementos->barraMenu), elementos->itemRanking);

  //MENU ACERCA DE
  gtk_menu_bar_append (GTK_MENU_BAR (elementos->barraMenu), elementos->itemAcercade);

  //TOOLBAR
  gtk_toolbar_insert (GTK_TOOLBAR(elementos->toolbar), elementos->playItem, -1);
  gtk_toolbar_insert (GTK_TOOLBAR(elementos->toolbar), elementos->undoItem, -1);
  gtk_toolbar_insert (GTK_TOOLBAR(elementos->toolbar), elementos->redoItem, -1);
  gtk_toolbar_insert (GTK_TOOLBAR(elementos->toolbar), elementos->saveItem, -1);
  gtk_toolbar_insert (GTK_TOOLBAR(elementos->toolbar), elementos->stopItem, -1);
  gtk_toolbar_insert (GTK_TOOLBAR(elementos->toolbar), elementos->avanzarM, -1);


  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaVertical), elementos->tablero);

  //TIMER Y JUGADORES
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaTiempo),elementos->eJugador1);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaTiempo),elementos->j1e);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaTiempo),elementos->labelTimer);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaTiempo),elementos->eJugador2);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaTiempo),elementos->j2e);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaVertical),elementos->cajaTiempo);

  //CONTADOR CARTAS CORRECTAS
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaPuntos), elementos->etiquetaJ1);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaPuntos), elementos->contadorJ1);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaPuntos), elementos->etiquetaJ2);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaPuntos), elementos->contadorJ2);
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaVertical), elementos->cajaPuntos);

  //BARRA DE ESTADO
  gtk_box_pack_start_defaults (GTK_BOX (elementos->cajaHorizontal),elementos->barraEstado);

  //CAJA DE LA BARRA DE ESTADO
  gtk_container_add (GTK_CONTAINER (elementos->cajaVertical),elementos->cajaHorizontal);


  //5. Mostrar widgets
  /*
  void gtk_widget_show (GtkWidget *widget);
  void gtk_widget_show_all (GtkWidget *widget);
  */
  gtk_widget_show_all (elementos->ventana);
  for (int i = 0; i < 64; i++) {
    gtk_widget_hide (elementos->botones [i]);
  }
  gtk_widget_hide (GTK_WIDGET (elementos->avanzarM));
  gtk_widget_hide (elementos->eJugador1);
  gtk_widget_hide (elementos->eJugador2);
  gtk_widget_hide (elementos->cajaPuntos);

  //6. Procesar seÃ±ales y eventos
  gtk_main ();
} //Fin gtk_main
