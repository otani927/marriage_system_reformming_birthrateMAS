import os
import csv

# parpers以下の各ディレクトリ名の配列
def generate_dir_list(path):  # ./paper
    dir_list = [
        d for d in os.listdir(path) if os.path.isdir(os.path.join(path, d))
    ]
    return dir_list
    
# papers以下のディレクトリ以下のファイル名の二次元配列
def generate_file_list(path):  # ex:./papers/birthrate
    file_list = [
        f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))
    ]
    return file_list

# csvに出力
def output_to_csv(path_csv, path_papers):
    # CSVファイルを書き込みモードでオープン
    with open(path_csv, mode="w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(["Directory", "File"])  # ヘッダー行を書き込む
        
        # papersディレクトリ内のsubディレクトリを走査
        for dir_name in generate_dir_list(path_papers):
            dir_path = os.path.join(path_papers, dir_name)

            # subディレクトリ内のファイルを走査
            for file_name in generate_file_list(dir_path):
                writer.writerow([dir_name, file_name])  # ファイル名とディレクトリ名を書き込む


# CSVファイルからMarkdown形式のテーブルを生成する
def csv_to_markdown_table(path_csv):
    markdown_table = "| Directory | File |\n|-----------|------|\n"
    with open(path_csv, mode="r") as file:
        reader = csv.reader(file)
        next(reader)  # ヘッダー行をスキップ
        for row in reader:
            markdown_table += f"| {row[0]} | {row[1]} |\n"
        file.close()
    return markdown_table


# Markdown形式のテーブルをREADME.mdに書き込む
def update_readme(path_readme, path_csv):
    with open(path_readme, mode="w") as readme_file:
        markdown_table = csv_to_markdown_table(path_csv)
        readme_file.write("\n\n")
        readme_file.write("### Files in B Directory\n")
        readme_file.write(markdown_table)
        readme_file.close()

def main():
    path_papers = "../papers"  # ディレクトリのパスを指定します
    path_csv    = "./table_papers.csv"
    path_readme = "../README.md"

    output_to_csv(path_csv, path_papers)
    update_readme(path_readme, path_csv)

if __name__ == "__main__":
    main()