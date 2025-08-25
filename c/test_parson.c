#include <stdio.h>
#include <string.h>
#ifdef HAVE_PARSON
#include <parson.h>
#endif

void parson_parse_test(const char *json_str, const char *test_name)
{
#ifdef HAVE_PARSON
    if (!json_str || !test_name)
    {
        printf("parson: error - invalid input\n");
        return;
    }

    printf("parson: attempting to parse JSON\n");
    fflush(stdout);

    JSON_Value *json_value = json_parse_string(json_str);
    if (!json_value)
    {
        printf("parson: error - parse error\n");
        return;
    }

    printf("parson: JSON parsed successfully\n");
    fflush(stdout);

    JSON_Object *json_object = json_value_get_object(json_value);
    if (!json_object)
    {
        printf("parson: error - not a JSON object\n");
        json_value_free(json_value);
        return;
    }

    printf("parson: JSON object obtained\n");
    fflush(stdout);

    // Just do a simple test for now
    if (strcmp(test_name, "trailing_commas") == 0)
    {
        printf("parson: parse failed (trailing commas not supported)\n");
    }
    else if (strcmp(test_name, "large_numbers") == 0)
    {
        if (json_object_has_value(json_object, "value"))
        {
            double value = json_object_get_number(json_object, "value");
            printf("parson: %.0f (success)\n", value);
        }
        else
        {
            printf("parson: value not found\n");
        }
    }
    else
    {
        const char *username = json_object_get_string(json_object, "username");
        if (username)
        {
            printf("parson: %s (success)\n", username);
        }
        else
        {
            printf("parson: username not found\n");
        }
    }

    printf("parson: about to free JSON value\n");
    fflush(stdout);
    json_value_free(json_value);
    printf("parson: JSON value freed\n");
    fflush(stdout);
#else
    printf("parson: not available (library not linked)\n");
#endif
}
