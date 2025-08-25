#include <stdio.h>
#include <string.h>
#ifdef HAVE_JANSSON
#include <jansson.h>
#endif

void jansson_parse_test(const char *json_str, const char *test_name)
{
#ifdef HAVE_JANSSON
    json_error_t error;
    // Use JSON_ALLOW_NUL flag for bad unicode tests
    size_t flags = 0;
    if (strcmp(test_name, "bad_unicode") == 0)
    {
        flags = JSON_ALLOW_NUL;
    }

    json_t *json = json_loads(json_str, flags, &error);
    if (!json)
    {
        printf("jansson: error - %s at line %d column %d\n", error.text, error.line, error.column);
        return;
    }

    if (strcmp(test_name, "duplicate_keys") == 0)
    {
        json_t *username = json_object_get(json, "username");
        if (json_is_string(username))
        {
            printf("jansson: %s (success)\n", json_string_value(username));
        }
        else
        {
            printf("jansson: username not found\n");
        }
    }
    else if (strcmp(test_name, "trailing_commas") == 0)
    {
        json_t *username = json_object_get(json, "username");
        json_t *value = json_object_get(json, "value");
        if (username && value)
        {
            printf("jansson: success - %s, %lld\n", json_string_value(username), json_integer_value(value));
        }
        else
        {
            printf("jansson: parse failed\n");
        }
    }
    else if (strcmp(test_name, "large_numbers") == 0)
    {
        json_t *value = json_object_get(json, "value");
        if (json_is_integer(value))
        {
            printf("jansson: %lld (success)\n", json_integer_value(value));
        }
        else
        {
            printf("jansson: value not found\n");
        }
    }
    else if (strcmp(test_name, "comments") == 0 || strcmp(test_name, "single_quotes") == 0)
    {
        json_t *username = json_object_get(json, "username");
        json_t *value = json_object_get(json, "value");
        if (username && value)
        {
            printf("jansson: success - %s, %lld\n", json_string_value(username), json_integer_value(value));
        }
        else
        {
            printf("jansson: parse failed\n");
        }
    }
    else if (strcmp(test_name, "bad_unicode") == 0)
    {
        json_t *username = json_object_get(json, "username");
        if (json_is_string(username))
        {
            const char *username_str = json_string_value(username);
            printf("jansson: username=\"");
            // Print each character as hex to show how it's handled
            for (const char *p = username_str; *p; p++)
            {
                printf("\\x%02x", (unsigned char)*p);
            }
            printf("\" (success)\n");
        }
        else
        {
            printf("jansson: username not found\n");
        }
    }

    json_decref(json);
#else
    printf("jansson: not available (library not linked)\n");
#endif
}
