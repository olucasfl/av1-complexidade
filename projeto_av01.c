#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *criar_arranjo(int modo, int *linhas, int *colunas, int max, int limitar)
{
    if (*linhas == 0) {
        printf("Quantas linhas? ");
        scanf("%d", linhas);
    }
    if (*colunas == 0) {
        printf("Quantas colunas? ");
        scanf("%d", colunas);
    }
    if (*linhas <= 0 || *colunas <= 0) {
        printf("Tamanho invalido.\n");
        return NULL;
    }

    int total = *linhas * *colunas;
    int *dados = malloc(sizeof(int) * total);
    if (dados == NULL) {
        printf("Memoria insuficiente.\n");
        return NULL;
    }

    for (int i = 0; i < total; i++) {
        if (modo == 1) {
            printf("Elemento %d: ", i);
            scanf("%d", &dados[i]);
            while (limitar && (dados[i] < 0 || dados[i] > max)) {
                printf("Valor deve estar entre 0 e %d. Digite de novo: ", max);
                scanf("%d", &dados[i]);
            }
        } else {
            dados[i] = rand() % (max + 1);
        }
    }
    return dados;
}

int perguntar_modo(void)
{
    int modo = 0;
    while (modo != 1 && modo != 2) {
        printf("Preenchimento (1 = manual, 2 = aleatorio): ");
        scanf("%d", &modo);
    }
    return modo;
}

void imprimir_vetor(int n, int v[n])
{
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void imprimir_matriz(int n, int M[n][n])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", M[i][j]);
        printf("\n");
    }
}

void imprimir_3d(int n, int A[n][n][n])
{
    for (int i = 0; i < n; i++) {
        printf("Camada %d:\n", i);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
                printf("%4d", A[i][j][k]);
            printf("\n");
        }
    }
}

int comparar(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void ordenar_vetor(int n, int v[n])
{
    qsort(v, n, sizeof(int), comparar);
}

/* FUNCAO 1 */
int contar_ocorrencias(int n, int v[n], int k, int buscados[k])
{
    int total = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (v[j] == buscados[i]) {
                total++;
            }
        }
    }
    return total;
}

/* FUNCAO 2 */
int analisar_pares(int n, int A[n][n])
{
    int contador = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if ((A[i][j] + A[j][i]) % 5 == 0) {
                contador++;
            }
        }
    }
    return contador;
}

/* FUNCAO 3 */
int comparar_3d(int n, int A[n][n][n], int B[n][n][n])
{
    long long somaA = 0;
    long long somaB = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                somaA += A[i][j][k];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                somaB += B[i][j][k];
            }
        }
    }
    if (somaA >= somaB) {
        return 1;
    }
    return 0;
}

long long fatorial(int x)
{
    long long resultado = 1;
    for (int i = 2; i <= x; i++) {
        resultado = resultado * i;
    }
    return resultado;
}

/* FUNCAO 4 */
long long processar_vetor(int n, int v[n])
{
    long long total = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] % 2 == 0) {
            total += v[i];
        } else {
            total += fatorial(v[i]);
        }
    }
    return total;
}

/* FUNCAO 5 */
int busca_binaria(int n, int v[n], int x)
{
    int inicio = 0;
    int fim = n - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (v[meio] == x) {
            return 1;
        }
        if (v[meio] < x) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return 0;
}

int contar_presentes(int n, int A[n], int B[n])
{
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (busca_binaria(n, B, A[i]) == 1) {
            total++;
        }
    }
    return total;
}

