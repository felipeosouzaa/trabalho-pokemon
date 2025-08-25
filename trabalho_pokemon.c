/*************************************************************
Trabalho Computacional - Programação I - 2024/2
Grupo:
<Felipe Augusto Oliveira Souza>
<Yan Pettene Pinto>
*************************************************************/

#include <stdio.h>
#include <math.h>

// função para calcular a distância
float distancia(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


// função p calcular o caminho mínimo
float caminho_minimo(int n, int cidades[400][2], int percurso[400]) {
    int visitado[400];  
    int atual = 0, prox, i;     
    float menor_dist, dist, dist_total = 0;  

  
    for (i = 0; i < 400; i++) {
        visitado[i] = 0;
    }

    
    percurso[0] = 0;  
    visitado[0] = 1;  

    
    for (i = 1; i < n; i++) {
        menor_dist = 1000000000;  
        prox = -1;         

        //cidade mais próxima da cidade atual
        for (int j = 1; j < n; j++) {
            if (visitado[j] == 0) {  
                dist = distancia(cidades[atual][0], cidades[atual][1], cidades[j][0], cidades[j][1]);
                if (dist < menor_dist) {  
                    menor_dist = dist;
                    prox = j;
                }
            }
        }

        // verifica as cidades e vai p próxima
        percurso[i] = prox;
        visitado[prox] = 1;
        dist_total += menor_dist;  
        atual = prox;  
    }

    
    dist_total += distancia(cidades[atual][0], cidades[atual][1], cidades[0][0], cidades[0][1]);
    percurso[n] = 0;  
    return dist_total;  
}


void batalhas(int n, char nomes[399][50], int hp[399], int atk[399], int def[399], int vitorias[399]) {
    //compara cada pokémon com os outros
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int hp1 = hp[i], hp2 = hp[j];  
            int dano1 = atk[i] - def[j];  
            int dano2 = atk[j] - def[i];  

            
            if (dano1 > 0 || dano2 > 0) {
                // Simula até um perder
                while (hp1 > 0 && hp2 > 0) {
                    if (dano1 > 0) hp2 -= dano1;  
                    if (hp2 > 0 && dano2 > 0) hp1 -= dano2;  
                }

                // conta as vitórias
                if (hp1 > 0 && hp2 <= 0) {
                    vitorias[i]++;  
                } else if (hp2 > 0 && hp1 <= 0) {
                    vitorias[j]++;  
                }
            }
        }
    }
}


int main() {
    int n, i, melhor_pokemon = 0;  
    float distancia_total;  
    int cidades[400][2];  
    int percurso[400];    
    char nomes[399][50];  
    int hp[399], atk[399], def[399]; 
    int vitorias[399]; 

    
    for (i = 0; i < 399; i++) {
        vitorias[i] = 0;
    }

    // lê o número de cidades
    scanf("%d", &n);

    // lê as coordenadas 
    for (i = 0; i < n; i++) {
        scanf("%d %d", &cidades[i][0], &cidades[i][1]);
    }

    // lê os dados 
    for (i = 0; i < n - 1; i++) {
        scanf("%s %d %d %d", nomes[i], &hp[i], &atk[i], &def[i]);
    }

    
    distancia_total = caminho_minimo(n, cidades, percurso);

    
    batalhas(n, nomes, hp, atk, def, vitorias);

    // pokémon com mais vitórias
    for (i = 1; i < n - 1; i++) {
        if (vitorias[i] > vitorias[melhor_pokemon]) {
            melhor_pokemon = i;
        }
    }


    printf("Caminho: ");
    for (i = 0; i <= n; i++) {
        printf("%d ", percurso[i]);
    }

    printf("\nDistancia: %.6f\n", distancia_total);
    printf("Campeao: %s\nNumero de vitorias: %d\n", nomes[melhor_pokemon], vitorias[melhor_pokemon]);

    return 0;  
}