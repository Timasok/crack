#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "graph_module.h"
#include "text_funcs.h"

// const char * file_name = "CRACK_ME.COM";
const char * file_name = "../../.dosbox/TIMA33/UP/CRACK_ME.COM";

int main()
{
    system("./sfml-app");
    char password[10] = {};

    Text_info src = {};
    textCtor(&src, file_name);

    printText(&src);
    textEdit(&src);
    picturePerfect();

    textDtor(&src);
}