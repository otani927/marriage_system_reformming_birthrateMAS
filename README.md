# ファイル説明
```
DemographicSimulation_for_Fertility_by_ABM/
│
├── .github/
│   ├── workflows/              # GitHub ActionsやCI/CDの設定ファイル
│   └── ISSUE_TEMPLATE/         # Issueテンプレート
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
｜　　　　├── seed．sql           # csvデータを初期値
｜　　　　├── anuual_trends       # 年次推移のcsvデータ
｜　　　　├── birth               # 出生関係のcsvデータ
｜　　　　├── divorce             # 離婚関係のcsvデータ
｜　　　　└── marriage            # 結婚関係のcsvデータ
｜
├── Dockerfile                  # Dockerコンテナのビルド設定
├── docker-compose.yml          # Docker Composeの設定
├── requirements.txt            # Python パッケージのリスト
├── README.md                   # プロジェクトの概要、使用方法、インストール手順など
├── LICENSE                     # ライセンス情報
└── .gitignore                  # Gitで無視するファイルやディレクトリのリスト

```

# 開発・実行環境

リポジトリ内で実行すると、Mysql:5.7とjupyterlab:testのコンテナを生成。
```
docker compose up -d --build
```
jupyterlabコンテナ
```
docker exec -it jupyterlab-abm bash
```
```
docker logs jupyter
```