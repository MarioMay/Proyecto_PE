#include <iostream> //Biblioteca estándar en C++
#include <stdio.h>
#include <conio.h>
#include <windows.h> //Biblioteca para utilizar algunas funciones de consola de Windows
#include <time.h> //Biblioteca para manejar la fecha y hora del sistema
#include <string.h> //Biblioteca para manejar cadenas
#include <stdlib.h> //Biblioteca estandar de proposito general
#include <stdbool.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
using namespace std;

//Definimos las macros a utilizar
#define fila 15
#define columna 15

//Definimos la estructura del Jugador
typedef struct player{
	char nombre[50];
	int puntos;
}player;
player Jugador;

//Inicializamos las funciones
void gotoxy(int x, int y);
void bordesSistema();
void tituloPrincipal();
void menuPrincipal();
void instrucciones();
void creditos();
void menuJuegos();
void llenarMatriz(int matriz[][15]);
void tituloBuscaminas();
int generarBombas(int x);
void colocarBombas(int matriz[][15], int bomb);
void generarTablero(int matriz[][15],int status);
void aumentarPuntosAciertos(int cont);
void cronometroBuscaminas(int status);
void juegoBuscaminas();
void juegoGato();
void puntajesJugadores();
void solicitarNombreBuscaminas();
void asignarPuntaje(int puntosJugador);
void guardarRegistroBuscaminas(player Jugador);
void consultarRegistroBuscaminas();

//PROTOTIPOS DE LAS FUNCIONES DEL SNAKE	

void ocultarCursor();
void cuadro();
void guardar_posicion();
void dibujar_cuerpo();
void borrar_cuerpo();
void teclear();
void comida();
bool perder();
int mainSnake();
void solicitarNombreSnake();
void guardarRegistroSnake(player Jugador);
void consultarRegistroSnake();
void asignarPuntajeSnake();

//DECLARACION GLOBAL DE VARIABLES
int cuerpo[200][2];
int n = 1, tam = 10, dir = 3;
int x = 10, y = 12;
int xc = 30, yc = 15;
int velocidad = 80;
int puntos=0;
char tecla;

//Funcion principal
int main(int argc, char *argv[]) {
	//Establecemos el nombre a la ventana de la consola del sistema
	system("title Proyecto Final");{	
		system("color 0a");
		//Llamamos a la funcion que muestra el titulo del sistema
		tituloPrincipal();
	}
	//Llamamos a la funcion que muestra el menu principal del sistema
	menuPrincipal();
	return 0;
}

