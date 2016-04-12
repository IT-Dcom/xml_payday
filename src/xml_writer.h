#ifndef __XML_WRITER_H__
#define __XML_WRITER_H__

#include <libxml/xmlwriter.h>
#include "xml_data.h"

typedef struct {
  char * name;
  char * value;
}ElementAttribute;

void             write_data(const char *, XML_Data);
xmlChar         *ConvertInput(const char *, const char *);
int              write_element(xmlTextWriterPtr, char *, ElementAttribute *,
                               size_t);
int              close_element(xmlTextWriterPtr);
int              write_writer_element(xmlTextWriterPtr, char *, char *);
ElementAttribute init_attribute(char *, char *);
void             free_attribute(ElementAttribute);
#endif /* __XML_WRITER_H__ */
