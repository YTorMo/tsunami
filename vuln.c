#include <string.h>

int main (int argc, char **argv)
{  
    char buffer[64];
	//strcpy es la vulnerabilidad que proboca el overflow ya que no controla el tamaño del string que se le pasa.
    strcpy (buffer, argv[1]);

    return 0;
}
