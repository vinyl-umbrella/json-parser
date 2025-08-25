package main

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"

	"github.com/buger/jsonparser"
	jsoniter "github.com/json-iterator/go"
)

type TestData struct {
	Username string `json:"username"`
	Value    int64  `json:"value"`
}

type TestCase struct {
	Name     string
	Filename string
	TestFunc func([]byte)
}

func loadTestData(filename string) ([]byte, error) {
	path := filepath.Join("/app", "test_data", filename)
	return os.ReadFile(path)
}

func testUsername(jsonBytes []byte) {
	// Standard library
	var data TestData
	err := json.Unmarshal(jsonBytes, &data)
	fmt.Printf("  Standard json.Unmarshal: %q (error: %v)\n", data.Username, err)

	// jsonparser library
	username, err := jsonparser.GetString(jsonBytes, "username")
	fmt.Printf("  jsonparser.GetString: %q (error: %v)\n", username, err)

	// json-iterator
	var jsoniterData TestData
	err = jsoniter.Unmarshal(jsonBytes, &jsoniterData)
	fmt.Printf("  jsoniter.Unmarshal: %q (error: %v)\n", jsoniterData.Username, err)
}

func testValue(jsonBytes []byte) {
	// Standard library
	var data TestData
	err := json.Unmarshal(jsonBytes, &data)
	fmt.Printf("  Standard json.Unmarshal: %d (error: %v)\n", data.Value, err)

	// jsonparser library
	value, err := jsonparser.GetInt(jsonBytes, "value")
	fmt.Printf("  jsonparser.GetInt: %d (error: %v)\n", value, err)

	// json-iterator
	var jsoniterData TestData
	err = jsoniter.Unmarshal(jsonBytes, &jsoniterData)
	fmt.Printf("  jsoniter.Unmarshal: %d (error: %v)\n", jsoniterData.Value, err)
}

func runTest(testCase TestCase) {
	fmt.Printf("%s\n", testCase.Name)
	jsonBytes, err := loadTestData(testCase.Filename)
	if err != nil {
		fmt.Printf("  Error loading test data: %v\n", err)
		return
	}
	testCase.TestFunc(jsonBytes)
	fmt.Println()
}

func main() {
	fmt.Println("=== JSON Parser Behavior Comparison (Go) ===")

	testCases := []TestCase{
		{"1. Duplicate Keys Test", "duplicate_keys.json", testUsername},
		{"2. Large Numbers Test", "large_numbers.json", testValue},
		{"3. Null Character Test", "bad_unicode_1.json", testUsername},
		{"4. C1 Control Code Test", "bad_unicode_2.json", testUsername},
		{"5. Unpaired Surrogate Test", "bad_unicode_3.json", testUsername},
		{"6. Noncharacter Test", "bad_unicode_4.json", testUsername},
	}

	for _, testCase := range testCases {
		runTest(testCase)
	}
}
