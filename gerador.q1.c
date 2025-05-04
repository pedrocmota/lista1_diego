#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 50000
#define MAX_PONTOS 20
#define COORD_MAX 1000

int main() {
  FILE* f = fopen("L0Q1.in", "w");
  if (!f) {
    perror("Erro ao criar L0Q1.in");
    return 1;
  }

  srand((unsigned)time(NULL));

  for (int i = 0; i < LINHAS; i++) {
    int qtd = (rand() % MAX_PONTOS) + 1;

    fprintf(f, "points");
    for (int j = 0; j < qtd; j++) {
      int x = rand() % (2 * COORD_MAX + 1) - COORD_MAX;
      int y = rand() % (2 * COORD_MAX + 1) - COORD_MAX;
      fprintf(f, " (%d,%d)", x, y);
    }
    fprintf(f, "\n");
  }

  fclose(f);
  printf("Arquivo L0Q1.in com %d linhas (1 a 20 pontos cada) gerado com sucesso.\n", LINHAS);
  return 0;
}