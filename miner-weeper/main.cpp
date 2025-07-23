#include "MinerWeeper.hpp"
int main() {
    int n = 0, m = 0, k = 0, g;
    cout << "8x8 - noob" << "\n" << "16x16 - fan" << "\n" << "30x16 - pro";
    cin >> g;
    switch (g) {
        case 1:
            n = 8, m = 8, k = 10;
            break;
        case 2:
            n = 16, m = 16, k = 40;
            break;
        case 3:
            n = 30, m = 16, k = 99;
            break;
    }

    RenderWindow window(VideoMode(1920, 1080), "Mines weeper");
    mines_weeper obj(n, m, k, window);
}
