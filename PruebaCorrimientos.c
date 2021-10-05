#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define CORRIMIENTO_IZQ(num, cantidad) (((num) << (cantidad)) | ((num) >> (32 - (cantidad))))
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

typedef unsigned long int buff32bit;

buff32bit A,B,C,D,AA,BB,CC,DD,TEMP=0x0,H0,H1,H2,H3;
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

buff32bit M[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char S[16] = {7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};

int main ()
{

	A = 0x01234567;
	B = 0x89ABCDEF;
	C = 0xFEDCBA98;
	D = 0x76543210;
	H0 = 0x01234567;
	H1 = 0x89ABCDEF;
	H2 = 0xFEDCBA98;
	H3 = 0x76543210;

int l=0, n=0;
for (int i=0;i<4;i++)
	{
		if (n < 16) 
		{
            l = n;
        }
		else if (n < 32)
		{
        	l = (5*n + 1) % 16;
        }
		else if (n < 48)
		{
            l = (3*n + 5) % 16;          
        }
		else 
		{
			l= (7*n) % 16;
		}
		for (int j=0; j<16; j++)
		{
				if (i == 0 ) 
				{
		            TEMP = D;
		            D = C;
		            C = B;
					B = B + CORRIMIENTO_IZQ(((A +F(B,C,D) + M[l] + K [n])),S[j]);
			        A = TEMP;
				}
				else if (i == 1)
				{
		        	TEMP = D;
		            D = C;
		            C = B;
					B = B + CORRIMIENTO_IZQ(((A +G(B,C,D) + M[l] + K [n])),S[j]);
			        A = TEMP;
		        }
				else if (n < 48)
				{
		            TEMP = D;
		            D = C;
		            C = B;
					B = B + CORRIMIENTO_IZQ(((A +H(B,C,D) + M[l] + K [n])),S[j]);
			        A = TEMP;         
		        }
				else 
				{
					TEMP = D;
		            D = C;
		            C = B;
					B = B + CORRIMIENTO_IZQ(((A +I(B,C,D) + M[l] + K [n])),S[j]);
			        A = TEMP;
				}
			n+=1;
			}
	}
	H0+=A;
	H1+=B;
	H2+=C;
	H3+=D;
	system ("pause");
	return 0;
}
