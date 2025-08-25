use serde::{Deserialize, Serialize};
use serde_json::{self, Value};
use std::collections::HashMap;
use std::fs;

#[derive(Serialize, Deserialize, Debug)]
struct TestData {
    username: Option<String>,
    value: Option<i64>,
}

fn main() {
    println!("=== JSON Parser Behavior Comparison (Rust) ===\n");

    let tests = [
        ("1. Duplicate Keys Test", "duplicate_keys.json", TestType::DuplicateKeys),
        ("2. Large Numbers Test", "large_numbers.json", TestType::LargeNumbers),
        ("3. Null Character Test", "bad_unicode_1.json", TestType::Unicode),
        ("4. C1 Control Code Test", "bad_unicode_2.json", TestType::Unicode),
        ("5. Unpaired Surrogate Test", "bad_unicode_3.json", TestType::Unicode),
        ("6. Noncharacter Test", "bad_unicode_4.json", TestType::Unicode),
    ];

    for (title, filename, test_type) in tests {
        run_test(title, filename, test_type);
    }
}

#[derive(Clone, Copy)]
enum TestType {
    DuplicateKeys,
    LargeNumbers,
    Unicode,
}

fn run_test(title: &str, filename: &str, test_type: TestType) {
    println!("{}", title);

    let json_str = match load_test_data(filename) {
        Ok(data) => data,
        Err(e) => {
            eprintln!("Error loading test data: {}", e);
            println!();
            return;
        }
    };

    match test_type {
        TestType::DuplicateKeys => test_duplicate_keys_impl(&json_str),
        TestType::LargeNumbers => test_large_numbers_impl(&json_str),
        TestType::Unicode => test_unicode_impl(&json_str),
    }

    println!();
}

fn load_test_data(filename: &str) -> Result<String, Box<dyn std::error::Error>> {
    let path = format!("/app/test_data/{}", filename);
    Ok(fs::read_to_string(path)?)
}

fn test_duplicate_keys_impl(json_str: &str) {
    // serde_json with struct
    match serde_json::from_str::<TestData>(json_str) {
        Ok(data) => println!("serde_json (struct): {:?} (success)", data.username),
        Err(e) => println!("serde_json (struct): error - {}", e),
    }

    // serde_json with HashMap
    match serde_json::from_str::<HashMap<String, Value>>(json_str) {
        Ok(data) => {
            if let Some(username) = data.get("username") {
                println!("serde_json (HashMap): {} (success)", username);
            }
        },
        Err(e) => println!("serde_json (HashMap): error - {}", e),
    }

    // Raw JSON value
    match serde_json::from_str::<Value>(json_str) {
        Ok(data) => {
            if let Some(username) = data["username"].as_str() {
                println!("serde_json (Value): {} (success)", username);
            }
        },
        Err(e) => println!("serde_json (Value): error - {}", e),
    }
}

fn test_large_numbers_impl(json_str: &str) {
    // serde_json with struct
    match serde_json::from_str::<TestData>(json_str) {
        Ok(data) => println!("serde_json: {:?} (success)", data.value),
        Err(e) => println!("serde_json: error - {}", e),
    }

    // Test with Value
    match serde_json::from_str::<Value>(json_str) {
        Ok(data) => {
            if let Some(value) = data.get("value") {
                if let Some(u_val) = value.as_u64() {
                    println!("serde_json (u64): {} (success)", u_val);
                } else if let Some(i_val) = value.as_i64() {
                    println!("serde_json (i64): {} (success)", i_val);
                }
            }
        },
        Err(e) => println!("serde_json (number): error - {}", e),
    }
}

fn test_unicode_impl(json_str: &str) {
    match serde_json::from_str::<TestData>(json_str) {
        Ok(data) => println!("serde_json: {:?} (success)", data.username),
        Err(e) => println!("serde_json: error - {}", e),
    }
}
