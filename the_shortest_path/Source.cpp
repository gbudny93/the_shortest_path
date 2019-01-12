#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define INF 99999
//functions
void logo();      //function that prints logo of the app
void buildGraph(); //function that builds a graph
void floyd(int **matrix);  //application of floyd warshall algorythm
void print(int **matrix);  //function printing final matrix

//global variables
char **city;   //array collecting cities' names
int **matrix;	//graph transformed into matrix
int V, c;       

void logo(){

	printf(" ####   #####  #   #  #######  #####   #####  #  ##   #  #####   #####  ####           \n");
	printf(" #   #  #   #  #   #     #     #       #      #  # #  #  #    #  #      #   #          \n");
	printf(" ####   #   #  #   #     #     ###     #####  #  #  # #  #    #  ###    ####           \n");
	printf(" #  #   #   #  #   #     #     #       #      #  #   ##  #    #  #      #   #          \n");
	printf(" #   #  #####  #####     #     #####   #      #  #    #  #####   #####  #    #         \n");
	printf("                                        by Grzegorz Budny CP Project     \n");
	


}
void buildGraph(){

	int i, j;
	char tmp, f;
	char a, b, r;
	int dist, pow;
	FILE *file;
	errno_t fp;

	fp = fopen_s(&file, "map.txt", "r");
	if (!file){
		printf("\nCannot open the file! Check if the proper file exits or go back to intructions!");
		_getch();
		exit(0);
	}
	rewind(file);
	fscanf_s(file, "%d", &V);
	tmp = fgetc(file);
	fscanf_s(file, "%d", &pow);
	tmp = fgetc(file);

	if (V < 0 || pow < 0){
		printf("An error occured! The number of cities or number of connections may posess negative value! Please check your input file!");
		_getch();
		exit(0);
	}
	
	//initialization of array for cities
	city = (char**)malloc(V*sizeof(char*));
	for (i = 0; i < V; i++){
		city[i] = (char*)malloc(10 * sizeof(char*));
		for (j = 0; j < 10; j++){
			city[i][j] = ' ';
		}
	}

	//read cities from file to array
	for (i = 0; i < V; i++){
		j = 0;
		while ((f = fgetc(file)) != '\n'){
			city[i][j] = f;
			j++;
		}
	}
	//graph matrix initialization
	matrix = (int**)malloc(V*sizeof(int*));
	for (i = 0; i < V; i++){
		matrix[i] = (int*)malloc(j*sizeof(int*));
		for (j = 0; j < V; j++){
			matrix[i][j] = INF;
			matrix[i][i] = 0;
		}
	}

	//creating matrix of graph
	for (i = 0; i < pow; i++){
		a = fgetc(file);
		b = fgetc(file);
		while (1){
			r = fgetc(file);
			if (r == '\n' || r == -1)break;
		}
		fscanf_s(file, "%d", &dist);

		if (dist < 0){
			printf("An error occured! Some of distances may posess negative value! Please check your input file!");
			_getch();
			exit(0);
		}

		matrix[a - 48][b - 48] = dist;
		r = fgetc(file);
	}
	fclose(file);

	
	

}

//function which is application of floyd-warshall algorythm
void floyd(int **matrix){

	int u, v, k;

	for (k = 0; k < V; k++){
		for (u = 0; u < V; u++){
			for (v = 0; v < V; v++){
				if ((matrix[u][k] + matrix[k][v]) < matrix[u][v]){
					matrix[u][v] = matrix[u][k] + matrix[k][v];
				}
			}
		}

	}
}
//function printing matrix representing the graph
void print(int **matrix){

	int i, j;

	for (i = 0; i < V; i++){
		for (j = 0; j < V; j++){
			if (matrix[i][j] == INF)printf("%7s", "INF");
			else{
				printf("%7d", matrix[i][j]);
			}
		}
		printf("\n");
	}
}


int main(){


	int a, b, i, j;
	int u, v, option;
	
	//menu and user interface
	while (1){
		system("cls");
		logo();
		printf("\nWelcome to ROUTE FINDER! Choose proper option:\n");
		printf("1. Find Route\n");
		printf("2. Instructions\n");
		printf("3. Exit\n");
		scanf_s("%d", &option);

		switch (option){
		case 1:{
				   buildGraph();
				   floyd(matrix);
				   printf("Available cities: \n");
				   for (i = 0; i < V; i++){
					   printf("%d. ", i);
					   for (j = 0; j < 10; j++){
						   printf("%c", city[i][j]);
					   }
					   printf("\n");
				   }
				   printf("Please insert number of your initial city: ");
				   scanf_s("%d", &a);
				   printf("Please insert number of your destination city: ");
				   scanf_s("%d", &b);
				   printf("The shortest route between: ");
				   for (i = 0; i < 10; i++){
					   printf("%c", city[a][i]);
				   }
				   printf("and ");
				   for (i = 0; i < 10; i++){
					   printf("%c", city[b][i]);
				   }
				   if (matrix[a][b] == INF)printf("There is no such a connection!");
				   else{
					   printf(" is equal to %d km", matrix[a][b]);
				   }
				   printf("\n\nPress any key to go back to main menu");
				   _getch();
				   //free memory
				   for (int i = 0; i<V; i++)
					   free(matrix[i]);
				   free(matrix);
				   matrix = NULL;

				   for (int i = 0; i<V; i++)
					   free(city[i]);
				   free(city);
				   matrix = NULL;

				   system("cls");
				   break;

		}
		case 2:{
				   /*Reading instructions from text file*/
				   FILE *file2;
				   errno_t fp2;
				   fp2 = fopen_s(&file2, "instructions.txt", "r");
				   if (!file2){
					   printf("\nCannot open the file! Check if the proper file exits or go back to intructions!");
					   _getch();
					   exit(0);
				   }
				   while (c != EOF){
					   c = fgetc(file2);
					   printf("%c", c);
				   }
				   fclose(file2);
				   printf("\n\nPress any key to go back to main menu");
				   _getch();
				   system("cls");
				   break;
		}
		case 3:{
				   exit(0);
				   break;
		}
		default:{
			printf("Wrong number please insert number from 1 to 3!\n");
			_getch();
			break;
		}
		}
	}
	
	getchar();
	return 0;
	
	
}