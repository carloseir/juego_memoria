//Alejandro Solorzano Santos, Bárbara Mondragón Herrada, Carlos Emilio Rodríguez
//Universidad Iberoameriacana
//Programacion Aplicada y Lab
//Proyecto Final
//Profr Andres Tortolero Baena
//14 de mayo de 2020

//ARCHIVOS DE INCLUSION
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

//ESTRUCTURAS DE ARCHIVOS

//Para lsita de movimientos
typedef struct movimientos{
  gint botonesActiv [64];
  gint turnoM;
  gint numeroTiros;
  gint recordarPC [64];
  gint carta;
  gint pares1J;
  gint pares2J;
  gint modo;
}MOVIMIENTOS;

//Primer paquete del archivo a guardar
typedef struct tablero
{
  gint posicionTablero [64];
  gint tiempoJuego;
  gchar *nombreJ1;
  gchar *nombreJ2;
}TABLERO;

//Mejores tiempos
typedef struct ranking{
  gchar *nombreGanador;
  gint tiempoTotal;
}RANKING;

//ESTRUCTURA PRINCIPAL
typedef struct elementos
{
  //VENTANA PRINCIPAL
  GtkWidget *ventana;

  //VENTANA DEL JUEGO.
  GtkWidget *cajaVertical,*cajaHorizontal; //Por cada widget se necesita una variable apuntando a GtkWidget

  //BARRA DE MENU
  GtkWidget *barraMenu, *itemAyuda, *itemAcercade, *itemJuego, *itemHerramientas, *itemRanking;
  GtkWidget *menuJuego, *menuHerramientas, *menuAyuda, *menuAcercade, *menuRanking;
  GtkWidget *subJugar, *subGuardar, *subRecuperar, *subTerminar, *subDeshacer, *subRehacer;
  GtkWidget *separadorItem1, *separadorItem2, *separadorItem3, *separadorItem4;

  //TOOLBAR
  GtkWidget *toolbar;
  GtkToolItem *playItem, *avanzarM, *stopItem, *saveItem, *undoItem, *redoItem;

  //BARRA DE ESTADO
  GtkWidget *barraEstado;
  int idEstado;

  //TABLERO
  GtkWidget *tablero;
  GtkWidget *botones [64];
  GtkWidget *imagenes [64];
  gint filasArriba, filasAbajo, columnasIzquierda, columnasDerecha, nombre;
  gint mapaimg [64];
  gint botonesActivos [64];

  //VARIABLE PARA GUARDAR NOMBRE DE BOTONES
  const gchar *nombres [64];

  //NOMBRE DE LOS JUGADORES
  const gchar *strJugador1;//Nombres
  const gchar *strJugador2;
  GtkWidget *eJugador1,*eJugador2;//labels
  GtkWidget *j1e,*j2e;//labels

  gint modoJuego;

  //TIEMPO
  gint timerSegundos,timerMinutos,timerHoras;
  gint segundosTotales;
  GtkWidget *labelTimer;
  gint juegoIniciado;//Indica si ya se inicio el timer por primera vez, 1 = iniciado, 0 = no iniciado

  //TIMER
  GtkWidget *cajaTiempo;
  gint timer;

  //VENTANA DE JUGAR
  GtkWidget *ventanaJugar;

  //VENTANA DE UN JUGADOR
  GtkWidget *ventanaUno,*nombre1;

  //VENTANA DE DOS JUGADORES
  GtkWidget *ventanaDos,*nombrej1,*nombrej2;

  //ACELERADORES
  GtkAccelGroup *grupoAceleradores;

  //TIROS
  gint numTiros,turno,paresJ1,paresJ2;
  const gchar *carta1;
  const gchar *carta2;
  gint bCarta1,bCarta2;
  gint primerTiro;

  //TERMINAR
  GtkWidget *terminar;

  //CONTADOR CARTAS CORRECTAS
 GtkWidget *cajaPuntos;
 GtkWidget *etiquetaJ1;
 GtkWidget *etiquetaJ2;
 GtkWidget *contadorJ1;
 GtkWidget *contadorJ2;
 gchar puntosJ1[10];
 gchar puntosJ2[10];
 gint totalPuntos;
 gchar *ganador;

 //COMPUTADORA
 gint recordar[64];
 gint igual;

 //LISTAS MOVIMIENTOS
 GList *lista;
 MOVIMIENTOS *movimientos;
 gpointer info;
 gint tiro;

 //GUARDAR TABLERO (ESTRUCTURA)
 TABLERO *tableroGuardar;
 gchar *nombreArchivoGuardar;

 //RANKING
 RANKING *datosGandor;
 GSList *listaRank;
 gpointer infoGanador;

 //CARGAR DE UN ARCHIVO
 int cargar;
 gchar *nombreArchivoRecuperar;

 //VENTANA RANKING
 GtkWidget *ventanaRanking;

}ELEMENTOS;

// DECLARACIÓN DE FUNCIONES
extern gboolean deleteEventHandler(GtkWidget *widget, GdkEvent *event,gpointer  user_data); //Funcion de destruir al salir
extern void salir (GtkWidget *widget, gpointer user_data);//Funcion de salir de la ventana principal
extern gint cuenta(gpointer user_data);//Funcion timer
extern void funcionJugar (GtkWidget *widget, gpointer user_data); //FUNCION DE LA OPCION JUGAR
extern void hideJugar (GtkWidget *widget, gpointer user_data);
extern void unJugador (GtkWidget *widget, gpointer   user_data);
extern void hideUnjugador (GtkWidget *widget, gpointer user_data);
extern void dosJugadores (GtkWidget *widget, gpointer   user_data);
extern void hideDosjugadores_judador1 (GtkWidget *widget, gpointer user_data);
extern void hideDosjugadores_judador2 (GtkWidget *widget, gpointer user_data);
extern void funcionAyuda(GtkWidget *widget, gpointer user_data);
extern void funcionAcercade(GtkWidget *widget, gpointer user_data);
extern void hideAcerca (GtkWidget *widget, gpointer user_data);
extern void terminar (GtkWidget *widget, gpointer user_data);
extern void rand10(ELEMENTOS *elementos);
extern void tiros (GtkWidget *widget, gpointer user_data);
extern void guardar (GtkWidget *widget, gpointer user_data);
extern void recuperar (GtkWidget *widget, gpointer user_data);
extern int igual (gint *numero);
extern void error_boton(GtkWidget *widget, gpointer user_data);
extern void ganador (GtkWidget *widget, gpointer user_data);
extern void computadora (GtkWidget *widget, gpointer user_data);
extern void listaRanking (GtkWidget *widget, gpointer user_data);
extern void deshacer (GtkWidget *widget,gpointer user_data);
extern int rand20(void);
extern void rehacer (GtkWidget *widget, gpointer user_data);
extern void guardarArchivo(GtkWidget *widget, gpointer user_data);
extern void recuperarArchivo (GtkWidget *widget, gpointer user_data);
extern void errorDeshacer (GtkWidget *widget,gpointer user_data);
extern void errorRehacer (GtkWidget *widget,gpointer user_data);
extern void movimiento (GtkWidget *widget, gpointer user_data);
extern void ventanaRanking(GtkWidget *widget, gpointer user_data);
extern void hideRanking(GtkWidget *widget, gpointer user_data);
extern void recuperarRanking(GtkWidget *widget, gpointer user_data);
extern void errorRanking(GtkWidget *widget, gpointer user_data);
