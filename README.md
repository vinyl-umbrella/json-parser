# JSON Parser Behavior Comparison

このリポジトリは、さまざまなプログラミング言語とJSONライブラリにおけるJSONパーサの挙動の違いを検証するためのものです。

## プロジェクト構造

```
jsonparser/
├── test_data/                    # 共通テストデータ
│   ├── duplicate_keys.json      # 重複キーのテスト
│   ├── large_numbers.json       # 大きな数値のテスト
│   └── README.md                # テストデータの説明
├── go/                          # Go言語での実装
├── python/                      # Python言語での実装
├── nodejs/                      # Node.js/JavaScript実装
├── c/                           # C言語での実装
├── rust/                        # Rust言語での実装
├── java/                        # Java言語での実装
├── csharp/                      # C#言語での実装
├── ruby/                        # Ruby言語での実装
├── php/                         # PHP言語での実装
└── compose.yml                  # Docker Compose設定
```

## 検証項目

各プログラミング言語は`test_data/`ディレクトリ内の共通JSONファイルを読み込み、以下の項目について検証します：

1. **重複キー** (`duplicate_keys.json`): 同じオブジェクト内に同じキーが複数回現れた場合の挙動
2. **大きな数値** (`large_numbers.json`): 大きな整数や浮動小数点数の精度の保持
3. **不正なUnicode** (`bad_unicode*.json`): 不正なUnicode文字を含む文字列の処理

**重要**: 各言語の実装は、これらのJSONファイルをテキストファイルとして読み込み、文字列としてJSONパーサに渡します。これにより、JSONの挙動確認が目的であるにも関わらず、テストデータ自体のパースに依存することを回避しています。

## テスト対象

### Go
- 標準ライブラリ (`encoding/json`)
- `github.com/buger/jsonparser`
- `github.com/json-iterator/go`

### Python
- 標準ライブラリ (`json`)
- `ujson`
- `orjson`
- `simplejson`

### Node.js/JavaScript
- 標準の `JSON.parse()`
- `fast-json-parse`
- `json5`

### C
- `cJSON`
- `jansson`
- `json-c`

### Rust
- `serde_json`
- `simd-json` (オプション)

### Java
- Jackson (`com.fasterxml.jackson`)
- Gson (`com.google.gson`)
- JSON-P (`javax.json`)

### C#
- System.Text.Json (.NET標準)
- Newtonsoft.Json

### Ruby
- 標準ライブラリ (`json`)
- `oj`
- `multi_json`

### PHP
- `json_decode` (標準)
- `simdjson-php` (オプション)

## 実行方法

このリポジトリは各言語のローカル環境を必要とせず、Dockerコンテナで実行するように設計されています。

### 前提条件

- Docker
- Docker Compose（`docker compose`コマンド）

### 実行手順

```bash
# 全言語のテストを順次実行
docker compose run all

# 特定の言語のみ実行
docker compose run go
docker compose run python
docker compose run nodejs
docker compose run c
docker compose run rust
docker compose run java
docker compose run csharp
docker compose run ruby
docker compose run php

# 全てのコンテナをビルド（初回や変更後）
docker compose build

# 特定の言語のコンテナをビルド
docker compose build go
```

### 実行例

```bash
# Goのテストのみ実行
docker compose run --rm go

# PythonとNode.jsのテストを実行
docker compose run --rm python
docker compose run --rm nodejs

# 全言語のテストを実行
docker compose run --rm all
```

## 結果

各テストの結果は、実行時にコンソールに出力されます。異なる挙動を示すケースには特に注意して記録されています。

## サンプル出力

### Go言語での実行例
```
=== JSON Parser Behavior Comparison (Go) ===

1. Duplicate Keys Test
Standard json.Unmarshal: second (error: <nil>)
jsonparser.GetString: first (error: <nil>)
jsoniter.Unmarshal: second (error: <nil>)
```

## 注目すべき違い

1. **重複キー処理**: Go標準ライブラリは最後の値、jsonparserは最初の値を使用
2. **数値精度**: JavaScriptでは大きな整数で精度が失われる場合がある
3. **不正なUnicode**: 不正なUnicode文字を含む文字列の処理に関して、各ライブラリの挙動が異なる

詳細な結果については、`RESULTS.md` を参照お願いします．
