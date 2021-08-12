#include <raylib.h>
#include <bits/stdc++.h>
#include <unistd.h>
// LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, WHITE, BLACK, BLANK, MAGENTA, RAYWHITE
#define PASTELGREEN Color{149, 178, 112, 255}
#define PASTELDARKGREEN Color{65, 115, 74, 255}
#define veryDARKGREEN Color{60, 100, 67  , 255}
#define PASTELRED Color{113, 50, 50, 255}

using namespace std;
const int width = 500, height = 500;
const int w = width, h = height;
const int res = 25;
const int boms = 30;

struct cell {
    int val;
    bool shown, det, bom;
};

cell grid[w/res][h/res];
bool win, lose;

void setup() {
    // setting up bombs
    for (int i = 0; i < boms; i++) {
        int x = rand()%w;
        int y = rand()%h;
        x /= res; y /= res;
        while (grid[x][y].bom) {
            x = rand()%w;
            y = rand()%h;
            x /= res; y /= res;
        }

        grid[x][y].bom = true;
    }

    // setting up numbers
    for (int x = 0; x < w/res; x++) {
        for (int y = 0; y < w/res; y++) {
            int val = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (x+i < 0 || x + i >= w/res) continue;
                    if (y+j < 0 || y + j >= h/res) continue;
                    val += grid[x+i][y+j].bom;
                }
            } grid[x][y].val = val;
        }
    }
}

void draw() {
    for (int x = 0; x < w/res; x++) {
        for (int y = 0; y < h/res; y++) {
            if (grid[x][y].shown) {
                DrawRectangle(x*res, -y*res+h-res, res, res, WHITE);
                if (grid[x][y].bom) {
                    DrawCircle(x*res+res/4, -y*res+h+res/4 - res, res/4, RED);
                } else {
                    string s = to_string(grid[x][y].val);
                    if (s != "0") DrawText(s.c_str(), x*res+res/4, -y*res+h+res/4-res, res/2, BLUE);
                }
            }

            if (grid[x][y].det) {
                DrawRectangle(x*res+res/4, -y*res+h+res/4-res, res/2, res/2, RED);
            }
        }
    }
}

void finish() {
    for (int x = 0; x < w/res; x++) {
        for (int y = 0; y < h/res; y++) {
            DrawRectangle(x*res, -y*res+h-res, res, res, WHITE);
            if (grid[x][y].det) {
                Color clr = RED;
                if (grid[x][y].bom) clr = GREEN;
                DrawRectangle(x*res+res/4, -y*res+h+res/4-res, res/2, res/2, clr);
            } else {
                if (grid[x][y].bom) DrawCircle(x*res+res/2, -y*res+h+res/2 - res, res/4, RED);
                else {
                    string s = to_string(grid[x][y].val);
                    if (s != "0") DrawText(s.c_str(), x*res+res/4, -y*res+h+res/4-res, res/2, BLUE);
                }
            }
        }
    }
}

void dfs(int x, int y) {
    if (x < 0 || x >= w/res) return;
    if (y < 0 || y >= h/res) return;
    if (grid[x][y].shown) return;
    if (grid[x][y].det) return;
    if (grid[x][y].bom) return;

    grid[x][y].shown = true;
    if (grid[x][y].val) return;
    dfs(x+1, y);
    dfs(x-1, y);
    dfs(x, y+1);
    dfs(x, y-1);
    dfs(x+1, y+1);
    dfs(x-1, y-1);
    dfs(x-1, y+1);
    dfs(x+1, y-1);
}

void drawGrid() {
    for (int i = 0; i < w/res; i++) {
        DrawLine(i*res, 0, i*res, h, DARKGRAY);
    }

    for (int i = 0; i < h/res; i++) {
        DrawLine(0, i*res, w, i*res, DARKGRAY);
    }
}

void check() {
    int a, b, c;
    a = b = c = 0;

    for (int i = 0; i < w/res; i++) {
        for (int j = 0; j < h/res; j++) {
            if (grid[i][j].det) {
                a++;
                if (grid[i][j].bom) b++;
            } else {
                c = !grid[i][j].shown;
            }
        }
    }

    if (!c && a == b && b == boms) {
        win = true;
    }
}

int main() {
    srand(time(0));
    InitWindow(w, h, "anything");
    
    setup();
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        int mx = GetMousePosition().x/res;
        int my = GetMousePosition().y/res;

        if (win || lose) {
            finish();
            goto end;
        }
        
        my = h/res - my - 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (grid[mx][my].det) {
                grid[mx][my].det = false;
            } else if (grid[mx][my].bom) {
                lose = true;
            } else {
                dfs(mx, my);
            }
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (!grid[mx][my].shown) {
                grid[mx][my].det = !grid[mx][my].det;
            }
        }

        check();
        draw();

        end:
        drawGrid();
        EndDrawing();
        usleep(10000);
    }

    return 0;
}
