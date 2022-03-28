memoria.out: principal.o jugar.o funcionesEspeciales.o errores.o modoJuego.o computadora.o movimientos.o guardar.o recuperar.o ranking.o salir.o ventanasInfo.o
	gcc -Wall -o memoria.out principal.o jugar.o funcionesEspeciales.o errores.o modoJuego.o computadora.o movimientos.o guardar.o recuperar.o ranking.o salir.o ventanasInfo.o `pkg-config --libs gtk+-2.0`

principal.o: principal.c
	gcc -g -c principal.c `pkg-config --cflags gtk+-2.0`

jugar.o: jugar.c
	gcc -g -c jugar.c `pkg-config --cflags gtk+-2.0`

funcionesEspeciales.o: funcionesEspeciales.c
	gcc -g -c funcionesEspeciales.c `pkg-config --cflags gtk+-2.0`

errores.o: errores.c
	gcc -g -c errores.c `pkg-config --cflags gtk+-2.0`

modoJuego.o: modoJuego.c
	gcc -g -c modoJuego.c `pkg-config --cflags gtk+-2.0`

computadora.o: computadora.c
	gcc -g -c computadora.c `pkg-config --cflags gtk+-2.0`

movimientos.o: movimientos.c
	gcc -g -c movimientos.c `pkg-config --cflags gtk+-2.0`

guardar.o: guardar.c
	gcc -g -c guardar.c `pkg-config --cflags gtk+-2.0`

recuperar.o: recuperar.c
	gcc -g -c recuperar.c `pkg-config --cflags gtk+-2.0`

ranking.o: ranking.c
	gcc -g -c ranking.c `pkg-config --cflags gtk+-2.0`

salir.o: salir.c
	gcc -g -c salir.c `pkg-config --cflags gtk+-2.0`

ventanasInfo.o: ventanasInfo.c
	gcc -g -c ventanasInfo.c `pkg-config --cflags gtk+-2.0`

clean:
	rm *.o

