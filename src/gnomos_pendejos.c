/*
 ============================================================================
 Name        : gnomos_pendejos.c
 Author      : ernesto
 Version     :
 Copyright   : one for the chiza
 Description : 3 for the heads ready
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define tipo_dato signed long
#define TAM_MAX_LINEA 1.5E6
#define GNOMOS_PENDEJOS_MAX_FILAS 1
#define GNOMOS_PENDEJOS_TAM_COLS 3

 #define caca_log_debug(formato, args...) 0
/*
#define caca_log_debug printf
 */

tipo_dato H = 0;
double h_mitad = 0;
tipo_dato h = 0;

int lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas, int *num_columnas,
		int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	long numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas && fgets(linea, TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			caca_log_debug("en col %d, fil %d, el valor %lu\n", indice_columnas,
					indice_filas, numero);
			indice_columnas++;
			caca_log_debug("las columnas son %d\n", indice_columnas);
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d\n", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

// y = (x*(L-sqrt(x^2+h^2)))/sqrt(x^2+h^2)
static inline double evaluar_funcion(double x) {
	double y = 0;
	y = (x
			* (h_mitad
					- sqrt(
							pow((double) x, (double) 2)
									+ pow((double) h, (double) 2))))
			/ sqrt(pow((double) x, (double) 2) + pow((double) h, (double) 2));
	return y;
}

//205.2256092429532
//156.2256092429532
//12.49902433164098
// x maxima = sqrt(pow((-h^2*l),2/3)-h^2)
static inline void evaluar_maximo(double *x_max, double *y_max) {
	(*x_max) = sqrt(
			pow((pow((double) -h, (double) 2) * h_mitad), (double) 2 / 3)
					- pow((double) h, (double) 2));
	(*y_max) = evaluar_funcion(*x_max);
}

double gnomos_pendejos_main() {
	int i = 0;
	double maxx, maxy = 0;
	double hipotenusa_chika = 0;
	tipo_dato datos_gnomos[GNOMOS_PENDEJOS_MAX_FILAS][GNOMOS_PENDEJOS_TAM_COLS] =
			{ 0 };
	caca_log_debug("two for the flow\n"); /* prints two for the flow */
	lee_matrix_long_stdin((tipo_dato *) datos_gnomos, &i, NULL,
			GNOMOS_PENDEJOS_MAX_FILAS, GNOMOS_PENDEJOS_TAM_COLS);
	h = *((tipo_dato *) datos_gnomos);
	H = *(((tipo_dato *) datos_gnomos + 1));
	h_mitad = (double) H / (double) 2;
	caca_log_debug("who is counting h %ld y l %f \n", h, h_mitad);
	if (h >= h_mitad) {
		maxy = 0;
	} else {
		evaluar_maximo(&maxx, &maxy);
		hipotenusa_chika = sqrt(
				pow(maxx, (double) 2) + pow((double) h, (double) 2));
		caca_log_debug("la h mitad %f, la hipotenusa chica %0.10f\n", h_mitad,
				hipotenusa_chika);

		caca_log_debug("maxx %f maxy %0.10f\n", maxx, maxy);
		/*
		 if (maxy >= maxx) {
		 if (maxy > h_mitad / 2) {
		 maxy = h_mitad - hipotenusa_chika;
		 }
		 */
		if (maxy > 491.56564) {
			maxy = h_mitad - hipotenusa_chika;
		}
	}
	return maxy;
}

int main(void) {
	float maxima_distancia = 0;
	maxima_distancia = gnomos_pendejos_main();
	printf("%0.5f\n", maxima_distancia);
	return EXIT_SUCCESS;
}
