/**
*********Autores*********
Caetan Tojeiro Carpente
Alexandre Velo Santorum

**********************************************************************

Copyright (C) 2017  Álex Velo Santórum y Caetán Tojeiro Carpente

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/agpl-3.0.html>

**********************************************************************

**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "prim.h"


void inicializar_semilla () {
	srand(time(NULL));
}

double microsegundos (){/* obtiene la hora del sistema en microsegundos*/
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void prim (matriz m, int nodos, cola *aristas) {
	int min, i, j, k=0;
	int n = nodos;
	arista a;
	int *masProximo = (int *) malloc(nodos*sizeof(int));
	int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
	crear_cola(aristas);
	distanciaMinima[0] = -1;
	for(i = 1; i < nodos; i++) {
		masProximo[i] = 0;
		distanciaMinima[i] = m[i][0];
	}
	while((n-1)>0){
		min = PESO_MAX+1;
		for(j = 1; j < nodos; j++){
			if((0 <= distanciaMinima[j]) && (distanciaMinima[j] < min)){
				min = distanciaMinima[j];
				k = j;
			}
		}
		a.x = masProximo[k];
		a.y = k;
		a.peso = min;
		insertar(a, aristas);
		distanciaMinima[k] = -1;

		for(j=1;j<nodos;j++){
			if(m[j][k] < distanciaMinima[j]){
				distanciaMinima[j] = m[j][k];
				masProximo[j] = k;
			}
		}
		n--;
	}
	free(masProximo);
	free(distanciaMinima);
}

void crear_cola (cola *c){
	c->cabeza = 0;
	c->final = -1;
	c->tamano = 0;
}

int cola_vacia (cola c){
	return (c.tamano == 0);
}

void incrementar (int *k){
	if (++(*k) == TAM_MAX){
		*k = 0;
	}
}

void insertar (tipo_elemento ar, cola *c){
	if(c->tamano == TAM_MAX){
		printf("La cola esta llena. Tam. maximo: %i\n", c->tamano);
		exit(EXIT_FAILURE);
	}
	c->tamano++;
	incrementar(&(c->final));
	c->vector[c->final] = ar; //insertar en cabeza o en final
}

tipo_elemento quitar_primero (cola *c){
	tipo_elemento te;
	if(cola_vacia(*c)){
		printf("La cola esta vacia");
		exit(EXIT_FAILURE);
	}
	c->tamano--;
	te = c->vector[c->cabeza];
	incrementar(&(c->cabeza));
	return te;
}

tipo_elemento primero (cola c){
	tipo_elemento te;
	if(cola_vacia(c)){
		printf("La cola esta vacia");
		exit(EXIT_FAILURE);
	}
	te = c.vector[c.cabeza];
	return te;
}

void mostrar_cola (cola c){
	int i = c.cabeza;
	int peso = 0;
	while(i < c.tamano){
		printf("(%i, %i) ", c.vector[i].x, c.vector[i].y);
		peso += c.vector[i].peso;
		incrementar(&(i));
	}
	printf("\n");
	printf("Peso: %i\n", peso);
}

matriz crear_matriz (int n) {
	int i;
	matriz aux;
	if ((aux = malloc(n*sizeof(int *))) == NULL)
		return NULL;
	for (i=0; i<n; i++)
		if ((aux[i] = malloc(n*sizeof(int))) == NULL)
			return NULL;
	return aux;
}

void inicializar_matriz (matriz m, int n) {
	int i, j;
	for (i=0; i<n; i++)
		for (j=i+1; j<n; j++)
			m[i][j] = rand() % n + 1;
	for (i=0; i<n; i++)
		for (j=0; j<=i; j++)
			if (i==j)
				m[i][j] = 0;
			else
				m[i][j] = m[j][i];
}

void liberar_matriz (matriz m, int n) {
	int i;
	for (i=0; i<n; i++)
		free(m[i]);
	free(m);
}

void testejem1 (){
	matriz m = crear_matriz(5);
	cola *c = (cola *) malloc(sizeof(cola));
	m[0][0] = 0; m[0][1] = 1; m[0][2] = 8; m[0][3] = 4; m[0][4] = 7;
	m[1][0] = 1; m[1][1] = 0; m[1][2] = 2; m[1][3] = 6; m[1][4] = 5;
	m[2][0] = 8; m[2][1] = 2; m[2][2] = 0; m[2][3] = 9; m[2][4] = 5;
	m[3][0] = 4; m[3][1] = 6; m[3][2] = 9; m[3][3] = 0; m[3][4] = 3;
	m[4][0] = 7; m[4][1] = 5; m[4][2] = 5; m[4][3] = 3; m[4][4] = 0;
	prim(m, 5, c);
	mostrar_cola(*c);
	liberar_matriz(m, 5);
	free(c);
}

