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

map<pair<int, int>, bool> ok;
int x, y, ax, ay, point = 1;
int xspeed, yspeed, scale;
int indx[w*h], indy[w*h];

bool fail;

void setup() {
    xspeed = 1;
    yspeed = 0;
    scale = 20;
    x = w/2; x -= x%scale;
    y = h/2; y -= y%scale;
    ax = rand()%(width-scale);
    ax -= ax%scale;
    ay = rand()%(height-scale);
    ay -= ay%scale;
    indx[0] = x;
    indy[0] = y;
}

void update() {
    switch(GetCharPressed()) {
        case 'w':
            if (!yspeed || point == 1) {
                xspeed = 0;
                yspeed = 1;
            }
            break;
        case 'd':
            if (!xspeed || point == 1) {
                xspeed = 1;
                yspeed = 0;
            }
            break;
        case 's':
            if (!yspeed || point == 1) {
                xspeed = 0;
                yspeed = -1;
            }
            break;
        case 'a':
            if (!xspeed || point == 1) {
                xspeed = -1;
                yspeed = 0;
            }
            break;
    }

    if (x == ax && y == ay) {
        ax = rand()%(width-scale) + scale;
        ax -= ax%scale;
        ay = rand()%(height-scale) + scale;
        ay -= ay%scale;
        while (ok[{ax, ay}]) {
            ax = rand()%(width/2);
            ax -= ax%scale;
            ay = rand()%(height/2);
            ay -= ay%scale;
        }

        point++;
    }

    x += xspeed*scale;
    y += yspeed*scale;

    if (x < 0) fail = true;
    if (y < scale) fail = true;

    if (x > width-scale) fail = true;
    if (y > h) fail = true;

    int inx[w*h], iny[w*h];
    for (int i = 0; i < w*h-1; i++) {
        iny[i+1] = indy[i];
    } iny[0] = y;

    for (int i = 0; i < w*h-1; i++) {
        inx[i+1] = indx[i];
    } inx[0] = x;

    for (int i = 0; i < w*h; i++) {
        indx[i] = inx[i];
        indy[i] = iny[i];
    }
}

void draw() {
    ok.clear();
    DrawRectangle(ax, -ay+h, scale, scale, PASTELRED);

    for (int i = 1; i < point; i++) {
        if (indx[i] == x && indy[i] == y) {
            fail = true;
            return;
        }
    }

    for (int i = 1; i < point; i++) {
        DrawRectangle(indx[i], -indy[i]+h, scale, scale, (i%2==0?PASTELDARKGREEN:veryDARKGREEN));
        DrawRectangleLines(indx[i], -indy[i]+h, scale, scale, (i%2==0?PASTELDARKGREEN:veryDARKGREEN));
        ok[{indx[i], indy[i]}] = true;
    }

    DrawRectangle(x, -y+h, scale, scale, veryDARKGREEN);
    DrawRectangleLines(x, -y+h, scale, scale, veryDARKGREEN);
}

int main() {
    srand(time(0));
    InitWindow(w, h, "anything");
    
    setup();
    while (!WindowShouldClose()) {
        SetTargetFPS(10*(point/15.0) + 5);
        BeginDrawing();
        ClearBackground(PASTELGREEN);

        if (!fail) {
            string length = "Length: " + to_string(point);
            DrawText(length.c_str(), 12, 12, 15, PASTELDARKGREEN);
            update();
            draw();
        } else {
            DrawText("YOU SUCK", w/2-60*2.5, h/2-30, 60, PASTELRED);
        }

        EndDrawing();
        usleep(10000);
    }

    return 0;
} 
