// Equipe: Pedro Henrique Cerqueira Mota
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINHA 1024
#define MAX_ITENS 512

typedef struct {
  double x, y;
} Ponto;

double distancia(Ponto p) {
  return sqrt(p.x * p.x + p.y * p.y);
}

int cmp_str(const void* a, const void* b) {
  return strcmp(*(char**)a, *(char**)b);
}

int cmp_int(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

int cmp_float(const void* a, const void* b) {
  double fa = *(double*)a;
  double fb = *(double*)b;
  if (fa < fb) return -1;
  if (fa > fb) return 1;
  return 0;
}

int cmp_ponto(const void* a, const void* b) {
  double da = distancia(*(Ponto*)a);
  double db = distancia(*(Ponto*)b);
  if (da < db) return -1;
  if (da > db) return 1;
  return 0;
}

void clean_token(char* token) {
  char* p = token;
  int i = 0;
  while (*p) {
    if (*p != '(' && *p != ')' && *p != ',') {
      token[i++] = *p;
    } else if (*p == ',') {
      token[i++] = ' ';
    }
    p++;
  }
  token[i] = '\0';
}

int main() {
  FILE* entrada = fopen("L0Q2.in", "r");
  FILE* saida = fopen("L0Q2.out", "w");

  if (!entrada || !saida) {
    fprintf(stderr, "Erro ao abrir os arquivos.\n");
    return 1;
  }

  char linha[MAX_LINHA];
  int primeiraLinha = 1;

  while (fgets(linha, sizeof(linha), entrada)) {
    char* tokens[MAX_ITENS];
    int ints[MAX_ITENS], n_ints = 0;
    double floats[MAX_ITENS];
    int n_floats = 0;
    Ponto pontos[MAX_ITENS];
    int n_pontos = 0;
    char* strings[MAX_ITENS];
    int n_strings = 0;

    char* token = strtok(linha, " \n");
    while (token) {
      if (token[0] == '(') {
        char pt[MAX_LINHA];
        strncpy(pt, token, sizeof(pt));
        pt[sizeof(pt) - 1] = '\0';
        while (!strchr(pt, ')')) {
          token = strtok(NULL, " \n");
          if (!token) break;
          strncat(pt, " ", sizeof(pt) - strlen(pt) - 1);
          strncat(pt, token, sizeof(pt) - strlen(pt) - 1);
        }

        clean_token(pt);
        double x, y;
        if (sscanf(pt, "%lf %lf", &x, &y) == 2) {
          pontos[n_pontos].x = x;
          pontos[n_pontos].y = y;
          n_pontos++;
        }

      } else {
        char* endptr;
        long val_int = strtol(token, &endptr, 10);
        if (*endptr == '\0') {
          ints[n_ints++] = (int)val_int;
        } else {
          double val_float = strtod(token, &endptr);
          if (*endptr == '\0') {
            floats[n_floats++] = val_float;
          } else {
            strings[n_strings++] = strdup(token);
          }
        }
      }
      token = strtok(NULL, " \n");
    }

    qsort(strings, n_strings, sizeof(char*), cmp_str);
    qsort(ints, n_ints, sizeof(int), cmp_int);
    qsort(floats, n_floats, sizeof(double), cmp_float);
    qsort(pontos, n_pontos, sizeof(Ponto), cmp_ponto);

    if (!primeiraLinha) fprintf(saida, "\n");
    primeiraLinha = 0;

    fprintf(saida, "str:");
    for (int i = 0; i < n_strings; i++) fprintf(saida, "%s%s", (i > 0 ? " " : ""), strings[i]);

    fprintf(saida, " int:");
    for (int i = 0; i < n_ints; i++) fprintf(saida, "%s%d", (i > 0 ? " " : ""), ints[i]);

    fprintf(saida, " float:");
    for (int i = 0; i < n_floats; i++) fprintf(saida, "%s%.10g", (i > 0 ? " " : ""), floats[i]);

    fprintf(saida, " p:");
    for (int i = 0; i < n_pontos; i++) fprintf(saida, "%s(%.10g,%.10g)", (i > 0 ? " " : ""), pontos[i].x, pontos[i].y);

    for (int i = 0; i < n_strings; i++) {
      free(strings[i]);
    }
  }

  fclose(entrada);
  fclose(saida);
  return 0;
}