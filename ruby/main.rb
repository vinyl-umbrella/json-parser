#!/usr/bin/env ruby
require 'json'
require 'oj'
require 'multi_json'

PARSERS = [
  ['Standard JSON', -> (json_str) { JSON.parse(json_str) }],
  ['Oj', -> (json_str) { Oj.load(json_str) }],
  ['MultiJSON', -> (json_str) { MultiJson.load(json_str) }]
].freeze

def load_test_data(filename)
  @test_data ||= {}
  @test_data[filename] ||= File.read(File.join('/app', 'test_data', filename))
end

def test_parser(parser_name, parser_proc, json_str, result_key = nil)
  result = parser_proc.call(json_str)
  value = result_key ? result[result_key] : result
  class_info = result_key && value.respond_to?(:class) ? " (class: #{value.class})" : ""
  puts "#{parser_name}: #{value}#{class_info} (success)"
rescue => e
  puts "#{parser_name}: error - #{e.message}"
end

def run_test(test_name, filename, result_key = nil)
  puts "#{test_name}"
  json_str = load_test_data(filename)

  PARSERS.each do |parser_name, parser_proc|
    test_parser(parser_name, parser_proc, json_str, result_key)
  end
  puts
end

def main
  puts "=== JSON Parser Behavior Comparison (Ruby) ===\n"

  run_test("1. Duplicate Keys Test", 'duplicate_keys.json', 'username')
  run_test("2. Large Numbers Test", 'large_numbers.json', 'value')
  run_test("3. Null Character Test", 'bad_unicode_1.json', 'username')
  run_test("4. C1 Control Code Test", 'bad_unicode_2.json', 'username')
  run_test("5. Unpaired Surrogate Test", 'bad_unicode_3.json', 'username')
  run_test("6. Noncharacter Test", 'bad_unicode_4.json', 'username')
end

main if __FILE__ == $0
