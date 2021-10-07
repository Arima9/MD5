//Inclusion de archivos de encabezado necesarios
#include <stdio.h>
#include <stdint.h>

/*
 * Programa que calcula la "huella digital" de un archivo por medio del
 * algoritmo de resumen de mensajes MD5 (Message Digest Algorithm 5).
 *
 * TAREA 04 / EQUIPO:
 * Andres Rivera Marquez.
 * Gustavo Alejandro Solorio Ramos.
 * */

//Definicion de las funciones predeterminadas F, G, H e I con define
//para hacer la sustitucion mas facil
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

//Definicion de la funcion de corrimiento izquierdo
#define CORRIMIENTO_IZQ(num, cantidad) ((num << cantidad) | (num >> (32 - cantidad)))

//Uso de un tipo de variable entera sin signo de 32 bits.
typedef uint32_t buff32bit;

//Inicio de la funcion main del programa
int main (int argc, char *argv[]) {
	
	//Creacion de las registros de 32 bits
	buff32bit one = 0x80, full = 0xFF, M[16];
	buff32bit cntBits0 = 0, cntBits1 = 0, temp, nBloques = 0; 
	buff32bit A, B, C, D, AA, BB, CC, DD, H0, H1, H2, H3;

	//Creacion de variables para ciclos
	unsigned char i = 0, j = 0, k, letra = 0; 
	int l = 0, n = 0;

	//Creacion de las variables relacionadas al archivo archivo
	FILE *Archivo; //Puntero al archivo a tratar
	char *let = argv[1]; //Asignacion de puntero
	char ruta[100]={"./"}; //Array donde se guarda la ruta del archivo

	//Creacion de los arreglos de constantes
	unsigned char S[4][4] = {{7, 12, 17, 22}, 
				{5,  9, 14, 20},
				{4, 11, 16, 23},
				{6, 10, 15, 21}};
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

	/*------------Inicio del programa.------------*/

	//Lectura del archivo
	i = 2;
	while (*let != '\0'){
		ruta[i] = *let;
		i++;
		let++;
	}
	//Se aniade el fin de cadena
	ruta[i] = '\0';
	Archivo = fopen(ruta, "r");

	//Inicializacion de los valores iniciales del registro HASH MD5
	H0 = 0x67452301;
	H1 = 0xEFCDAB89;
	H2 = 0x98BADCFE;
	H3 = 0x10325476;


//Ciclo for que repite el proceso de obtencion de hash dependiendo del numero
//de bloques que se obtuvieron
for(k = 0; k <= nBloques; k++){
	
	//Los registros del MD5 se asignan a los buffer A, B, C y D
	A = H0;
	B = H1;
	C = H2;
	D = H3;

	//Se setea el arreglo M a 0 cada inicio del ciclo
	for (i=0; i < 16; i++) M[i] = 0;

	//Ciclo for que recorre las 16 posiciones de los bloques M
	for (i = 0; i < 16 && letra != 0XFF; i++){
		
		//Ciclo for para recorrer los 4 bytes de las words de M
		for (j = 0; j < 4; j++){

			//Se lee el contenido del archivo caracter por caracter
			letra = fgetc(Archivo);

			//Mientras no se detecte el fin del archivo
			if (letra != 0xFF){
				
				//Append de los caracteres del archivo a las
				//words de M, en little endian
				M[i] = M[i] | ((buff32bit)(letra)<<(8*j));	
				
				//Condicional que contara el tamaño
				//del mensaje
				if (cntBits0 == 0xFFFFFFF8){
					cntBits0 = 0;
					cntBits1 += 1;
				}
				else cntBits0 += 8;
			}
			//Si detecta un fin de archivo inyecta el 0x80
			else {
				M[i] = M[i]|(one<<(8*j));
				break;
			}
		}
		//Si se detecto el fin de archivo se sale del ciclo
		if (letra == 0XFF) break;
	}
	
	//Si el bloque de codigo anterior abarca mas de 448 bits entonces
	//aumenta el contador de bloques M en uno
	if (i >= 14) nBloques++;

	//Si se detecto el fin de archivo, y se tienen las ultimas dos lineas
	//disponibles para inyectarle el tamaño del archivo
	if ((letra == 0XFF) && (i < 14)){

		//Ciclo for para recorrer las ultimas 2 words del bloque
		for (j = 0; j < 4; j++){
			
			//Ecuaciones para guardar el tamaño del archivo en el
			//bloque M
			temp = (cntBits0 >> (8*j)) & full;
			M[14] = M[14] | (temp << (8*j));
			
			temp = (cntBits1 >> (8*j)) & full; 
			M[15] = M[15] | (temp << (8*j));
		}
	} 

//Ciclo for utilizado para realizar las 4 vueltas de las operaciones F,G,H y I
for (n = 0, i = 0; i < 4; i++){
	
	//Ciclo for que realizara las 16 vueltas para cada funcion.
	for (j = 0; j < 16; j++, n++){

		//Condicional if que calcula la palabra a utilizar para cada
		//ciclo
		if (n < 16) l = n;
		else if (n < 32) l = (5*n + 1) % 16;
		else if (n < 48) l = (3*n + 5) % 16;          
		else l= (7*n) % 16;

		//Se guardan en registros auxiliares los valores de A,B,C,D
		AA = D;
		CC = B;
		DD = C;
		//Condicional if que determina la funcion que se utilizara
		//en cada vuelta para calcular la nueva B
		if (i == 0 ) BB = B + CORRIMIENTO_IZQ(((A +F(B,C,D) + M[l] + K [n])),S[i][j%4]);
		else if (i == 1) BB = B + CORRIMIENTO_IZQ(((A +G(B,C,D) + M[l] + K [n])),S[i][j%4]);
		else if (i == 2) BB = B + CORRIMIENTO_IZQ(((A +H(B,C,D) + M[l] + K [n])),S[i][j%4]);
		else if (i == 3) BB = B + CORRIMIENTO_IZQ(((A +I(B,C,D) + M[l] + K [n])),S[i][j%4]);

		//Una vez reacomodadas en las variables auxiliares se asignan
		//a los registros originales
		A = AA;
		B = BB;
		C = CC;
		D = DD;
	}
}
	//Una vez terminadas las 64 iteraciones del bloque M actual se le suman
	//los valores calculados de A,B,C y D
	H0+=A;
	H1+=B;
	H2+=C;
	H3+=D;
}

//Una vez terminado el codigo, se cierra el archivo.
fclose(Archivo);

//Fin del algoritmo, inversion del hash a little endian.
A=0;
B=0;
C=0;
D=0;

//Ciclo for para convertir a Big-endian el HASH MD5
for (i=0; i<4; i++){
	A = A | ((H0>>(i*8)) & full)<<(8*(3-i));
	B = B | ((H1>>(i*8)) & full)<<(8*(3-i));
	C = C | ((H2>>(i*8)) & full)<<(8*(3-i));
	D = D | ((H3>>(i*8)) & full)<<(8*(3-i));
}

//Desplegar el valor del hash semejante al md5sum de linux
printf("%x%x%x%x  %s\n", A, B, C, D, argv[1]);

//Fin del programa
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
