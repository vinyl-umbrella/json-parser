#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test case structure
typedef struct
{
    const char *name;
    const char *filename;
    const char *test_type;
} test_case_t;

// Test cases definition
static const test_case_t test_cases[] = {
    {"1. Duplicate Keys Test", "duplicate_keys.json", "duplicate_keys"},
    {"2. Large Numbers Test", "large_numbers.json", "large_numbers"},
    {"3. Null Character Test", "bad_unicode_1.json", "bad_unicode"},
    {"4. C1 Control Code Test", "bad_unicode_2.json", "bad_unicode"},
    {"5. Unpaired Surrogate Test", "bad_unicode_3.json", "bad_unicode"},
    {"6. Noncharacter Test", "bad_unicode_4.json", "bad_unicode"},
    {NULL, NULL, NULL} // Sentinel
};

// Forward declarations
char *load_test_data(const char *filename);
void run_test_case(const test_case_t *test_case);
void run_library_test(const char *json_str, const char *test_type, const char *library_name,
                      void (*test_func)(const char *, const char *));

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

// Helper function to run a test with a specific library
void run_library_test(const char *json_str, const char *test_type, const char *library_name,
                      void (*test_func)(const char *, const char *))
{
    if (test_func)
    {
        test_func(json_str, test_type);
    }
    else
    {
        printf("%s: not available (library not linked)\n", library_name);
    }
}

// Run a single test case with all available libraries
void run_test_case(const test_case_t *test_case)
{
    printf("%s\n", test_case->name);
    char *json_str = load_test_data(test_case->filename);
    if (!json_str)
        return;

#ifdef HAVE_CJSON
    run_library_test(json_str, test_case->test_type, "cJSON", cjson_parse_test);
#else
    run_library_test(json_str, test_case->test_type, "cJSON", NULL);
#endif

#ifdef HAVE_JANSSON
    run_library_test(json_str, test_case->test_type, "jansson", jansson_parse_test);
#else
    run_library_test(json_str, test_case->test_type, "jansson", NULL);
#endif

#ifdef HAVE_JSON_C
    run_library_test(json_str, test_case->test_type, "json-c", json_c_parse_test);
#else
    run_library_test(json_str, test_case->test_type, "json-c", NULL);
#endif

#ifdef HAVE_PARSON
    // Skip parson for certain bad unicode tests as it may crash
    if (strcmp(test_case->test_type, "bad_unicode") == 0)
    {
        printf("parson: skipped (known to crash on certain unicode sequences)\n");
    }
    else
    {
        run_library_test(json_str, test_case->test_type, "parson", parson_parse_test);
    }
#else
    run_library_test(json_str, test_case->test_type, "parson", NULL);
#endif

    free(json_str);
    printf("\n");
}

int main(void)
{
    printf("=== JSON Parser Behavior Comparison (C) ===\n\n");

    // Run all test cases
    for (int i = 0; test_cases[i].name != NULL; i++)
    {
        run_test_case(&test_cases[i]);
    }

    return 0;
}
