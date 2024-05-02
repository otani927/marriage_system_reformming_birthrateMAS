import os
import re
import PyPDF2

# pdfファイルからファイルタイトルを採取する
def extract_pdf_info(pdf_path):
    with open(pdf_path, 'rb') as file:
        reader = PyPDF2.PdfFileReader(file)
        title = reader.getDocumentInfo().title
        if not title:
            title = os.path.basename(pdf_path)  # ファイル名をタイトルとして使用
        return title

# readmeに表示する用のテーブルを制作する
def generate_table(pdf_info):
    table_content = "| PDFファイル | タイトル |\n| --- | --- |\n"
    for file, title in pdf_info:
        table_content += f"| {file} | {title} |\n"
    return table_content

def main():
    pdf_files = [file for file in os.listdir(".") if file.endswith(".pdf")]
    pdf_info = []
    for pdf_file in pdf_files:
        title = extract_pdf_info(pdf_file)
        pdf_info.append((pdf_file, title))

    # README.mdに書き込むためのテーブル形式の文字列を作成
    table_content = generate_table(pdf_info)

    # README.mdにテーブルを書き込む
    with open("README.md", "w") as readme:
        readme.write("# PDFファイル情報\n\n")
        readme.write(table_content)

if __name__ == "__main__":
    main()