//Funcion que permite establecer las coordenadas en el cuadro de juego (consola windows)
void gotoxy(int x, int y){ 
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

//Funcion que genera los bordes de la interfaz
void bordesSistema(){
	//Declaracion de las dimensiones
	int c = 22, f = 78;
	//Genera los bordes del cuadro de la interfaz
	for(int i = 0 ; i < f; i++){
		gotoxy(i,0);printf("%c", 178);
		gotoxy(i,c);printf("%c", 178);
	}
	for(int i = 0 ; i <= c; i++){
		gotoxy(0,i);printf("%c", 178);
		gotoxy(f,i);printf("%c", 178);
	}
}

//Funcion que despliega las instrucciones de los juegos
void instrucciones(){
	//Declaracion de Variables
	int opcion;
	system("color 0b");
	system("cls");
	bordesSistema();
	gotoxy(5,1);printf("\t\t   **************** COMO JUGAR ****************  \n");
	gotoxy(26,4);printf("1. GATO (Tic Tac Toe)");
	gotoxy(26,6);printf("2. BUSCAMINAS");
	gotoxy(26,8);printf("3. SNAKE");
	gotoxy(26,10);printf("4. AHORCADO (Hangman)");
	gotoxy(26,12);printf("0. Regresar al Menu Principal");
	gotoxy(21,16);printf("Opcion: ");
	gotoxy(30,16);scanf("%d",&opcion);
	
	do{
		fflush(stdin);
		system("cls");
		switch(opcion){
		case 1:
			system("cls");
			bordesSistema();
			gotoxy(7,1);
			printf("\t\t   **************** GATO ****************  \n"); 
			printf("\n\t\t\t   Juego Para 2 Personas.\n\n\t El jugador 1 tendria la ficha 'X' y el Jugador 2 la Ficha 'O'.\n\t Deberan Escribir el Numero Que Deesen de Acuerdo a la Plantilla\n\t Mostrada en Pantalla. Gana la Persona que Logre Juntar 3 de sus\n\t Fichas en Linea Horizontal, Vertical o Diagonal. El Resultado se\n\t Mostrara en la Parte Superior. En Caso de Querer Volver a jugar\n\t Escriba 'y', sino, 'n' para Regresar Al Menu de Juegos.");
			printf("\n\n\n\tPresione Cualquier Tecla Para Regresar");
			getch();
			menuPrincipal();
			break;	
		case 2:
			system("cls");
			bordesSistema();
			gotoxy(7,1);
			printf("\n\t\t   **************** BUSCAMINAS ****************\n"); 
			printf("\n\t\t\t       Juego de 1 Persona.\n\n\tEl Jugador Decidira que Dificultad Jugar y Este\n\tComenzara en Seguida. Para Marcar la Casilla Deseada\n\tSe debe Escribir Primero la Coordenada X y Presionar Enter;\n\tSeguidamente Escribir la Coordenada Y y Presionar Enter\n\tPor Cada Acierto, obtienes 25 puntos. Pierdes Cuando se\n\tHaya Seleccionado una Bomba.");		
			printf("\n\n\n\tPresione Cualquier Tecla Para Regresar");
			getch();
			menuPrincipal();
			break;
		case 3:
			system("cls");
			bordesSistema();
			gotoxy(7,1);printf("\n\t\t   **************** SNAKE ****************\n"); 
			gotoxy(29,4);printf("Juego de 1 Persona."); 
			gotoxy(3,6);printf("El Juego Comienza Automaticamente Despues de Presionar Cualquier Tecla");
			gotoxy(3,7);printf("Se Controla el Movimiento Con las Flechas del Teclado el Objetivo");
			gotoxy(3,8);printf("Es Comer los Frutos, Hasta Obtener el Tamaño Maximo. Se Pierde");
			gotoxy(3,9);printf("Tocando los Bordes o Si la Serpiente se Toca Asi Misma.");
			gotoxy(3,10);printf("El Tiempo y el Puntaje se Muestra en la Parte Superior.");
			gotoxy(3,15);printf("Presione Cualquier Tecla Para Regresar");
			getch();
			menuPrincipal();
			break;
		case 4:
			system("cls");
			bordesSistema();
			gotoxy(5,1);printf("\n\t\t   **************** AHORCADO ****************\n"); 
			gotoxy(27,4);printf("Juego de 2 o Mas Personas."); 
			gotoxy(3,6);printf("El Juego Comienza Automaticamente Despues de Presionar Cualquier Tecla");
			gotoxy(3,7);printf("Cualquier Jugador Debera Ingresar la Palabra a Adivinar por el Jugador ");
			gotoxy(3,8);printf("Contrario. El Jugador Contario Debera Adivinar la Palabra Ingresando");
			gotoxy(3,9);printf("Letra por Letra. El Jugador Contara con 10 Vidas");
			gotoxy(3,15);printf("Presione Cualquier Tecla Para Regresar");
			getch();
			menuPrincipal();		
			break;
		case 0:
			system("cls");
			menuPrincipal();
			break;
		}
	}while((opcion >= 5) || (opcion < 0));
}

//Funcion que despliega el menu principal (interfaz principal)
void menuPrincipal(){
	//Declaracion de variables
	int opcion; 
	
	system("color 0a");
	system("cls");
	bordesSistema();
	gotoxy(7,1);printf("\n\t\t   **************** ARCADE ****************  \n");
	gotoxy(31,4);printf("1. Menu de Juegos");
	gotoxy(31,6);printf("2. Instrucciones");
	gotoxy(31,8);printf("3. Creditos");
	gotoxy(31,10);printf("4. Jugadores y Puntajes");
	gotoxy(31,12);printf("0. Salir");
	gotoxy(26,16);printf("Opcion: ");
	gotoxy(35,16);scanf("%d",&opcion);
	
	do{
		fflush(stdin);
		system("cls");
		switch(opcion){
		case 1:
			//Ingresar al menu de juegos
			system("cls");
			menuJuegos();
			break;
		case 2:
			//Instrucciones de los juegos
			system("cls");
			instrucciones();
			break;
		case 3:
			//Creditos
			system("cls");
			system("color 0e");
			bordesSistema();
			creditos();
			break;
		case 4:
			//Puntajes
			system("cls");
			system("color 0a");
			puntajesJugadores();
			break;
		case 0:
			//Finaliza la ejecucion del programa
			system("cls");
			printf("\n\n\n\n\t\t\t       ¡GRACIAS POR UTILIZAR!      ");
			getch();
			exit(1);
			break;
		}
	}while((opcion >= 5) || (opcion < 0));
}

//Funcion que despliega los creditos de los autores del sistema
void creditos(){
	gotoxy(3,3);printf("\t\t\t    Proyecto Desarrollado Por:");
	gotoxy(3,4);printf("\t\tUriel Cauich, Mario May, Jamart Perez y Luis Tovar\n");
	gotoxy(6,6);printf("\t\t\t Ingenieria de Software - MEFI");
	gotoxy(5,9);printf("\t\t\t   Programacion Estructurada");
	gotoxy(5,12);printf("\t\t        Universidad Autonoma de Yucatan");
	gotoxy(4,15);printf("\t\t\t  Facultad de Matematicas");
	gotoxy(5,20); printf("Presione Cualquier Tecla Para Regresar");
	getch();
	menuPrincipal();
}

//Funcion que despliega el menu de juegos
void menuJuegos(){
	//Declaracion de variables
	int opcion;
	
	system("cls");
	system("color 0f");
	bordesSistema();
	gotoxy(9,1);printf("\n\t\t  **************** JUEGOS ****************  \n");
	gotoxy(31,4);printf("1. GATO (Tic Tac Toe)");
	gotoxy(31,6);printf("2. BUSCAMINAS ");
	gotoxy(31,8);printf("3. SNAKE");
	gotoxy(31,10);printf("4. AHORCADO (Hangman)");
	gotoxy(31,12);printf("0. Regresar");
	gotoxy(26,16);printf("Opcion: ");
	gotoxy(35,16);scanf("%d",&opcion);
	
	do{
		fflush(stdin);
		system("cls");
		switch(opcion){
		case 1:
			//Juego de Gato
			system("cls");
			break;
		case 2:
			//Buscaminas
			system("cls");
			juegoBuscaminas();
			break;
		case 3:
			//Juego de Snake
			system("cls");
			mainSnake();
			break;
		case 4:
			//Juego de ahorcado
			system("cls");
			break;
		case 0:
			//Regresa al menu principal
			system("cls");
			menuPrincipal();
			break;
		}
	}while((opcion >= 5) || (opcion < 0));
}

//Funcion que despliega el mensaje de inicio 
void tituloPrincipal(){
	system("cls");
	system("color 0a");
	bordesSistema();
	gotoxy(1,4);puts("           d8888 8888888b.   .d8888b.        d8888 8888888b.  8888888888 ");
	gotoxy(1,5);puts("          d88888 888   Y88b d88P  Y88b      d88888 888   Y88b 888       ");
	gotoxy(1,6);puts("         d88P888 888    888 888    888     d88P888 888    888 888  ");
	gotoxy(1,7);puts("        d88P 888 888   d88P 888           d88P 888 888    888 8888888 ");
	gotoxy(1,8);puts("       d88P  888 8888888P'  888          d88P  888 888    888 888  ");
	gotoxy(1,9);puts("      d88P   888 888 T88b   888    888  d88P   888 888    888 888  ");
	gotoxy(1,10);puts("     d8888888888 888  T88b  Y88b  d88P d8888888888 888  .d88P 888   ");
	gotoxy(1,11);puts("    d88P     888 888   T88b  'Y8888P' d88P     888 8888888P'  8888888888");
	gotoxy(2,17);puts("                     Oprima Cualquier Tecla Para Comenzar              \n");
	getch();
	system("cls");
}

//Funcion para llenar el tablero de Buscaminas
void llenarMatriz(int matriz[][15]){
	for(int i = 0; i < fila; i++){
		for(int j=0; j < columna; j++){
			matriz[i][j] = 2;
		}
	}
}
//Funcion para dar la bienvenida al usuario al juego
void tituloBuscaminas(){
	bordesSistema();
	gotoxy(5,1);printf("\t\t **************** BUSCAMINAS ****************  \n");
	gotoxy(7,3);printf("\t\t   >>Ingrese el Nivel de su Preferencia");
	gotoxy(31,6);printf("1. Facil");
	gotoxy(31,8);printf("2. Medio");
	gotoxy(31,10);printf("3. Dificil");
	gotoxy(31,12);printf("4. Imposible");
	gotoxy(31,14);printf("0. Regresar al Menu Principal");
	gotoxy(26,17);printf("Opcion: ");
}

//Funcion para seleccionar el nivel y la cantidad de bombas
int generarBombas(int x){
	switch(x){
	case 1:
		return 10;
		break;	
	case 2:
		return 25;
		break;
	case 3:
		return 50;
		break;
	case 4:
		return 100;
		break;	
	}
	return 0;
}

//Funcion para colocar las bombas previamente generadas en el tablero
void colocarBombas(int matriz[][15], int bomb){
	int i, dominio, codominio;
	for(i = 1; i <= bomb; i++){
		dominio = 0 + rand() % 14;
		codominio = 0 + rand() % 14;
		matriz[dominio][codominio] = 3;
	}
}

//Funcion para imprimir el tablero
void generarTablero(int matriz[][15], int status){
	//Declaramos variables
	int i, j;
	
	for(i = 0; i <= fila-1; i++)
		printf("%d ", i);
	printf("\n");
	
	for(i = 0; i <= columna; i++)
		printf("%c%c",205,205);
	printf("\n");
	
	for(i = 0; i <= fila -1; i++){
		printf("%c ",186);
		for(j = 0; j <= columna - 1; j++){
			if(matriz[i][j] == 1)
				printf("%d ", matriz[i][j]);
			else if((matriz[i][j] == 3) && (status == 0))
				printf("%c ",157);
			else
				printf("%c ",254);         
		}
		printf("%c %d", 186,i);    
		printf("\n");  
	}
	
	for(i = 0; i <= fila; i++){
		printf ("%c%c",205,205);
	}	
	printf ("\n");
}
//Funcion para aumentar los puntos en caso de acertar
void aumentarPuntosAciertos(int cont){
	int auxiliar;
	auxiliar = cont * 25;
	printf("\n\t\t\t\tPuntaje: %d \n\n", auxiliar);
}

//Funcion Para Llevar el Tiempo
void cronometroBuscaminas(int status){
	int horas = 0, min = 0, sec = 0, x;
	while(status != 1 && status != 0){
		x = 1000;
		sec++;
		if(sec == 60){
			sec = 0;
			min++;
		}if(min == 60){
			min = 0;
			horas++;
		}
		printf("Tiempo: %.2d:%.2d:%.2d", horas, min, sec);
		Sleep(x);
	}
}

//Funcion que permite generar el juego de Buscaminas
void juegoBuscaminas(){
	//Declaracion de variables
	int buscaminas[fila][columna];
	int nivel, bombas, repetir;
	int decision;
	
	do{
		system("cls");	
		int i, j, contador = 0;
		int estatus = -1;
		//Se imprime y llena el tablero del buscaminas	
		llenarMatriz(buscaminas);	
		tituloBuscaminas();
		//Se captura el nivel
		do{
			scanf("%d",&nivel);
			fflush(stdin);
			if(nivel == 0){
				return menuPrincipal();
			}
			if((nivel < 0) || (nivel > 4)){
				printf ("\n <<Caracter No Valido>>\n   Opcion: ");
			}
		}while((nivel < 0) || (nivel > 4));
		
		bombas = generarBombas(nivel);
		srand(time(NULL)); 
		colocarBombas(buscaminas, bombas);
		system("cls");
		printf("\n\t\t\t>>Intentalo mejor<<\t\t\t\n\n");
		aumentarPuntosAciertos(contador);
		generarTablero(buscaminas, estatus); 
		
		do{
			puts("Ingrese su tiro: (x,y)");
			do{
				printf("X=");
				scanf("%d", &i);
				if((i < 0 || i > 14)){
					printf("<<Tiro No Valido>> \n Ingrese su Tiro Nuevamente\n");
				}
				fflush(stdin);	
			}while(!(i >= 0 &&  i <= 14));
			do{
				printf("Y=");
				scanf("%d", &j);
				if((j<0 || j>14)){
					printf("<<Tiro No Valido>> \n Ingrese su Tiro Nuevamente\n");
				}
				fflush(stdin);	
			}while(!(j >= 0 &&  j <= 14) );
			system("cls");
			
			if(buscaminas[i][j] == 3){
				printf("\t\t\t>>'BUSCAMINAS'<<\t\t\t\t\n\n");
				estatus = 0;
				generarTablero(buscaminas, estatus); 
				aumentarPuntosAciertos(contador);
				puts("\n!!!!Usted Ha Perdido!!!!\n");
			}else{
				if(buscaminas[i][j] == 2){
					printf("\n\t\t\t\t\t>>'BUSCAMINAS'<<\t\t\t\t\t\n\n");
					buscaminas[i][j] = 1;
					contador++;
					estatus = -1;
					aumentarPuntosAciertos(contador);
					generarTablero(buscaminas, estatus); 
				}
			}if(contador == (255 - bombas)){
				printf("\n\t\t\t\t\t\t>>'BUSCAMINAS'<<\t\t\t\t\t\n\n");
				aumentarPuntosAciertos(contador);
				estatus = 1;
				generarTablero(buscaminas, estatus);
				puts("\n!!!Usted Ha Ganado!!!\n");
			}
		}while(estatus != 1 && estatus != 0);
		printf("¿Desea Jugar de Nuevo?: 1 - Si    0 - No: ");
		fflush(stdin);//Limpia el Buffer de los Datos Almacenados
		
		do{
			scanf("\t%d", &decision);
			fflush(stdin);
			if(decision == 1){
				repetir = 1;
				break;
			}
			if(decision == 0){
				repetir = 0;
				solicitarNombreBuscaminas();
				asignarPuntaje(contador * 25);
				guardarRegistroBuscaminas(Jugador);
				menuJuegos();
			}
			if((decision != 1) || (decision != 0)){
				puts("\n<<Caracter No Valido>>\n");
			}
		}while((decision != 1) || (decision != 0));
		system("cls");	
	}while(repetir);
}

void juegoGato(){
	//Declaracion de Variables	
	int jugador=1;
	int error;
	int empate=0;
	int ganar=0;
	
	char c1='1',c2='2', c3='3', c4='4', c5='5', c6='6', c7='7', c8='8', c9='9';
	char tiro, marca, respuesta='y';
	
	//Declaracion de las dimensiones
	int c=22, f=78; 
	do{
		//Limpia la Pantalla
		system("cls");
		
		//Generación de bordes del cuadro de la interfaz
		for(int i=0 ; i<f ; i++){
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		
		//Generación de bordes del cuadro de la interfaz
		for(int i=0 ; i<=c ; i++){
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		
		//Cambio de color de texto de la consola
		system("color 0a");
		error=1;
		
		//Impresion de Tablero
		gotoxy(5,1);
		printf("\t\t\t  ***JUEGO DE GATO***\n\n");
		printf("\n\t\t\t     %c | %c | %c\n", c1, c2, c3);
		printf("\t\t\t    ---+---+---\n");
		printf("\n\t\t\t     %c | %c | %c\n", c4, c5, c6);
		printf("\t\t\t    ---+---+---\n");
		printf("\n\t\t\t     %c | %c | %c\n\n\n", c7, c8, c9);

		//Asignacon de Marca Para Cada Jugador
		if(jugador==1){
			marca='X';
		}else{
			marca='O';
		}
		
		//Muestra el turno del Jugador Actual
		printf("\tTurno del Jugador %d:  ", jugador);
		
		fflush(stdin);
		
		do{
			scanf("%c",&tiro);
			fflush(stdin);
		}while(tiro>'9' || tiro<'1');
		
		//Condicionales Para Cambiar el Numero Puesto Por la Ficha del Jugador Actual
		if (tiro=='1' && c1=='1'){c1=marca;}
		else if (tiro=='2' && c2=='2') {c2=marca;}
		else if (tiro=='3' && c3=='3') {c3=marca;}
		else if (tiro=='4' && c4=='4') {c4=marca;}
		else if (tiro=='5' && c5=='5') {c5=marca;}
		else if (tiro=='6' && c6=='6') {c6=marca;}
		else if (tiro=='7' && c7=='7') {c7=marca;}
		else if (tiro=='8' && c8=='8') {c8=marca;}
		else if (tiro=='9' && c9=='9') {c9=marca;}
		else{
			printf("\n\tError! Movimiento No Valido\n");
			Sleep(400); 
			error=2;
		}
		
		//Condicionales para Detectar 3 Marcas Iguales en Fila y Ganar el Juego
		if(c1=='X'||c1=='O'){
			if(c2==c1&&c3==c1){
				ganar=1;
			}
			if(c4==c1&&c7==c1){
				ganar=1;
			}
		}
		
		//Condicionales para Detectar 3 Marcas Iguales en Diagonal y Ganar el Juego
		if(c5=='X'||c5=='O'){
			if(c1==c5 && c9==c5){
				ganar=1;
			}
			if(c2==c5 && c8==c5){
				ganar=1;
			}
			if(c4==c5 && c6==c5){
				ganar=1;
			}
			if(c3==c5 && c7==c5){
				ganar=1;
			}
		}
		
		//Condicionales para Detectar 3 Marcas Iguales en Columna y Ganar el Juego
		if(c9=='X'||c9=='O'){
			if(c6==c9 && c3==c9){
				ganar=1;
			}
			if(c7==c9 && c8==c9){
				ganar=1;
			}
		}
		
		//Condicionales Para Detectar Si Hay Empate
		if((c1!='1' && c2!='2' && c3!='3' && c4!='4' && c5!='5' && c6!='6' && c7!='7' && c8!='8' && c9!='9') && ganar==0){
			empate=1;
		}
		
		if(ganar==1 || empate==1){
			//Limpieza de Pantalla y Muestra de Resultado Final
			system("cls"); 
			if(ganar==1){
				//Generación de los bordes del cuadro de la interfaz
				for(int i=0 ; i<f ; i++){ 
					gotoxy(i,0);
					printf("%c",178);
					gotoxy(i,c);
					printf("%c",178);
				}
				
				//Generación de los bordes del Cuadro de la Interfaz
				for(int i=0 ; i<=c ; i++){ 
					gotoxy(0,i);
					printf("%c",178);
					gotoxy(f,i);
					printf("%c",178);
				}
				
				gotoxy(5,2);
				printf("\t\t\t¡JUGADOR: %d HA GANADO!\n\n",jugador);
				printf("\n\t\t\t      %c | %c | %c\n", c1, c2, c3);
				printf("\t\t\t     ---+---+---\n");
				printf("\n\t\t\t      %c | %c | %c\n", c4, c5, c6);
				printf("\t\t\t     ---+---+---\n");
				printf("\n\t\t\t      %c | %c | %c\n\n", c7, c8, c9);
			}
			
			//Generación de bordes del cuadro de la interfaz
			if(empate==1){
				for(int i=0 ; i<f ; i++){
					gotoxy(i, 0);
					printf("%c", 178);
					gotoxy(i,c);
					printf("%c", 178);
				}
				
				//Generación de bordes del cuadro de la interfaz
				for(int i=0 ; i<=c ; i++){
					gotoxy(0, i);
					printf("%c", 178);
					gotoxy(f, i);
					printf("%c", 178);
				}
				
				gotoxy(5,1);
				printf("\t\t\t    ¡¡EMPATE!! \n");
				printf("\n\t\t\t     %c | %c | %c\n",c1,c2,c3);
				printf("\t\t\t    ---+---+---\n");
				printf("\n\t\t\t     %c | %c | %c\n",c4,c5,c6);
				printf("\t\t\t    ---+---+---\n");
				printf("\n\t\t\t     %c | %c | %c\n\n\n",c7,c8,c9);
			}
			
			gotoxy(3, 15);printf("¿Desea Jugar de Nuevo?: Si.(Oprima 'y')    No. (Cualquier Otra Tecla)  ");
			
			//Limpieza del Buffer de los Datos Almacenados
			fflush(stdin);
			
			gotoxy(75, 15);
			scanf("%c", &respuesta);
			
			//Condicional para el caso si se quiere volver a jugar, reimpresión del tablero y reinicio de contadores
			if (respuesta=='y' || respuesta=='Y'){
				empate=0;
				jugador=2;
				ganar=0;
				c1='1';
				c2='2';
				c3='3';
				c4='4';
				c5='5';
				c6='6';
				c7='7';
				c8='8';
				c9='9';
			}
		}
		//Condicional para cambio de turno
		if(error==1){
			if(jugador==1){
				jugador=2;
			}else{
				jugador=1;
			}
		}	

	//Ciclo para repetir el juego hasta que se desee salir
	}while(respuesta=='y' || respuesta=='Y');
}

//Funcion que despliega los puntajes de los jugadores registrados
void puntajesJugadores(){
	//Declaracion de variables
	int opcion;
	
	system("color 0c");
	system("cls");
	bordesSistema();
	gotoxy(1,2);printf("\t   **************** JUGADORES RECIENTES ****************  \n");
	gotoxy(26,4);printf("1. BUSCAMINAS");
	gotoxy(26,6);printf("2. SNAKE");
	gotoxy(26,8);printf("0. Regresar al Menu Principal");
	gotoxy(21,11);printf("Opcion: ");
	gotoxy(30,11);scanf("%d",&opcion);
	
	do{
		fflush(stdin);
		system("cls");
		switch(opcion){
		case 1:
			bordesSistema();
			gotoxy(7,1);printf("\n\t\t   **************** BUSCAMINAS ****************\n"); 
			gotoxy(20,3);printf("\t     Jugador");
			gotoxy(39,3);printf("\t   Score");
			consultarRegistroBuscaminas();
			gotoxy(20,20);printf("Presione Cualquier Tecla Para Regresar");
			getch();
			menuPrincipal();
			break;
		case 2:
			system("cls");
			bordesSistema();
			gotoxy(7,1);printf("\n\t\t   **************** SNAKE ****************\n"); 
			gotoxy(20,3);printf("\t    Jugador");
			gotoxy(39,3);printf("\t Score");
			consultarRegistroSnake();
			gotoxy(20,20);printf("Presione Cualquier Tecla Para Regresar");
			getch();
			menuPrincipal();
			break;
		case 0:
			system("cls");
			menuPrincipal();
			break;
		}
	}while(opcion>=3 || opcion<0);
}

//Funcion que solicita el nombre al usuario para el juego de Buscaminas
void solicitarNombreBuscaminas(){
	fflush(stdin);
	gotoxy(46,10);printf("Inserte Su Nickname:");
	gotoxy(66,10);gets(Jugador.nombre);
}

//Funcion que asigna los puntos al jugador
void asignarPuntaje(int puntosJugador){
	fflush(stdin);
	Jugador.puntos = puntosJugador;
}

//Funcion que guarda el registo de Buscaminas en un archivo txt
void guardarRegistroBuscaminas(player Jugador){
	FILE *f;
	f = fopen("RegistroBuscaminas.txt","a+");
	if(f == NULL){
		printf("No se pudo abrir el archivo.\n");
	}else{
		gotoxy(3,5);fprintf(f, "\n\t\t\t\t%s.........", Jugador.nombre); 
		gotoxy(17,5);fprintf (f,"%d", Jugador.puntos);
	}
	fclose(f);
}

//Funcion que despliega el registro de puntaje de Buscaminas en un archivo txt
void consultarRegistroBuscaminas(){
	FILE *f;
	char frase[21];
	f = fopen("RegistroBuscaminas.txt", "a+");
	if(f == NULL)
		printf("No se pudo abrir el archivo.\n");
	else{
		do{
			fgets(frase,21, f);
			puts(frase);
		}
		while(!feof(f));
	}
}

//INICIO DE LA SECCION DEL SNAKE//
//FUNCION SUBPRINCIPAL MAIN DEL SNAKE
int mainSnake(){
	system("mode con cols=80 lines=25");
 	gotoxy (35,1); printf("JUEGO SNAKE");
 	printf("\n\n");
	ocultarCursor();
 	cuadro();
 	gotoxy(xc, yc); printf("%c", 4);
 
 	while(tecla != ESC && perder()){
 		gotoxy (3,2); printf("PUNTUACION: %i",puntos);
		borrar_cuerpo();
		guardar_posicion();
		dibujar_cuerpo();
		comida();
		teclear();
		teclear();
 
		if(dir == 1) y--;
		if(dir == 2) y++;
		if(dir == 3) x++;
		if(dir == 4) x--;
 
		Sleep(velocidad);
 	}
 	
 	system("cls");
 	gotoxy (35,1); printf("JUEGO SNAKE");
 	cuadro();
 	gotoxy (22,12); printf("OBTUVISTE UNA PUNTUACION DE: %i",puntos);
 	gotoxy (22,14); printf("Presione una tecla para continuar..");
 	solicitarNombreSnake();
 	guardarRegistroSnake(Jugador);
 	menuJuegos();
 	getch();
	
}


//FUNCION QUE REALIZA EL RECUADRO DEL JUEGO SNAKE
void cuadro(){ 
	int i,v;
	
	for(i=2; i < 78; i++){
		gotoxy (i, 4); printf ("%c", 205);
 		gotoxy(i, 23); printf ("%c", 205); 
	}

	for(v=4; v < 23; v++){
 		gotoxy (2,v); printf ("%c", 186);
 		gotoxy(77,v); printf ("%c", 186); 
	}
	
 	gotoxy (2,4); printf ("%c", 201);
 	gotoxy (2,23); printf ("%c", 200);
 	gotoxy (77,4); printf ("%c", 187);
 	gotoxy(77,23); printf ("%c", 188); 
}

 
//FUNCION QUE GUARDA LA POSICION EN LA QUE SE ENCUENTRA LA SERPIENTE
void guardar_posicion(){
	cuerpo[n][0] = x;
 	cuerpo[n][1] = y;
 	n++;
 
 	if(n == tam) n = 1;
}

//FUNCION QUE DIBUJA EL CUERPO DE LA SERPIENTE
void dibujar_cuerpo(){
	int i;
	for(i = 1; i < tam; i++){
 		gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf("*");
	}
}

//FUNCION QUE BORRA EL CUERPO DE LA SERPIENTE (SE BORRA LA ULTIMA PARTE DEL CUERPO)
void borrar_cuerpo(){
	gotoxy(cuerpo[n][0] , cuerpo[n][1]); printf(" ");
}
 

//FUNCION QUE DETECTA QUE TECLA SE ESTA PRESIONANDO
void teclear(){
	if(kbhit()){
		tecla = getch();
	 	switch(tecla){
	 		
			case ARRIBA : if(dir != 2) dir = 1; break;
	 		case ABAJO : if(dir != 1) dir = 2; break;
	 		case DERECHA : if(dir != 4) dir = 3; break;
	 		case IZQUIERDA : if(dir != 3) dir = 4; break;
		}
 	}
}

//FUNCION QUE MUESTRA LA COMIDA DE FORMA ALEATORIA EN ALGUNA ZONA DE LA PANTALLA 
void comida(){
	if(x == xc && y == yc){
		xc = (rand() % 73) + 4;
 		yc = (rand() % 18) + 5;
 		tam++;
 		puntos+=100;
 		gotoxy(xc, yc); printf("%c", 4);
	}
}

//FUNCION QUE VERIFICA SI SE TOPADO EL RECUADRO O SE HA CHOCADO CON EL MISMO CUERPO
bool perder(){
	int j;
	
	if(y == 4 || y == 23 || x == 2 || x == 77) 
		return false;
		
 	for(j = tam - 1; j > 0; j--){
	 	if(cuerpo[j][0] == x && cuerpo[j][1] == y)
	 	return false;
	}
	
	return true;
}

//Funcion que solicita el nombre al usuario para el juego de snake
void solicitarNombreSnake(){
	fflush(stdin);
	gotoxy(46,10);printf("Inserte Su Nickname:");
	gotoxy(66,10);gets(Jugador.nombre);



}

//Funcion que guarda el registo de snake en un archivo txt
void guardarRegistroSnake(player Jugador){
	FILE *f;
	f = fopen("RegistroSnake.txt","a+");
	if(f == NULL){
		printf("No se pudo abrir el archivo.\n");
	}else{
		gotoxy(3,5);fprintf(f, "\n\t\t\t\t%s.........", Jugador.nombre); 
		gotoxy(17,5);fprintf (f,"%d", Jugador.puntos);
	}
	fclose(f);
}

//Funcion que despliega el registro de puntaje de Snake en un archivo txt
void consultarRegistroSnake(){
	FILE *f;
	char frase[21];
	f = fopen("RegistroSnake.txt", "a+");
	if(f == NULL)
		printf("No se pudo abrir el archivo.\n");
	else{
		do{
			fgets(frase,21, f);
			puts(frase);
		}
		while(!feof(f));
	}
}

//Funcion que asigna los puntos al jugador de snake
void asignarPuntajeSnake(int puntosJugador){
	fflush(stdin);
	Jugador.puntos = puntos;
}


//FUNCION QUE OCULTA EL CURSOR
void ocultarCursor() {
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

//HASTA AQUI TERMINA LA SECCION DEL SNAKE//


