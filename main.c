#include <stdlib.h>
#include <stdio.h>

void print_1d(int* matrix, int matrix_size){
    int i;
    for(i=0; i<matrix_size; i++){
        printf("%d ", matrix[i]);
    }    
}

void print_2d(int* matrix, int matrix_size){
    int i, j;
    for(i=0; i<matrix_size; i++){
        for(j=0; j<matrix_size; j++){
            printf("%d\t", matrix[i*matrix_size+j]);
        }
        printf("\n");
    }
}

void print_result(int* matrix, int matrix_size, int edge_size){
    int i, j, n;
}

int check_matrix(int* matrix, int matrix_size, int edge, int element){
    int i = matrix_size - edge, val=0;
    while(i<matrix_size && val==0){
        if(matrix[i] == element){
            val = 1;
        }
        i++;
    }
    return val;
}

void insert_node(int* matrix, int* matrix_size, int element){
    int n = *matrix_size;
    if(n==0){
        *matrix_size = *matrix_size+1;
        matrix[0] = element;
    }
    else{
        *matrix_size = *matrix_size+1;
        matrix[n] = element;
    }
    *matrix;
}

void copy_node(int* matrix, int* matrix_size, int edge){
    int i, n=*matrix_size;

    for(i=n; i<n+edge; i++){
        *matrix_size = *matrix_size + 1;
        matrix[i] = matrix[i-edge];
    }
    *matrix;
}

void delete_node(int* matrix, int* matrix_size){
    int n = *matrix_size;
    matrix[n-1] = 0;
    *matrix_size = *matrix_size-1;
    *matrix;
}

void find_paths(int* matrix, int matrix_size, int* result, int* result_size, int src, int dest, int edge, int* edge_r, int loc){
    int i, edge_temp=edge-1, m=matrix_size, n=*result_size, val=0;
    int* temp = malloc((m+1) * sizeof(int));
    
    // copy adjacent matrix dari node bersangkutan kemudian ditambah satu nilai nol pada index terakhir ditambah 1
    for(i=0; i<m+1; i++){
        if(i<m){
            temp[i] = matrix[(loc-1)*m+i];
        }
        else{
            temp[i] = 0;
        }
    }

    i = 0;
    while(i<m+1 && val==0){
        printf("\n");
        print_1d(temp, m);
        printf("\nloc: %d\n", loc);
        printf("idx: %d\n", i+1);
        printf("edge_r: %d, edge: %d\n", *edge_r, edge_temp);
        printf("check: %d\n", check_matrix(result, n, *edge_r, i+1));
        printf("RESULT\n");
        print_1d(result, *result_size);
        printf("\n");
        if(*edge_r<edge_temp && check_matrix(result, n, *edge_r, i+1)==0 && i!=src-1 && i!=dest-1 && temp[i]==1){
            printf("\n->case 1\n");
            insert_node(result, result_size, i+1);
            *edge_r = *edge_r + 1;
            find_paths(matrix, matrix_size, result, result_size, src, dest, edge, edge_r, i+1);
        }
        else if(*edge_r==edge_temp && check_matrix(result, n, *edge_r, i+1)==0 && i!=src-1 && i==dest-1 && temp[i]==1){
            printf("\n->case 2\n");
            copy_node(result, result_size, *edge_r);
            delete_node(result, result_size);
            val = 1;
            *edge_r = *edge_r - 1;
        }
        else if(*edge_r>0 && *edge_r<=edge_temp && i==m){
            printf("\n->case 3\n");
            delete_node(result, result_size);
            *edge_r = *edge_r - 1;
        }
        i++;
    }
}

int main(){
    int i, j, edge_r=0, edge, src, dest, size_r = 0;
    int file_1[] = {0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0}, size_1 = 4;
    int file_2[] = {0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,1,0,0,1,1,0}, size_2 = 5;
    int file_3[] = {0,1,1,0,0,1,0,1,0,1,1,1,0,1,1,0,0,1,0,1,0,1,1,1,0}, size_3 = 5;
    int* result = malloc((size_r) * sizeof(int));
    int* temp = malloc((size_3*size_3) * sizeof(int));
    for(i=0; i<size_3*size_3; i++){
        temp[i] = file_3[i];
    }

    printf("\nAdjacent Matrix:\n");
    print_2d(temp, size_3);
    printf("\nMasukan Vertex Asal: ");
    scanf("%d", &src);
    printf("Masukan Vertex Tujuan: ");
    scanf("%d", &dest);
    printf("Masukan Batas Edges: ");
    scanf("%d", &edge);

    find_paths(temp, size_3, result, &size_r, src, dest, edge, &edge_r, src);
    
    printf("\nResult\n");
    print_1d(result, size_r);
    printf("\n");
    printf("%d", size_r);

    free(result);
    return 0;
}