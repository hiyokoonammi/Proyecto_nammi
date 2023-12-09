/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 0

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{
	FILE* fpDicc;
	char linea[800000];
	char palabra[TAMTOKEN];
	char fraselimpia[800000];
	char fraselimpia2[800000];
	int i,n, b, h, posicion;
	char blanco = ' ';
	int iContador, iLongCadena, iNumPalabras;
	int estadistica[NUMPALABRAS];
	char palabras[NUMPALABRAS][TAMTOKEN];
	char prov[2][TAMTOKEN];

	iNumElementos = 0;

	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);
	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{
		if (DEPURAR == 1)
			printf("\nSi lo pude abrir");
		n = 0;
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			_strlwr(linea);
			if (DEPURAR == 1) {
				printf("\nFrase con caracteres esp: %s\n", linea);}
			for (i = 0; i < strlen(linea); i++)
			{
				//quitar caracteres especiales, dejar solo punto para los punto y aparte
				if(linea[i] == 'a' || linea[i] == 'b' || linea[i] == 'c' || linea[i] == 'd' || linea[i] == 'e' || linea[i] == 'f' || linea[i] == 'g' || linea[i] == 'h' || linea[i] == 'i' || linea[i] == 'j' || linea[i] == 'k' || linea[i] == 'l' || linea[i] == 'm' || linea[i] == 'n' || linea[i] == 164 || linea[i] == 'o' || linea[i] == 'p' || linea[i] == 'q' || linea[i] == 'r' || linea[i] == 's' || linea[i] == 't' || linea[i] == 'u' || linea[i] == 'v' || linea[i] == 'w' || linea[i] == 'x' || linea[i] == 'y' || linea[i] == 'z' || linea[i] == '�' || linea[i] == '�' || linea[i] == '�' || linea[i] == '�' || linea[i] == '�' || linea[i] == 129 || linea[i] == ' ' || linea[i] == '.')
				{ 
					//printf("%c", linea[i]);
					fraselimpia[n] = linea[i];
					n++;
				//	printf("%c", fraselimpia[n]);
				}
			}
			fraselimpia[n] = '\0';
		//	printf("\nFrase sin caracteres final: %s\n", fraselimpia);
		}
	n = 0;
	for(i = 0; i < strlen(fraselimpia); i++)
	{
		if (fraselimpia[i] == '.')
		{
			fraselimpia2[n] = ' ';
			n++;
		}
		else 
		{
			fraselimpia2[n] = fraselimpia[i];
			n++;
		}
	}
	fraselimpia2[n] = '\0';
	printf("\n%s\n", fraselimpia2);
	/*********************************************************************/
	iLongCadena = strlen(fraselimpia2);
	if(fraselimpia2[0] == blanco)
	{	iNumPalabras = 0; }
	else 	{		iNumPalabras = 1;	}
	iContador = 0;
	i = 0;
	b = 0;
	while(fraselimpia2[iContador] != '\0')
	{
		if(fraselimpia2[iContador] == blanco || fraselimpia2[iContador] == '\0')
		{
			iContador++;
			if (fraselimpia2[iContador] != '\0' && fraselimpia2[iContador] != blanco)
			{
				palabra[i] = '\0';
				strcpy_s(palabras[b], 50, palabra);
				estadistica[b] = 1;
			//	printf("\np: %s", palabras[b]);
			//	printf("\tp: %i", estadistica[b]);
				b++;
				i = 0;
				for (h = 0; h < strlen(palabra); h++)
				{
					palabra[h] = ' ';
				}
				iNumPalabras++;
			}
		}
		else
		{
			palabra[i] = fraselimpia2[iContador];
			iContador++;
			i++;
		}
	}
	palabra[i] = '\0';
	strcpy_s(palabras[b], 50, palabra);
	estadistica[b] = 1;
	//printf("\n p: %s", palabras[b]);
	//printf("\tp: %i", estadistica[b]);

	//printf("\ntotal palabras: %i\n", iNumPalabras);
	/**********************************************************************************/
	/*Acomodar las palabras por abecedario*/
	for (i = 0; i < iNumPalabras - 1; i++)
	{
		for (posicion = 0; posicion < iNumPalabras - 1; posicion++)
		{
			if ((strcmp(palabras[posicion], palabras[posicion + 1])) == 1)
			{
				//cambio de posicion
				strcpy_s(prov[0], TAMTOKEN, palabras[posicion]);
				strcpy_s(palabras[posicion], TAMTOKEN, palabras[posicion + 1]);
				strcpy_s(palabras[posicion + 1], TAMTOKEN, prov[0]);

			}
		}
	}
	for (i = 0; i < iNumPalabras; i++) {
		//printf("\n pp: %s", palabras[i]);
	}
	/*************************************************************************************/
		//palabras repetidas
	for (i = 0; i < iNumPalabras - 1; i++) 
	{
		for (h = i + 1; h < iNumPalabras;) 
		{
			if (strcmp(palabras[i], palabras[h]) == 0) 
			{
				estadistica[i] = estadistica[i] + 1;
				// Eliminar elemento duplicado
				for (b = h; b < iNumPalabras - 1; b++)
				{
					strcpy_s(palabras[b], TAMTOKEN, palabras[b + 1]);

				}
				(iNumPalabras)--;

			}
			else {
				h++;
			}
		}
	}
	for (i = 0; i < iNumPalabras; i++) {
		printf("\n pp: %s %i", palabras[i],estadistica[i]);
	}
	printf("\nElementos: %i", iNumPalabras);

	/***********************************************************************************/
	/*Pasar la informacion de palabras y estaditisca a las cadenas finales*/
	for (i = 0; i < iNumPalabras; i++)
	{
		strcpy_s(szPalabras[i], TAMTOKEN, palabras[i]);
		iEstadisticas[i] = estadistica[i];

	}
	iNumElementos = iNumPalabras;;
	for (i = 0; i < iNumElementos; i++) {
		printf("\n ppp: %s %i", szPalabras[i], iEstadisticas[i]);
	}
	printf("\nElementos dicc: %i", iNumElementos);
	
	fclose(fpDicc);
	}
	else
	{
		if (DEPURAR == 1)
			printf("\nNo lo pude abrir");
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c�digo
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
