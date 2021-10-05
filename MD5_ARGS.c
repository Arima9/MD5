#include <stdio.h>
#include <stdlib.h>

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
	buff32bit one = 0x80, full = 0xFF, M[16];
	buff32bit cntBits0=0, cntBits1=0, temp;
	buff32bit A,B,C,D,AA,BB,CC,DD;
	unsigned char cicl=0, i = 0, j = 0, k = 0, letra=0, nBloques;
	FILE *Archivo;
	//Creacion del array de corrimientos S
	unsigned char S[] = {7, 12, 17, 22, 
		             5,  9, 14, 20,
			     4, 11, 16, 23,
			     6, 10, 15, 21};
	//Creacion del array de K
	buff32bit K[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	 /*------------Lectura del archivo------------*/
	char *let = argv[1]; //Asignacion de puntero
	char ruta[50]={"./"}; //Array donde se guarda la ruta del archivo

	//Organizacion de la ruta relativa
	i = 2;
	while (*let != '\0'){
		ruta[i] = *let;
		i++;
		let++;
	}
	ruta[i] = '\0';
	Archivo = fopen(ruta, "r");
	/*
	//Se imprime la ruta que se obtiene
	printf("La ruta queda: %s\n", ruta);
	*/

	//Se asignan los valores iniciales al buffer
	A = 0x01234567;
	B = 0x89ABCDEF;
	C = 0xFEDCBA98;
	D = 0x76543210;

	/*
	 * Este bloque de codigo se encarga de leer el archivo y pasarlo a un
	 * array de registros de 32 bits llamado M para cada bloque.
	 */

	for(; k <= nBloques; k++){
	//Paso de informacion del archivo al bloque M
	for (i=0; i < 16; i++) M[i] = 0;
	for (i = 0; i < 16 && letra != 0XFF; i++){
			for (j = 0; j < 4; j++){
				letra = fgetc(Archivo);
				if (letra != 0xFF){
					M[i] = M[i] | ((buff32bit)(letra)<<(8*j));
					if (cntBits0 == 0xFFFFFFF8){
						cntBits0 += 8;
						cntBits1 += 1;
					}
					else cntBits0 += 8;
				}
				else {
					M[i] = M[i]|(one<<(8*j));
					break;
				}
			}
			if (letra == 0XFF) break;
	}
	
	//Si el bloque de codigo anterior abarca mas de 448 bits entonces
	//aumenta el contador de bloques M en uno
	if (i >= 14) nBloques++;
	//Ingreso del tamaño del mensaje
	if ((letra == 0XFF) && (i < 14)){
			for (j = 0; j < 4; j++){
				temp = (cntBits0 >> (8*j)) & full;
				M[14] = M[14] | (temp << (8*j));
				
				temp =((cntBits1 >> (8*j)) & full); 
				M[15] = M[15] | (temp << (8*j));
			}
	} 
	/*
	//Estas lineas de codigo sirven para desplegar los bloques M de cada
	//iteracion.
	printf("----------Impresion del bloque M%d----------\n", k+1);

	for (cicl=0; cicl < 16; cicl++){
		printf("0x%8lx\n", M[cicl]);
	}
	*/

	
	}
	//fin de las 64 iteraciones para cada bloque

	


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

