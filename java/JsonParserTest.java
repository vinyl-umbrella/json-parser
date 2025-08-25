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
import java.util.Map;

public class JsonParserTest {

    public static void main(String[] args) {
        System.out.println("=== JSON Parser Behavior Comparison (Java) ===\n");

        testDuplicateKeys();
        testLargeNumbers();
    }

    private static String loadTestData(String filename) {
        try {
            return new String(Files.readAllBytes(Paths.get("/app/test_data/" + filename)));
        } catch (IOException e) {
            System.err.println("Error loading test data: " + e.getMessage());
            return "";
        }
    }

    private static void testDuplicateKeys() {
        System.out.println("1. Duplicate Keys Test");
        String jsonStr = loadTestData("duplicate_keys.json");

        // Jackson
        try {
            ObjectMapper mapper = new ObjectMapper();
            JsonNode node = mapper.readTree(jsonStr);
            System.out.println("Jackson: " + node.get("username").asText() + " (success)");
        } catch (Exception e) {
            System.out.println("Jackson: error - " + e.getMessage());
        }

        // Gson
        try {
            Gson gson = new Gson();
            JsonObject jsonObject = JsonParser.parseString(jsonStr).getAsJsonObject();
            System.out.println("Gson: " + jsonObject.get("username").getAsString() + " (success)");
        } catch (Exception e) {
            System.out.println("Gson: error - " + e.getMessage());
        }

        // JSON-P (javax.json)
        try {
            JsonReader reader = Json.createReader(new StringReader(jsonStr));
            javax.json.JsonObject jsonObject = reader.readObject();
            System.out.println("JSON-P: " + jsonObject.getString("username") + " (success)");
            reader.close();
        } catch (Exception e) {
            System.out.println("JSON-P: error - " + e.getMessage());
        }

        System.out.println();
    }

    private static void testLargeNumbers() {
        System.out.println("3. Large Numbers Test");
        String jsonStr = loadTestData("large_numbers.json");

        // Jackson
        try {
            ObjectMapper mapper = new ObjectMapper();
            JsonNode node = mapper.readTree(jsonStr);
            System.out.println("Jackson: " + node.get("value").asLong() + " (type: long)");
        } catch (Exception e) {
            System.out.println("Jackson: error - " + e.getMessage());
        }

        // Gson
        try {
            Gson gson = new Gson();
            JsonObject jsonObject = JsonParser.parseString(jsonStr).getAsJsonObject();
            System.out.println("Gson: " + jsonObject.get("value").getAsLong() + " (type: long)");
        } catch (Exception e) {
            System.out.println("Gson: error - " + e.getMessage());
        }

        // JSON-P
        try {
            JsonReader reader = Json.createReader(new StringReader(jsonStr));
            javax.json.JsonObject jsonObject = reader.readObject();
            System.out.println("JSON-P: " + jsonObject.getJsonNumber("value").longValue() + " (type: long)");
            reader.close();
        } catch (Exception e) {
            System.out.println("JSON-P: error - " + e.getMessage());
        }

        System.out.println();
    }
}
