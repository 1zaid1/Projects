let tri = [], s3 = Math.sqrt(3);
function Point(x, y) {
    this.x = x;
    this.y = y;

    this.add = function(a) {return new Point(this.x+a.x, this.y+a.y);}
    this.sub = function(a) {return new Point(this.x-a.x, this.y-a.y);}
    this.mul = function(a) {return new Point(this.x * a, this.y * a);}
    this.dev = function(a) {return new Point(this.x / a, this.y / a);}

    this.len = function() {
        return sqrt(this.x**2 + this.y**2);
    }

    this.norm = function(n) {
        let l = this.len();
        return new Point(this.x/l*n, this.y/l*n);
    }
}

function linep(a, b) {
    line(a.x, a.y, b.x, b.y);
}

function Tri(a, b, c) {
    this.a = a;
    this.b = b;
    this.c = c;

    this.render = function () {linep(a, b);linep(b, c); linep(c, a);}
    this.fill = function () {beginShape(); vertex(a.x, a.y); vertex(b.x, b.y); vertex(c.x, c.y); endShape();}
    this.len = function () {return dist(a.x, a.y, b.x, b.y);}
}

function render() {
    for (let i = 0; i < tri.length; i++) {
        tri[i].fill();
    }
}

function av(a, b) {
    return new Point((a.x+b.x)/2, (a.y+b.y)/2);
}

function frame() {
    let nw = [];
    for (let i = 0; i < tri.length; i++) {
        let t = tri[i];

        let fs = av(t.a, t.b);
        let sc = av(t.a, t.c);
        let th = av(t.b, t.c);
        nw.push(new Tri(t.a, fs, sc));
        nw.push(new Tri(fs, t.b, th));
        nw.push(new Tri(sc, th, t.c));
    }

    tri = nw;
    console.log(tri.length);
}

function setup() {
    createCanvas(500, 500);
    stroke(255);
    // noFill();
    fill(255);

    let r = 100;
    let a = new Point(width/2 - r, height/2 + s3*r/2);
    let b = new Point(width/2 + r, height/2 + s3*r/2);
    let c = new Point(width/2    , height/2 - s3*r/2);

    tri.push(new Tri(c, a, b));

    frameRate(5);
    background(0);
    render();
    console.log(1);
}

function keyPressed() {
    if (key === ' ') {
        background(0);
        if (tri.length < 1000) frame();
        render();
    }
}

function draw() {}
