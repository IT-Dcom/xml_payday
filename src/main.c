// XML library
#include <libxml/parser.h>
#include <string.h>

typedef struct XML_Data {
  char last_balise[256];
  char* return_val;
  double price;
  int b;
}XML_Data;

// Appelée à la rencontre de chaque balise ouvrante
void
start_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
  XML_Data *xml = user_data;
  strcpy(xml->last_balise, name);
  printf("Début de l'élément : %s\n", name);
  if (attrs != NULL) {
    for (int i = 0; attrs[i] != NULL; i+=2) {
      printf("Attribut '%s' a pour valeur %s\n", attrs[i], attrs[i+1]);
    }
  }
  // strcpy(user_data.last_balise, name);
  // printf("%s\n", user_data.last_balise);
}

void
caracteres(void *user_data, const xmlChar *ch, int len) {
  XML_Data *xml = user_data;
  // printf("Elément texte : (longueur = %d) %.*s\n", len, len, ch);

  if(strcmp("price", xml->last_balise) == 0)
  {
    char *value = malloc(len * sizeof(xmlChar));
    sprintf(value, "%.*s", len, ch);
    double n = atof(value);
    if(n != 0)
    {
      printf("Value = %lf\n", n);
      xml->price += n;
    }
  }
    // if(strcmp("price", attrs[i]))
    // {
    //   *user_data.price += attrs[i + 1];
    // }
}

xmlEntityPtr
entite(void *user_data, const xmlChar *name) {
    printf("Entité rencontrée : %s\n", name);
    return xmlGetPredefinedEntity(name); // Ceci est le traitement par défaut
}


int
main (void) {
  printf ("XML Parser\n");
  xmlSAXHandler sh = { 0 };
  sh.startElement = start_element;
  sh.characters = caracteres;
  sh.getEntity = entite;

  XML_Data data = { 0 };
  sprintf(data.last_balise, "Lol");

  if (xmlSAXUserParseFile(&sh, &data, "../templates/before.xml") != 0)
  {
    fprintf(stderr, "Une erreur est survenue lors du parsing\n");
      return EXIT_FAILURE;
  }

  printf("final price ! --------------->%lf\n", data.price);
  // xmlParserCtxtPtr ctxt;
  //
  // if ((ctxt = xmlCreateFileParserCtxt("../templates/before.xml")) == NULL) {
  //   fprintf(stderr, "Erreur lors de la création du contexte\n");
  //   return EXIT_FAILURE;
  // }
  //
  // ctxt->sax = &sh;

  // if (ctxt->wellFormed) {
  //   printf("Document XML bien formé\n");
  // } else {
  //   fprintf(stderr, "Document XML mal formé\n");
  //   xmlFreeParserCtxt(ctxt);
  //   return EXIT_FAILURE;
  // }

  // xmlFreeParserCtxt(ctxt);

  return EXIT_SUCCESS;
}
