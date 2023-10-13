let input_entry = document.getElementById("entry");
let dico = {
    "a": [1, 0, 0, 0, 0], // les 1 sont les doigts qui sont levés
    "b": [0, 1, 1, 1, 1], // ici ce sont des fausses valeurs, il faut les remplacer par les bonnes
    "c": [1, 0.5, 0.5, 0.5, 0.5], // premier element = le pouce
    "d": [0.5, 1, 0.5, 0.5, 0.5],
    "e": [0, 0.5, 0.5, 0.5, 0.5],
    "f": [0.5, 0.5, 1, 1, 1],
    "g": [0.5, 1, 0, 0, 0],
    "h": [0, 1, 0, 0, 1],
    "i": [0, 0, 0, 0, 1],
    "j": [1, 0, 0, 0, 1],
    "k": [0.5, 1, 0.5, 0, 0],
    "l": [1, 1, 0.5, 0.5, 0.5],
    "m": [0, 1, 1, 1, 1],
    "n": [0, 1, 1, 0, 0],
    "o": [0.5, 0.5, 0.5, 0.5, 0.5],
    "p": [0.5, 1, 1, 0, 0],
    "q": [0, 1, 0, 0, 0],
    "r": [0, 1, 1, 0, 0],
    "s": [0, 0, 0, 0, 0],
    "t": [0.5, 0.5, 1, 1, 1],
    "u": [0, 1, 1, 0, 0],
    "v": [0, 1, 1, 0, 0],
    "w": [0, 1, 1, 1, 0],
    "x": [0, 0.5, 0.5, 0, 0],
    "y": [1, 0, 0, 0, 1],
    "z": [0, 1, 0, 0, 0],
    "-": [1, 1, 1, 1, 1],
};
let buffer = [];
const activeFinger = [1, 1, 1, 1, 1];

function send_message() {
    let message = input_entry.value
        .replace(/[0-9]+/g, "")
        .trim()
        .toLowerCase();

    for (let i = 0; i < message.length; i++) {
        let letter = message[i];
        if (dico[letter] == undefined) {
            buffer.push([0, 0, 0, 0, 0]);
        } else {
            buffer.push(dico[letter]);
        }
    }

    input_entry.value = "";
}

function execute_buffer() {
    console.log(buffer);

    if (buffer.length > 0) {
        let hand_pos = buffer.shift();

        let xhttp = new XMLHttpRequest();
        xhttp.open(
            "GET", "/set-pos?0=" + hand_pos[0] +
            "&1=" + hand_pos[1] +
            "&2=" + hand_pos[2] +
            "&3=" + hand_pos[3] +
            "&4=" + hand_pos[4],
            true
        );
        xhttp.send();

        activeFinger[0] = hand_pos[0];
        activeFinger[1] = hand_pos[1];
        activeFinger[2] = hand_pos[2];
        activeFinger[3] = hand_pos[3];
        activeFinger[4] = hand_pos[4];
    }

    update_image();
    buf_timout = setTimeout(execute_buffer, 500);
}

function update_image() {
    activeFinger[0] ? thumb.style.display = 'block' : thumb.style.display = 'none';
    activeFinger[1] ? index.style.display = 'block' : index.style.display = 'none';
    activeFinger[2] ? middle.style.display = 'block' : middle.style.display = 'none';
    activeFinger[3] ? ring.style.display = 'block' : ring.style.display = 'none';
    activeFinger[4] ? pinky.style.display = 'block' : pinky.style.display = 'none';
}

function init() {
    execute_buffer();
}

// Hand image click

const handBG = document.getElementById('handBG');
const pinky = document.getElementById('pinky');
const ring = document.getElementById('ring');
const middle = document.getElementById('middle');
const index = document.getElementById('index');
const thumb = document.getElementById('thumb');

document.addEventListener('click', function (event) {
    const clickX = event.clientX - handBG.getBoundingClientRect().left;
    const imageWidth = handBG.width;

    if (clickX <= imageWidth / 2.5 && clickX >= imageWidth / 3) {
        activeFinger[4] = (activeFinger[4]+1) %2;
    } else if (clickX <= imageWidth / 2.1 && clickX >= imageWidth / 2.5) {
        activeFinger[3] = (activeFinger[3]+1) %2;
    } else if (clickX <= imageWidth / 1.8 && clickX >= imageWidth / 2.1) {
        activeFinger[2] = (activeFinger[2]+1) %2;
    } else if (clickX <= imageWidth / 1.6 && clickX >= imageWidth / 1.8) {
        activeFinger[1] = (activeFinger[1]+1) %2;
    } else if (clickX <= imageWidth / 1.3 && clickX >= imageWidth / 1.6) {
        activeFinger[0] = (activeFinger[0]+1) %2;
    }

    let xhttp = new XMLHttpRequest();
        xhttp.open(
            "GET", "/set-pos?0=" + activeFinger[0] +
            "&1=" + activeFinger[1] +
            "&2=" + activeFinger[2] +
            "&3=" + activeFinger[3] +
            "&4=" + activeFinger[4],
            true
        );
        xhttp.send();
    
    update_image();
});