#!/usr/bin/env node
/**
 * JSON Parser Behavior Comparison (Node.js/JavaScript)
 */

const fs = require('fs');
const path = require('path');

// Import optional libraries with fallbacks
let fastJsonParse;
let json5;

try {
    fastJsonParse = require('fast-json-parse');
} catch (e) {
    fastJsonParse = null;
}

try {
    json5 = require('json5');
} catch (e) {
    json5 = null;
}

function loadTestData(filename) {
    const testDataPath = path.join('/app', 'test_data', filename);
    return fs.readFileSync(testDataPath, 'utf8');
}

// Parser configuration
const parsers = [
    {
        name: 'Standard JSON.parse',
        fn: (jsonStr) => JSON.parse(jsonStr),
        available: true
    },
    {
        name: 'fast-json-parse',
        fn: (jsonStr) => {
            const result = fastJsonParse(jsonStr);
            if (result.err) throw result.err;
            return result.value;
        },
        available: !!fastJsonParse
    },
    {
        name: 'JSON5.parse',
        fn: (jsonStr) => json5.parse(jsonStr),
        available: !!json5
    }
];

function runTest(testName, filename, extractValue = (result) => result.username) {
    console.log(`${testName}`);
    const jsonStr = loadTestData(filename);

    parsers.forEach(parser => {
        if (!parser.available) {
            console.log(`${parser.name}: not available`);
            return;
        }

        try {
            const result = parser.fn(jsonStr);
            const value = extractValue(result);
            const typeInfo = typeof value === 'number' ? ` (type: ${typeof value})` : '';
            console.log(`${parser.name}: ${value}${typeInfo} (success)`);
        } catch (e) {
            console.log(`${parser.name}: error - ${e.message}`);
        }
    });

    console.log();
}

function main() {
    console.log("=== JSON Parser Behavior Comparison (Node.js) ===\n");

    // Test cases
    runTest("1. Duplicate Keys Test", 'duplicate_keys.json');
    runTest("2. Large Numbers Test", 'large_numbers.json', (result) => result.value);
    runTest("3. Null Character Test", 'bad_unicode_1.json');
    runTest("4. C1 Control Code Test", 'bad_unicode_2.json');
    runTest("5. Unpaired Surrogate Test", 'bad_unicode_3.json');
    runTest("6. Noncharacter Test", 'bad_unicode_4.json');
}

if (require.main === module) {
    main();
}
