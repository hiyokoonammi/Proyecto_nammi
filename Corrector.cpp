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
				if(linea[i] == 'a' || linea[i] == 'b' || linea[i] == 'c' || linea[i] == 'd' || linea[i] == 'e' || linea[i] == 'f' || linea[i] == 'g' || linea[i] == 'h' || linea[i] == 'i' || linea[i] == 'j' || linea[i] == 'k' || linea[i] == 'l' || linea[i] == 'm' || linea[i] == 'n' || linea[i] == 164 || linea[i] == 'o' || linea[i] == 'p' || linea[i] == 'q' || linea[i] == 'r' || linea[i] == 's' || linea[i] == 't' || linea[i] == 'u' || linea[i] == 'v' || linea[i] == 'w' || linea[i] == 'x' || linea[i] == 'y' || linea[i] == 'z' || linea[i] == 'á' || linea[i] == 'é' || linea[i] == 'í' || linea[i] == 'ó' || linea[i] == 'ú' || linea[i] == 129 || linea[i] == ' ' || linea[i] == '.')
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
 
	//Sustituya estas lineas por su código
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
	//Sustituya estas lineas por su código
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