void opcao1(void)
{
    int modo = perguntar_modo();
    int lin = 1, col = 0, lin2 = 1, col2 = 0;

    printf("Vetor v:\n");
    int *v = criar_arranjo(modo, &lin, &col, 99, 0);
    if (v == NULL)
        return;
    int n = col;

    printf("Vetor de buscados:\n");
    int *buscados = criar_arranjo(modo, &lin2, &col2, 99, 0);
    if (buscados == NULL) {
        free(v);
        return;
    }
    int k = col2;

    printf("\nv: ");
    imprimir_vetor(n, v);
    printf("buscados: ");
    imprimir_vetor(k, buscados);
    printf("Total de ocorrencias: %d\n", contar_ocorrencias(n, v, k, buscados));

    free(v);
    free(buscados);
}

void opcao2(void)
{
    int modo = perguntar_modo();
    int n;
    printf("Tamanho n da matriz: ");
    scanf("%d", &n);
    if (n <= 0)
        return;
    int lin = n, col = n;

    int (*A)[n] = (int (*)[n])criar_arranjo(modo, &lin, &col, 99, 0);
    if (A == NULL)
        return;

    printf("\nMatriz A:\n");
    imprimir_matriz(n, A);
    printf("Pares multiplos de 5: %d\n", analisar_pares(n, A));

    free(A);
}

void opcao3(void)
{
    int modo = perguntar_modo();
    int n;
    printf("Tamanho n dos arranjos: ");
    scanf("%d", &n);
    if (n <= 0)
        return;
    int lin = n * n, col = n;

    printf("Arranjo A:\n");
    int (*A)[n][n] = (int (*)[n][n])criar_arranjo(modo, &lin, &col, 99, 0);
    if (A == NULL)
        return;

    lin = n * n;
    col = n;
    printf("Arranjo B:\n");
    int (*B)[n][n] = (int (*)[n][n])criar_arranjo(modo, &lin, &col, 99, 0);
    if (B == NULL) {
        free(A);
        return;
    }

    printf("\nA:\n");
    imprimir_3d(n, A);
    printf("B:\n");
    imprimir_3d(n, B);
    printf("soma(A) >= soma(B)? %d\n", comparar_3d(n, A, B));

    free(A);
    free(B);
}

void opcao4(void)
{
    int modo = perguntar_modo();
    int lin = 1, col = 0;

    int *v = criar_arranjo(modo, &lin, &col, 20, 1);
    if (v == NULL)
        return;
    int n = col;

    printf("\nv: ");
    imprimir_vetor(n, v);
    printf("Resultado: %lld\n", processar_vetor(n, v));

    free(v);
}

void opcao5(void)
{
    int modo = perguntar_modo();
    int n;
    printf("Tamanho n dos vetores: ");
    scanf("%d", &n);
    if (n <= 0)
        return;
    int lin = 1, col = n;

    printf("Vetor A:\n");
    int *A = criar_arranjo(modo, &lin, &col, 99, 0);
    if (A == NULL)
        return;

    lin = 1;
    col = n;
    printf("Vetor B:\n");
    int *B = criar_arranjo(modo, &lin, &col, 99, 0);
    if (B == NULL) {
        free(A);
        return;
    }

    printf("\nA: ");
    imprimir_vetor(n, A);
    printf("B: ");
    imprimir_vetor(n, B);
    ordenar_vetor(n, B);
    printf("B ordenado: ");
    imprimir_vetor(n, B);
    printf("Presentes em B: %d\n", contar_presentes(n, A, B));

    free(A);
    free(B);
}

int main(void)
{
    int opcao = -1;
    srand(time(NULL));

    printf("Integrantes: Lucas Farias, Jean, Iago, Igor, Lucas Lopes\n");

    do {
        printf("\n1 - Contar ocorrencias\n");
        printf("2 - Analisar pares\n");
        printf("3 - Comparar 3D\n");
        printf("4 - Processar vetor\n");
        printf("5 - Contar presentes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1)
            opcao = 0;

        switch (opcao) {
        case 1: opcao1(); break;
        case 2: opcao2(); break;
        case 3: opcao3(); break;
        case 4: opcao4(); break;
        case 5: opcao5(); break;
        case 0: printf("Encerrando.\n"); break;
        default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
