#include <stdio.h>
#include <stdlib.h>

//Windows 
#define CLEAR() system("CLS")
//UNIX
//#define CLEAR() system("clear")

void generarTablero(short int, short int, char*);
void colocarIndicador(char*, short int, short int);
void configuracionDelJuego(void);
void juego(char*, char*, short int, short int, short int);

int main(void)
{
	char opcion; 
	
	srand(time(NULL)); //Semilla.
	
	do
	{
		CLEAR(); //Limpiar pantalla.
		
		printf("\n\t   ____       _   _    ____       ____      _      __   __              _   _       _      ____  ");
		printf("\n\tU | __\") u U |\"|u| |  / __\"| u U /\"___| U  /\"\\  u U|' \\/ '|u   ___     | \\ |\"|  U  /\"\\  u / __\"| u ");
		printf("\n\t \\|  _ \\ /  \\| |\\| |  \\___ \\/  \\| | u    \\/ _ \\/  \\| |\\/| |/  |_\"_|   <|  \\| |>  \\/ _ \\/ <\\___ \\/ ");
		printf("\n\t  | |_) |    | |_| |  u___) |   | |/__   / ___ \\   | |  | |    | |    U| |\\  |u  / ___ \\  u___) | ");
		printf("\n\t  |____/    <<\\___/   |____/>>   \\____| /_/   \\_\\  |_|  |_|  U/| |\\u   |_| \\_|  /_/   \\_\\ |____/>>  ");
		printf("\n\t _|| \\\\_   (__) )(     )(  (__) _// \\\\   \\\\    >> <<,-,,-..-,_|___|_,-.||   \\\\,-.\\\\    >>  )(  (__) ");
		printf("\n\t(__) (__)      (__)   (__)    (__) (__) (__)  (__) (./  \\.)\\_)-' '-(_/ (_\")  (_/(__)  (__)(__)    ");
		printf("\n\n\t\t\t\t\tby Miguel Angel Rosas Ocampo");
		printf("\n\t\t\t\t\t\tversi%cn 1.0",162);
		
		printf("\n\n\n\t\t\t\t\t\t  a) Juego.");
		printf("\n\n\t\t\t\t\t\t  s) Salir.");
		
		printf("\n\n\n\t\t\t\t\t\tIngrese opci%cn: ",162);
		scanf("%c",&opcion);

		if(opcion == 'a' || opcion == 'A')
			configuracionDelJuego();
		
	}while(opcion != 's' && opcion != 'S');
	
	
	return 0;
}

void configuracionDelJuego()
{
	char *numerosTableros, *tableroJugador, nivel;
	short int filas, columnas, i, j, k=0, minas, posicionDeMina;
		
	do
	{	
		CLEAR();
		setbuf(stdin,NULL);
		
		printf("\n\n\t\t\t\ta) Nivel principiante: 8x8 casillas y 10 minas.");
		printf("\n\n\t\t\t\tb) Nivel intermedio: 16x16 casillas y 40 minas. ");
		printf("\n\n\t\t\t\tc) Nivel experto: 16x30 casillas y 99 minas.");
		printf("\n\n\t\t\t\td) Nivel personalizado.");
		
		printf("\n\n\n\t\t\t\t\tIngresa opci%cn: ",162);
		
		scanf("%c",&nivel);
	
	}while(nivel != 'a' && nivel != 'A' && nivel != 'b' && nivel != 'B' && nivel != 'c' && nivel != 'C'
			&& nivel != 'd' && nivel != 'D');
	
	if(nivel == 'a' || nivel == 'A')
		minas = 2 + (filas = columnas = 8); 
	
	else if(nivel == 'b' || nivel == 'B')
		minas = 24 + (filas = columnas = 16);
		
	else if(nivel == 'c' || nivel == 'C')
		minas = 69 + (filas = 14 + (columnas = 16) );
		
	else if(nivel == 'd' || nivel == 'D')
	{	
		do //Sorry, no sé cómo pasó, pero use las filas como columnas y las columnas como filas ._.
		{	
			printf("\n\t\tIngresa el n%cmero de filas: ",163);
			scanf("%hd",&columnas);
		
		}while(columnas<1);
		
		do
		{
			printf("\n\t\tIngresa el n%cmero de columnas: ",163);
			scanf("%hd",&filas); 
		
		}while(filas<1);
		
		do
		{
			printf("\n\t\tIngresa el n%cmero minas: ",163);
			scanf("%hd",&minas);
			
			if(minas > filas*columnas)		
			{
				printf("\n\tEl m%cximo de minas para un tablero de %hd x %hd es de %hd",160,columnas,filas,columnas*filas);
				setbuf(stdin, NULL); 
				getchar();
			}
			
		}while(minas <= 0  || minas > filas*columnas);
	}
	
	numerosTableros = (char*) malloc(sizeof(char)*filas*columnas);
	
	if(!numerosTableros)
	{
		printf("\nNo se ha podido reservar memoria suficiente.");
		exit(-1);
	}
		
	tableroJugador = (char*) malloc(filas*columnas*sizeof(char));
	
	if(!tableroJugador)
	{
		printf("\nNo se ha podido reservar memoria suficiente.");
		exit(-1);
	}
	
	for(i=0; i<filas*columnas; i++) //LLenar los tablero de espacios.
		*(tableroJugador + i) = 219;
	
	for(i=0; i<filas*columnas; i++) //LLenar los tablero de espacios.
		*(numerosTableros + i) = 32;	
		
	for(i=0; i<minas; i++) //Se llenan las minas en el tablero.
	{
		posicionDeMina = 0 + rand() % (filas*columnas);

		if( *(numerosTableros + posicionDeMina) != '0') //Verifica que NO haya una mina ya puesta.
		{
			*(numerosTableros + posicionDeMina) = '0'; //En esa posición se coloca un '0' (mina).
			
			if( (posicionDeMina+1)%filas && *(numerosTableros + (posicionDeMina+1)) != '0')
				colocarIndicador(numerosTableros, posicionDeMina,-1); //Se manda con - para que sea +		
			
			if( posicionDeMina%filas && *(numerosTableros + posicionDeMina - 1) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, 1);
				
			if( posicionDeMina<((filas*columnas)-filas) && *(numerosTableros + (posicionDeMina + filas)) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, -filas);
		
			if( posicionDeMina>=filas && *(numerosTableros + (posicionDeMina - filas) ) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, filas);					
		
			if( posicionDeMina<((filas*columnas)-filas) && (posicionDeMina+1)%filas && *(numerosTableros + (posicionDeMina + filas + 1) ) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, -filas-1);	
				
			if( posicionDeMina<((filas*columnas)-filas) && posicionDeMina%filas  && *(numerosTableros + (posicionDeMina + filas -1) ) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, -filas+1);
		
			if( posicionDeMina>=filas && posicionDeMina%filas && *(numerosTableros + (posicionDeMina - filas - 1)) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, filas+1);
	
			if( posicionDeMina>=filas && (posicionDeMina+1)%filas && *(numerosTableros + (posicionDeMina - filas + 1)) != '0' )
				colocarIndicador(numerosTableros, posicionDeMina, filas-1); 
		}			
		
		else --i; //Si ya había un '0' en esa posición, se vuelve a repetir la iteración.
	}
	
	juego(numerosTableros, tableroJugador, filas, columnas, minas);
	
	free(numerosTableros);
	free(tableroJugador);	
}

