#include <stdlib.h>
#include "xml_data.h"

XML_Data *
XML_Data_init() {
  XML_Data *data    = malloc(sizeof(XML_Data));
  data->last_balise = malloc(sizeof(char) * 256);
  data->price       = calloc(sizeof(double), 6000);
  data->last_relais = 0;

  return data;
}


bool
XML_Data_destroy(XML_Data* data) {
  free(data->price);
  free(data->last_balise);
  free(data);

  return true;
}
