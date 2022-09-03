#include <bits/stdc++.h>
#include <chrono>
using namespace std;
#define endl '\n'
const int M = 4e5+5;
const int width = 100, height = 80;
char board[height][width+1];
struct vec {
    float x=0, y=0;
    vec operator+(vec a) {return {x+a.x, y+a.y};}
    vec operator-(vec a) {return {x-a.x, y-a.y};}
    vec operator/(float a) {return {x/a, y/a};}
    vec operator*(float a) {return {x*a, y*a};}
    void operator=(vec a) {x=a.x, y=a.y;}
    float len() {return sqrt(x*x+y*y);}
    void setMag(float x) {(*this) = (*this)/len();(*this) = (*this)*x;};
};

struct ball {
    float r;
    char c;
    vec p, p2=p, v={0,0}, a={0,0};

    void force(vec f) {
        a = f+a;
    }

    void col() {
        if (p.y + r > height) p.y = height-r;
        if (p.x + r > width) p.x = width-r;
        if (p.x - r < 0) p.x = r;
    }

    void update(float dt = 0.5) {
        col();
        auto tmp = p;
        p = p*2 - p2 + a*dt*dt;
        p2 = tmp;

        a = {0,0};
    }
};

void draw(ball b) {
    for (int i = max(0.0f, (b.p.x)-2*b.r); i <= min((float)width, (b.p.x)+2*b.r); i++) {
        for (int j = max(0.0f, (b.p.y)-2*b.r); j <= min((float)height, (b.p.y)+2*b.r); j++) {
            if ((i+0.5-b.p.x)*(i+0.5-b.p.x) + (j+0.5-b.p.y)*(j+0.5-b.p.y) < b.r*b.r) {
                if (b.c) board[j][i] = b.c;
            }
        }
    }
}

void col(ball& A, ball& B) {
    if ((A.p-B.p).len() < A.r+B.r) {
        auto F = (A.p-B.p);
        F.setMag(A.r+B.r-(A.p-B.p).len());
        A.p = A.p + F/2;
        B.p = B.p - F/2;
    }
}

signed main() {
    srand(time(0));
    cin.tie(0)->sync_with_stdio(0);
    int fc = 0;
    vector<ball> balls;
    ball wall = {width/2.0, '8', {width/2.0f, height/2.0f}};
    while (++fc) {
        system("clear");
        for (auto&a:board) for (auto&b:a) b = ' ';
        if (fc%10 == 1) {
            float ang = float(rand())/RAND_MAX * M_PI;
            ball b = {float(rand()%7+3), "<^*.Z+"[rand()%5], {float(rand()%(width-14)+7), 0.0f}};
            b.p2=b.p-vec({cos(ang), sin(ang)});
            balls.push_back(b);
        }

        for (ball &b:balls) b.force({0, 1});

        for (int j = 0; j < 100; j++) {
            for (auto&A:balls) {
                for (auto&B:balls) {
                    if (&A-&balls[0] == &B-&balls[0]) continue;
                    col(A, B);
                }
            }
        }

        for (ball &b:balls) b.update();
        for (ball &b:balls) draw(b);
        for (auto&a:board) {for (auto x:a) cout << x << ' '; cout<<endl;}
        this_thread::sleep_for(chrono::milliseconds((int)round(1000/20)));
    }

    return 0;
}


/* 
*/
