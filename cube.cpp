#include <raylib.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
vector<Color> clrs = {LIGHTGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, WHITE, BLANK, MAGENTA, RAYWHITE};
int w = 500, h = 500;
int width = w;
int height = h;

int trX = w/2;
int trY = h/2;

double str = 5;
double deg = 30;
double dist = 1.5;
double bb = 0.0005*2;
double angle = M_PI/8;


struct v3d {
    double x, y, z;
    v3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    v3d(double pp[3]) : x(pp[0]), y(pp[1]), z(pp[2]) {}
    v3d(vector<vector<double>> pp) : x(pp[0][0]), y(pp[1][0]), z((pp.size()-2?pp[2][0]:0)) {}
    vector<vector<double>> ar() {
        return {{x}, {y}, {z}};
    }
};

double rad(int n) {
    return n/180.0*M_PI;
}

vector<vector<double>> rotX(double ang) {
    return {
        {1,        0,         0},
        {0, cos(ang), -sin(ang)},
        {0, sin(ang),  cos(ang)}
    };
}

vector<vector<double>> rotY(double ang) {
    return {
        {cos(ang), 0, -sin(ang)},
        {0,        1,         0},
        {sin(ang), 0,  cos(ang)}
    };
}

vector<vector<double>> rotZ(double ang) {
    return {
        {cos(ang), -sin(ang), 0},
        {sin(ang),  cos(ang), 0},
        {       0,         0, 1}
    };
}

vector<vector<double>> mult(vector<vector<double>> a, vector<vector<double>> b) {
    int n = a.size(), m = a[0].size();
    int q = b.size(), p = b[0].size();
    if (q != m) {
        cout << "ERROR q != m" << endl;
        cout << "ERROR q != m" << endl;
        cout << "ERROR q != m" << endl;
        cout << "ERROR q != m" << endl;
        return {{-1}};
    }

    vector<vector<double>> c(n, vector<double>(p));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }

    return c;
}


v3d v[] = {
    v3d({-0.5, -0.5, -0.5}),
    v3d({0.5, -0.5, -0.5}),
    v3d({0.5, 0.5, -0.5}),
    v3d({-0.5, 0.5, -0.5}),
    v3d({-0.5, -0.5, 0.5}),
    v3d({0.5, -0.5, 0.5}),
    v3d({0.5, 0.5, 0.5}),
    v3d({-0.5, 0.5, 0.5})
};

vector<v3d> pp = {
    v3d({-0.5, -0.5, -0.5}),
    v3d({-0.5, 0.5, -0.5}),
    v3d({0.5, 0.5, -0.5}),
    v3d({0.5, -0.5, -0.5}),
    v3d({-0.5, -0.5, 0.5}),
    v3d({-0.5, 0.5, 0.5}),
    v3d({0.5, 0.5, 0.5}),
    v3d({0.5, -0.5, 0.5})
};

void line(int a, int b, Color clr) {
    DrawLine(pp[a].x*100+trX, -pp[a].y*100+trY, pp[b].x*100+trX, -pp[b].y*100+trY, clr);
}

Color colr = WHITE;

int main() {
    srand(time(0));
    InitWindow(w, h, "anything");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < 8; i++) {
            pp[i] = v3d(mult(rotY(angle), v[i].ar()));
            pp[i] = v3d(mult(rotX(rad(deg)), pp[i].ar()));

            double kk = 1/(dist-pp[i].z);
            vector<vector<double>> pro = {
                {kk, 0, 0},
                {0, kk, 0}
            };

            str = kk+3;

            pp[i] = v3d(mult(pro, pp[i].ar()));
            v3d zg = v3d(mult(pro, v3d(0, -1000, 0).ar()));
            v3d gz = v3d(mult(pro, v3d(0, 1000, 0).ar()));
            DrawCircle(pp[i].x*100+trX, -pp[i].y*100+trY, str, WHITE);
        }

        for (int i = 0; i < 4; i++) {
            line (i, i+4, colr);
            line (i, (i+1)%4, colr);
            line (i+4, ((i+1)%4) + 4, colr);
        }

        angle += bb;
        if (angle >= M_PI) angle = 0;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) colr = clrs[rand()%clrs.size()];
        if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD)) dist += 0.5;
        if (IsMouseButtonPressed(MOUSE_BUTTON_BACK)) dist -= 0.5;
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) bb -= bb*2;

        // deg += 0.05;
        EndDrawing();
        usleep(100);
    }

    return 0;
}
