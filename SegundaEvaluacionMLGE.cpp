#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct producto{
	int folio;
	float precio;
	int dia;
	int mes;
	int anio;		
};
struct Nodo{
	int dato;
	Nodo *siguiente;
};
Nodo *pila = NULL;


void menu2(struct producto stock,struct producto *m1,int n,int precio);
void agregarP(Nodo *&,int );
void quitarP(Nodo *&,int &) ;

int menu(struct producto stock,struct producto *m1,int n,int precio);
int leerP(struct producto stock,struct producto *m1,int n,int precio);
int consultarP(struct producto stock,struct producto *m1,int n);
void venderP(struct producto stock,struct producto *m1,int n,int precio);

int main(){
	struct producto stock,*m1;
	int n=75, precio=0;
	m1=(struct producto*) malloc(n*sizeof(stock));
	menu(stock,m1,n,precio);
 
	return 0;
}
int menu(struct producto stock,struct producto *m1,int n,int precio){
	int b;
	do{
		printf("                MENU\n");
		printf("1. Almacenar productos leyendo un archivo de texto\n");
		printf("2. Consultar productos\n");
		printf("3. Vender producto\n");
		printf("4. Salir\n");
		printf("Seleccione la opcion deseada\n");
		scanf("%d",&b);
		fflush(stdin);
	
	
		switch(b){
			
			case 1:	
					leerP(stock,m1,n,precio);
				
				break;
				
			case 2: 
					precio=consultarP(stock,m1,n);
				break;
			case 3: 
					venderP(stock,m1,n,precio);
				break;
			case 4:
					printf("\nEl programa ha finalizado\n");
					return 0;
				break;
		}
		menu(stock,m1,n,precio);
	}while(b<1 || b>4);
}

int leerP(struct producto stock,struct producto *m1,int n,int precio){
	//Definir variables, arreglos y punteros a usar
	int cont=0,i=0,c=0;
	int f,d,m,a;
	float p;
	FILE *archivo;
	char dir[100],temp[15],caracter,car;
	//Preguntarle al usuario la ruta del archivo y asignarla a un arreglo de caracteres
	printf("Escribe la ruta del archivo que deseas leer o el nombre del archivo (si el ejecutable esta en la misma carpeta)\n");
	scanf("%[^\n]",dir);
	//Abrir el archivo en modo lectura
	archivo = fopen(dir,"rb");
	//Uso de condicional doble para evaluar si el puntero apunta a una direccion de memoria
	if (archivo == NULL){
		system("cls");
		printf("\nError de apertura del archivo. \n\n");
		return main();
	}
	else{
		//Leer el archivo
		printf("Los productos que contiene el archivo son: \n\n");
		//Uso de la funcion rewind para llevar el puntero al inicio del archivo
		rewind(archivo);
		
		while(!feof(archivo)){
			fgets(temp,15,archivo);
			cont++;
		}
		//Uso de la funcion malloc para determinar el tamaño del arreglo estructurado
		m1=(struct producto*) malloc(cont*sizeof(stock));
		rewind(archivo);
		;
		//Leer los datos del archivo y asignarlos a el arerglo estructurado
		printf("%c",'\n');
		while(fscanf(archivo,"%d\t%f\t%d\t%d\t%d\t", &f,&p,&d,&m,&a )==5){
			printf("%d %f %d %d %d\n",f,p,d,m,a);
			m1[c].folio=f;
			m1[c].precio=p;			
			m1[c].dia=d;			
			m1[c].mes=m;	
			m1[c].anio=a;	
			c++;	
		}
	//Cerrar archivo	
	fclose(archivo);	
	}	
	//Mostrar los puntos añadidos en la terminal
	printf("\nLos productos añadidos son:\n\n");
	for(int x=0; x<cont/2; x++){
		printf("Folio: %d\n",m1[x].folio);
		printf("Precio: $%.2f\n",m1[x].precio);
		printf("Fecha de caducidad: %d/%d/%d\n\n",m1[x].dia,m1[x].mes,m1[x].anio);
	}
	menu(stock,m1,n,precio);		
}

