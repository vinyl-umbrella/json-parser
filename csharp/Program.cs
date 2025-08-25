using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace JsonParserTest
{
    public class TestData
    {
        public string Username { get; set; }
        public long? Value { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("=== JSON Parser Behavior Comparison (C#) ===\n");

            var testCases = new List<(string name, string filename)>
            {
                ("1. Duplicate Keys Test", "duplicate_keys.json"),
                ("2. Large Numbers Test", "large_numbers.json"),
                ("3. Null Character Test", "bad_unicode_1.json"),
                ("4. C1 Control Code Test", "bad_unicode_2.json"),
                ("5. Unpaired Surrogate Test", "bad_unicode_3.json"),
                ("6. Noncharacter Test", "bad_unicode_4.json")
            };

            foreach (var (name, filename) in testCases)
            {
                RunTest(name, filename);
            }
        }

        static string LoadTestData(string filename)
        {
            string path = Path.Combine("/app", "test_data", filename);
            return File.ReadAllText(path);
        }

        static void RunTest(string testName, string filename)
        {
            Console.WriteLine(testName);
            string jsonStr = LoadTestData(filename);

            // System.Text.Json
            try
            {
                var data = System.Text.Json.JsonSerializer.Deserialize<TestData>(jsonStr);
                Console.WriteLine($"System.Text.Json: {data?.Username ?? data?.Value?.ToString() ?? "null"} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"System.Text.Json: error - {e.Message}");
            }

            // Newtonsoft.Json
            try
            {
                var data = JsonConvert.DeserializeObject<TestData>(jsonStr);
                Console.WriteLine($"Newtonsoft.Json: {data?.Username ?? data?.Value?.ToString() ?? "null"} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Newtonsoft.Json: error - {e.Message}");
            }

            // Newtonsoft.Json with JObject
            try
            {
                var jObject = JObject.Parse(jsonStr);
                var value = jObject["username"]?.ToString() ?? jObject["value"]?.ToString() ?? "null";
                Console.WriteLine($"Newtonsoft.Json (JObject): {value} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Newtonsoft.Json (JObject): error - {e.Message}");
            }

            Console.WriteLine();
        }
    }
}
