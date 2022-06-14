#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // se agrega libreria para usar una variable booleana de validación

int main(int argc, char *argv[]) // Aquí definimos de esta manera las variables
{
    // Esta indentación también fue corregida
    int c, i; //, inword;
    // FILE *fp;
    long linect = 0; //, wordct, charct;
    long tlinect = 0, twordct = 0, tcharct = 0; // Estas variables se tienen que inicializar en 0 para que no afecte el resultado de sumatoria

    i = 1;
    bool error = false; // variable para validación

    do
    {
        long wordct = 0, charct = 0; // scope reducido como indica el analisis estatico
        int inword = 0; // scope reducido como indica el analisis estatico
        FILE *fp; // scope reducido como indica el analisis estatico
        
        if ((fp=fopen(argv[i], "r")) == NULL) // Se elimina la condición argc > 1 puesto que sólo validamos que el archivo se abra
        {
            error = true; // se agrega bandera para validar el estado de error
            fprintf (stderr, "can't open %s\n", argv[i]);
            continue; // exit(1) no corresponde aquí porque detiene el ciclo por completo
        }

        while ((c = getc(fp)) != EOF)
        {
            // Aquí se agregaron las llaves restantes a los IF/ELSE
            ++charct;
            if (c == '\n')
            {
                ++linect;
            }
            if (c == ' ' || c == '\t' || c == '\n'){
                inword = 0;
            }
            else if (inword == 0)
            {
                inword = 1;
                ++wordct;
            }
        }

        printf("%7ld %7ld %7ld", linect, wordct, charct);
        if (argc > 1)
        { // Aquí se agregaron las llaves restantes a los IF/ELSE
            printf(" %s\n", argv[i]); // Aquí se agrega la variable iteradora para mostrar el nombre de cada uno de los archivos
        } 
        else
        {
            printf("\n");
        }
        fclose(fp);
        tlinect += linect;
        twordct += wordct;
        tcharct += charct; 

    } while (++i < argc); // Condición corregida para que no tome un último argumento NULL

    // Aquí se agregaron las llaves restantes a los IF/ELSE
    if (argc > 2)
    { // Se modifica la condición para que sólo imprima el total cuando se le pase más de un solo archivo, es decir, más de dos elementos
        printf("%7ld %7ld %7ld total\n", linect, twordct, tcharct); 
    }
    if (error == true) // se valida el status code para cuando finalice el programa
    {
        exit(1); // programa ejecutado pero fallido por la No lectura de un archivo
    }       
    exit(0);
}