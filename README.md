## **概要**

TCU R-PresCo2022 作業用リポジトリ

## **環境**

#### **コンテナの起動**

1. 以下のコマンドを実行

```
docker-compose up -d
docker-compose exec app bash
```

#### **VScode で作業するとき**

1. Remote-Containers をインストール
2. 「Remote-Containers:Open Folder in Container...」を選択
3. リポジトリのホームディレクトリを開く

<br>

#### **JupyterLab で作業するとき**

1. コンテナ内で以下のコマンドを実行

```
jupyter notebook --port=8888 --ip=0.0.0.0 --allow-root --NotebookApp.token=''
```

2. ブラウザで以下の url にアクセス
   > http://localhost:8888/tree


## **コミットメッセージの絵文字**

- :tada: バージョン
- :sparkles: 新機能
- :bug: バグ
- :recycle: リファクタリング
- :books: ドキュメント
- :rotating_light: テスト
- :wastebasket: 削除
- :construction: WIP
- :whale: Docker
