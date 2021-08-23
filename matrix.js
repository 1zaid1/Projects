let simpSize;
let simps;

let cnt = 0;
let c;

let smsm = 0.5;
function Simp(x, y, speed, rnd, op) {
    this.op = op;
    this.first = false;
    this.val;
    this.speed = speed;
    this.x = x;
    this.y = y;
    this.rnd = round(rnd);
    this.setRandom = function () {
        this.val = String.fromCharCode(0x30A0 + round(random(0, 96)));
        // this.val = String.fromCharCode(0x0623 + round(random(0, 40)));
    }

    this.move = function () {
        this.y += this.speed;
        if (this.y > height) this.y = 0;
    }

    this.display = function () {
        if (this.first) fill(180, 255, 210, op);
        else fill(50, 205, 50, op);
        this.move();
        if (frameCount % this.rnd == 0) {
            this.setRandom();
        }

        text(this.val, this.x, this.y);
    }
}
function Stream() {
    this.arr = [];

    this.display = function () {
        for (let i = 0; i < this.arr.length; i++) {
            this.arr[i].display();
        }
    }
}

function setup() {
    c = createCanvas(window.innerWidth-50, window.innerHeight-50);

    simpSize = 20;
    textSize(simpSize);
    simps = [];
    for (let x = 0; x < width; x += simpSize) {
        let tmp = new Stream();
        let y = round(random(0, -2000));

        let speed = random(5, 22);

        let sz = round(random(5, 35));
        let pp = 255 / sz;
        for (let i = 0; i < sz; i++) {
            tmp.arr.push(new Simp(x, y, speed, random(5, 10), pp*i/smsm));
            tmp.arr[i].setRandom();

            y += simpSize;
        }

        if (random(0, 1) <= 0.3) tmp.arr[sz-1].first = true;

        simps.push(tmp);
    }

    console.log(width, height);
}

function draw() {
    background(0, 180);
    frameRate(30);
    fill('lime');

    simps.forEach(function (simp) {
        simp.display();
    });
}
