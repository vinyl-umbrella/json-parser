<?php

function loadTestData($filename) {
    $path = "/app/test_data/" . $filename;
    return file_get_contents($path);
}

function testDuplicateKeys() {
    echo "1. Duplicate Keys Test\n";
    $jsonStr = loadTestData("duplicate_keys.json");

    // Standard json_decode
    $result = json_decode($jsonStr, true);
    if (json_last_error() === JSON_ERROR_NONE) {
        echo "json_decode: " . $result['username'] . " (success)\n";
    } else {
        echo "json_decode: error - " . json_last_error_msg() . "\n";
    }

    // simdjson-php (if available)
    if (function_exists('simdjson_decode')) {
        try {
            $result = simdjson_decode($jsonStr, true);
            echo "simdjson_decode: " . $result['username'] . " (success)\n";
        } catch (Exception $e) {
            echo "simdjson_decode: error - " . $e->getMessage() . "\n";
        }
    } else {
        echo "simdjson_decode: not available\n";
    }

    echo "\n";
}

function testLargeNumbers() {
    echo "3. Large Numbers Test\n";
    $jsonStr = loadTestData("large_numbers.json");

    // Standard json_decode
    $result = json_decode($jsonStr, true);
    if (json_last_error() === JSON_ERROR_NONE) {
        echo "json_decode: " . $result['value'] . " (type: " . gettype($result['value']) . ")\n";
    } else {
        echo "json_decode: error - " . json_last_error_msg() . "\n";
    }

    // json_decode with JSON_BIGINT_AS_STRING
    $result = json_decode($jsonStr, true, 512, JSON_BIGINT_AS_STRING);
    if (json_last_error() === JSON_ERROR_NONE) {
        echo "json_decode (BIGINT_AS_STRING): " . $result['value'] . " (type: " . gettype($result['value']) . ")\n";
    } else {
        echo "json_decode (BIGINT_AS_STRING): error - " . json_last_error_msg() . "\n";
    }

    // simdjson-php (if available)
    if (function_exists('simdjson_decode')) {
        try {
            $result = simdjson_decode($jsonStr, true);
            echo "simdjson_decode: " . $result['value'] . " (type: " . gettype($result['value']) . ")\n";
        } catch (Exception $e) {
            echo "simdjson_decode: error - " . $e->getMessage() . "\n";
        }
    } else {
        echo "simdjson_decode: not available\n";
    }

    echo "\n";
}

function main() {
    echo "=== JSON Parser Behavior Comparison (PHP) ===\n\n";

    testDuplicateKeys();
    testLargeNumbers();
}

main();
?>
