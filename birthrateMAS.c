#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
#define NUM_AGENTS 10000            /* エージェント数 */
#define SIMU_YEAR_TERM 50           /* 検証する期間（年） */
#define MARRIGE_AGE_MIN 15          /* 結婚可能下限年齢 */ 
#define MARRIGE_AGE_MAX 45          /* 結婚可能上限年齢 */ 
#define MARRIGE_TIMES_MAX 10        /* 結婚可能回数 */
#define DEATH_RATE 0.00             /* 死亡率 */

/* 制御パラメータ */
#define MARRIGE_PAIR_MAX_MAN   1      /* 男の同時結婚可能上限数 */
#define MARRIGE_PAIR_MAX_WOMAN 1      /* 女の同時結婚可能上限数 */
#define ENCOUNTER_COUNT 10            /* 遭遇する異性の数 */
#define BURDEN_TAX             0.4    /* 負担率（税・社会保険料など） */
#define BURDEM_EDUCATION       0.2    /* 負担率（教育費） */
#define BURDEN_RENT            0.01   /* 負担率（家賃） */
#define INCOME_THRESHOLD 300          /* 結婚する最低限の所得 */

/* エージェントの配列構造体 */
typedef struct {
    int partner_man[MARRIGE_PAIR_MAX_MAN];     /* 男性パートナー固有番号（構造体配列添字） */
    int partner_woman[MARRIGE_PAIR_MAX_WOMAN]; /* 女性パートナー固有番号（構造体配列添字） */
    int age_marriage[MARRIGE_TIMES_MAX];       /* 結婚した年齢 */
    int age_divorce[MARRIGE_TIMES_MAX];        /* 離婚した年齢 */
    int life;                                  /* 生1 死0  */
    int married_check;                         /* 既婚1 独身0 */
    int gender;                                /* 性別 女1 男0 */
    int age;                                   /* 年齢 16~45 */
    int edu_level;                             /* 教育レベル。 高校卒　短大卒　大卒（１〜３） */
    int occupation;                            /* 業種　第n次産業（１〜３） */
    double income;                             /* 可処分の月収（性別と教育レベルから分布） */
    double tax;                                /* 税・社会保険料（独身かどうかでも変わる） */
    double rate_hours_work;                    /* 労働時間率 */
    double rate_hours_housework;               /* 家事時間率 */
    double rate_hours_childcare;               /* 育児時間率 */
    double cost_childcare;                     /* 育児コスト */
    int times_marriage;                        /* 結婚回数 */
    double cost_marriage;                      /* 結婚コスト */
    double rate_marriage;                      /* 成婚率（男女で計算式が異なりそう） */
    double rate_divorce;                       /* 離婚率（人口統計から世帯収入別の？年別離婚率を採用） */
    
} Agent;

/* 性別決定 */
double GenerateGender(void){
    return rand() % 2; 
}

/* 年齢決定 */
int GenerateAge(){
    return 15;
}

/* 学歴 */
double GenerateEduLevel(){
    return rand() % 3;
}

/* 業種 */
double GenerateOccupation(){
    return rand() % 3;
}

/* 所得 */
double GenerateIncome(){
    return 400;
}

/* 自己負担率 */
double GenerateRateTax(){
    return 0.5;
}

/* 成婚率 */
double GenerateRateMarriage(){
    return 0.5;
}

/* 離婚率 */
double GenerateRateDivorce(){
    return 0.1;
}

/* 結婚・出産・子育てによる所得減率 */
double RateIncomeCut(){
    return 0.2;
}

/* 死亡率 */
double RateDeath(){
    return 0.01;
}

