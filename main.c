#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct estudiante {
	int cedula;
	char nombre[30];
	int semestre;
};



struct estudiante *crearBaseDatos(char *nombre, int *numero) 
{
	struct estudiante *baseDatos = malloc(
		(*numero) * sizeof(struct estudiante)); 
											

	FILE *bdArchivos;

	bdArchivos = fopen(nombre, "w");

	if (bdArchivos != NULL) {
		fprintf(bdArchivos, "%d %d\n", *numero, 0);
	} else {
		perror("ERROR AL CREAR BASE DE DATOS \n");
	}

	fclose(bdArchivos);

	return (baseDatos);
}

struct estudiante *cargarBaseDatos(
	char *nombre,
	int *numero,
	int *numeroRegistros,
	char (*arregloDatos)[4][30]) 
{
	struct estudiante *baseDatos;
	strcpy(nombre, (*arregloDatos)[1]);
	FILE *bdArchivos;
	bdArchivos = fopen(nombre, "r");
	if (bdArchivos != NULL) {
		fscanf(bdArchivos, "%d %d", numero, numeroRegistros);
		baseDatos = malloc((*numero) * sizeof(struct estudiante));
		for (int i = 0; i < *numeroRegistros; i++) {
			fscanf(bdArchivos, "%d", &baseDatos[i].cedula);
			fscanf(bdArchivos, "%s", baseDatos[i].nombre);
			fscanf(bdArchivos, "%d", &baseDatos[i].semestre);
		}
	} else {
		perror("EROR AL CARGAR BASE DE DATOS \n");
	}

	fclose(bdArchivos);
	return (baseDatos);
}

void salvarBaseDatos(
	struct estudiante *arregloEstudiante,
	char *nombre,
	int numero,
	int numeroRegistros) 
{
	FILE *bdArchivos;
	bdArchivos = fopen(nombre, "w");
	if (bdArchivos != NULL) {
		fprintf(bdArchivos, "%d %d\n", numero, numeroRegistros);

		for (int i = 0; i < numeroRegistros; i++) {
			fprintf(bdArchivos, "%d\n", arregloEstudiante[i].cedula);
			fprintf(bdArchivos, "%s\n", arregloEstudiante[i].nombre);
			fprintf(bdArchivos, "%d\n", arregloEstudiante[i].semestre);
		}

	} else {
		perror("ERROR AL SALVAR  BASE DE DATOS \n");
	}

	fclose(bdArchivos);
}

void leerTodo(
	struct estudiante *arregloEstudiante,
	int numeroRegistros) 
{
	for (int i = 0; i < numeroRegistros; i++) {
		printf("%d\n", arregloEstudiante[i].cedula);
		printf("%s\n", arregloEstudiante[i].nombre);
		printf("%d\n", arregloEstudiante[i].semestre);
		printf("\n");
	}
}

void leerTamano(int numeroRegistros) 
{
	printf("NUMERO DE REGISTROS EN LA BASE DE DATOS: %d\n", numeroRegistros);
}

void crearRegistro(
	struct estudiante *arregloEstudiante,
	int *numeroRegistros,
	char (*arregloDatos)[4][30])
{
	arregloEstudiante[*numeroRegistros].cedula = atoi((*arregloDatos)[1]);

	strcpy(arregloEstudiante[*numeroRegistros].nombre, (*arregloDatos)[2]);

	arregloEstudiante[*numeroRegistros].semestre = atoi((*arregloDatos)[3]);

	*numeroRegistros += 1;
}

void leerRegistro(
	struct estudiante *arregloEstudiante,
	int numeroRegistros,
	int cedula) 
{
	for (int i = 0; i < numeroRegistros; i++) {
		int temp = (int)arregloEstudiante[i].cedula;
		if (cedula == temp) {
			printf("%d\n", arregloEstudiante[i].cedula);
			printf("%s\n", arregloEstudiante[i].nombre);
			printf("%d\n", arregloEstudiante[i].semestre);
			printf("\n");
			break;
		}
	}
}



struct estudiante *crearBaseDatos(char *nombre, int *numero);
struct estudiante *cargarBaseDatos(
	char *nombre,
	int *numero,
	int *numeroRegistros,
	char (*arregloDatos)[4][30]);
void salvarBaseDatos(
	struct estudiante *arregloEstudiante,
	char *nombre,
	int numero,
	int numeroRegistros);
void leerTodo(struct estudiante *arregloEstudiante, int numeroRegistros);
void leerTamano(int numeroRegistros);
void crearRegistro(
	struct estudiante *arregloEst,
	int *numeroRegistros,
	char (*arregloDatos)[4][30]);
void leerRegistro(
	struct estudiante *arregloEstudiante,
	int numeroRegistros,
	int cedula);

int main() {
	char strComando[30];
	const char splitChar[] = " ";
	char comandoTok[4][30];
	int i = 0;
	struct estudiante *arregloEstudiante;
	int continuar = 0;
	int numeroRegistros = 0;
	char nombreBD[40];
	int numeroBD = 0;

	printf("\b***Bienvenido al sistema para bases de datos***\n");
	printf("\nEstos son los comandos :\n\n");

	while (continuar == 0) {
		printf("\t> mkdb nombre tamaño\n");
		printf("\t> loaddb nombre\n");
		printf("\t> savedb nombre\n");
		printf("\t> readall\n");
		printf("\t> readsize\n");
		printf("\t> mkreg cedula nombre semestre\n");
		printf("\t> readreg cédula\n");
		printf("\t> exit\n\n");

		printf(">");

		i = 0; 

		//
		if (fgets(strComando, 30, stdin)) 
		{
			strComando[strcspn(strComando, "\n")] = 0;
		}

		char *token = strtok(strComando, splitChar);

		if (token != NULL) {
			while (token != NULL) {
				strcpy(comandoTok[i], token);
				token = strtok(NULL, splitChar);
				i++;
			}
		}

		// Condicionales Comandos
		if (strcmp(comandoTok[0], "mkdb") == 0) {
			printf("MKDB CHECK");
			strcpy(nombreBD, comandoTok[1]);
			numeroBD = atoi(comandoTok[2]);
			arregloEstudiante = crearBaseDatos(nombreBD, &numeroBD);

		}

		else if (strcmp(comandoTok[0], "loaddb") == 0) {
			printf("LOADDB CHECK");
			cargarBaseDatos(nombreBD, &numeroBD, &numeroRegistros, &comandoTok);
		}

		else if (strcmp(comandoTok[0], "savedb") == 0) {
			printf("SAVEDB CHECK");
			salvarBaseDatos(
				arregloEstudiante, nombreBD, numeroBD, numeroRegistros);
		}

		else if (strcmp(comandoTok[0], "readall") == 0) {
			printf("READALL CHECK");
			leerTodo(arregloEstudiante, numeroRegistros);
		}

		else if (strcmp(comandoTok[0], "readsize") == 0) {
			printf("READSIZE CHECK");
			leerTamano(numeroRegistros);
		}

		else if (strcmp(comandoTok[0], "mkreg") == 0) {
			printf("MKREG CHECK");
			crearRegistro(arregloEstudiante, &numeroRegistros, &comandoTok);
		}

		else if (strcmp(comandoTok[0], "readreg") == 0) {
			printf("READREG CHECK");
			leerRegistro(
				arregloEstudiante, numeroRegistros, atoi(comandoTok[1]));
		}

		else if (strcmp(comandoTok[0], "exit") == 0) {
			printf(" VUEVA PRONTO");
			continuar = 1;
		}

		else {
			printf("COMANDO INVALIDO");
		}
	}
}