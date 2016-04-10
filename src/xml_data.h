#ifndef __XML_DATA_H__
#define __XML_DATA_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct XML_Data {
  char* last_balise;
  size_t last_relais;
  double *price;
}XML_Data;

XML_Data *XML_Data_init();
bool XML_Data_destroy(XML_Data* data);

#endif /* __XML_DATA_H__ */
