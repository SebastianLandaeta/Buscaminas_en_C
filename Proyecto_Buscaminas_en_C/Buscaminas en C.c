/*
Estudiante: Sebastián Landaeta
Cédula: 28.240.979
Carrera: Ingeniería Informática
Materia: Técnicas de Programación II
Sección: 1

Un proyecto logrado gracias a Miguel Angel Rosas Ocampos, cuyo código fuente se usó como base para realizar este Buscaminas en C.

Canal de Miguel: https://www.youtube.com/channel/UCA0OK6M_H7HgqwzckPeNMyg
Perfil de Github de Miguel: https://github.com/MiguelAngelRosasOcampo
Código fuente original: https://github.com/MiguelAngelRosasOcampo/Buscaminas/blob/main/buscaminas.c
*/

//Librerías a utilizar.
#include <stdio.h>
#include <stdlib.h>

#define CLEAR() system("cls") //Si desea compilar en un sistema operativo UNIX, cambie "system("cls")" por "system("clear")" 

void configuracion_del_juego(); //Permite al jugador elegir la dificultad, y se configurará el juego en función de eso.
void colocar_indicador(char*, short int, short int); //Coloca en un bloque el número de minas que hay a su alrededor.
void juego(char*, char*, short int, short int, short int); //Contiene todo lo referente al gameplay.
void generar_tablero(char*, short int, short int); //Como su nombre lo indica, genera el tablero de juego.

int main() //Función principal
{
        char opcion; //"opcion" almacenará la opción del menú que elija el jugador.
	srand(time(NULL)); //Semilla.
	
	do
	{
		CLEAR(); //Limpiar pantalla.
		
		//Interfaz de usuario
		printf("########  ##     ##  ######   ######     ###    ##     ## #### ##    ##    ###     ######\n");
                printf("##     ## ##     ## ##    ## ##    ##   ## ##   ###   ###  ##  ###   ##   ## ##   ##    ##\n");
                printf("##     ## ##     ## ##       ##        ##   ##  #### ####  ##  ####  ##  ##   ##  ##\n");
                printf("########  ##     ##  ######  ##       ##     ## ## ### ##  ##  ## ## ## ##     ##  ######\n");
                printf("##     ## ##     ##       ## ##       ######### ##     ##  ##  ##  #### #########       ##\n");
                printf("##     ## ##     ## ##    ## ##    ## ##     ## ##     ##  ##  ##   ### ##     ## ##    ##\n");
                printf("########   #######   ######   ######  ##     ## ##     ## #### ##    ## ##     ##  ######\n\n");
		
		printf("j) Jugar.\n");
		printf("s) Salir.\n\n");
		
		printf("Ingrese una opci%cn: ", 162);
		scanf("%c", &opcion);

		if (opcion == 'j' || opcion == 'J')
		{
			configuracion_del_juego(); //Una vez elegida la opción de jugar, se procede a configurar el juego.
		}
		
	} while(opcion != 's' && opcion != 'S'); 
	//Si el jugador inserta un caracter que no está asociado a las opciones disponibles, este bucle le permitirá elegir de nuevo.
	
	return 0;
} //Fin de la función principal.

