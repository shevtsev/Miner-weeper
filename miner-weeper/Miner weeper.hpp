#ifndef Miner_weeper_hpp
#define Miner_weeper_hpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;
const int cntxt = 32, cntyt = 88;
class mines_weeper {
private:
    bool y = false, game = true;
    int n, k, m, rx = 0, ry = 0, cntx = cntxt, cnty = cntyt, cntt = k,
    seconds, flags = 0, cnt = 0, nume = 13;
    vector<Sprite> num;
    vector <vector<int>> a;
    vector <vector<Sprite>> b;
    vector<vector<bool>> w, f;
    RenderWindow& window;
    Mouse u;
    Texture tex, t;
    Sprite smile;
    Text text, text1;
    Font font;
    Clock clock;
    void init();
    void load();
    void map_generate(mt19937_64 gen);
    void left_click();
    void game_instructions();
    void right_click();
    void game_restart(mt19937_64 gen);
    void draw_obj();
    void start();
public:
    mines_weeper(int n, int m, int k, RenderWindow& win) : n(n), m(m), k(k), window(win)  {  start(); };
};
#endif /* Miner_weeper_hpp */
