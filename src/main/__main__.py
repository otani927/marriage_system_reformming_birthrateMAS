from load import Load_Env_Info
from generate import Generate_Agents
from init import Init_Agents, Init_Degree
from update import Update_Env, Update_Edu, Update_Income, Update_Marriage, Update_Fertility
from cheack import Is_Death, Is_Age_Degree, Is_Live_Income, Is_Fertility_Income

period     = 70 # 1950~2020
num_agents = 10000

# 環境情報の読み込み
Load_Env_Info()

# エージェントを生成（人数）
Generate_Agents(num_agents)

# エージェントを初期化
Init_Agents()

# エージェントの学歴を初期化
Init_Degree()

# 指定する年数のシミュレーション実行
for year in period:

    Update_Env()

    # 全エージェントの年次更新
    for agent in agents:

        # 年齢加算
        agents.age = agents.age+1

        # 生存判定。45歳超過で破棄。確率的に死亡。配偶者は強制的に独身状態
        if not Is_Death():
            # agentを破棄
            continue
        
        # 規定の学歴（に達する年齢）を満たしていない場合、＋１年
        if not Is_Age_Degree(agents.degree, agents.age):
            
            #Update_Status_Edu()
            continue

        # 賃金ステータス更新
        Update_Income() 

        # 独身・世帯ごとに異なる閾値で生活貯蓄条件を判定
        if not Is_Live_Income():
            continue

        # 婚姻ステータス更新。独身に対して結婚処理。世帯に対して離婚処理。
        Update_Marriage()

        if not adents.marriage:
            continue

        if not Is_Fertility_Income():
            continue

        # 出生ステータス更新
        Update_Fertility()




