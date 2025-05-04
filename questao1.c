// Equipe: Pedro Henrique Cerqueira Mota
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 5000
#define MAX_PONTOS 1024

typedef struct {
  int x, y;
} Ponto;

double distancia(Ponto a, Ponto b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double distanciaOrigem(Ponto p) {
  return sqrt(p.x * p.x + p.y * p.y);
}

int compararOrigem(const void* a, const void* b) {
  Ponto* p1 = (Ponto*)a;
  Ponto* p2 = (Ponto*)b;
  double d1 = distanciaOrigem(*p1);
  double d2 = distanciaOrigem(*p2);
  return (d1 > d2) - (d1 < d2);
}

int main() {
  FILE* entrada = fopen("L0Q1.in", "r");
  FILE* saida = fopen("L0Q1.out", "w");

  if (!entrada || !saida) {
    fprintf(stderr, "Erro ao abrir os arquivos L0Q1.in ou L0Q1.out\n");
    return 1;
  }

  char linha[MAX_LINHA];
  int primeira = 1;

  while (fgets(linha, sizeof(linha), entrada)) {
    Ponto pontos[MAX_PONTOS];
    int qtd = 0;

    for (int i = 0; linha[i]; i++) {
      if (linha[i] == '(') {
        int x, y;
        if (sscanf(&linha[i], "(%d,%d)", &x, &y) == 2) {
          pontos[qtd].x = x;
          pontos[qtd].y = y;
          qtd++;
        }
      }
    }

    Ponto originais[MAX_PONTOS];
    memcpy(originais, pontos, qtd * sizeof(Ponto));

    qsort(pontos, qtd, sizeof(Ponto), compararOrigem);

    if (!primeira) fprintf(saida, "\n");
    primeira = 0;

    fprintf(saida, "points ");
    for (int i = 0; i < qtd; i++) {
      fprintf(saida, "(%d,%d) ", pontos[i].x, pontos[i].y);
    }

    double distTotal = 0.0;
    for (int i = 1; i < qtd; i++) {
      distTotal += distancia(originais[i - 1], originais[i]);
    }

    double atalho = (qtd >= 2) ? distancia(originais[0], originais[qtd - 1]) : 0.0;

    fprintf(saida, "distance %.2lf shortcut %.2lf", distTotal, atalho);
  }

  fclose(entrada);
  fclose(saida);
  return 0;
}