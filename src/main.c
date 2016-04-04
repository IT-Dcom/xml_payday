// XML library
#include <libxml/parser.h>

// Appelée à la rencontre de chaque balise ouvrante
void debut_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
    printf("Début de l'élément : %s\n", name);
}

int main () {
  printf ("XML Parser\n");
  xmlSAXHandler sh = { 0 };
  sh.startElement = debut_element;

  xmlParserCtxtPtr ctxt;

  if ((ctxt = xmlCreateFileParserCtxt("../templates/before.xml")) == NULL) {
    fprintf(stderr, "Erreur lors de la création du contexte\n");
    return EXIT_FAILURE;
  }

  ctxt->sax = &sh;
  xmlParseDocument(ctxt);

  if (ctxt->wellFormed) {
    printf("Document XML bien formé\n");
  } else {
    fprintf(stderr, "Document XML mal formé\n");
    xmlFreeParserCtxt(ctxt);
    return EXIT_FAILURE;
  }

  // xmlFreeParserCtxt(ctxt);

  return EXIT_SUCCESS;
}