void juego(char *numerosTableros, char* tableroJugador, short int filas, short int columnas, short int minas)
{
	char comando, columnaUsuario;
	short int i, j, turno = 0, banderas = minas, ganar;
	
	do
	{
		CLEAR();
		
		ganar = 0;
		printf("\n\tTurno:%3hd    Minas:%3hd    Banderas disponibles:%3hd\n\n",turno++, minas,banderas);
		generarTablero(filas, columnas, tableroJugador);
		
		printf("\n    COMANDOS    L (Abrir casilla)    B (poner/quitar bandera)    S (salir)\n");
		printf("\n\t\tIngresa comando: ");
		scanf("%c",&comando);
		setbuf(stdin, NULL);
						
		if(comando == 'l' || comando == 'L' || comando == 'B' || comando == 'b') 
		{
			printf("Ingresa la fila y la columna (ejemplo 1,A (Fila 1, columna 1)): ");
			scanf("%hd,%c%*c",&j,&columnaUsuario);

			//Verifica las coordeanadas ingresadas.
			if(j > 0 && j<=columnas && columnaUsuario-65 >= 0 && columnaUsuario-65 < filas)
			{
				if(comando == 'l' || comando == 'L')
				{
					if(numerosTableros[(filas*(j-1))+(columnaUsuario-65)] == '0' && tableroJugador[(filas*(j-1))+(columnaUsuario-65)] != 'P')
					{
						CLEAR();
						
						for(i=0; i<filas*columnas; i++)
							if( *(numerosTableros+i) == '0')
								*(numerosTableros+i) = 207;
						
						printf("\n\n\n");
						generarTablero(filas, columnas, numerosTableros);				
						printf("\n\t\tPERDISTE.");
						printf("\n\nTurno: %2hd\tMinas: %2hd",turno, minas);
						printf("\t%cltima coordenada ingresada: %hd,%c\n\n",233,j,columnaUsuario);
						
						getchar();
						comando = 's';	
					}
					
					else if(tableroJugador[(filas*(j-1))+(columnaUsuario-65)] != 'P')//'P' bandera.	
					{
						tableroJugador[(filas*(j-1))+(columnaUsuario-65)] = numerosTableros[(filas*(j-1))+(columnaUsuario-65)];					
						
						i=0;
						while( ((filas*(j-1))+(columnaUsuario-65)+i) < (filas*columnas) - 1)
						{
							++i;
							if(numerosTableros[(filas*(j-1))+(columnaUsuario-65)+i] == ' ')
								tableroJugador[(filas*(j-1))+(columnaUsuario-65)+i] = ' ';
								
							else break;	
						}
						
						if(numerosTableros[(filas*(j-1))+(columnaUsuario-65)+i] != '0' && numerosTableros[(filas*(j-1))+(columnaUsuario-65)+i-1] == ' ')
							tableroJugador[(filas*(j-1))+(columnaUsuario-65)+i] = numerosTableros[(filas*(j-1))+(columnaUsuario-65)+i];
				
						i=0;
						while( ((filas*(j-1))+(columnaUsuario-65)+i) >= 1)
						{
							++i;
							if(numerosTableros[(filas*(j-1))+(columnaUsuario-65)-i] == ' ')
								tableroJugador[(filas*(j-1))+(columnaUsuario-65)-i] = ' ';
								
							else break;
						}
					
						if(numerosTableros[(filas*(j-1))+(columnaUsuario-65)-i] != '0' && numerosTableros[(filas*(j-1))+(columnaUsuario-65)-i+1] == ' ')
							tableroJugador[(filas*(j-1))+(columnaUsuario-65)-i] = numerosTableros[(filas*(j-1))+(columnaUsuario-65)-i];
						
					}
				}
				
				else if( comando == 'b' || comando == 'b')
				{
					if( (tableroJugador[(filas*(j-1))+(columnaUsuario-65)] != 'P') && banderas)	
					{
						tableroJugador[(filas*(j-1))+(columnaUsuario-65)] = 'P';
						--banderas;
					}
					
					else if(tableroJugador[(filas*(j-1))+(columnaUsuario-65)] == 'P')
					{
						tableroJugador[(filas*(j-1))+(columnaUsuario-65)] = 219;
						++banderas;
					}
				
				}
				
				for(i=0; i<filas*columnas; i++)
					if(tableroJugador[i] == 'P' && numerosTableros[i] == '0')
						++ganar;
			}
			
			else
			{
				printf("\t\t\t\tFuera del rango.");
				getchar();
				turno--;
			}
		}
				
		else turno--;	
		
		if(ganar == minas)
			comando = 's';
		
	}while(comando != 's' && comando!= 'S');
	
	if(ganar == minas)
	{
		CLEAR();
		printf("\n\t\t    %cFelicidades!, Has ganado\tTurno: %2hd\tMinas: %2hd\n\n",173,turno, minas);

		for(i=0; i<filas*columnas; i++)
			if( *(numerosTableros+i) == '0')
				*(numerosTableros+i) = 207;
				
		generarTablero(filas, columnas, numerosTableros);	
		getch();
	}
}

