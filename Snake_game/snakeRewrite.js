let snake = [
    { x: 0, y: 190 }
];

const myCanvas = document.getElementById("myCanvas");
const ctx = myCanvas.getContext("2d");

let dx = 10;
let dy = 0;
let direction = "right";
let timer;
let countdown = 10000;
let food = randomFood();

function drawSnake() {
    snake.forEach(drawSnakePart);
}

function drawSnakePart(snakePart) {
    ctx.fillStyle = 'red';
    ctx.fillRect(snakePart.x, snakePart.y, 10, 10);
}

function move_snake() {
    const head = {
        x: snake[0].x + dx,
        y: snake[0].y + dy
    };
    snake.unshift(head);

    if (head.x === food.x && head.y === food.y) {
        food = randomFood();
    } else {
        snake.pop();
    }
}

function randomFood() {
    const foodX = Math.floor(Math.random() * (myCanvas.width / 10)) * 10;
    const foodY = Math.floor(Math.random() * (myCanvas.height / 10)) * 10;
    return { x: foodX, y: foodY };
}

function drawFood() {
    ctx.fillStyle = 'green';
    ctx.fillRect(food.x, food.y, 10, 10);
}

function goLeft() {
    if (direction === "right") {
        dx = 0;
        dy = -10;
        direction = "up";
    } else if (direction === "up") {
        dx = -10;
        dy = 0;
        direction = "left";
    } else if (direction === "left") {
        dx = 0;
        dy = 10;
        direction = "down";
    } else if (direction === "down") {
        dx = 10;
        dy = 0;
        direction = "right";
    }
}

function goRight() {
    if (direction === "right") {
        dx = 0;
        dy = 10;
        direction = "down";
    } else if (direction === "up") {
        dx = 10;
        dy = 0;
        direction = "right";
    } else if (direction === "left") {
        dx = 0;
        dy = -10;
        direction = "up";
    } else if (direction === "down") {
        dx = -10;
        dy = 0;
        direction = "left";
    }
}

function checkCollision() {
    const hitLeftWall = snake[0].x < 0;
    const hitRightWall = snake[0].x >= myCanvas.width;
    const hitTopWall = snake[0].y < 0;
    const hitBottomWall = snake[0].y >= myCanvas.height;

    if (hitLeftWall || hitRightWall || hitTopWall || hitBottomWall) {
        return true;
    }

    for (let i = 1; i < snake.length; i++) {
        if (snake[i].x === snake[0].x && snake[i].y === snake[0].y) {
            return true;
        }
    }
    return false;
}

function stopTime() {
    clearInterval(timer);
    timer = null;
    document.getElementById("header").innerText = "GAME OVER";
    setTimeout(function() {
        location.reload();
    }, 5000);
}

function startTime() {
    if (!timer) {
        timer = setInterval(function() {
            countdown--;
            document.getElementById("here").innerHTML = countdown;

            ctx.clearRect(0, 0, myCanvas.width, myCanvas.height);

            move_snake();
            drawFood();
            drawSnake();

            if (checkCollision()) {
                stopTime();
            }

            if (countdown <= 0) {
                stopTime();
            }
        }, 300);
    }
}