#!/usr/bin/env ruby
require 'json'

begin
  require 'oj'
  OJ_AVAILABLE = true
rescue LoadError
  OJ_AVAILABLE = false
end

begin
  require 'multi_json'
  MULTI_JSON_AVAILABLE = true
rescue LoadError
  MULTI_JSON_AVAILABLE = false
end

def load_test_data(filename)
  test_data_path = File.join('/app', 'test_data', filename)
  File.read(test_data_path)
end

def test_duplicate_keys
  puts "1. Duplicate Keys Test"
  json_str = load_test_data('duplicate_keys.json')

  # Standard JSON
  begin
    result = JSON.parse(json_str)
    puts "Standard JSON: #{result['username']} (success)"
  rescue => e
    puts "Standard JSON: error - #{e.message}"
  end

  # Oj
  if OJ_AVAILABLE
    begin
      result = Oj.load(json_str)
      puts "Oj: #{result['username']} (success)"
    rescue => e
      puts "Oj: error - #{e.message}"
    end
  else
    puts "Oj: not available"
  end

  # MultiJSON
  if MULTI_JSON_AVAILABLE
    begin
      result = MultiJson.load(json_str)
      puts "MultiJSON: #{result['username']} (success)"
    rescue => e
      puts "MultiJSON: error - #{e.message}"
    end
  else
    puts "MultiJSON: not available"
  end

  puts
end

def test_large_numbers
  puts "3. Large Numbers Test"
  json_str = load_test_data('large_numbers.json')

  # Standard JSON
  begin
    result = JSON.parse(json_str)
    puts "Standard JSON: #{result['value']} (class: #{result['value'].class})"
  rescue => e
    puts "Standard JSON: error - #{e.message}"
  end

  # Oj
  if OJ_AVAILABLE
    begin
      result = Oj.load(json_str)
      puts "Oj: #{result['value']} (class: #{result['value'].class})"
    rescue => e
      puts "Oj: error - #{e.message}"
    end
  else
    puts "Oj: not available"
  end

  # MultiJSON
  if MULTI_JSON_AVAILABLE
    begin
      result = MultiJson.load(json_str)
      puts "MultiJSON: #{result['value']} (class: #{result['value'].class})"
    rescue => e
      puts "MultiJSON: error - #{e.message}"
    end
  else
    puts "MultiJSON: not available"
  end

  puts
end

def main
  puts "=== JSON Parser Behavior Comparison (Ruby) ===\n"

  test_duplicate_keys
  test_large_numbers
end

main if __FILE__ == $0