void configuracion_del_juego() //Comienzo de la función "configuracion_del_juego()".
{
	char *tablero_nm, *tablero_jugador, nivel;
	short int filas, columnas, i, minas, posicion_de_mina;
	
	//"tablero_nm" Es el tablero en el que se van a almacenar las minas y el número de minas que hay a los alrededores de cada bloque.
	//"tablero_jugador" Es el tablero que verá el jugador.
	//"nivel" Es la variable que almacenará la dificultad que escoja el jugador.
	//"filas" y "columnas" Son las variables que almacenarán las dimensiones del tablero.
	//"minas" Almacenará el número de minas que habrá en el tablero.
	//"posicion_de_mina" Almacenará el lugar del tablero en el que se encuentre una mina.
	//"i" Solo es un inicializador para ciclos.
	
	do
	{	
		CLEAR();
		setbuf(stdin, NULL); //Limpiar buffer.
		
		//Elegir dificultad
		printf("a) Nivel principiante: Tablero 8x8 y 10 minas.\n");
		printf("b) Nivel intermedio: Tablero 16x16 y 40 minas (Maximice la pesta%ca).\n", 164);
		printf("c) Nivel experto: Tablero 16x30 y 99 minas (Maximice la pesta%ca).\n\n", 164);
		
		printf("Ingrese una opci%cn: ", 162);
		scanf("%c", &nivel);
	
	} while(nivel != 'a' && nivel != 'A' && nivel != 'b' && nivel != 'B' && nivel != 'c' && nivel != 'C');
	//Si el jugador inserta un caracter que no está asociado a las opciones disponibles, este bucle le permitirá elegir de nuevo.
	
	if (nivel == 'a' || nivel == 'A')
	{
		minas = 2 + (filas = columnas = 8); //Minas y dimensiones del tablero en la dificultad fácil.
	}
	
	else if (nivel == 'b' || nivel == 'B')
	{
		minas = 24 + (filas = columnas = 16); //Minas y dimensiones del tablero en la dificultad intermedio.
	}
		
	else if (nivel == 'c' || nivel == 'C')
	{
		minas = 69 + (columnas = 14 + (filas = 16)); //Minas y dimensiones del tablero en la dificultad experto.
	}
	
	tablero_nm = (char*)malloc(sizeof(char)*filas*columnas); //Se reserva el espacio en memoria que necesitará el vector "tablero_nm".
	
	if (!tablero_nm) //Si no se puede reservar el espacio, el programa se cierra.
	{
		printf("\nNo se ha podido reservar memoria suficiente.");
		exit(-1);
	}
		
	tablero_jugador = (char*)malloc(sizeof(char)*filas*columnas); //Se reserva el espacio en memoria que necesitará el vector "tablero_jugador".
	
	if (!tablero_jugador) //Si no se puede reservar el espacio, el programa se cierra.
	{
		printf("\nNo se ha podido reservar memoria suficiente.");
		exit(-1);
	}
	
	for (i = 0; i < filas*columnas; i++) //LLenar los tableros de espacios.
		*(tablero_jugador + i) = 219;
	
	for (i = 0; i < filas*columnas; i++) //LLenar los tableros de espacios.
		*(tablero_nm + i) = 32;	
		
	for (i = 0; i < minas; i++) //Se llena a "tablero_nm" de minas.
	{
		posicion_de_mina = 0 + rand() % (filas*columnas);

		if (*(tablero_nm + posicion_de_mina) != '0') //Verifica que NO haya una mina ya puesta.
		{
			*(tablero_nm + posicion_de_mina) = '0'; //En esa posición se coloca un '0' (mina).
			
			//En todos estos casos, se llama a la función "colocar_indicador()" para que indique en la tabla el número de minas que habrá alrededor de cada casilla que no contenga mina.
			if ((posicion_de_mina+1)%columnas && *(tablero_nm + (posicion_de_mina+1)) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, -1); //Se manda con - para que sea +		
			
			if (posicion_de_mina%columnas && *(tablero_nm + posicion_de_mina - 1) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, 1);
				
			if (posicion_de_mina<((filas*columnas)-columnas) && *(tablero_nm + (posicion_de_mina + columnas)) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, -columnas);
		
			if (posicion_de_mina>=columnas && *(tablero_nm + (posicion_de_mina - columnas) ) != '0' )
				colocar_indicador(tablero_nm, posicion_de_mina, columnas);					
		
			if (posicion_de_mina<((filas*columnas)-columnas) && (posicion_de_mina+1)%columnas && *(tablero_nm + (posicion_de_mina + columnas + 1)) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, -columnas-1);
				
			if (posicion_de_mina<((filas*columnas)-columnas) && posicion_de_mina%columnas  && *(tablero_nm + (posicion_de_mina + columnas -1)) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, -columnas+1);
		
			if (posicion_de_mina>=columnas && posicion_de_mina%columnas && *(tablero_nm + (posicion_de_mina - columnas - 1)) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, columnas+1);
	
			if (posicion_de_mina>=columnas && (posicion_de_mina+1)%columnas && *(tablero_nm + (posicion_de_mina - columnas + 1)) != '0')
				colocar_indicador(tablero_nm, posicion_de_mina, columnas-1); 
		}	
		else --i; //Si ya había un '0' en esa posición, se vuelve a repetir la iteración.
	}
	
	juego(tablero_nm, tablero_jugador, filas, columnas, minas); //Configurado ya el juego, se procede a jugar.
	
	free(tablero_nm); //Como los tableros son vectores dinámicos, hay que liberar espacio una vez se terminan de usar.
	free(tablero_jugador);	
} //Fin de la función "configuración_de_juego".

