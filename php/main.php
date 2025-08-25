<?php

function loadTestData($filename) {
    $path = "/app/test_data/" . $filename;
    return file_get_contents($path);
}

function runTest($testName, $filename, $extractValue = null) {
    echo $testName . "\n";
    $jsonStr = loadTestData($filename);

    // Standard json_decode
    $result = json_decode($jsonStr, true);
    if (json_last_error() === JSON_ERROR_NONE) {
        $value = $extractValue ? $extractValue($result) : $result['username'];
        echo "json_decode: " . $value . " (success)\n";
    } else {
        echo "json_decode: error - " . json_last_error_msg() . "\n";
    }

    // json_decode with JSON_BIGINT_AS_STRING (for large numbers test)
    if (strpos($testName, "Large Numbers") !== false) {
        $result = json_decode($jsonStr, true, 512, JSON_BIGINT_AS_STRING);
        if (json_last_error() === JSON_ERROR_NONE) {
            $value = $extractValue ? $extractValue($result) : $result['username'];
            echo "json_decode (BIGINT_AS_STRING): " . $value . " (type: " . gettype($value) . ")\n";
        } else {
            echo "json_decode (BIGINT_AS_STRING): error - " . json_last_error_msg() . "\n";
        }
    }

    // simdjson-php (if available)
    if (function_exists('simdjson_decode')) {
        try {
            $result = simdjson_decode($jsonStr, true);
            $value = $extractValue ? $extractValue($result) : $result['username'];
            echo "simdjson_decode: " . $value . " (success)\n";
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

    $testCases = [
        ["1. Duplicate Keys Test", "duplicate_keys.json"],
        ["2. Large Numbers Test", "large_numbers.json", function($result) {
            return $result['value'] . " (type: " . gettype($result['value']) . ")";
        }],
        ["3. Null Character Test", "bad_unicode_1.json"],
        ["4. C1 Control Code Test", "bad_unicode_2.json"],
        ["5. Unpaired Surrogate Test", "bad_unicode_3.json"],
        ["6. Noncharacter Test", "bad_unicode_4.json"]
    ];

    foreach ($testCases as $testCase) {
        $testName = $testCase[0];
        $filename = $testCase[1];
        $extractValue = isset($testCase[2]) ? $testCase[2] : null;

        runTest($testName, $filename, $extractValue);
    }
}

main();
?>
