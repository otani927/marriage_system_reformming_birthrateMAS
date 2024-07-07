# ファイル説明
```
DemographicSimulation_for_Fertility_by_ABM/
│
├── src/                        # ソースコード
│   ├── main/                   # メインのアプリケーションコード
│   └── tests/                  # ユニットテストや統合テスト
│
├── tools/                      # ユーティリティスクリプトやビルドスクリプト
│   ├── build.sh                # ビルド用スクリプト
│   └── deploy.sh               # デプロイ用スクリプト
│
├── database/                   # データベース関連のファイルやスクリプト
│   ├── schema.sql              # データベースのスキーマ定義
│   ├── migrations/             # データベースのマイグレーションスクリプト
│   └── seed/                   # 初期データ投入用のスクリプトやデータ
│　　　　├── seed．sql            # csvデータを初期値
│　　　　├── anuual_trends       # 年次推移のcsvデータ
│　　　　├── birth               # 出生関係のcsvデータ
│　　　　├── divorce             # 離婚関係のcsvデータ
│　　　　└── marriage            # 結婚関係のcsvデータ
│
├── Dockerfile                  # Dockerコンテナのビルド設定
├── docker-compose.yml          # Docker Composeの設定
├── requirements.txt            # Python パッケージのリスト
└── LICENSE                     # ライセンス情報
```

# 開発・実行環境

リポジトリ内で実行。  
MySQL:5.7とJupyterLab:testのコンテナを生成。
```
docker compose up -d --build
```
JupyterLabコンテナ内でコマンドを実行可能にする。
```
docker exec -it jupyterlab-abm bash
```
コンテナ内で実行。  
以下のような実行中のサーバーのURLとそのtokenを表示する。  
`http://cb1ac1f6ea94:8888/?token=?????? :: /work`

```
jupyter server list
```
> `cb1ac1f6ea94`の部分はJupyterLabのコンテナID。

ブラウザ上で実行。  
JupyterLabを起動する。
```
localhost:8888
```