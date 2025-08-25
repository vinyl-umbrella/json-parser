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

func loadTestData(filename string) (string, error) {
	path := filepath.Join("/app", "test_data", filename)
	data, err := os.ReadFile(path)
	if err != nil {
		return "", err
	}
	return string(data), nil
}

func main() {
	fmt.Println("=== JSON Parser Behavior Comparison (Go) ===")

	testDuplicateKeys()
	testLargeNumbers()
}

func testDuplicateKeys() {
	fmt.Println("1. Duplicate Keys Test")
	jsonStr, err := loadTestData("duplicate_keys.json")
	if err != nil {
		fmt.Printf("Error loading test data: %v\n", err)
		return
	}
	jsonBytes := []byte(jsonStr)

	// Standard library
	var data TestData
	err = json.Unmarshal(jsonBytes, &data)
	fmt.Printf("Standard json.Unmarshal: %s (error: %v)\n", data.Username, err)

	// jsonparser library
	username, err := jsonparser.GetString(jsonBytes, "username")
	fmt.Printf("jsonparser.GetString: %s (error: %v)\n", username, err)

	// json-iterator
	var jsoniterData TestData
	err = jsoniter.Unmarshal(jsonBytes, &jsoniterData)
	fmt.Printf("jsoniter.Unmarshal: %s (error: %v)\n", jsoniterData.Username, err)

	fmt.Println()
}

func testLargeNumbers() {
	fmt.Println("3. Large Numbers Test")
	jsonStr, err := loadTestData("large_numbers.json")
	if err != nil {
		fmt.Printf("Error loading test data: %v\n", err)
		return
	}
	jsonBytes := []byte(jsonStr)

	// Standard library
	var data TestData
	err = json.Unmarshal(jsonBytes, &data)
	fmt.Printf("Standard json.Unmarshal: %d (error: %v)\n", data.Value, err)

	// jsonparser library
	value, err := jsonparser.GetInt(jsonBytes, "value")
	fmt.Printf("jsonparser.GetInt: %d (error: %v)\n", value, err)

	// json-iterator
	var jsoniterData TestData
	err = jsoniter.Unmarshal(jsonBytes, &jsoniterData)
	fmt.Printf("jsoniter.Unmarshal: %d (error: %v)\n", jsoniterData.Value, err)

	fmt.Println()
}
