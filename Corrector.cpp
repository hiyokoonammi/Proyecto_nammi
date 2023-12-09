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
	char linea[900000];
	char palabra[TAMTOKEN];
	char fraselimpia[900000];
	char fraselimpia2[900000];
	int i,n, b, h, posicion;
	char blanco = ' ';
	int iContador, iLongCadena, iNumPalabras, prov2;
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
				if(!(linea[i] == '\t' || linea[i] == '\n' || linea[i] == ',' || linea[i] == ';' || linea[i] == '(' || linea[i] == ')' || linea[i] == '13'))
				{ 
					//printf("%c", linea[i]);
					fraselimpia[n] = linea[i];
					n++;
				//	printf("%c", fraselimpia[n]);
				}
			}
			fraselimpia[n] = '\0';
			printf("\nFrase sin caracteres final: %s\n", fraselimpia);
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
	/*for (i = 0; i < iNumPalabras; i++) {
		printf("\n pp: %s %i", palabras[i], estadistica[i]);
	}
	printf("\nElementos: %i", iNumPalabras);*/
	/*************************************************************************************/
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

				prov2 = estadistica[posicion];
				estadistica[posicion] = estadistica[posicion + 1];
				estadistica[posicion + 1] = prov2;
			}
		}
	}
	/*for (i = 0; i < iNumPalabras; i++) {
		//printf("\n pp: %s", palabras[i]);
	}*/
	/***********************************************************************************/
	for (i = 0; i < iNumPalabras; i++)
	{
		strcpy_s(szPalabras[i], TAMTOKEN, palabras[i]);
		iEstadisticas[i] = estadistica[i];

	}
	iNumElementos = iNumPalabras;
	/*for (i = 0; i < iNumElementos; i++) {
	//	printf("\n ppp: %s %i", szPalabras[i], iEstadisticas[i]);
	}
	//	printf("\nElementos dicc: %i", iNumElementos);*/
	
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
	int i, b,k;
	char list[3300][TAMTOKEN], prov2[2][TAMTOKEN];
	int peso[3300];
	int total, prov, posicion;

	b = 0;
	total = 0;

	//guardar solo las que estan en las clonas y diccionario
	for (i = 0; i < iNumSugeridas; i++)
	{
		for (k = 0; k < iNumElementos; k++)
		{
			if (strcmp(szPalabrasSugeridas[i], szPalabras[k]) == 0)
			{
				strcpy_s(list[b], TAMTOKEN, szPalabras[k]);
				peso[b] = iEstadisticas[k];
				b++;
				total++;
			}
			else
			{
			}
		}
	}
	//printf("\ntotal: %i", total);
	/*for (i = 0; i < total; i++) {
		printf("\n listafinal: %s %i", list[i], peso[i]);
	}*/
	//acomodar por mayor peso
	for (i = 0; i < total; i++)
	{
		for (posicion = i + 1; posicion < total; posicion++)
		{
			if (peso[i] < peso[posicion])
			{
				//cambio de posicion
				strcpy_s(prov2[0], TAMTOKEN, list[posicion]);
				strcpy_s(list[posicion], TAMTOKEN, list[i]);
				strcpy_s(list[i], TAMTOKEN, prov2[0]);

				prov = peso[posicion];
				peso[posicion] = peso[i];
				peso[i] = prov;
			}
		}
	}

	/*for (i = 0; i < total; i++) {
		printf("\n listafinal: %s %i", list[i], peso[i]);
	}*/
	//pasar a oficial
	for (i = 0; i < total; i++)
	{
		strcpy_s(szListaFinal[i], TAMTOKEN, list[i]);
		iPeso[i] = peso[i];

	}
	iNumLista = total;
	/*for (i = 0; i < iNumLista; i++) {
		printf("\n listafinal: %s %i", szListaFinal[i], iPeso[i]);
	}*/

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
	char sug[95000][TAMTOKEN];
	int i, b, k;
	int longi;
	char abc[32] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n',164,'o','p','q','r','s','t','u','v','w','x','y','z',160, 130, 161 , 162, 163};
	char prov;
	int posicion;
	char prov2[2][TAMTOKEN];

	strcpy_s(sug[0], TAMTOKEN, szPalabraLeida);
	iNumSugeridas = 1;
	longi = strlen(szPalabraLeida);

	for (i = 0; i < longi; i++) //elima caracteres
	{
		strcpy_s(szPalabraLeida, TAMTOKEN, sug[0]);
		for (b = i; b < longi; b++)
		{
			szPalabraLeida[b] = szPalabraLeida[b+1];
		}
		strcpy_s(sug[i + 1], TAMTOKEN, szPalabraLeida);
		iNumSugeridas++;
	}
	// Transponer pares de caracteres y almacenar las nuevas sugerencias
	for (i = 0; i < longi; i++)
	{
		strcpy_s(szPalabraLeida, TAMTOKEN, sug[0]);

			prov = szPalabraLeida[i];
			szPalabraLeida[i] = szPalabraLeida[i + 1];
			szPalabraLeida[i + 1] = prov;
	
		strcpy_s(sug[longi + i + 1], TAMTOKEN, szPalabraLeida);
		iNumSugeridas++;
	}

	//Cambiar caracter por abecedario
	b = longi+longi;
	for (i = 0; i < longi; i++)
	{
		strcpy_s(szPalabraLeida, TAMTOKEN, sug[0]);
		for (k = 0; k < 32; k++) 
		{
			szPalabraLeida[i] = abc[k];
			strcpy_s(sug[++b], TAMTOKEN, szPalabraLeida);
			iNumSugeridas++;
		}
	}

	//palabras repetidas
	for (i = 0; i < iNumSugeridas - 1; i++)
	{
		for (k = i + 1; k < iNumSugeridas;)
		{
			if (strcmp(sug[i], sug[k]) == 0)
			{
				// Eliminar elemento duplicado
				for (b = k; b < iNumSugeridas - 1; b++)
				{
					strcpy_s(sug[b], TAMTOKEN, sug[b + 1]);

				}
				(iNumSugeridas)--;

			}
			else {
				k++;
			}
		}
	}
	//acomodar abc
	for (i = 0; i < iNumSugeridas - 1; i++)
	{
		for (posicion = 0; posicion < iNumSugeridas - 1; posicion++)
		{
			if ((strcmp(sug[posicion], sug[posicion + 1])) == 1)
			{
				//cambio de posicion
				strcpy_s(prov2[0], TAMTOKEN, sug[posicion]);
				strcpy_s(sug[posicion], TAMTOKEN, sug[posicion + 1]);
				strcpy_s(sug[posicion + 1], TAMTOKEN, prov2[0]);

			}
		}
	}
	//oasar a lista
	for (i = 0; i < iNumSugeridas; i++)
	{
		strcpy_s(szPalabrasSugeridas[i], TAMTOKEN, sug[i]);
		//printf("\nps: %s", szPalabrasSugeridas[i]);
	}
}