void colocar_indicador(char *tablero_nm, short int posicion_de_mina, short int posicion_indicador) //Comienzo de la función "colocar_indicador()". 
{
	if (*(tablero_nm + posicion_de_mina - posicion_indicador) == 32)
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '1';
	}
	else if ( *(tablero_nm + posicion_de_mina - posicion_indicador) == '1')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '2';
	}
	else if (*(tablero_nm + posicion_de_mina - posicion_indicador) == '2')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '3';
	}
	else if(*(tablero_nm + posicion_de_mina - posicion_indicador) == '3')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '4';
	}
	else if(*(tablero_nm + posicion_de_mina - posicion_indicador) == '4')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '5';
	}
	else if (*(tablero_nm + posicion_de_mina - posicion_indicador) == '5')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '6';
	}
	else if (*(tablero_nm + posicion_de_mina - posicion_indicador) == '6')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '7';
	}
	else if (*(tablero_nm + posicion_de_mina - posicion_indicador) == '7')
	{
		*(tablero_nm + posicion_de_mina - posicion_indicador) = '8';
	}
} //Fin de la función "colocar_indicador()". 

void juego(char *tablero_nm, char* tablero_jugador, short int filas, short int columnas, short int minas) //Comienzo de la función "juego()"
{
	char comando, columna_usuario;
	short int i, j, turno = 0, banderas = minas, ganar;
	
	//"comando" Almacenará el comando ingresado por el jugador.
	//Cuando el jugador quiera interactuar con una casilla, la coordenada de la fila y la coordenada de la columna se almacenarán en "j" y "columna_usuario", respectivamente.
	//"turno" Almacenará el turno en el que se encuentre el jugador.
	//"banderas" Almacenará el número de banderás que tendrá el usuario. El número de banderas siempre es igual al número de minas que hay en el tablero.
	//"ganar" Es una variable que se iniciará en "0", y será "1" si el jugador gana la partida.
	//"i" Solo es un inicializador para bucles.
	do
	{
		CLEAR();
		
		ganar = 0;
		printf("\n\tTurno: %3hd    Minas:%3hd    Banderas disponibles:%3hd\n\n", turno++, minas, banderas);
		generar_tablero(tablero_jugador, filas, columnas); //Se llama a la función "generar_tablero" para dibujar el tablero en pantalla.
		
		printf("\n    COMANDOS    L (Abrir casilla)    B (Poner/Quitar bandera)    S (Salir)\n"); //Comandos disponibles al momento de jugar.
		printf("\n\t\tIngrese un comando: ");
		scanf("%c", &comando);
		setbuf(stdin, NULL);
		
		if (comando == 'l' || comando == 'L' || comando == 'B' || comando == 'b') 
		{
			printf("Ingrese la fila y la columna (Ejemplo 1,A): ");
			scanf("%hd,%c%*c", &j, &columna_usuario);
			
			if (columna_usuario >= 97 && columna_usuario <= 122) //Para que "columna_usuario" siempre sea una letra mayúscula, aunque el jugador la escriba en minúscula.
			{
				columna_usuario -= 32;
			}
			
			if (j > 0 && j <= filas && columna_usuario-65 >= 0 && columna_usuario-65 < columnas) //Verifica las coordenadas ingresadas.
			{
				if (comando == 'l' || comando == 'L') //Si el jugador decidió abrir una casilla...
				{
					if (tablero_nm[(columnas*(j-1))+(columna_usuario-65)] == '0' && tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] != 'P') //Si en la coordenada que escribió el usuario hay una mína y no hay bandera...
					{
						CLEAR();
						
						for (i = 0; i < filas*columnas; i++) //Revisa los lugares del tablero en el que hay minas '0' y las cambia por el caracter '¤', el cual se mostrará para indicar en dónde estaban las minas.
						{
							if (*(tablero_nm+i) == '0')
							{
								*(tablero_nm+i) = 207;
							}
					        }
					    
						printf("\n\n\n");
						generar_tablero(tablero_nm, filas, columnas); //Se genera el tablero con los lugares en donde estaban las minas.
						printf("\n\t\tHa perdido."); //Si el jugador pierde, el programa lo indicará, y mostrará el turno en el que perdió, las minas que habían, y la última coordenada ingresada.
						printf("\n\nTurno: %2hd\tMinas: %2hd", turno, minas);
						printf("\t%cltima coordenada ingresada: %hd,%c\n\n", 233, j, columna_usuario);
						
						getchar(); //Finalmente, el programa esperará que el jugador presione una tecla para regresarlo al menú.
						comando = 's';	
					}
					
					else if (tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] != 'P') //Si en la coordenada que escribió el usuario no hay una mina y tampoco una bandera...
					{
						tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] = tablero_nm[(columnas*(j-1))+(columna_usuario-65)]; //Se le mostrará al jugador lo que hay en la casilla que abrió.				
						
						i = 0; //Se inicia un contador.
						
						while( ((columnas*(j-1))+(columna_usuario-65)+i) < (filas*columnas) - 1) //Mientras la posición que ingresó el usuario sea menor que el número de posiciones que hay en toda la tabla...
						{
							++i; //Se incrementa el contador para que empiece en la posición siguiente a la ingresada por el usuario
							if (tablero_nm[(columnas*(j-1))+(columna_usuario-65)+i] == ' ')//Si en la posicion ingresada por el usuario +i, del tablero de los numeros y minas, hay un espacio vacio...
							{
							    tablero_jugador[(columnas*(j-1))+(columna_usuario-65)+i] = ' '; //Se le mostrará al usuario ese espacio vacío.
							}		
							else break;	
						}
						
						if (tablero_nm[(columnas*(j-1))+(columna_usuario-65)+i] != '0' && tablero_nm[(columnas*(j-1))+(columna_usuario-65)+i-1] == ' ') //Si en la posición ingresada por el usuario +i, del tablero de los números y minas, no hay mina y en la posición anterior a esa hay un espacio vacío...
							tablero_jugador[(columnas*(j-1))+(columna_usuario-65)+i] = tablero_nm[(columnas*(j-1))+(columna_usuario-65)+i]; //Al jugador se le mostrará ese espacio vacio
				        
						i = 0; //El contador se reinicia
						while (((columnas*(j-1))+(columna_usuario-65)+i) >= 1) //Mientras la posición ingresada por el usuario +i sea mayor o igual a 1...
						{
							++i; //Se incrementa el contador para que empiece en la posición siguiente a la ingresada por el usuario.
							if (tablero_nm[(columnas*(j-1))+(columna_usuario-65)-i] == ' ') //Si en esa posición hay un espacio vacío...
							{ 
								tablero_jugador[(columnas*(j-1))+(columna_usuario-65)-i] = ' '; //Se le mostrará al jugador ese espacio vacío.
						        }
							else break;
						}
					
						if (tablero_nm[(columnas*(j-1))+(columna_usuario-65)-i] != '0' && tablero_nm[(columnas*(j-1))+(columna_usuario-65)-i+1] == ' ') //Si en la posición anterior a la ingresa por el usuario +i no hay una mina y en la posición siguiente hay un espacio vacío...
						{
							tablero_jugador[(columnas*(j-1))+(columna_usuario-65)-i] = tablero_nm[(columnas*(j-1))+(columna_usuario-65)-i]; //Se le muestra al usuario ese espacio vacío.
						}
					}
				}
				else if (comando == 'b' || comando == 'b') //Si el jugador decidió colocar o quitar una bandera...
				{
					if ((tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] != 'P') && banderas) //Si en la posición que ingresó el usuario no hay una bandera..
					{
						tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] = 'P'; //Se coloca la bandera y se decrementa el número de banderas totales que hay.
						--banderas;
					}
					else if(tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] == 'P') //Si en la posición que ingresaste ya hay una bandera...
					{
						tablero_jugador[(columnas*(j-1))+(columna_usuario-65)] = 219; //La quita y se incrementa el número de banderas total.
						++banderas;
					}
				}
				
				for (i = 0; i < filas*columnas; i++) //Despues de cada iteración, se revisará el tablero para ver si el jugador ya ganó, y de ser así, la variable "ganas" pasa a ser "1" y se muestra el mensaje de victoria.
				{
					if (tablero_jugador[i] == 'P' && tablero_nm[i] == '0')
					{
						++ganar;
					}
				}
			}
			else //Estas instrucciones se ejecutan si el jugador inserta coordenadas no válidas.
			{
				printf("\t\t\t\tFuera del rango.");
				getchar();
				turno--;
			}
		}	
		else 
		{
			turno--;
		}	
		
		if (ganar == minas)
		{
			comando = 's';
		}
	} while (comando != 's' && comando!= 'S');
	
	if (ganar == minas) //Mensaje de victoria.
	{
		CLEAR();
		printf("\n\t\t    %cFelicidades!, Ha ganado\tTurno: %2hd\tMinas: %2hd\n\n", 173, turno, minas);

		for (i = 0; i < filas*columnas; i++)
		{
			if (*(tablero_nm+i) == '0')
			{
				*(tablero_nm+i) = 207;
			}
		}
			
		generar_tablero(tablero_nm, filas, columnas); //Finalmente, cuando el jugador gana se le muestra el tablero con las minas y se espera a que presione una tecla para regresarlo al menú.
		getch();
	}
} //Fin de la función "juego()".

