#include <stdio.h>
#include <windows.h>

//Este programa ejecuta mediante la consola de comandos la calculadora de windows
//y tras un analisis con un debugger podemos obtener el shellcode
int main () {

    LoadLibrary("msvcrt.dll");
    __asm{
        push ebp
        mov ebp,esp
        xor edi,edi
        push edi
        sub esp,08h
        mov byte ptr [ebp-09h],63h
        mov byte ptr [ebp-08h],61h
        mov byte ptr [ebp-07h],6Ch
        mov byte ptr [ebp-06h],63h
        mov byte ptr [ebp-05h],2Eh
        mov byte ptr [ebp-04h],65h
        mov byte ptr [ebp-03h],78h
		mov byte ptr [ebp-02h],65h
        lea eax,[ebp-09h]
        push eax
        //0x77c293c7 es el offset de la consola de comandos dentro de la librería
        //msvcrt.dll y puede ser obtenido mediante el uso de herramientas externas
        mov ebx,0x77c293c7
        call ebx
        }
    }