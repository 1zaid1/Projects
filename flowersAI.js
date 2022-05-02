let img, n = 10, pp = [], w = 200, gen, rate = 0.1;
function Dna(r, n, p) {
    this.r = r;//random()*60+30;
    this.n = n;//round(random()*10);
    this.p = p;//random();
}

function comb(a, b) {
    let n = new Dna(0,0,0);// round((a.n+b.n)/2), (a.p+b.p)/2);
    let r = random();
    n.r = a.r*r + (1-r)*b.r;
    r = random();
    n.n = round(a.n*r+(1-r)*b.n);
    r = random();
    n.p = a.p*r+(1-r)*b.p;

    return n;
}

function flower(x, y) {
    this.x = x;
    this.y = y;
    this.dna = new Dna(random()+1, round(random()*10), random());
    this.mute = function() {
        if (random() <= rate) this.dna.r += (random()-0.5)*(2-this.dna.r);
        if (random() <= rate) this.dna.p = random();
        if (random() <= rate) this.dna.n += round(random()*6-3);
    }

    this.render = function () {
        push();
        fill(0);
        rect(this.x, this.y, w);
        translate(this.x+w/2, this.y+w/2);
        fill(255);
        beginShape();
        for (let i = 0; i <= TWO_PI; i += 0.01) {
            let r = this.dna.r-2 + this.dna.p*sin(this.dna.n*i);
            r *= w/4;
            vertex(r*cos(i), r*sin(i));
        } endShape();
        pop();
    }
}

function generation() {
    this.pop = [];
    this.fit = [];
    this.setup = function(size) {
        for (let i = 0; i < size; i++) {
            this.pop.push(new flower(i*(w+10)+10, 10));
            this.fit.push(1);
        }
    }

    this.pick = function(f) {
        if (!f) f = flower(0, 0, 0);
        let sum = 0, av = 0;
        let r = random(), tmp = 0, ft = 0;
        for (let i = 0; i < this.fit.length; i++) if (pop[i] == f) tmp = i;
        ft = this.fit[tmp];
        if (random() <= 0.5) this.fit[tmp] = 0;
        for (let i = 0; i < this.fit.length; i++) {
            av += this.fit[i];
        }

        for (let i = 0; i < this.fit.length; i++) {
            sum += this.fit[i]/av;
            if (r <= sum) {
                this.fit[tmp] = ft;
                return this.pop[i];
            }
        } this.fit[tmp] = ft;
        return this.pop[this.pop.length-1];
    }

    this.evu = function() {
        let nw = [];
        for (let i = 0; i < this.pop.length; i++) {
            let f = new flower(this.pop[i].x, this.pop[i].y);
            let a = this.pick().dna;
            f.dna = comb(a, this.pick(a).dna);
            f.mute();
            nw.push(f);
        }

        for (let i = 0; i < this.fit.length; i++) this.fit[i] = 1;
        for (let i = 0; i < this.fit.length; i++) this.pop[i] = nw[i];
    }

    this.textR = function () {
        push();
        for (let i = 0; i < this.pop.length; i++) {
            fill(255);noStroke();
            rect(this.pop[i].x-1, this.pop[i].y+w, w, 20);
            fill(0); stroke(0);
            textSize(10);
            text(String(this.fit[i]-1), this.pop[i].x, this.pop[i].y+w+10);
        } pop();
    }
    this.render = function() {
        for (let i = 0; i < this.pop.length; i++) {
            this.pop[i].render();
        } this.textR();
    }
}

function setup() {
  createCanvas(1070, w+50);
  gen = new generation();
  gen.setup(5);
  gen.render();
  noFill();
  fill(0);
  background(250);
  gen.render();
}

function mousePressed() {
    if (mouseY >= height) return;
    let i = floor(mouseX/(w+10));
    gen.fit[i]++;
    gen.textR();
}

function clack() {
    gen.evu();
    background(250);
    gen.render();
}

function draw() {
    if (mouseY > 0 && mouseY < height) {
        let i = floor(mouseX/(w+10));
        gen.fit[i]+=0.25;
        gen.textR();
    }
}
