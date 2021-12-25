let lines = [], s3 = Math.sqrt(3);
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

function Line(a, b) {
    this.a = a;
    this.b = b;

    this.render = function () {line(a.x, a.y, b.x, b.y);}
    this.len = function () {return dist(a.x, a.y, b.x, b.y);}
}

function render() {
    fill(255);
    beginShape();
    for (let i = 0; i < lines.length; i++) {
        vertex(lines[i].a.x, lines[i].a.y);
    } endShape();
}

// function render() {
//     for (let i = 0; i < lines.length; i++) {
//         lines[i].render();
//     }
// }

function frame() {
    let nw = [];
    for (let i = 0; i < lines.length; i++) {
        let l = lines[i];
        let a = l.a, b = l.b, len = l.len()/3;
        b = b.sub(a);
        b = b.norm(len);
        nw.push(new Line(a, a.add(b)));
        a = a.add(b);
        let c = new Point((b.x-s3*b.y)/2, (b.y+s3*b.x)/2);
        nw.push(new Line(a, a.add(c)));
        nw.push(new Line(a.add(c), a.add(b)));
        a = a.add(b);
        nw.push(new Line(a, a.add(b)));
    }

    lines = nw;
}

function setup() {
    createCanvas(500, 500);
    stroke(255);
    noFill();

    let r = 100;
    let a = new Point(width/2 - r, height/2 + s3*r/2);
    let b = new Point(width/2 + r, height/2 + s3*r/2);
    let c = new Point(width/2    , height/2 - s3*r/2);

    lines.push(new Line(c, a));
    lines.push(new Line(a, b));
    lines.push(new Line(b, c));

    frameRate(5);
    background(0);
    render();
}

function keyPressed() {
    if (key === ' ') {
        background(0);
        if (lines.length < 1000) frame();
        render();
    }
}

function draw() {}
