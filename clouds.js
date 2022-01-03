let res = 4, sl, tm, cnv, pp = false, ppcnt = 0;
function setup() {
    cnv = createCanvas(800, 400);
    frameRate(10);
    sl = createSlider(3, 100, 17);
    tm = createSlider(0, 100, 25);
}

function keyPressed() {
    if (key == 's') {
        frameRate(1);
        pp = true;
    }
}

function draw() {
    background(0);
    background(200 - 50, 220 - 50, 255 - 50);
    noStroke();
    push();
    // rotateX(PI/1.5);
    // translate(-width/2, -height/2, 150);
    sl.position(30, 30);
    tm.position(30, 50);
    th = 1;
    let smooth = sl.value(),
    slow = 150 - tm.value();
    for (let i = -1; i <= width / res; i++) {
        for (let j = -1; j <= height / res; j++) {
            let n = noise(i / smooth, j / smooth, frameCount / slow);
            n = atan(13 * n - 5) / 3;
            if (n < 0) n = 0;
            n *= 500;
            fill(255, n);
            rect(i * res, j * res, res);
            // ellipse(i*res, j*res, res);
        }
    } pop();

    // fill(0);
    // translate(-width/2, -height/2, 50);
    // rect(0, 0, width, height/4);
    // rect(0, height/4, width/4, height/2);
    // rect(0, height/4*3, width, height);
    // rect(width/4*3, height/4, width/4, height/2);
}
