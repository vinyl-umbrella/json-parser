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

function testDuplicateKeys() {
    console.log("1. Duplicate Keys Test");
    const jsonStr = loadTestData('duplicate_keys.json');

    // Standard JSON.parse
    try {
        const result = JSON.parse(jsonStr);
        console.log(`Standard JSON.parse: ${result.username} (success)`);
    } catch (e) {
        console.log(`Standard JSON.parse: error - ${e.message}`);
    }

    // fast-json-parse
    if (fastJsonParse) {
        try {
            const result = fastJsonParse(jsonStr);
            if (result.err) {
                console.log(`fast-json-parse: error - ${result.err.message}`);
            } else {
                console.log(`fast-json-parse: ${result.value.username} (success)`);
            }
        } catch (e) {
            console.log(`fast-json-parse: error - ${e.message}`);
        }
    } else {
        console.log("fast-json-parse: not available");
    }

    // JSON5
    if (json5) {
        try {
            const result = json5.parse(jsonStr);
            console.log(`JSON5.parse: ${result.username} (success)`);
        } catch (e) {
            console.log(`JSON5.parse: error - ${e.message}`);
        }
    } else {
        console.log("JSON5.parse: not available");
    }

    console.log();
}

function testLargeNumbers() {
    console.log("3. Large Numbers Test");
    const jsonStr = loadTestData('large_numbers.json');

    // Standard JSON.parse
    try {
        const result = JSON.parse(jsonStr);
        console.log(`Standard JSON.parse: ${result.value} (type: ${typeof result.value})`);
    } catch (e) {
        console.log(`Standard JSON.parse: error - ${e.message}`);
    }

    // fast-json-parse
    if (fastJsonParse) {
        try {
            const result = fastJsonParse(jsonStr);
            if (result.err) {
                console.log(`fast-json-parse: error - ${result.err.message}`);
            } else {
                console.log(`fast-json-parse: ${result.value.value} (type: ${typeof result.value.value})`);
            }
        } catch (e) {
            console.log(`fast-json-parse: error - ${e.message}`);
        }
    } else {
        console.log("fast-json-parse: not available");
    }

    // JSON5
    if (json5) {
        try {
            const result = json5.parse(jsonStr);
            console.log(`JSON5.parse: ${result.value} (type: ${typeof result.value})`);
        } catch (e) {
            console.log(`JSON5.parse: error - ${e.message}`);
        }
    } else {
        console.log("JSON5.parse: not available");
    }

    console.log();
}

function main() {
    console.log("=== JSON Parser Behavior Comparison (Node.js) ===\n");

    testDuplicateKeys();
    testLargeNumbers();
}

if (require.main === module) {
    main();
}
