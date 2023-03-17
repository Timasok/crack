#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "text_funcs.h"

const char* TXT_BORDER = "************************************************************";

static FILE *text_logs;

#define ASSERT_OK(textPtr)                                                  \
   do{                                                                      \
      if (returnTextError(textPtr) != 0)                                    \
       {  /*fprintf(stderr, "DUMP_CALLED: file: %s func: %s line: %d\n",*/  \
                            /*  __FILE__, __FUNCTION__, __LINE__); */       \
           printText(textPtr);                                              \
       }                                                                    \
   } while (0)

#define PRINT_LOG(...)                                                  \
        do {                                                            \
            fprintf(text_logs, __VA_ARGS__);                            \
        } while(0)   

int openTextLogs()
{
    text_logs = fopen("./logs/text_log.txt", "w+");
    return 0;
}

int closeTextLogs()
{
    fclose(text_logs);
    return 0;
}

int textCtor(Text_info * text, const char * file_name)
{
    ASSERT((file_name != nullptr));
    openTextLogs();

    text->file_name = strdup(file_name);
    text->source_file = fopen(file_name, "rb");

    ASSERT((text->source_file != nullptr));

    struct stat data = {};
    stat(file_name, &data);
    text->buf_length = data.st_size;

    // fseek(text->source_file, 0L, SEEK_END);
    // text->buf_length = ftell(text->source_file);

    text->buf = (char *)calloc(text->buf_length + 2, sizeof(char));

    fread(text->buf, sizeof(char), text->buf_length, text->source_file);

    fclose(text->source_file);

    return 0;
}

int textEdit(Text_info * text)
{
    printf("Choose crack mode\n\t1 - easy\n\t2 - hardcore\n");

    char answer;
    int symbol = getchar(); 
    
    if (symbol != '\n')
        ungetc(symbol, stdin);
      
    answer = getchar();

    while (getchar() != '\n')
        ;

    if (answer == '1')
    {
        int pass_len = 4;
        const char * old_password = "opa$";
        text->corrected_adr = 0x0000035B;//aboba password start
        // printf("%s\n", &text->buf[text->corrected_adr]);

        for (size_t i = text->corrected_adr; i - text->corrected_adr < pass_len; i++ )
        {
            text->buf[i] = old_password[i - text->corrected_adr];
        }

        return 0;

    }else if(answer == '2')
    {
        text->corrected_adr = 0x000002E5;

        text->buf[text->corrected_adr] = 0x33;
        text->buf[text->corrected_adr+1] = 0x0C0;
    }

    return 0;
}

int textDtor(Text_info * text)
{
    text->source_file = fopen(text->file_name, "wb");
    fwrite(text->buf, sizeof(char), text->buf_length, text->source_file);
    fclose(text->source_file);

    free(text->file_name);
    free(text->buf);
    closeTextLogs();
    return 0;
}

int printText(Text_info * text)
{
    ASSERT((text != nullptr));

    PRINT_LOG("\n%s\n", TXT_BORDER);
    PRINT_LOG("FILE = %p\n", text);
    PRINT_LOG("Code_of_error = %d\n", text->code_of_error);
    PRINT_LOG("Buf_length = %ld\n", text->buf_length);
    PRINT_LOG("\n%s\n", TXT_BORDER);

    return 0;
}

int stringDump(const char *string, const char * name_of_var, const char * name_of_file, const char * name_of_func, int number_of_line)
{
    printf("\e[0;32m\n%s\e[0m at %s at %s(%d)\n",  name_of_var, name_of_func,
           name_of_file, number_of_line);

    printf("string = %s, string_length = %ld\n", string, strlen(string));

    return 0;
}

int returnTextError(Text_info * text)
{

    text->code_of_error |= ((!text->source_file) * TEXT_ERROR_SOURCE_FILE_IS_NULL);

    text->code_of_error |= ((!text->lines) * TEXT_ERROR_LINES_IS_NULL);

    text->code_of_error |= ((text->number_of_lines < 1) * TEXT_ERROR_NUMBER_OF_LINES_IS_INAPROPRIATE);

    text->code_of_error |= ((!text->buf) * TEXT_ERROR_BUF_IS_NULL);

    return text->code_of_error;

}

// =====^^actual funcs^^=====

//lines == nullptr
int textCtorOnlyBuffer(Text_info * text, const char * file_name)
{
    // DBG_OUT;
    ASSERT((file_name != nullptr));
    openTextLogs();

    text->source_file = fopen(file_name, "r");
    
    ASSERT((text->source_file != nullptr));

    struct stat data = {};
    stat(file_name, &data);
    text->buf_length = data.st_size;

    text->buf = (char *)calloc(text->buf_length + 2, sizeof(char));

    fread(text->buf, sizeof(char), text->buf_length, text->source_file);

    fclose(text->source_file);

    text->buf[text->buf_length] = '\0';

    text->number_of_lines = 1;
    for (size_t counter = 0;counter <= text->buf_length; counter++)
    {
        if(text->buf[counter] == '\n')
        {
            // text->buf[counter] = '\0';
            text->number_of_lines++;
        }
        
    }

    text->lines = (const char **)calloc(text->number_of_lines, sizeof(char *));
    
    //ASSERT_OK(text);

    return 0;
}

#undef ASSERT_OK