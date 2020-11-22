
/****************************************************************/
/* rdate.c - client program for remote date service */
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cJSON.h"
#include "date.h"

void delete_banda(CLIENT *cl) {
  char name[255];
  char **res;

  printf("Nome da banda: ");
  scanf("%s", name);

  char *namePtr = &name[0];

  if ((res = delete_banda_1(&namePtr, cl)) == NULL) {
    printf(" remote procedure delete_banda_1() failure\n");
    exit(3);
  }

  printf("Banda deletada\n%s\n", *res);
}

void read_banda(CLIENT *cl) {
  char name[255];
  char **res;

  printf("Nome da banda: ");
  scanf("%s", name);

  char *namePtr = &name[0];

  if ((res = read_banda_1(&namePtr, cl)) == NULL) {
    printf(" remote procedure read_banda_1() failure\n");
    exit(3);
  }

  printf("Banda:\n%s\n", *res);
}

void list_bandas(CLIENT *cl) {
  char **res;

  if ((res = list_banda_1(NULL, cl)) == NULL) {
    printf(" remote procedure list_banda_1() failure\n");
    exit(3);
  }

  printf("Bandas:\n%s\n", *res);
}

void create_banda(CLIENT *cl) {
  char **res;
  char name[255];

  printf("Nome da banda: ");
  scanf("%s", name);

  cJSON *json = cJSON_CreateObject();

  cJSON_AddStringToObject(json, "nome", name);
  cJSON_AddArrayToObject(json, "musicas");

  char *jsonStr = cJSON_Print(json);

  if ((res = create_banda_1(&jsonStr, cl)) == NULL) {
    printf(" remote procedure create_banda_1() failure\n");
    exit(3);
  }

  printf("Banda adicionada:\n%s\n", *res);
}

int ask_user(CLIENT *cl) {
  int res;
  do {
    printf("0 - Exit\n");
    printf("1 - Criar Banda\n");
    printf("2 - Deletar Banda\n");
    printf("3 - Listar Bandas\n");
    printf("4 - Achar banda\n");
    printf("Insira a opção: ");

    scanf("%i", &res);

    switch (res) {
      case 0:
        break;
      case 1:
        create_banda(cl);
        break;
      case 2:
        delete_banda(cl);
        break;
      case 3:
        list_bandas(cl);
        break;
      case 4:
        read_banda(cl);
        break;

      default:
        printf("Opção inválida\n");
        break;
    }

  } while (res);
}

int main(int argc, char *argv[]) {
  CLIENT *cl;
  char *server;

  if (argc != 2) {
    fprintf(stderr, "usage: %s hostname\n", argv[0]);
    exit(1);
  }
  server = argv[1];

  /* create client handle */
  if ((cl = clnt_create(server, DATEPROG, DATEVERS, "udp")) == NULL) {
    /* couldn't establish connection with server */
    printf("can't establish connection with host %s\n", server);
    exit(2);
  }

  ask_user(cl);
  clnt_destroy(cl); /* done with handle */
  return 0;
}
