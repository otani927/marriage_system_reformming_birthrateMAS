-- コンテナ生成時にデータベースを初期化

-- データベースを選択
USE demographics;

-- 日本のライフイベント発生件数の年次推移
LOAD DATA INFILE '/seed/annual_trends/distr_num_year_lifevent.csv'
INTO TABLE demographics_jp
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(year,birth_num,marriage_num,devorce_num);

-- 日本のライフイベント発生率の年次推移
```
LOAD DATA INFILE '/seed/annual_trends/distr_rate_year_lifevent.csv'
INTO TABLE demographics_jp
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 2 LINES
(年, 人口千対出生率, 人口千対婚姻率, 人口千対離婚率, 期間合計特殊出生率, 夫婦ともに初婚割合, 夫婦ともに再婚割合, 妻初婚夫再婚割合, 妻再婚夫初婚割合);
```