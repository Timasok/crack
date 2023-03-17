#include <stdio.h>
#include <string.h>

#include "text_funcs.h"

// const char * file_name = "CRACK_ME.COM";
const char * file_name = "../../.dosbox/TIMA33/UP/CRACK_ME.COM";
int main()
{
    char password[10] = {};

    Text_info src = {};
    textCtor(&src, file_name);
    printText(&src);
    textEdit(&src);

    textDtor(&src);
}