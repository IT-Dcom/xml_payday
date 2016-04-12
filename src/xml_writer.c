#include <stdio.h>
#include <string.h>
#include <libxml/encoding.h>

#include "xml_writer.h"

#define MY_ENCODING "ISO-8859-1"

void
write_data(const char *file, XML_Data data) {
  int rc;
  xmlTextWriterPtr writer;
  xmlDocPtr doc;
  xmlNodePtr node;
  xmlChar *tmp;

  doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
  if (doc == NULL) {
    printf("testXmlwriterTree: Error creating the xml document tree\n");
    return;
  }

  node = xmlNewDocNode(doc, NULL, BAD_CAST "parse", NULL);
  if (node == NULL) {
    printf("testXmlwriterTree: Error creating the xml node\n");
    return;
  }

  xmlDocSetRootElement(doc, node);

  writer = xmlNewTextWriterTree(doc, node, 0);
  if (writer == NULL) {
    printf("testXmlwriterTree: Error creating the xml writer\n");
    return;
  }

  rc = xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL);
  if (rc < 0) {
    printf("testXmlwriterTree: Error at xmlTextWriterStartDocument\n");
    return;
  }

  write_element(writer, "relays", NULL, 0);
  for(size_t i = 0; i < 6000; ++i)
  {
    ElementAttribute attrs[2];
    char buffer_id[5];
    char buffer_value[16];
    sprintf(buffer_id, "%zu", i);
    sprintf(buffer_value, "%lf", data.price[i]);
    attrs[0] = init_attribute("id", buffer_id);
    attrs[1] = init_attribute("payment", buffer_value);

    write_element(writer, "relay", attrs, 2);
    close_element(writer);

    free_attribute(attrs[0]);
    free_attribute(attrs[1]);
  }
  close_element(writer);

  rc = xmlTextWriterEndDocument(writer);
  if (rc < 0) {
    printf("testXmlwriterTree: Error at xmlTextWriterEndDocument\n");
    return;
  }

  xmlFreeTextWriter(writer);

  xmlSaveFileEnc(file, doc, MY_ENCODING);

  xmlFreeDoc(doc);
}

int
write_element(xmlTextWriterPtr writer, char *name,
              ElementAttribute *attributes, size_t length) {
  int rc = xmlTextWriterStartElement(writer, BAD_CAST name);
  if (rc < 0) {
    printf("testXmlwriterTree: Error at xmlTextWriterStartElement\n");
    return -1;
  }

  for(size_t i = 0; i < length; ++i) {
    rc = xmlTextWriterWriteAttribute(writer, BAD_CAST attributes[i].name,
                                     BAD_CAST attributes[i].value);
    if (rc < 0) {
      printf("testXmlwriterTree: Error at xmlTextWriterWriteAttribute\n");
      return -1;
    }
  }
  return 0;
}

int
close_element(xmlTextWriterPtr writer) {
  int rc = xmlTextWriterEndElement(writer);
  if (rc < 0) {
    printf("testXmlwriterTree: Error at xmlTextWriterEndElement\n");
    return -1;
  }
  return 0;
}

int
write_writer_element(xmlTextWriterPtr writer, char *name, char *content) {
  int rc = 0;
  xmlTextWriterWriteFormatElement(writer, BAD_CAST name, BAD_CAST content);
  if (rc < 0) {
    printf("testXmlwriterTree: Error at xmlTextWriterWriteFormatElement\n");
    return -1;
  }
  return 0;
}

ElementAttribute
init_attribute(char *name, char *value)
{
  ElementAttribute attr;
  attr.name = malloc(strlen(name) + 1);
  strcpy(attr.name, name);

  attr.value = malloc(strlen(value) + 1);
  strcpy(attr.value, value);

  return attr;
}

void
free_attribute(ElementAttribute attr)
{
  free(attr.name);
  free(attr.value);
}