void generar_tablero(char *tablero_jugador, short int filas, short int columnas) //Conmienzo de la función "generar_tablero()".
{
	short int i, j, k, l = 0, m = 1;
	char letra = 'A';
	
	//En esta función no hay mucho que destacar en cuanto a variables, porque casi todas son contadores o inicializadores de bucles.
	//Sin embargo, se puede destacar la variable "letra", la cual empezará en "A" y sirve para colocar las letras que representarán a cada columna en la tabla que verá el usuario.
	
	printf("\t\t");
	
	for (i = 0; i < columnas; i++)
	{ 
		printf("  %c ", letra+i);
	}
	
	printf("\n\n\t\t%c", 201); //Esquina superior izquierda
	
	for (i = 0; i < columnas; i++)
	{
		printf("%c%c%c%c", 205, 205, 205, 203);
	}
	
	printf("\b%c\n", 187); //Esquina superior derecha
	
	for (j = 0; j < filas; j++)
	{
		printf("\t%hd\t", m++);
		
		for (k = 0; k < columnas; k++)
		{
			if (tablero_jugador[l] == 'P')
			{
				printf("%c%c%c ", 186, 179, 223);
				tablero_jugador[l++];
			}
			else
			{
				printf("%c %c ", 186, tablero_jugador[l++]);
			}			
		}
		
		printf("%c\n\t\t%c", 186, 204);

		if (j < filas-1)
		{
			for (i = 0; i < columnas; i++)
			{
				printf("%c%c%c%c", 205, 205, 205, 206);
			}
			
			printf("\b%c\n", 185);
		}
		else
		{
			printf("\b%c", 200); //Esquina inferior izquierda.
		
			for (i = 0; i < columnas; i++)
			{
				printf("%c%c%c%c", 205, 205, 205, 202);
			}
			
			printf("\b%c\n", 188); //Esquina inferior derecha.
		}
	}
} //Fin de la función "generar_tablero()".