void testejem2 (){
	matriz m = crear_matriz(4);
	cola *c = (cola *) malloc(sizeof(cola));
	m[0][0] = 0; m[0][1] = 1; m[0][2] = 4; m[0][3] = 7; 
	m[1][0] = 1; m[1][1] = 0; m[1][2] = 2; m[1][3] = 8; 
	m[2][0] = 4; m[2][1] = 2; m[2][2] = 0; m[2][3] = 3; 
	m[3][0] = 7; m[3][1] = 8; m[3][2] = 3; m[3][3] = 0;
	prim(m, 4, c);
	mostrar_cola(*c);
	liberar_matriz(m, 4);
	free(c);
}

void testejem3 (){
	matriz m = crear_matriz(7);
	cola *c = (cola *) malloc(sizeof(cola));
	m[0][0] = 0; m[0][1] = 7; m[0][2] = 99; m[0][3] = 5; m[0][4] = 99; 
	m[0][5] = 99; m[0][6] = 99;
	m[1][0] = 7; m[1][1] = 0; m[1][2] = 8; m[1][3] = 9; m[1][4] = 7; 
	m[1][5] = 99; m[1][6] = 99;
	m[2][0] = 99; m[2][1] = 8; m[2][2] = 0; m[2][3] = 99; m[2][4] = 5; 
	m[2][5] = 99; m[2][6] = 99;
	m[3][0] = 5; m[3][1] = 9; m[3][2] = 99; m[3][3] = 0; m[3][4] = 15; 
	m[3][5] = 6; m[3][6] = 99;
	m[4][0] = 99; m[4][1] = 7; m[4][2] = 5; m[4][3] = 15; m[4][4] = 0; 
	m[4][5] = 8; m[4][6] = 9;
	m[5][0] = 99; m[5][1] = 99; m[5][2] = 99; m[5][3] = 6; m[5][4] = 8; 
	m[5][5] = 0; m[5][6] = 11;
	m[6][0] = 99; m[6][1] = 99; m[6][2] = 99; m[6][3] = 99; m[6][4] = 9; 
	m[6][5] = 11; m[6][6] = 0;
	prim(m, 7, c);
	mostrar_cola(*c);
	liberar_matriz(m, 7);
	free(c);
}

void testrandom (int n){
	matriz m = crear_matriz(n);
	cola *c = (cola *) malloc(sizeof(cola));
	inicializar_matriz(m, n);
	prim(m, n, c);
	mostrar_cola(*c);
	liberar_matriz(m, n);
	free(c);
}	


void pintarTabla (int cont, int n, double t){
	if(cont == 1){
		printf("(*)");
		printf("%12i%18f%20f%20f%20f\n", n, t, t/(pow (n, 1.5)), 
			t/(pow (n, 2)), t/(pow (n,2.3)));
	}else{
		printf("%15i%18f%20f%20f%20f\n", n, t, t/(pow (n, 1.5)), 
			t/(pow (n, 2)), t/(pow (n,2.3)));	
	}
}

void pintarCabeceras (){
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/n^1.5", 
		"t(n)/n^2", "t(n)/n^2.3");
}

void t_ejec (int n){
	int j = 0;
	matriz m = crear_matriz(n);
	cola *c = (cola *) malloc(sizeof(cola));
	int cont_a = 0;
	double t_ini_a, t_fin_a, t_a, t_a2, t_a_aux;
	inicializar_matriz(m, n);
	t_ini_a = microsegundos ();
	prim(m, n, c);
	t_fin_a = microsegundos ();
	t_a = t_fin_a - t_ini_a;
	if(t_a < 500){
		cont_a = 1;
		t_ini_a = microsegundos();
		for(j=0; j<10000; j++){
			inicializar_matriz(m, n);
			prim(m, n, c);
		}
		t_fin_a = microsegundos ();
		t_a_aux = t_fin_a - t_ini_a;
		t_ini_a = microsegundos();
		for(j=0; j<10000; j++){
			inicializar_matriz(m, n);
		}
		t_fin_a = microsegundos ();
		t_a2 = t_fin_a - t_ini_a;
		t_a = (t_a_aux - t_a2) / 10000;
	}
	pintarTabla (cont_a, n, t_a);
	liberar_matriz(m, n);
	free(c);
}




int main (){
	int i;
	inicializar_semilla();
	testejem1();
	testejem2();
	testejem3();
	testrandom(10);
	pintarCabeceras();
	for(i=25; i <= 800; i=i*2)
		t_ejec(i);
	return 0;
}
