using System;
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

            TestDuplicateKeys();
            TestLargeNumbers();
        }

        static string LoadTestData(string filename)
        {
            string path = Path.Combine("/app", "test_data", filename);
            return File.ReadAllText(path);
        }

        static void TestDuplicateKeys()
        {
            Console.WriteLine("1. Duplicate Keys Test");
            string jsonStr = LoadTestData("duplicate_keys.json");

            // System.Text.Json
            try
            {
                var data = System.Text.Json.JsonSerializer.Deserialize<TestData>(jsonStr);
                Console.WriteLine($"System.Text.Json: {data.Username} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"System.Text.Json: error - {e.Message}");
            }

            // Newtonsoft.Json
            try
            {
                var data = JsonConvert.DeserializeObject<TestData>(jsonStr);
                Console.WriteLine($"Newtonsoft.Json: {data.Username} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Newtonsoft.Json: error - {e.Message}");
            }

            // Newtonsoft.Json with JObject
            try
            {
                var jObject = JObject.Parse(jsonStr);
                Console.WriteLine($"Newtonsoft.Json (JObject): {jObject["username"]} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Newtonsoft.Json (JObject): error - {e.Message}");
            }

            Console.WriteLine();
        }

        static void TestLargeNumbers()
        {
            Console.WriteLine("3. Large Numbers Test");
            string jsonStr = LoadTestData("large_numbers.json");

            // System.Text.Json
            try
            {
                var data = System.Text.Json.JsonSerializer.Deserialize<TestData>(jsonStr);
                Console.WriteLine($"System.Text.Json: {data.Value} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"System.Text.Json: error - {e.Message}");
            }

            // Newtonsoft.Json
            try
            {
                var data = JsonConvert.DeserializeObject<TestData>(jsonStr);
                Console.WriteLine($"Newtonsoft.Json: {data.Value} (success)");
            }
            catch (Exception e)
            {
                Console.WriteLine($"Newtonsoft.Json: error - {e.Message}");
            }

            Console.WriteLine();
        }
    }
}
