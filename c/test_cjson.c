#include <stdio.h>
#include <string.h>
#ifdef HAVE_CJSON
#include <cjson/cJSON.h>
#endif

void cjson_parse_test(const char *json_str, const char *test_name)
{
#ifdef HAVE_CJSON
    cJSON *json = cJSON_Parse(json_str);
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        printf("cJSON: error - %s\n", error_ptr ? error_ptr : "parse error");
        return;
    }

    if (strcmp(test_name, "duplicate_keys") == 0)
    {
        cJSON *username = cJSON_GetObjectItem(json, "username");
        if (username && cJSON_IsString(username))
        {
            printf("cJSON: %s (success)\n", username->valuestring);
        }
        else
        {
            printf("cJSON: username not found\n");
        }
    }
    else if (strcmp(test_name, "trailing_commas") == 0)
    {
        cJSON *username = cJSON_GetObjectItem(json, "username");
        cJSON *value = cJSON_GetObjectItem(json, "value");
        if (username && value)
        {
            printf("cJSON: success - %s, %d\n", username->valuestring, value->valueint);
        }
        else
        {
            printf("cJSON: parse failed\n");
        }
    }
    else if (strcmp(test_name, "large_numbers") == 0)
    {
        cJSON *value = cJSON_GetObjectItem(json, "value");
        if (value && cJSON_IsNumber(value))
        {
            printf("cJSON: %.0f (success)\n", value->valuedouble);
        }
        else
        {
            printf("cJSON: value not found\n");
        }
    }
    else if (strcmp(test_name, "comments") == 0 || strcmp(test_name, "single_quotes") == 0)
    {
        cJSON *username = cJSON_GetObjectItem(json, "username");
        cJSON *value = cJSON_GetObjectItem(json, "value");
        if (username && value)
        {
            printf("cJSON: success - %s, %d\n", username->valuestring, value->valueint);
        }
        else
        {
            printf("cJSON: parse failed\n");
        }
    }
    else if (strcmp(test_name, "bad_unicode") == 0)
    {
        cJSON *username = cJSON_GetObjectItem(json, "username");
        if (username && cJSON_IsString(username))
        {
            const char *username_str = username->valuestring;
            printf("cJSON: username=\"");
            // Print each character as hex to show how it's handled
            for (const char *p = username_str; *p; p++)
            {
                printf("\\x%02x", (unsigned char)*p);
            }
            printf("\" (success)\n");
        }
        else
        {
            printf("cJSON: username not found\n");
        }
    }

    cJSON_Delete(json);
#else
    printf("cJSON: not available (library not linked)\n");
#endif
}
