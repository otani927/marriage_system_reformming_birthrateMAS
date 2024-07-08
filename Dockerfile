# ベースイメージを指定
FROM python:3.9

# 必要なシステムパッケージをインストール
RUN apt-get update && apt-get install -y \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# 作業ディレクトリを設定
WORKDIR /work

# 依存関係ファイルをコピー
COPY requirements.txt .

# 依存関係をインストール
RUN pip install --no-cache-dir -r requirements.txt

# Jupyter Labをインストール
RUN pip install jupyterlab

# MySQL用のPythonライブラリをインストール
RUN pip install mysql-connector-python

# コンテナが起動した際にJupyter Labを自動実行
CMD ["jupyter-lab", "--ip", "0.0.0.0", "--allow-root"]
