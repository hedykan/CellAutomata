# 不知怎么称呼的元胞自动机框架
## 简单介绍
    本框架试图以元胞（Cell）视角去建立一个构建元胞自动机的方法
    元胞（Cell）在此被定义为一种拥有状态，状态组，规则组，输入组，输入状态转换规则的集合
    其中状态，状态组，规则组，输入组均可跟随时间或输入更改

## 状态status
    状态status = 规则组rule_group[∑(输入组input_group.上一时刻status)]
    即每个Cell当前的状态status，受到自身所接受的输入组input_group中包含的其他Cell的状态status所影响
    根据输入组input_group中输入的所有status计算得出对应的规则号
    根据规则号rule_id可以在规则组rule_group中获得这一时刻演化后得到的status

## 状态组status_group
    状态组status_group中包含当前Cell可以表达的所有状态status

## 规则组rule_group
    规则组rule_group是当前Cell进行状态status转换的根据
    规则组rule_group的规则条数取决于输入组input_group中所有的[Cell的[状态status经过输入状态转换规则得到的总状态数]]的乘积
    当然，也不一定
    规则组rule_group的规则条数也可以设定固定的缺省值

## 输入组input_group
    输入组rule_group是当前Cell所接受输入的所有Cell的集合
    当然，也可以包括自己

## 设计初衷
    设计这个框架是为了建立一种构建元胞自动机的标准方法
    为啥要建立这种标准方法呢
    那是因为作者想要通过元胞自动机去构建宇宙的一切，或者一个情感元胞自动机
    因为这很有趣
    也因为作者痴迷于人工的一切
