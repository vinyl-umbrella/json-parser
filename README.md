# JSON Parser Behavior Comparison

このリポジトリは、さまざまなプログラミング言語とJSONライブラリにおけるJSONパーサの挙動の違いを検証するためのものです。

## 検証項目

各プログラミング言語は`test_data/`ディレクトリ内の共通JSONファイルを読み込み、以下の項目について検証します：

1. **重複キー** (`duplicate_keys.json`): 同じオブジェクト内に同じキーが複数回現れた場合の挙動
2. **大きな数値** (`large_numbers.json`): 大きな整数や浮動小数点数の精度の保持
3. **不正なUnicode** (`bad_unicode*.json`): 不正なUnicode文字を含む文字列の処理

**重要**: 各言語の実装は、これらのJSONファイルをテキストファイルとして読み込み、文字列としてJSONパーサに渡します。これにより、JSONの挙動確認が目的であるにも関わらず、テストデータ自体のパースに依存することを回避しています。

## 実行方法

このリポジトリは各言語のローカル環境を必要とせず、Dockerコンテナで実行するように設計されています。

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
