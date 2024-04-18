#include <stdio.h>

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

/* 設定パラメータ */
#define ARGENT 100000               /* エージェント数 */
#define SIMU_YEAR_MIN  1970         /* 検証する年代の下限 */
#define SIMU_YEAR_MAX  2020         /* 検証する年代の上限 */
#define MARRIGE_AGE_MIN 16          /* 結婚可能下限年齢 */ 
#define MARRIGE_AGE_MAX 45          /* 結婚可能上限年齢 */ 
#define MARRIGE_TIMES_MAX 100       /* 結婚可能回数 */       

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
    int gender;                                   /* 性別 男１ 女２ */
    int age;                                      /* 年齢 16~45 */
    int age_marriage[MARRIGE_TIMES_MAX]={};       /* 結婚した年齢 */
    int age_divorce[MARRIGE_TIMES_MAX]={};        /* 離婚した年齢 */
    int education_level;  /* 教育レベル */
    double income;        /* 可処分の月収（性別と教育レベルから分布） */
    double tax;           /* 税・社会保険料（独身かどうかでも変わる） */
    double rate_marriage; /* 成婚率（男女で計算式が異なりそう） */
    double rate_divorce;  /* 離婚率（人口統計から世帯収入別の？年別離婚率を採用） */
}argent;

/* 入力管理　分布に基づいて確率的にパラメータを与える */
void SetupDistribution(argent a[], int statistics){
    for(i=1; i<ARGENT+1; i++){
        
    }
}

/* 出力管理 */
void Output(int year ,int age, double data){

}

/* 個人収入 */
double PersonalIncome(){

}

/* 世帯収入 */
double HouseholdoIncom(){

}

/* 可処分所得 */
double DisposableIncome(){

}

/* 税・社会保険料負担率 */
double RateTax(){

}

/* 結婚・出産・子育てによる所得減率 */
double RateIncomeCut(){

}

/* 成婚率 */
double RateMarrige(){

}

/* 離婚率 */
double RateDivord(){

}

/* 死亡率 */
double RateDeath(){

}


int main (void){
    char filename[20];
    int argent[ARGENT];

    int 

    /*
        シナリオ実行
    */
}