void generarTablero(short int filas, short int columnas, char *tableroJugador)
{
	short int i, j, k, l = 0, m = 1;
	char letra = 'A';
	
	printf("\t\t");
	for(i=0; i<filas; i++)
		printf("  %c ",letra+i);
		
	printf("\n\n\t\t%c",201); //Esquina superior derecha.
	
	for(i=0; i<filas; i++)
		printf("%c%c%c%c",205,205,205,203);

	printf("\b%c\n",187); //Esquina superior izquierda.
		
	for(j=0; j<columnas; j++)
	{
		printf("\t%hd\t",m++);
		for(k=0; k<filas; k++)
		{
			if(tableroJugador[l] == 'P')
			{
				printf("%c%c%c ",186,179,223);
				tableroJugador[l++];
			}			
			else printf("%c %c ",186, tableroJugador[l++]);			
		}
			
		printf("%c\n\t\t%c",186,204);

		if( j<columnas-1 )
		{
			for(i=0; i<filas; i++)
				printf("%c%c%c%c",205,205,205,206);	
			
			printf("\b%c\n",185);			
		}
		
		else
		{
			printf("\b%c",200); //Esquina inferior derecha.
		
			for(i=0; i<filas; i++)
				printf("%c%c%c%c",205,205,205,202);	
				
			printf("\b%c\n",188); //Esquina inferior izquierda.				
		}
	}
}

void colocarIndicador(char *numerosTableros, short int posicionDeMina, short int posicionIndicador)
{
	if(	*(numerosTableros + posicionDeMina - posicionIndicador) == 32)
		*(numerosTableros + posicionDeMina - posicionIndicador) = '1';
	
	else if( *(numerosTableros + posicionDeMina - posicionIndicador) == '1')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '2';
		
	else if(*(numerosTableros + posicionDeMina - posicionIndicador) == '2')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '3';	
		
	else if( *(numerosTableros + posicionDeMina - posicionIndicador) == '3')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '4';
		
	else if(*(numerosTableros + posicionDeMina - posicionIndicador) == '4')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '5';	
		
	else if( *(numerosTableros + posicionDeMina - posicionIndicador) == '5')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '6';
		
	else if(*(numerosTableros + posicionDeMina - posicionIndicador) == '6')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '7';	
		
	else if(*(numerosTableros + posicionDeMina - posicionIndicador) == '7')
		*(numerosTableros + posicionDeMina - posicionIndicador) = '8';
}
