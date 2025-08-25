import json
import os

import orjson
import simplejson
import ujson


def load_test_data(filename):
    test_data_path = os.path.join("/app", "test_data", filename)
    with open(test_data_path, "r") as f:
        return f.read()


def test_duplicate_keys():
    print("1. Duplicate Keys Test")
    json_str = load_test_data("duplicate_keys.json")

    # Standard library
    try:
        result = json.loads(json_str)
        print(f"Standard json.loads: {result.get('username')} (success)")
    except Exception as e:
        print(f"Standard json.loads: error - {e}")

    # ujson
    if ujson:
        try:
            result = ujson.loads(json_str)
            print(f"ujson.loads: {result.get('username')} (success)")
        except Exception as e:
            print(f"ujson.loads: error - {e}")
    else:
        print("ujson.loads: not available")

    # orjson
    if orjson:
        try:
            result = orjson.loads(json_str)
            print(f"orjson.loads: {result.get('username')} (success)")
        except Exception as e:
            print(f"orjson.loads: error - {e}")
    else:
        print("orjson.loads: not available")

    # simplejson
    if simplejson:
        try:
            result = simplejson.loads(json_str)
            print(f"simplejson.loads: {result.get('username')} (success)")
        except Exception as e:
            print(f"simplejson.loads: error - {e}")
    else:
        print("simplejson.loads: not available")

    print()


def test_large_numbers():
    print("3. Large Numbers Test")
    json_str = load_test_data("large_numbers.json")

    # Standard library
    try:
        result = json.loads(json_str)
        print(f"Standard json.loads: {result['value']} (type: {type(result['value'])})")
    except Exception as e:
        print(f"Standard json.loads: error - {e}")

    # ujson
    if ujson:
        try:
            result = ujson.loads(json_str)
            print(f"ujson.loads: {result['value']} (type: {type(result['value'])})")
        except Exception as e:
            print(f"ujson.loads: error - {e}")
    else:
        print("ujson.loads: not available")

    # orjson
    if orjson:
        try:
            result = orjson.loads(json_str)
            print(f"orjson.loads: {result['value']} (type: {type(result['value'])})")
        except Exception as e:
            print(f"orjson.loads: error - {e}")
    else:
        print("orjson.loads: not available")

    # simplejson
    if simplejson:
        try:
            result = simplejson.loads(json_str)
            print(f"simplejson.loads: {result['value']} (type: {type(result['value'])})")
        except Exception as e:
            print(f"simplejson.loads: error - {e}")
    else:
        print("simplejson.loads: not available")

    print()

def main():
    print("=== JSON Parser Behavior Comparison (Python) ===\n")

    test_duplicate_keys()
    test_large_numbers()


if __name__ == "__main__":
    main()
