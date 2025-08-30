#!/bin/bash

echo "=== JSON Parser Behavior Comparison ==="
echo "Running tests for all languages using containers..."
echo ""

echo "Testing C..."
docker compose run --rm c
echo ""

echo "Testing C#..."
docker compose run --rm csharp
echo ""

echo "Testing Go..."
docker compose run --rm go
echo ""

echo "Testing Java..."
docker compose run --rm java
echo ""

echo "Testing Node.js..."
docker compose run --rm nodejs
echo ""

echo "Testing PHP..."
docker compose run --rm php
echo ""

echo "Testing Python..."
docker compose run --rm python
echo ""

echo "Testing Ruby..."
docker compose run --rm ruby
echo ""

echo "Testing Rust..."
docker compose run --rm rust
echo ""

echo "All tests completed!"
