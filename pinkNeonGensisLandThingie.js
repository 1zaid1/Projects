let res = 15, angle = 0, isMoving = false;
function setup() {
    createCanvas(windowWidth-50, windowHeight-50, WEBGL);
}

function mousePressed() {
    isMoving = !isMoving;
}

function draw() {
    let w = width/2, h = height/2;
    background(0);
    stroke(255, 120, 150);
    noFill();
    rotateX(PI/3);
    rotateZ(angle);
    translate(-w/2, -h/2);

    let rn = [];
    for (let y = 0; y <= h; y += res) {
        let tmp = [];
        for (let x = 0; x <= w; x += res) {
            tmp.push(noise(x/1000.0*res, y/1000.0*res)*50);
        } rn.push(tmp);
    }

    w -= w%res;
    h -= h%res;
    for (let y = 0; y <= h; y += res) {
        // beginShape(TRIANGLE_STRIP);
        beginShape();
        for (let x = 0; x <= w; x += res) {
            vertex(x, y, rn[y/res][x/res]);
            // vertex(x+res, y+res, rn[y/res+1][x/res+1]);
            // vertex(x, y+res, rn[y/res+1][x/res]);
            // vertex(x+res, y, rn[y/res][x/res+1]);
        } endShape();

        if (rn[y/res+1]) line(0, y, rn[y/res][0], 0, y+res, rn[y/res+1][0]);
        if (rn[y/res+1]) line(rn[y/res].length*res-res, y, rn[y/res][rn[y/res].length-1], rn[y/res].length*res-res, y+res, rn[y/res+1][rn[y/res].length-1]);
    } //endShape();

    line(0, 0, 0, 0, 0, rn[0][0]);
    line(w, 0, 0, w, 0, rn[0][w/res]);
    line(0, h, 0, 0, h, rn[h/res][0]);
    line(w, h, 0, w, h, rn[h/res][w/res]);
    rect(0, 0, w, h);
    if (isMoving) angle += 0.01;
}
