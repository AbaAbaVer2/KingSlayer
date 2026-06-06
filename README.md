# 🗡️ KingSlayer (弑君者)
![C++](https://img.shields.io/badge/C++-17%2B-blue.svg) ![Qt](https://img.shields.io/badge/Qt-6.0%2B-41CD52.svg) ![License](https://img.shields.io/badge/License-MIT-yellow.svg)
基于 C++ 和 Qt 6 框架开发的硬核单机桌面卡牌对战游戏。灵感来源于著名高难度桌游《弑君者 (Regicide)》。玩家需要通过策略性地打出手牌，利用四大花色的独特机制与连击效果，单挑并击败 12 位强大的皇家 Boss！
![Uploading image.png…]()

---
## ✨ 核心特性 (Features)
*   **🃏 严谨的卡牌战斗引擎**：深度还原原版规则，支持单卡打出、A 牌组合判定以及同点数多牌连击伤害计算。
*   **🛡️ 四大花色特效系统**：
    *   ❤️ **红桃 (Heart)**：治疗系，将弃牌堆的卡牌洗回牌库底，延长生存。
    *   ♦️ **方块 (Diamond)**：过牌系，造成伤害的同时抽取等量的卡牌补充手牌。
    *   ♣️ **梅花 (Club)**：暴击系，本次攻击的基础伤害直接翻倍。
    *   ♠️ **黑桃 (Spade)**：防御系，提供等同于伤害值的护盾，抵御 Boss 的致命反击。
*   **⚔️ 精确击杀 (Exact Kill)**：当对 Boss 造成的伤害**完全等于**其当前生命值时，不仅不会遭到反击，还能将该 Boss 招募至自己的弃牌堆，成为后续对战的顶级战力！
*   **🎬 Qt 原生丝滑动效**：利用 `QPropertyAnimation` 实现了爽快的出牌飞行动画、Boss 受击震屏反馈 (Screen Shake) 以及动态的伤害飘字特效。
*   **🏗️ 标准 MVC 架构**：将 `GameManager` (状态机)、`PlayValidator` (规则校验) 与 UI 视图彻底解耦，代码结构清晰，极易扩展与维护。
---
## 🎮 玩法图解
<img width="1540" height="1199" alt="image" src="https://github.com/user-attachments/assets/d5826a41-eb96-4729-9745-5bd302d87271" />
**极简战斗循环：**
1.  **出牌阶段**：打出单张或符合规则的组合牌（除 A 外总点数不得超过 10）。
2.  **结算阶段**：系统结算伤害，触发花色特效，扣除 Boss 血量。
3.  **Boss 反击**：若 Boss 未阵亡，将对玩家造成等同于其攻击力的伤害。
4.  **防守阶段**：玩家必须消耗黑桃护盾或主动弃掉手牌来抵挡伤害，手牌不足抵消则**游戏失败**。
---
## 🛠️ 构建与运行 (Build & Run)
本项目使用标准的 C++/Qt 构建流程，开箱即用。
### 环境要求
*   **C++ 标准**：C++ 17 及以上
*   **框架版本**：Qt 6.0+ 
*   **构建系统**：CMake
### 运行步骤
1.  克隆本仓库到本地：
    ```bash
    git clone https://github.com/AbaAbaVer2/KingSlayer.git
    ```
2.  在 **Qt Creator** 中打开项目根目录的 `CMakeLists.txt`。
3.  配置你的编译套件 (Kit)，例如 Desktop Qt 6.x.x MinGW 64-bit。
4.  点击左下角的 **Build**，编译完成后点击 **Run** 即可体验游戏！
---
## 📂 核心代码结构 (Architecture)
*   **`gamemanager.h/cpp`**：游戏底层中枢，管理牌库、手牌、弃牌堆以及回合状态机流转。
*   **`playvalidator.h/cpp`**：纯逻辑抽象模块，负责校验玩家出牌的合法性以及计算连击伤害。
*   **`mainwindow.h/cpp`**：主界面 UI 控制台，连接底层的 `battleLog` 信号并触发视觉特效。
*   **`cardwidget.h/cpp`**：自定义的卡牌 UI 控件，重写了原生鼠标事件，实现卡牌悬停上浮与点击选中效果。
---
## 👨‍💻 开发者彩蛋 (Debug Mode)
> 在主界面中，如果在不选中任何卡牌的情况下**快速连续点击 5 次“出牌”按钮**，可直接触发开发者秒杀外挂，瞬间清空当前 Boss 血量！ps：立绘是用gpt生成的
---
**Enjoy the game!** 如果你觉得这个练手项目还不错，欢迎右上角点个 ⭐ Star 支持一下！
