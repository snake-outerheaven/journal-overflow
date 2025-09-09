#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// verificar se tres valores obtidos podem ser os 
// lados de um triangulo.

// alerta: o código só pode ser executado em sistemas que seguem o padrão POSIX ( Linux, MacOS, UNIX, FreeBSD e similares.)


// protótipo das funções 

void wait_posix(unsigned int time);
void trim (char *buf);
int converter(float *x);

int main(void) {}


void wait_posix(unsigned int time) { usleep(time * 1000); }

void trim(char *buf) {
  size_t end = strlen(buf);
  size_t start = 0;
  size_t len = 0;

  while(end >= start && isspace(buf++)) start++;

  while (start <= end && isspace(buf++)) end--;
  
  // terminar rascunho depois.

