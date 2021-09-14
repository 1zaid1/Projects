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

double dist(double x, double y, double a, double b) {
    return sqrt((x-a)*(x-a)+(y-b)*(y-b));
}

struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
    vec() {x = 0; y = 0;}

    vec(double angle, double length, bool state) {
        if (!state) {
            angle = angle/180*M_PI;
        }

        x = cos(angle)*length;
        y = sin(angle)*length;
    }

    vec operator -(const vec& o) const { // addtion
        return vec(x-o.x, y-o.y);
    }

    vec operator +(const vec& o) const { // subtraction
        return vec(x+o.x, y+o.y);
    }

    vec operator *(const double o) const { // addtion
        return vec(x*o, y*o);
    }

    vec operator /(const double o) const { // subtraction
        return vec(x/o, y/o);
    }

    double operator *(const vec& o) const { // dot product
        return x*o.x + y*o.y;
    }

    double operator ^(const vec& o) const { // cross product
        return x*o.y - y*o.x;
    }

    bool operator !=(const vec& o) const {
        return (o.x != x || o.y != y);
    }

    double len() {
        return sqrt(x*x+y*y); // length
    }

    double sqlen() {
        return x*x+y*y; // length squared
    }

    void normalize() {
        vec pp = (vec(x, y)/len());
        x = pp.x;
        y = pp.y;
    }
};

struct wall {
    vec a, b;
    wall(vec _a, vec _b) : a(_a), b(_b) {}
    wall(double a, double b, double x, double y) : a(vec(a, b)), b(vec(x, y)) {}
};

double dist(vec a, vec b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

vec p, m, tmp(-1,-1);
bool on = false;
Color ms = GREEN;
vector<vec> rays;
vector<wall> walls;

void line(vec A, vec B, Color clr = YELLOW) {
    DrawLine(A.x, A.y, B.x, B.y, clr);
}

void line(wall w, Color clr = YELLOW) {
    vec A = w.a;
    vec B = w.b;
    DrawLine(A.x, A.y, B.x, B.y, clr);
}

void setup() {
    p = vec(100, 250);
    
    for (int i = 0; i < 360; i+=1) {
        rays.push_back(vec(i, 1, false));
    }

    walls.push_back(wall(0, 0, 0, h));
    walls.push_back(wall(0, 0, w, 0));
    walls.push_back(wall(w, 0, w, h));
    walls.push_back(wall(0, h, w, h));
}
    
vec inter(vec p, vec d, wall w) {
    double x1 = w.a.x;
    double y1 = w.a.y;
    double x2 = w.b.x;
    double y2 = w.b.y;

    double x3 = p.x;
    double y3 = p.y;
    double x4 = p.x + d.x;
    double y4 = p.y + d.y;

    double den = (x1 - x2)*(y3-y4) - (y1 - y2)*(x3-x4);
    if (den == 0) return vec(-1, -1);

    double t = ((x1 - x3)*(y3-y4) - (y1 - y3)*(x3-x4))/den;
    double u = ((x2 - x1)*(y1-y3) - (y2 - y1)*(x1-x3))/den;
    if (t > 0 && t < 1 && u > 0) {
        return vec(x1 + t*(x2-x1), y1 + t*(y2-y1));
    } else return vec(-1, -1);
}

void draw() {
    for (wall i:walls) line(i, RED);
    for (vec d:rays) {
        vec v(-1, -1);
        double mn = INT_MAX;
        for (wall i:walls) {
            vec A = (i.a - p);
            vec B = (i.b - p);
            
            vec h = inter(p, d, i);
            if (h != vec(-1, -1)) {
                if (dist(p, h) < mn) {
                    v = h;
                }

                mn = min(mn, dist(p, h))
            }
        } if (v != vec(-1, -1)) line(p, v);
    }
}

int main() {
    srand(time(0));
    InitWindow(w, h, "anything");
    
    setup();
    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        m = vec(GetMousePosition().x, GetMousePosition().y);
        p = m;

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (on) {
                walls.push_back(wall(tmp, m));
                tmp = vec(-1, -1);
                on = false;
            } else {
                tmp = m;
                on = true;
            }
        }

        if (tmp != vec(-1, -1)) {
            line(tmp, m, RED);
        }

        draw();

        EndDrawing();
        usleep(10000);
    }

    return 0;
}