/* 結婚の意思決定 */
int DecideMarriage(struct Agent *agents, int id1, int id2){
    double random_value = (double)rand() / RAND_MAX;
    double probability;

    /* 既婚者は結婚できない */
    if(agents[id1]->married_check + agents[id2]->married_check != 0){
        return 0;
    }

    /* 乱数が確率以上なら1を、そうでなければ0を返す */
    probability = agents[id1]->rate_marrige * agents[id2]->rate_marrige;
    if(random_value > probability) {
        return 0;
    }

    /* 結婚可能なペアを世帯所得で脚切り */
    if(agents[id1]->income + agents[id2]->income > INCOME_THRESHOLD){
        agents[id1]->married_check = 1;
        agents[id2]->married_check = 1;
        return 1;
    }
}

/* ランダム遭遇と結婚行動 */
void EncounterWithOppositeSex(struct Agent *agents, int agent_id) {
    int count = 0;
    int opposite_id[ENCOUNTER_COUNT];

    while (count < ENCOUNTER_COUNT) {
        /* ランダムに他のエージェントを選択 */
        int random_agent_id = rand() % NUM_AGENTS;

        /* 異性である場合、結婚の意思決定を判定する */
        if (agents[agent_id].gender != agents[random_agent_id].gender) {
            DecideMarriage(agents, agent_id, random_agent_id);
        }
        count++;
    }
}


int main (void){
    int i, j, k;

    srand(time(NULL));  /* 乱数シード */

    /* 1000人のエージェントを生成し、初期値を設定 */
    Agent agents[NUM_AGENTS];

    for(i=0; i<NUM_AGENTS; ++i){
        for(j=0; j<MARRIGE_PAIR_MAX_MAN; ++j){
            agents[i].partner_man[j]=0;      /* 男性パートナー固有番号（構造体配列添字） */
        }
        for(j=0; j<MARRIGE_PAIR_MAX_WOMAN; ++j){
            agents[i].partner_woman[j]=0;  /* 女性パートナー固有番号（構造体配列添字） */
        }
        for(j=0; j<MARRIGE_TIMES_MAX; ++j){
            agents[i].age_marriage[j]=0;        /* 結婚した年齢 */
            agents[i].age_divorce[j]=0;         /* 離婚した年齢 */
        }
        agents[i].life = 1;                                  /* 生1 死0  */
        agents[i].gender=GenerateGender();                   /* 性別決定 女1 男0 */
        agents[i].age = GenerateAge();                       /* 年齢決定 16~45 */
        agents[i].edu_level=GenerateEduLevel();              /* 学歴決定 1~3*/
        agents[i].occupation=GenerateOccupation();           /* 業種決定 1~3 */
        agents[i].income=GenerateIncome();                   /* 所得決定 */
        agents[i].tax=GenerateRateTax();                     /* 負担率決定 */
        agents[i].rate_marriage=GenerateRateMarriage();      /* 成婚率 */
        agents[i].rate_divorce=GenerateRateDivorce();        /* 離婚率 */
    }

    /* エージェントをイベントに遭遇させる。1年を繰り返す */
    for(k=0; k<SIMU_YEAR_TERM; k++){
        for(i=0; i<NUM_AGENTS; i++){
            EncounterWithOppositeSex(&agents, i);
        }
    }

/* ファイル出力 */
    FILE *file = fopen(FILENAME_OUTPUT, "w");
    
    /* ファイルが正常に開けたかを確認*/
    if (file != NULL) {
        /* ヘッダーを書き込む*/
        fprintf(file, 
            "UniqueID,Age,Gender,EduLevel,Occupation,Income,Tax, \
            RateHoursWork,RateHoursHousework,RateHoursChildcare, \
            CostChildcare,TimesMarriage,AgeFirstMarriage,ConstMarriage\n");
        
        /* 各人物の情報をファイルに書き込む */
        for (int i = 0; i < sizeof(agents) / sizeof(agents[0]); ++i) {
            fprintf(file, "%d,%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%lf\n", 
                i, agents[i].age, agents[i].gender, agents[i].occupation, agents[i].income, agents[i].tax,
                agents[i].rate_hours_work, agents[i].rate_hours_housework, agents[i].rate_hours_childcare,
                agents[i].cost_childcare, agents[i].times_marriage, agents[i].age_marriage[0], agents[i].cost_marriage
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
