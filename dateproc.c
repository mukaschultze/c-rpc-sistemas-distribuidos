#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "date.h"

const char *BANCO_FILENAME = "./banco.json";

cJSON *parse_banco() {
  char *buffer = 0;
  long length;
  FILE *f = fopen(BANCO_FILENAME, "r");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
      fread(buffer, sizeof(char), length, f);
    }
    fclose(f);
  }

  cJSON *json = cJSON_Parse(buffer);

  // char *formatted = cJSON_Print(json);
  // printf("%s", formatted);

  return json;
}

void save_banco(cJSON *json) {
  char *formatted = cJSON_Print(json);
  long length = strlen(formatted);

  FILE *f = fopen(BANCO_FILENAME, "w");

  if (f) {
    fwrite(formatted, sizeof(char), length, f);
    fclose(f);
  }
}

void *test_1_svc(void *arg1, struct svc_req *arg2) {
  cJSON *json = parse_banco();
  save_banco(json);
}

json_result *create_banda_1_svc(json_result *arg1, struct svc_req *arg2) {
  printf("Creating banda: %s\n", *arg1);

  cJSON *banda_json = cJSON_Parse(*arg1);
  cJSON *banco = parse_banco();
  cJSON *banco_bandas = cJSON_GetObjectItem(banco, "bandas");
  cJSON_AddItemToArray(banco_bandas, banda_json);
  save_banco(banco);

  static char *json;
  json = cJSON_Print(banda_json);
  return (&json);
}

json_result *list_banda_1_svc(void *arg1, struct svc_req *arg2) {
  printf("Listing bandas\n");
  static char *json;
  json = cJSON_Print(parse_banco());
  return (&json);
}

json_result *read_banda_1_svc(json_result *arg1, struct svc_req *arg2) {
  printf("Reading banda: %s\n", *arg1);

  cJSON *target_nome_banda = cJSON_CreateString(*arg1);
  cJSON *banco = parse_banco();
  cJSON *banco_bandas = cJSON_GetObjectItem(banco, "bandas");
  cJSON *banda_found = cJSON_CreateNull();
  cJSON *banda;

  cJSON_ArrayForEach(banda, banco_bandas) {
    cJSON *nome_banda = cJSON_GetObjectItem(banda, "nome");
    if (cJSON_Compare(nome_banda, target_nome_banda, cJSON_False)) {
      banda_found = banda;
    }
  }

  static char *json;
  json = cJSON_Print(banda_found);
  return (&json);
}

json_result *delete_banda_1_svc(json_result *arg1, struct svc_req *arg2) {
  printf("Deleting banda: %s\n", *arg1);

  cJSON *target_nome_banda = cJSON_CreateString(*arg1);
  cJSON *banco = parse_banco();
  cJSON *banco_bandas = cJSON_GetObjectItem(banco, "bandas");
  cJSON *banda_found = cJSON_CreateNull();
  int banda_found_idx = -1;
  int idx = 0;
  cJSON *banda;

  cJSON_ArrayForEach(banda, banco_bandas) {
    cJSON *nome_banda = cJSON_GetObjectItem(banda, "nome");
    if (cJSON_Compare(nome_banda, target_nome_banda, cJSON_False)) {
      banda_found_idx = idx;
      banda_found = banda;
    }
    idx++;
  }

  static char *json;
  json = cJSON_Print(banda_found);

  if (idx > -1) {
    cJSON_DeleteItemFromArray(banco_bandas, banda_found_idx);
  }
  save_banco(banco);
  return (&json);
}