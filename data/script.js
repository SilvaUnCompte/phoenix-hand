let input_entry = document.getElementById("entry");
let dico = {
  // premier element et tjr le pouce
  a: [1, 0, 0, 0, 0], // les 1 sont les doigts qui sont levés
  b: [0, 1, 1, 1, 1], // ici ce sont des fausses valeurs, il faut les remplacer par les bonnes
  c: [1, 0.5, 0.5, 0.5, 0.5],
  d: [0.5, 1, 0.5, 0.5, 0.5],
  e: [0, 0.5, 0.5, 0.5, 0.5],
  f: [0.5, 0.5, 1, 1, 1],
  g: [0.5, 1, 0, 0, 0],
  h: [0, 1, 0, 0, 1],
  i: [0, 0, 0, 0, 1],
  j: [1, 0, 0, 0, 1],
  k: [0.5, 1, 0.5, 0, 0],
  l: [1, 1, 0.5, 0.5, 0.5],
  m: [0, 1, 1, 1, 1],
  n: [0, 1, 1, 0, 0],
  o: [0.5, 0.5, 0.5, 0.5, 0.5],
  p: [0.5, 1, 1, 0, 0],
  q: [0, 1, 0, 0, 0],
  r: [0, 1, 1, 0, 0],
  s: [0, 0, 0, 0, 0],
  t: [0.5, 0.5, 1, 1, 1],
  u: [0, 1, 1, 0, 0],
  v: [0, 1, 1, 0, 0],
  w: [0, 1, 1, 1, 0],
  x: [0, 0.5, 0.5, 0, 0],
  y: [1, 0, 0, 0, 1],
  z: [0, 1, 0, 0, 0],
  "-": [1, 1, 1, 1, 1],
};
let buffer = [];

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
}

function execute_buffer() {
  console.log(buffer);

  if (buffer.length > 0) {
    let hand_pos = buffer.shift();

    let xhttp = new XMLHttpRequest();
    xhttp.open(
      "GET",
      "/set-pos?0=" +
        hand_pos[0] +
        "&1=" +
        hand_pos[1] +
        "&2=" +
        hand_pos[2] +
        "&3=" +
        hand_pos[3] +
        "&4=" +
        hand_pos[4],
      true
    );
    xhttp.send();
  }

  buf_timout = setTimeout(execute_buffer, 700);
}

function init() {
  execute_buffer();
}
