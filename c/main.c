#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
void test_duplicate_keys(void);
void test_trailing_commas(void);
void test_large_numbers(void);
void test_comments(void);
void test_single_quotes(void);
char *load_test_data(const char *filename);

// External library test functions
#ifdef HAVE_CJSON
extern void cjson_parse_test(const char *json_str, const char *test_name);
#endif
#ifdef HAVE_JANSSON
extern void jansson_parse_test(const char *json_str, const char *test_name);
#endif
#ifdef HAVE_JSON_C
extern void json_c_parse_test(const char *json_str, const char *test_name);
#endif
#ifdef HAVE_PARSON
extern void parson_parse_test(const char *json_str, const char *test_name);
#endif

// Load test data from file
char *load_test_data(const char *filename)
{
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "/app/test_data/%s", filename);

    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        printf("Error: Could not open file %s\n", filepath);
        return NULL;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer
    char *buffer = malloc(file_size + 1);
    if (!buffer)
    {
        fclose(file);
        return NULL;
    }

    // Read file content
    size_t read_size = fread(buffer, 1, file_size, file);
    buffer[read_size] = '\0';

    fclose(file);
    return buffer;
}

void test_duplicate_keys(void)
{
    printf("1. Duplicate Keys Test\n");
    char *json_str = load_test_data("duplicate_keys.json");
    if (!json_str)
        return;

#ifdef HAVE_CJSON
    cjson_parse_test(json_str, "duplicate_keys");
#else
    printf("cJSON: not available (library not linked)\n");
#endif

#ifdef HAVE_JANSSON
    jansson_parse_test(json_str, "duplicate_keys");
#else
    printf("jansson: not available (library not linked)\n");
#endif

#ifdef HAVE_JSON_C
    json_c_parse_test(json_str, "duplicate_keys");
#else
    printf("json-c: not available (library not linked)\n");
#endif

#ifdef HAVE_PARSON
    parson_parse_test(json_str, "duplicate_keys");
#else
    printf("parson: not available (library not linked)\n");
#endif

    free(json_str);
    printf("\n");
}

void test_large_numbers(void)
{
    printf("3. Large Numbers Test\n");
    char *json_str = load_test_data("large_numbers.json");
    if (!json_str)
        return;

#ifdef HAVE_CJSON
    cjson_parse_test(json_str, "large_numbers");
#else
    printf("cJSON: not available (library not linked)\n");
#endif

#ifdef HAVE_JANSSON
    jansson_parse_test(json_str, "large_numbers");
#else
    printf("jansson: not available (library not linked)\n");
#endif

#ifdef HAVE_JSON_C
    json_c_parse_test(json_str, "large_numbers");
#else
    printf("json-c: not available (library not linked)\n");
#endif

#ifdef HAVE_PARSON
    parson_parse_test(json_str, "large_numbers");
#else
    printf("parson: not available (library not linked)\n");
#endif

    free(json_str);
    printf("\n");
}

int main(void)
{
    printf("=== JSON Parser Behavior Comparison (C) ===\n\n");

    test_duplicate_keys();
    test_large_numbers();

    return 0;
}
