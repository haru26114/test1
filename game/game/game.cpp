#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;


class Character {
public:
    string name;
    int hp;
    int maxHp;
    int atk;

    Character(string n, int h, int a) : name(n), maxHp(h), hp(h), atk(a) {}

    virtual void define() {
        hp = hp + 3;
        cout << name << "对自己回复了3" << endl;

    }

    virtual void attack(Character& target) {
        int damage = atk + (rand() % 5); // 加一点随机波动
        target.hp -= damage;
        if (target.hp < 0) target.hp = 0;
        cout << name << " 对 " << target.name << " 造成了 " << damage << "点伤害，";
        cout << target.name << " 剩余血量为 " << target.hp << endl;
    }

    virtual void attack11(Character& target) {
        int damage = 99999999;
        target.hp -= damage;
        if (target.hp < 0) target.hp = 0;
        cout << name << " 对 " << target.name << " 造成了 " << damage << "点伤害，";
        cout << target.name << " 剩余血量为 " << target.hp << endl;
    }


    inline bool isAlive() const { return hp > 0; }
};

// 玩家类
class Player : public Character {
public:
    Player(string n, int h, int a) : Character(n, h, a) {}
};

// Boss类
class Boss : public Character {
public:
    Boss(string n, int h, int a) : Character(n, h, a) {}
};



// 设置控制台文字颜色
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 隐藏光标
void hideCursor() {
    CONSOLE_CURSOR_INFO info = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

int main() {
    hideCursor();

    // 菜单选项
    string menu[] = { "开始游戏", "游戏设置", "关于游戏", "退出游戏" };
    int n = sizeof(menu) / sizeof(menu[0]);
    int sel = 0;

    while (true) {
        system("cls");

        // 标题（青色）
        setColor(11);
        cout << "=====================================\n";
        cout << "          原神主菜单                \n";
        cout << "=====================================\n\n";

        // 画选项
        for (int i = 0; i < n; i++) {
            if (i == sel) {
                setColor(9); // 选中：绿色
                cout << "      -> " << menu[i] << " <-\n";
            }
            else {
                setColor(7); // 未选中：白色
                cout << "         " << menu[i] << "\n";
            }
        }

        // 提示
        setColor(14); // 黄色
        cout << "\n     ↑↓ 选择    Enter 确认\n";

        setColor(7); // 恢复白色

        // 按键
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) sel = (sel - 1 + n) % n; // 上
            if (key == 80) sel = (sel + 1) % n;     // 下
        }
        else if (key == 13) { // 回车
            system("cls");
            setColor(10);
            cout << "\n     你选择了：" << menu[sel] << "\n";
            if (sel == 0) {
                srand(time(0)); // 初始化随机数种子


                Player player("勇者", 91, 12);
                Boss boss("Boss", 92, 8);

                cout << "开始和Boss战斗了，按J键继续..." << endl;
                char c;
                cin >> c;

                while (player.isAlive() && boss.isAlive()) {

                    if (c == '1')
                        player.attack11(boss);
                    if (c == '2')
                        player.define();
                    if (c == 'j')
                        player.attack(boss);

                    if (!boss.isAlive()) break;


                    boss.attack(player);
                    if (!player.isAlive()) break;

                    cout << "------------------------" << endl;
                    cout << "按J键继续下一回合..." << endl;
                    cin >> c;
                }


                if (player.isAlive()) {
                    cout << "恭喜你，战胜了Boss！" << endl;
                }
                else {
                    cout << "很遗憾，你被Boss击败了..." << endl;
                }
            }
            if (sel == 1) {
                cout << "无设置";
            }
            if (sel == 2) {
                cout << "这是一款关于原神的游戏";
            }
            if (sel == n - 1) {
                system("cls");
                setColor(12);
                cout << "\n     退出游戏...\n";
                Sleep(500);
                break;
            }
            Sleep(1000);
        }
    }
    setColor(7);
    return 0;
}