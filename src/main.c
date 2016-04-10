// XML library
#include <libxml/parser.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "directory.h"
#include "xml_data.h"


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

int
main (void) {
  char * foldername = "../src/xml";
  char ** names     = file_list(foldername);
  size_t count      = file_count(foldername);

  xmlSAXHandler sh = { 0 };
  sh.startElement = start_element;
  sh.characters = caracteres;

  XML_Data *data = XML_Data_init();

  for(size_t i = 0; i < count; ++i)
  {
    size_t length = (strlen(foldername) + strlen(names[i]) + 2);
    char *name = malloc( length * sizeof(char));
    strcat(strcat(strcpy(name, foldername), "/"), names[i]);
    if (xmlSAXUserParseFile(&sh, data, name) != 0)
    {
      fprintf(stderr, "Une erreur est survenue lors du parsing\n");
      return EXIT_FAILURE;
    }
  }

  for(size_t i = 0; i < 6000; i++)
  {
    if(data->price[i] != 0.0)
      printf("Relay %lu -> %lf€\n", i, data->price[i]);
  }

  XML_Data_destroy(data);

  return EXIT_SUCCESS;
}
