#include <stdio.h>
#include <string.h>
#ifdef HAVE_JSON_C
#include <json-c/json.h>
#endif

void json_c_parse_test(const char *json_str, const char *test_name)
{
#ifdef HAVE_JSON_C
    if (!json_str || !test_name)
    {
        printf("json-c: error - invalid input\n");
        return;
    }

    struct json_object *json = json_tokener_parse(json_str);
    if (!json)
    {
        printf("json-c: error - parse error\n");
        return;
    }

    if (strcmp(test_name, "duplicate_keys") == 0)
    {
        struct json_object *username;
        if (json_object_object_get_ex(json, "username", &username) && username)
        {
            const char *username_str = json_object_get_string(username);
            if (username_str)
            {
                printf("json-c: %s (success)\n", username_str);
            }
            else
            {
                printf("json-c: username value is null\n");
            }
        }
        else
        {
            printf("json-c: username not found\n");
        }
    }
    else if (strcmp(test_name, "trailing_commas") == 0)
    {
        struct json_object *username, *value;
        if (json_object_object_get_ex(json, "username", &username) &&
            json_object_object_get_ex(json, "value", &value) &&
            username && value)
        {
            const char *username_str = json_object_get_string(username);
            int value_int = json_object_get_int(value);
            if (username_str)
            {
                printf("json-c: success - %s, %d\n", username_str, value_int);
            }
            else
            {
                printf("json-c: username value is null\n");
            }
        }
        else
        {
            printf("json-c: parse failed\n");
        }
    }
    else if (strcmp(test_name, "large_numbers") == 0)
    {
        struct json_object *value;
        if (json_object_object_get_ex(json, "value", &value) && value)
        {
            int64_t value_val = json_object_get_int64(value);
            printf("json-c: %ld (success)\n", value_val);
        }
        else
        {
            printf("json-c: value not found\n");
        }
    }
    else if (strcmp(test_name, "comments") == 0 || strcmp(test_name, "single_quotes") == 0)
    {
        struct json_object *username, *value;
        if (json_object_object_get_ex(json, "username", &username) &&
            json_object_object_get_ex(json, "value", &value) &&
            username && value)
        {
            const char *username_str = json_object_get_string(username);
            int value_int = json_object_get_int(value);
            if (username_str)
            {
                printf("json-c: success - %s, %d\n", username_str, value_int);
            }
            else
            {
                printf("json-c: username value is null\n");
            }
        }
        else
        {
            printf("json-c: parse failed\n");
        }
    }

    json_object_put(json);
#else
    printf("json-c: not available (library not linked)\n");
#endif
}
