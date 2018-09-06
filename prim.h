/**********************************************************************

Copyleft (C) 2017  Álex Velo Santórum y Caetán Tojeiro Carpente

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

**********************************************************************/


#define TAM_MAX 1600
#define PESO_MAX 1000 

typedef int ** matriz;
typedef struct {
	int x, y, peso;
} arista;

typedef arista tipo_elemento;
typedef struct {
	int cabeza, final, tamano;
	tipo_elemento vector[TAM_MAX];
} cola;
void crear_cola(cola *);
int cola_vacia(cola);
void insertar(tipo_elemento, cola *);
tipo_elemento quitar_primero(cola *);
tipo_elemento primero(cola);
void mostrar_cola(cola);
