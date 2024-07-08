# 覚書

## ファイル説明
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

## 開発・実行環境
リポジトリ内で実行。  
MySQL:5.7とJupyterLab:testのコンテナを生成。
```
docker compose up -d --build
```
> `Cannot connect to the Docker daemon at unix:///var/run/docker.sock. Is the docker daemon running?`と言われたら、以下のコマンドでDockerデーモンが実行されているか確認。
>```
> sudo systemctl status docker
>```
> `Active: inactive(dead)`なら、以下のコマンドで起動。
> ```
> sudo systemctl start docker
> ```
> `sudo systemctl enable docker`でシステム起動時にDockerデーモンが起動するように設定できる。

> `ailed to solve: process "/bin/sh -c pip install --no-cache-dir -r requirements.txt" did not complete successfully: exit code: 1`と言われたときは、プロキシの問題かもしれない。以下をDockerfileのFROM以下に追記。
> ```
> ENV http_proxy=http://your-proxy-server:port
> ENV https_proxy=http://your-proxy-server:port
> ```

### JupyterLab
ローカルホストで実行。  
JupyterLabコンテナ内でコマンドを実行可能にする。
```
docker exec -it jupyterlab-abm bash
```
コンテナ内で実行。  
以下のような実行中のサーバーのURLとそのtokenを表示する。  
`http://cb1ac1******:8888/?token=********** :: /work`

```
jupyter server list
```
> `cb1ac1******`の部分はJupyterLabのコンテナID。

ブラウザ上で実行。  
JupyterLabを起動する。
```
localhost:8888
```

### MySQL
ローカルホストで実行。  
MySQLコンテナ内でコマンドを実行可能にする。
```
docker exec -it mysql-db bash
```
MySQLコンテナ内で実行。  
SQLコマンドを入力できるようにする。
```
mysql -u root -p
```
コンテナ生成時に初期化し、生成したデータベースを表示する。
```
SHOW database;
```
以下のような表示がされる。`demographics`の存在を確認。
```
+--------------------+
| Database           |
+--------------------+
| information_schema |
| demographics       |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
5 rows in set (0.00 sec)
```

