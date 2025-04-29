let snake = [{
    x: 0,
    y: 190
}]



function drawSnake() {

    snake.forEach(drawSnakePart)
}


const myCanvas = document.getElementById("myCanvas");

const ctx = myCanvas.getContext("2d");

function drawSnakePart(snakePart) {


    ctx.fillStyle = 'red';


    ctx.fillRect(snakePart.x, snakePart.y, 10, 10);

}

let dx = 10;

let dy = 0;

function move_snake() {

    const head = {
        x: snake[0].x + dx,
        y: snake[0].y + dy
    };

    snake.unshift(head);

}

let direction = "right";

function goLeft() {
    if (direction == "right") {
        dx = 0;
        dy = -10;
        direction = "up";
    } else if (direction == "up") {
        dx = -10;
        dy = 0;
        direction = "left";
    } else if (direction == "left") {
        dx = 0;
        dy = 10;
        direction = "down";

    } else if (direction == "down") {
        dx = 10;
        dy = 0;
        direction = "right";
    }


}

function goRight() {
    if (direction == "right") {
        dx = 0;
        dy = 10;
        direction = "down";
    } else if (direction == "up") {
        dx = 10;
        dy = 0;
        direction = "right";
    } else if (direction == "left") {
        dx = 0;
        dy = -10;
        direction = "up";

    } else if (direction == "down") {
        dx = -10;
        dy = 0;
        direction = "left";
    }

}


function checkWall() {
    for (let i = 4; i < snake.length; i++) {
        if (snake[i].x === snake[0].x && snake[i].y === snake[0].y) return true
    }
    const hitLeftWall = snake[0].x < 0;
    const hitRightWall = snake[0].x > myCanvas.width - 10;
    const hitToptWall = snake[0].y < 0;
    const hitBottomWall = snake[0].y > myCanvas.height - 10;
    return hitLeftWall || hitRightWall || hitToptWall || hitBottomWall
}

let timer;

function stopTime() {
    clearInterval(timer);
    timer = null;
}

function startTime() {
    if (!timer) {
        var i = 100;
        timer = setInterval(function() {
            document.getElementById("here").innerHTML = i--;

            move_snake();
            drawSnake();
            if (checkWall()) {
                dx = 0;
                dy = 0;
            }
        }, 1000)
    }

}