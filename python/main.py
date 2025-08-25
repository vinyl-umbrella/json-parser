import json
import os

import orjson
import simplejson
import ujson


def load_test_data(filename):
    test_data_path = os.path.join("/app", "test_data", filename)
    with open(test_data_path, "r") as f:
        return f.read()


def test_parser(parser_name, parser_func, json_str, result_key=None):
    """Test a JSON parser and return formatted result."""
    try:
        result = parser_func(json_str)
        if result_key:
            value = result.get(result_key) if hasattr(result, 'get') else result[result_key]
            if parser_name.endswith("large_numbers"):
                print(f"{parser_name}: {value} (type: {type(value)})")
            else:
                print(f"{parser_name}: {value} (success)")
        else:
            print(f"{parser_name}: success")
    except Exception as e:
        print(f"{parser_name}: error - {e}")


def run_parser_tests(test_name, json_str, result_key=None):
    """Run all parsers against the same JSON string."""
    print(f"{test_name}")

    parsers = [
        ("Standard json.loads", json.loads),
        ("ujson.loads", ujson.loads if ujson else None),
        ("orjson.loads", orjson.loads if orjson else None),
        ("simplejson.loads", simplejson.loads if simplejson else None),
    ]

    for name, parser_func in parsers:
        if parser_func is None:
            print(f"{name}: not available")
        else:
            test_parser(name, parser_func, json_str, result_key)

    print()


def test_duplicate_keys():
    json_str = load_test_data("duplicate_keys.json")
    run_parser_tests("1. Duplicate Keys Test", json_str, "username")


def test_large_numbers():
    json_str = load_test_data("large_numbers.json")
    run_parser_tests("2. Large Numbers Test", json_str, "value")


def test_null_char():
    json_str = load_test_data("bad_unicode_1.json")
    run_parser_tests("3. Null Character Test", json_str, "username")

def test_c1_control_code():
    json_str = load_test_data("bad_unicode_2.json")
    run_parser_tests("4. C1 Control Code Test", json_str, "username")

def test_unpaired_surrogate():
    json_str = load_test_data("bad_unicode_3.json")
    run_parser_tests("5. Unpaired Surrogate Test", json_str, "username")

def test_noncharacter():
    json_str = load_test_data("bad_unicode_4.json")
    run_parser_tests("6. Noncharacter Test", json_str, "username")


def main():
    print("=== JSON Parser Behavior Comparison (Python) ===\n")

    test_duplicate_keys()
    test_large_numbers()
    test_null_char()
    test_c1_control_code()
    test_unpaired_surrogate()
    test_noncharacter()


if __name__ == "__main__":
    main()
