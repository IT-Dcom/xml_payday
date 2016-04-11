#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include "xml_data.h"
#include "xml_reader.h"

void
start_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
  XML_Data *xml = user_data;
  strcpy(xml->last_balise, name);
  if (attrs != NULL) {
    for (int i = 0; attrs[i] != NULL; i+=2) {
      if(strcmp("relay", xml->last_balise) == 0)
      {
        xml->last_relais = atoi(attrs[i+1]);
      }
    }
  }
}

void
caracteres(void *user_data, const xmlChar *ch, int len) {
  XML_Data *xml = user_data;

  if(strcmp("price", xml->last_balise) == 0)
  {
    char *value = malloc(len * sizeof(xmlChar));
    sprintf(value, "%.*s", len, ch);
    double n = atof(value);
    if(n != 0)
    {
      xml->price[xml->last_relais] += n;
    }
  }
}
