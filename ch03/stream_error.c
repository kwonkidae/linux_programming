#include <stdio.h>

int main() {
  FILE* pFile;
  pFile = fopen("myfile.txt", "r");
  if (!pFile) perror("Error opening file");
  else {
    fputc('x', pFile);
    if (ferror(pFile)) {
      printf("Error Writing to myfile.txt\n");
      clearerr(pFile);
    }
    fgetc(pFile);
    if (!ferror(pFile)) printf("No errors reading myfile.txt\n");
    fclose(pFile);
  }
  return 0;
}
