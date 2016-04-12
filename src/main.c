// XML library
#include <libxml/parser.h>
#include <string.h>

#include "directory.h"
#include "xml_data.h"
#include "xml_reader.h"
#include "xml_writer.h"

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

  write_data("result.xml", *data);

  XML_Data_destroy(data);

  return EXIT_SUCCESS;
}
