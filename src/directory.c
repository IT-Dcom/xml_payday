#include "directory.h"

#ifndef DT_DIR
  #define DT_DIR 4
#endif

#ifndef DT_FILE
  #define DT_FILE 8
#endif

int
file_count(const char *name) {
  DIR *dir;
  struct dirent *entry;
  size_t count = 0;

  if (!(dir = opendir(name)))
    return -1;
  if (!(entry = readdir(dir)))
    return -1;

  do {
    if (entry->d_type == DT_FILE)
      ++count;
  } while (entry = readdir(dir));

  if (closedir(dir) == -1) /* S'il y a eu un souci avec la fermeture */
    exit(-1);

  return count;
}

char **
file_list(const char *name) {
  size_t count = file_count(name);
  char **files = malloc(count * sizeof(char *));
  for(size_t i = 0; i < count; i++)
  {
    files[i] = malloc(256 * sizeof(char));
  }

  DIR *dir;
  struct dirent *entry;

  if (!(dir = opendir(name)))
    return NULL;

  if (!(entry = readdir(dir)))
    return NULL;

  for(size_t i = 0; i < count; ++i, entry = readdir(dir))
  {
    if (entry->d_type == DT_FILE)
      strcpy(files[i], entry->d_name);
    else
      --i;
  }

  if (closedir(dir) == -1) /* S'il y a eu un souci avec la fermeture */
    exit(-1);

  return files;
}
