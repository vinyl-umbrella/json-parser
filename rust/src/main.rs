use serde::{Deserialize, Serialize};
use serde_json;
use std::collections::HashMap;
use std::fs;

#[derive(Serialize, Deserialize, Debug)]
struct TestData {
    username: Option<String>,
    value: Option<i64>,
}

fn main() {
    println!("=== JSON Parser Behavior Comparison (Rust) ===\n");

    test_duplicate_keys();
    test_large_numbers();
}

fn load_test_data(filename: &str) -> String {
    let path = format!("/app/test_data/{}", filename);
    fs::read_to_string(path).unwrap_or_else(|e| {
        eprintln!("Error loading test data: {}", e);
        String::new()
    })
}

fn test_duplicate_keys() {
    println!("1. Duplicate Keys Test");
    let json_str = load_test_data("duplicate_keys.json");

    // serde_json with struct
    match serde_json::from_str::<TestData>(&json_str) {
        Ok(data) => println!("serde_json (struct): {:?} (success)", data.username),
        Err(e) => println!("serde_json (struct): error - {}", e),
    }

    // serde_json with HashMap
    match serde_json::from_str::<HashMap<String, serde_json::Value>>(&json_str) {
        Ok(data) => {
            if let Some(username) = data.get("username") {
                println!("serde_json (HashMap): {} (success)", username);
            }
        },
        Err(e) => println!("serde_json (HashMap): error - {}", e),
    }

    // Raw JSON value
    match serde_json::from_str::<serde_json::Value>(&json_str) {
        Ok(data) => {
            if let Some(username) = data["username"].as_str() {
                println!("serde_json (Value): {} (success)", username);
            }
        },
        Err(e) => println!("serde_json (Value): error - {}", e),
    }

    println!();
}

fn test_large_numbers() {
    println!("3. Large Numbers Test");
    let json_str = load_test_data("large_numbers.json");

    // serde_json
    match serde_json::from_str::<TestData>(&json_str) {
        Ok(data) => println!("serde_json: {:?} (success)", data.value),
        Err(e) => println!("serde_json: error - {}", e),
    }

    // Test with u64
    match serde_json::from_str::<serde_json::Value>(&json_str) {
        Ok(data) => {
            if let Some(value) = data["value"].as_u64() {
                println!("serde_json (u64): {} (success)", value);
            } else if let Some(value) = data["value"].as_i64() {
                println!("serde_json (i64): {} (success)", value);
            }
        },
        Err(e) => println!("serde_json (number): error - {}", e),
    }

    println!();
}
