#include <raylib.h>
#include <bits/stdc++.h>
#include <unistd.h>
// LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, WHITE, BLACK, BLANK, MAGENTA, RAYWHITE
#define PASTELGREEN Color{149, 178, 112, 255}
#define PASTELDARKGREEN Color{65, 115, 74, 255}
#define veryDARKGREEN Color{60, 100, 67  , 255}
#define PASTELRED Color{113, 50, 50, 255}

using namespace std;
const int width = 700, height = 700;
const int w = width, h = height;

struct circle {
    int x, y, r;
    circle(int _x, int _y, int r = 10) : x(_x), y(_y) {}
    bool operator !=(const circle& c) const {
        return (c.x != x || c.y != y || c.r != r);
    }
    bool operator ==(const circle& c) const{
        return (c.x == x && c.y == y && c.r == r);
    }
};

vector<circle> v;
double dist(int a, int b, int x, int y) {
    return sqrt((a-x)*(a-x) + (y-b)*(y-b));
}

circle newCir(int x, int y) {
    bool ok = true;
    
    for (circle c:v) {
        if (dist(x, y, c.x, c.y) < c.r) {
            ok = false;
            break;
        }
    }

    if (ok) return circle(x, y);
    else return circle(-100, -100);
}

bool grow(circle c) {
    if (c.x-c.r <= 0 || c.x+c.r >= width) return 0;
    if (c.y-c.r <= 0 || c.y+c.r >= height) return 0;

    for (circle i:v) {
        if (i == c) continue;
        if (dist(i.x, i.y, c.x, c.y)-1 <= c.r+i.r) return false;
    } return true;
}

void setup() {
        int x, y;
        x = rand()%width;
        y = rand()%height;
        circle c = newCir(x, y);
        /*while (!c) {
            x = rand()%width();
            y = rand()%height();
            c = newCir(x, y);
        }*/

        if (c != circle(-100, -100)) v.push_back(c);
}

void update() {
    for (circle& c:v) {
        if (grow(c)) {
            c.r += 1;
        }
    }
}

void draw() {
    for (auto c:v) {
        DrawCircleLines(c.x, c.y, c.r, WHITE);
    }
}

int main() {
    srand(time(0));
    InitWindow(w, h, "anything");
    
    setup();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        setup();
        update();
        draw();

        EndDrawing();
        // usleep(10000);
    }

    return 0;
}
