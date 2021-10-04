#include <stdio.h>

/*
 * Programa que calcula la "huella digital" de un archivo por medio del
 * algoritmo de resumen de mensajes MD5 (Message Digest Algorithm 5).
 *
 * TAREA 04 / EQUIPO:
 * Andres Rivera Marquez.
 * Gustavo Alejandro Solorio Ramos.
 * */

//Definicion de las funciones predeterminadas F, G, H e I con un define
//para hacer la sustitucion mas facil
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

typedef unsigned long int buff32bit;

int main (int argc, char *argv[])
{
	/*Se deben crear primero todas las variables y arreglos necesarios
	 * para el programa, estructuras de datos, arreglos de constantes,
	 * arreglos para almacenar datos, y las variables temporales donde
	 * se realizaran las operaciones
	 * */

	const char one = 0x80;
	unsigned char i = 0, j = 0;
	unsigned char letra;
	//Creacion de los datos A, B, C, D y sus valores temporales
	buff32bit A,B,C,D,AA,BB,CC,DD;

	//Creacion del bloque de palabras M de tipo _32bitBuff
	buff32bit M[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//Creacion del array de corrimientos S
	unsigned char S[4][4] = {{7, 12, 17, 22},
				 {5, 9, 14, 20},
				 {4, 11, 16, 23},
				 {6, 10, 15, 21}};


	//Creacion de la ruta del archivo
	char *let = argv[1]; //Asignacion de puntero
	char ruta[50]={"./"}; //Array donde se guarda la ruta del archivo

	//Asignacion del nombre para crear la ruta
	i = 2;
	while (*let != NULL){
		ruta[i] = *let;
		i++;
		let++;
	}
	ruta[i] = NULL;
	
	//Se imprime la ruta que se obtiene
	printf("La ruta queda: %s\n", ruta);

	/*
	 * Bloque en trabajo.......
	 * Este bloque comentado se encarga de leer el archivo y pasarlo a un
	 * array de registros de 32 bits llamado M.
	 */
	//Apertura del archivo en modo de solo lectura

	/*Descomentar para seguir trabajando en el
	FILE *Archivo;
	Archivo = fopen(ruta, "r");
	//Paso de informacion del archivo al bloque M
	letra = fgetc(Archivo);
	for (i = 0; i < 14; i++){
		if (letra != -1){
			for (j = 0; j < 4; j++){
				M[i] = M[i] | ((buff32bit)(letra)<<(8*j));
				letra = fgetc(Archivo);
				if (letra == -1) break;
			}
		}
		else break;
		if (letra == -1) break;
	}
	if (letra 
	for (i = 0; i < 14; i++){
		if (letra != -1){
			for (j = 0; j < 4; j++){
				M[i] = M[i] | ((buff32bit)(letra)<<(8*j));
				letra = fgetc(Archivo);
				if (letra == -1) break;
			}
		}
		else break;
		if (letra == -1) break;
	}
	*/

	//Se asignan los valores iniciales al buffer
	A = 0x01234567;
	B = 0x89ABCDEF;
	C = 0xFEDCBA98;
	D = 0x76543210;


/* Se agrega branch de Gustavo */


       	return 0; 
} 
/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html 
 * Local variables: 
 * c-basic-offset: 8 
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */

