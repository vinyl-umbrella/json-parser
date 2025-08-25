import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonSyntaxException;

import javax.json.Json;
import javax.json.JsonReader;
import javax.json.JsonException;
import java.io.StringReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class JsonParserTest {

    private static class TestCase {
        final String name;
        final String filename;

        TestCase(String name, String filename) {
            this.name = name;
            this.filename = filename;
        }
    }

    public static void main(String[] args) {
        System.out.println("=== JSON Parser Behavior Comparison (Java) ===\n");

        List<TestCase> testCases = List.of(
            new TestCase("1. Duplicate Keys Test", "duplicate_keys.json"),
            new TestCase("2. Large Numbers Test", "large_numbers.json"),
            new TestCase("3. Null Character Test", "bad_unicode_1.json"),
            new TestCase("4. C1 Control Code Test", "bad_unicode_2.json"),
            new TestCase("5. Unpaired Surrogate Test", "bad_unicode_3.json"),
            new TestCase("6. Noncharacter Test", "bad_unicode_4.json")
        );

        for (TestCase testCase : testCases) {
            runTest(testCase);
        }
    }

    private static void runTest(TestCase testCase) {
        System.out.println(testCase.name);
        String jsonStr = loadTestData(testCase.filename);

        if (jsonStr.isEmpty()) {
            System.out.println("Skipping test - no data loaded\n");
            return;
        }

        testJackson(jsonStr);
        testGson(jsonStr);
        testJsonP(jsonStr);

        System.out.println();
    }

    private static String loadTestData(String filename) {
        try {
            return new String(Files.readAllBytes(Paths.get("/app/test_data/" + filename)));
        } catch (IOException e) {
            System.err.println("Error loading test data: " + e.getMessage());
            return "";
        }
    }

    private static void testJackson(String jsonStr) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            JsonNode node = mapper.readTree(jsonStr);
            JsonNode usernameNode = node.get("username");
            if (usernameNode != null) {
                System.out.println("Jackson: " + usernameNode.asText() + " (success)");
            } else {
                System.out.println("Jackson: no username field found (success)");
            }
        } catch (Exception e) {
            System.out.println("Jackson: error - " + e.getMessage());
        }
    }

    private static void testGson(String jsonStr) {
        try {
            Gson gson = new Gson();
            JsonObject jsonObject = JsonParser.parseString(jsonStr).getAsJsonObject();
            if (jsonObject.has("username")) {
                System.out.println("Gson: " + jsonObject.get("username").getAsString() + " (success)");
            } else {
                System.out.println("Gson: no username field found (success)");
            }
        } catch (Exception e) {
            System.out.println("Gson: error - " + e.getMessage());
        }
    }

    private static void testJsonP(String jsonStr) {
        try (JsonReader reader = Json.createReader(new StringReader(jsonStr))) {
            javax.json.JsonObject jsonObject = reader.readObject();
            if (jsonObject.containsKey("username")) {
                System.out.println("JSON-P: " + jsonObject.getString("username") + " (success)");
            } else {
                System.out.println("JSON-P: no username field found (success)");
            }
        } catch (Exception e) {
            System.out.println("JSON-P: error - " + e.getMessage());
        }
    }
}
