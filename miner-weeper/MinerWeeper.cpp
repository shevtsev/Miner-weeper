#include "MinerWeeper.hpp"
inline bool isMouseOver(const RenderWindow& window, const Sprite& sprite) {
    Vector2i mousePos = Mouse::getPosition(window);
    return mousePos.x > sprite.getPosition().x && mousePos.x < sprite.getPosition().x + 32
        && mousePos.y > sprite.getPosition().y && mousePos.y < sprite.getPosition().y + 32;
}
void mines_weeper::init() {
    w.resize(n, vector<bool>(m, false));
    f.resize(n, vector<bool>(m, false));
    num.resize(nume);
    a.resize(n, vector<int>(m, 0));
    b.resize(n, vector<Sprite>(m));
}
void mines_weeper::load() {
    t.loadFromFile("images/smile.bmp");
    tex.loadFromFile("images/tiles.png");
    font.loadFromFile("images/Samson.ttf");
    smile.setTexture(t);
    // Позиционируем элементы интерфейса в зависимости от размера окна
    float centerX = window.getSize().x / 2;
    smile.setPosition(centerX - 16, 10); // 16 - половина ширины смайлика
    text.setPosition(10, 10);
    text1.setPosition(window.getSize().x - 100, 10);
    text.setFont(font);
    text1.setFont(font);
    text.setCharacterSize(50);
    text1.setCharacterSize(50);
    text.setString(to_string(cntt));
    for (int i = 0; i < nume; ++i) {
        num[i].setTexture(tex);
        num[i].setTextureRect(IntRect(rx, ry, 32, 32));
        rx += 32;
    }
}
void mines_weeper::map_generate(mt19937_64 gen) {
    for (int i = 0; i < k; ++i) {
        int* cnt = &a[gen() % n][gen() % m];
        if (*cnt == 0)
            *cnt = -100;
        else
            i--;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] < 0) {
                if (i < n - 1) a[i + 1][j]++;
                if (j < m - 1) a[i][j + 1]++;
                if (i > 0) a[i - 1][j]++;
                if (j > 0) a[i][j - 1]++;
                if (i < n - 1 && j < m - 1) a[i + 1][j + 1]++;
                if (i > 0 && j > 0) a[i - 1][j - 1]++;
                if (i < n - 1 && j > 0) a[i + 1][j - 1]++;
                if (j < m - 1 && i > 0) a[i - 1][j + 1]++;
            }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            Sprite f;
            f = num[nume - 4];
            f.setPosition(cntx, cnty);
            b[i][j] = f;
            cntx += 32;
        }
        cnty += 32;
        cntx = cntxt;
    }
}
void mines_weeper::game_instructions() {
    if (game) {
        //win check
        for (int i = 0; i < b.size(); ++i) {
            for (int j = 0; j < b[i].size(); ++j)
                if ((b[i][j].getTextureRect() != num[nume - 4].getTextureRect() &&
                    b[i][j].getTextureRect() != num[nume - 2].getTextureRect()) || a[i][j] < 0)
                    y = true;
                else {
                    y = false;
                    break;
                }
            if (!y)    break;
        }
        //bombs kol
        int kol = 0;
        for (int i = 0; i < b.size(); ++i)
            for (int j = 0; j < b[i].size(); ++j)
                if (b[i][j].getTextureRect() == num[nume - 2].getTextureRect())
                    kol++;
        cntt = k - kol;
        text.setString(to_string(cntt));
        //init time
        seconds = clock.getElapsedTime().asSeconds();
        if (seconds < 10)
            text1.setString("00" + to_string(seconds));
        else if (seconds < 100 && seconds >= 10)
            text1.setString("0" + to_string(seconds));
        else
            text1.setString(to_string(seconds));
        //zeros fields open
        for (int i = 0; i < b.size(); ++i)
            for (int j = 0; j < b[i].size(); ++j)
                if (a[i][j] == 0 && b[i][j].getTextureRect() == num[0].getTextureRect()) {
                    if (i < n - 1) b[i + 1][j].setTextureRect(num[a[i + 1][j]].getTextureRect()), f[i + 1][j] = true;
                    if (j < m - 1) b[i][j + 1].setTextureRect(num[a[i][j + 1]].getTextureRect()), f[i][j + 1] = true;
                    if (i > 0) b[i - 1][j].setTextureRect(num[a[i - 1][j]].getTextureRect()), f[i - 1][j] = true;
                    if (j > 0) b[i][j - 1].setTextureRect(num[a[i][j - 1]].getTextureRect()), f[i][j - 1] = true;
                    if (i < n - 1 && j < m - 1) b[i + 1][j + 1].setTextureRect(num[a[i + 1][j + 1]].getTextureRect()), f[i + 1][j + 1] = true;
                    if (i > 0 && j > 0) b[i - 1][j - 1].setTextureRect(num[a[i - 1][j - 1]].getTextureRect()), f[i - 1][j - 1] = true;
                    if (i < n - 1 && j > 0) b[i + 1][j - 1].setTextureRect(num[a[i + 1][j - 1]].getTextureRect()), f[i + 1][j - 1] = true;
                    if (j < m - 1 && i > 0) b[i - 1][j + 1].setTextureRect(num[a[i - 1][j + 1]].getTextureRect()), f[i - 1][j + 1] = true;
                }
    }
    //end game bombs show
    else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (a[i][j] < 0 && b[i][j].getTextureRect() != num[nume - 2].getTextureRect())
                    b[i][j].setTextureRect(num[nume - 3].getTextureRect());
                else if (b[i][j].getTextureRect() == num[nume - 2].getTextureRect() && a[i][j] > 0)
                    b[i][j].setTextureRect(num[nume - 1].getTextureRect());
        clock.restart();
    }
    //win
    if (y)
        game = false, text.setString("WIN!");
}
void mines_weeper::left_click() {
    if (Mouse::isButtonPressed(Mouse::Left) && game)
        for (int i = 0; i < b.size(); ++i)
            for (int j = 0; j < b[i].size(); ++j)
                if (isMouseOver(window, b[i][j]) && !f[i][j]) {
                    f[i][j] = true;
                    if (a[i][j] >= 0)
                        b[i][j].setTextureRect(num[a[i][j]].getTextureRect());
                    else {
                        b[i][j].setTextureRect(num[nume - 3].getTextureRect());
                        game = false;
                        text.setString("LOSE");
                    }
                }
}
void mines_weeper::right_click() {
    if (Mouse::isButtonPressed(Mouse::Right) && game)
        for (int i = 0; i < b.size(); ++i)
            for (int j = 0; j < b[i].size(); ++j)
                if (isMouseOver(window, b[i][j]) && !f[i][j] && !w[i][j]) {
                    w[i][j] = true;
                    b[i][j].setTextureRect(num[nume - 2].getTextureRect());
                }
}
void mines_weeper::game_restart(mt19937_64 gen) {
    if (!game && Mouse::isButtonPressed(Mouse::Left))
        if (isMouseOver(window, smile)) {
            game = true, cnty = cntyt, cntt = k, y = false;
            a.clear(), a.resize(n, vector<int>(m, 0));
            f.clear(), f.resize(n, vector<bool>(m, false));
            w.clear(), w.resize(n, vector<bool>(m, false));
            map_generate(gen);
        }
}
void mines_weeper::draw_obj() {
    window.clear();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            window.draw(b[i][j]);
    window.draw(text);
    window.draw(text1);
    window.draw(smile);
    window.display();
}
void mines_weeper::start() {
    random_device rd;
    mt19937_64 gen(rd());
    init(), load(), map_generate(gen);
    while (window.isOpen())
    {
        mt19937_64 gen(rd());
        game_restart(gen);
        left_click();
        right_click();
        game_instructions();
        Event event;
        while (window.pollEvent(event))
            if (Keyboard::isKeyPressed(Keyboard::Escape)
                || event.type == event.Closed)
                window.close();
        draw_obj();
    }
}