int consultarP(struct producto stock,struct producto *m1,int n){
	int hash[75][6]={{0}};
	int b, res, i, f=n, v;
	int precio=0;
	
	printf("Ingresa el ID del producto que deseas buscar\n");
	scanf("%d",&b);

	res = b %n;

	//Algoritmo para llenar la tabla hash mediante referencia de la de datos
	for(i=0; i<75; i++){
		
		res = m1[i].folio % f;	

		while(hash[res][5]==1){	
			 res++;
		 	if(res>74){
		 		res=0;
			}
		}
	
		hash[res][0]=m1[i].folio;
		hash[res][1]=m1[i].precio;
		hash[res][2]=m1[i].dia;
		hash[res][3]=m1[i].mes;
		hash[res][4]=m1[i].anio;
		hash[res][5]= 1;
	
	}
	//Visualizacion de Tabla hash
	printf("\n");
	printf("             .:Productos:.\n");
	printf("  ID\tPrecio\t      Caducidad\n\n");
	for(int i=0; i<n; i++){
		for(int j=0; j<6; j++){
			printf("%d\t",hash[i][j]);
		}
		printf("\n");
	}

	//funcion para buscar de manera secuencial
	while((hash[res][0]!=b)&&(v<75)){
		res++;	
		if(res>74){
		 	res=0;
		}
		v++;	
	}
	//Condicion por si la clave no esta en la tabla
	if(hash[res][0]!=b){
		printf("\nEl ID no corresponde a ningun producto\n");
		
	}else{
		printf("\nEl ID %d tiene un precio de $%d y caduca el %d/%d/%d\n Ademas se encuentra en la posicon %d de la Tabla de Consulta\n",hash[res][0],hash[res][1],hash[res][2],hash[res][3],hash[res][4],res);
		precio=hash[res][1];
		precio=precio*1.6;
		return precio;
	}
		
}
void venderP(struct producto stock,struct producto *m1,int n,int precio){
	menu2(stock,m1,n,precio);
	
	
}
void menu2(struct producto stock,struct producto *m1,int n,int precio){
	int opcion,total=0;
	char res;
	
	
	do{
		printf( "\n          .:MENU:.   \n");
		printf( "1. Ingresar productos que deseas vender\n");
        printf( "2. Finalizar venta\n");
        printf( "0. Salir.\n\n" );
        scanf( "%d", &opcion );
		
		switch(opcion){
			
			case 1:	do{
						precio=consultarP(stock,m1,n);
						printf("%d",precio);
						agregarP(pila,precio);
						printf("Deseas agregar otro elemento(s/n):\n");
						scanf("%s",&res);
					}while((res=='S')||(res=='s'));
				break;
				
			case 2: if(pila == NULL){
						printf("No has agregado ningun producto a vender\n");
					} else {
						printf("Los precios de los productos eran: \n");
						while(pila !=NULL){ //Mientras no esta al final de la pila
							quitarP(pila,precio);
							if(pila != NULL){
								printf("%d , ",precio);
								total=total+precio;
							}
							else{
								printf("%d.\n",precio);
								total=total+precio;
							}
						}
					}
					printf("El costo total de los productos añadidos es: %d",total);
				break;
		}
			
	}while(opcion!=0);
	
	printf("Regresando al MENU Principal\n");
	
}
//Agrega elementos a la pila
void agregarP(Nodo *&pila, int n){
	Nodo *n_nodo = new Nodo();
	n_nodo->dato = n;
	n_nodo->siguiente = pila;
	pila = n_nodo;	
	printf("\nEl producto con precio todal de %d se ha agregado correctamente\n",n);
	
}

//Sacar elementos de pila
void quitarP(Nodo *&pila, int &n){
	Nodo *aux = pila;
	n = aux->dato;
	pila = aux->siguiente;
	delete aux;	
}


