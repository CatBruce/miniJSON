#include <stdio.h>
#include <stdlib.h>

#define JSON_KEY_LEN 256
#define JSON_VALUE_LEN 1024
#define JSON_ELEMENT_LEN 32

typedef struct _json_pair
{
    char* key;
    char* value;
}json_pair_t;

static json_pair_t s_json_data[JSON_ELEMENT_LEN];
int json_obj_parse(char* data)
{
    char* tmp = NULL;
    char* ptr = NULL;
    int element_num = 0;
    int record_len = 0;
    int i = 0;
    if(data == NULL)
    {
        return -1;
    }

    tmp = data;

    if(*tmp++ != '{')
    {
        return -1;
    }

    if(*tmp == '}')
    {
        printf("empty json\n");
        return 0;
    }

    while(*tmp != NULL)
    {
        if((ptr = strchr(tmp, ':')) != NULL)
       if(*(ptr-1) != '\\')
       {
            record_len = ptr - tmp;
            if(*tmp++ != '\"')
            {
                return -1;
            }
            if(((ptr = strchr(tmp, ':')) != NULL) && (ptr-tmp < record_len))
            {
                i = 0;
                for(; i<JSON_ELEMENT_LEN; i++)
                {
                    if(s_json_data[i].key == NULL)
                    {
                        s_json_data[i].key = (char*)malloc(ptr-tmp-1);
                        memset(s_json_data[i].key, 0, ptr-tmp-1);
                        memcpy(s_json_data[i].key, tmp, ptr-tmp-2);
                        printf("key[%s]",s_json_data[i].key);

                        s_json_data[i].value = (char*)malloc(record_len-ptr);
                        memset(s_json_data[i].value, 0, record_len-ptr);
                        memcpy(s_json_data[i].value, ptr+1, record_len-ptr-1);
                        printf("value[%s]\n",s_json_data[i].value);
                        break;
                    }
                }
                if(i == JSON_ELEMENT_LEN) 
                {
                    printf("length over JSON_ELEMENT_LEN\n");
                    return -1;
                }
            }
            else
            {
                printf("wrong json \n");
                return -1;
            }
       } 
    }
    return 0;
} 




int main(int argc, char** argv)
{

    return 0;
}
