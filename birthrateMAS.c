#include <stdio.h>
#include <string.h>

/* エージェント設定に必要な統計データ 
    性別別・年齢別の人口分布
    性別別・年齢別の所得分布
    年代別・年齢別の成婚率分布
    年代別・年齢別の離婚率分布
    生活支出・物価の分布
    家賃の人口分布
    教育支出の人口分布
    個人負担率の時系列
*/

/* モデルの妥当性検証に必要なデータ
    年代別・コーホート別の初婚率分布
    年代別・コーホート別の出生率分布
*/

#define MAX_FILENAME_LENGTH 100     /* 入力ファイル名上限 */
#define FILENAME_INPUT  "input.csv"
#define FILENAME_OUTPUT "output.csv"

/* 設定パラメータ */
#define NUM_ARGENTS 10000           /* エージェント数 */
#define SIMU_YEAR_MIN  1970         /* 検証する年代の下限 */
#define SIMU_YEAR_MAX  2020         /* 検証する年代の上限 */
#define MARRIGE_AGE_MIN 15          /* 結婚可能下限年齢 */ 
#define MARRIGE_AGE_MAX 45          /* 結婚可能上限年齢 */ 
#define MARRIGE_TIMES_MAX 10        /* 結婚可能回数 */       

/* 制御パラメータ */
#define MARRIGE_PAIR_MAX_MAN   1    /* 男の同時結婚可能上限数 */
#define MARRIGE_PAIR_MAX_WOMAN 1    /* 女の同時結婚可能上限数 */
#define BURDEN_TAX             1    /* 負担率（税・社会保険料など） */
#define BURDEM_EDUCATION       1    /* 負担率（教育費） */
#define BURDEN_RENT            1    /* 負担率（家賃） */

/* エージェントの配列構造体 */
typedef struct {
    int partner_man[MARRIGE_PAIR_MAX_MAN]={};     /* 男性パートナー固有番号（構造体配列添字） */
    int partner_woman[MARRIGE_PAIR_MAX_WOMAN]={}; /* 女性パートナー固有番号（構造体配列添字） */
    int life;                                 /* 生１ 死０  */
    int gender;                                   /* 性別 女１ 男０ */
    int age;                                      /* 年齢 16~45 */
    int age_marriage[MARRIGE_TIMES_MAX]={};       /* 結婚した年齢 */
    int age_divorce[MARRIGE_TIMES_MAX]={};        /* 離婚した年齢 */
    int education_level;  /* 教育レベル */
    double income;        /* 可処分の月収（性別と教育レベルから分布） */
    double tax;           /* 税・社会保険料（独身かどうかでも変わる） */
    double rate_marriage; /* 成婚率（男女で計算式が異なりそう） */
    double rate_divorce;  /* 離婚率（人口統計から世帯収入別の？年別離婚率を採用） */
} Argent;


/* 分布の読み込み */
void LoadDistribution(Argent argents[], char filename){
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;

    /* ファイルを開く */
    file = fopen(filename, "r");
    if (file == NULL){
        fprintf(stderr, "ファイル %s を開けませんでした。\n", filename);
        /* エラー処理などを行う */
        return 1;
    }
}

/* 分布に基づいて確率的にパラメータを与える */
double GenerateIncome(double income[], int age){
    double u = ((double) rand() / RAND_MAX);    /* 0〜1の一様分布乱数 */
}

/* 個人収入 */
double PersonalIncome(Argent argent){
    if(agent.gender == 0)
        return 400
    else
        return 200
}

/* 世帯収入 */
double HouseholdoIncom(double income_man, double income_wman){}

/* 税・社会保険料負担率 */
double RateTax(){}

/* 結婚・出産・子育てによる所得減率 */
double RateIncomeCut(){}

/* 成婚率 */
double RateMarrige(){
    return 0.8
}

/* 離婚率 */
double RateDivord(){}

/* 死亡率 */
double RateDeath(){
    return 0.01
}


int main (void){
    srand(time(NULL));  /* 乱数シード */

    Argent argents[NUM_ARGENTS];
    
    /* 1000人のエージェントを生成し、初期値を設定 */
    Agent agents[NUM_AGENTS];
    for (int i=0; i<NUM_AGENTS; ++i){
        agents[i].partner_man[MARRIGE_PAIR_MAX_MAN]={};      /* 男性パートナー固有番号（構造体配列添字） */
        agents[i].partner_woman[MARRIGE_PAIR_MAX_WOMAN]={};  /* 女性パートナー固有番号（構造体配列添字） */
        agents[i].life = 1                                   /* 生１ 死０  */
        agents[i].gender                                     /* 性別 女１ 男０ */
        agents[i].age = 15                                   /* 年齢 16~45 */
        agents[i].age_marriage[MARRIGE_TIMES_MAX]={0};       /* 結婚した年齢 */
        agents[i].age_divorce[MARRIGE_TIMES_MAX]={0};        /* 離婚した年齢 */
        agents[i].education_level=1;
        agents[i].income=GenerateIncome(agents[i].gender);        
        agents[i].tax=0
        agents[i].rate_marriage=0
        agents[i].rate_divorce=0
    }

/* ファイル出力 */
    FILE *file = fopen(FILENAME_OUTPUT, "w");
    
    /* ファイルが正常に開けたかを確認*/
    if (file != NULL) {
        /* ヘッダーを書き込む*/
        fprintf(file, 
            "UniqueID,Age,Gender,edu_level,occupation,income,tax,
            rate_hours_work,rate_hours_housework,rate_hours_childcare,
            cost_childcare,times_marriage,age_first_marriage,const_marriage\n"
        );
        
        /* 各人物の情報をファイルに書き込む */
        for (int i = 0; i < sizeof(people) / sizeof(people[0]); ++i) {
            fprintf(file, "%d,%d,%c\n", 
                i, agent[i].age, agent[i].gender, agent[i].income
            );
        }

        fclose(file);
        printf("CSVファイルが正常に書き出されました。\n");
    } else {
        /* ファイルが開けなかった場合の処理 */
        printf("エラー：CSVファイルを開けませんでした。\n");
        return 1;
    }
    
    return 0;
}
