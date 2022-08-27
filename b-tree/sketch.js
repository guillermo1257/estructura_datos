let tree;
let deleteInput;
let deleteButton;
let delayInput;
let setDelayButton;
let currentNode = null;
let delay = 0 ;
let running = false;
function setup() {
  tree = new BTree(2);

  createCanvas(windowWidth, windowHeight);
  background(51);
  textAlign(CENTER, CENTER);
}

function draw() {
	canvas = createCanvas(windowWidth, windowHeight);
	canvas.position(02, 0);
	canvas.style("z-index", "-1"); 
  textAlign(CENTER, CENTER);
	background(51);
  stroke(255);
  tree.draw(50, 150, 50);
}

document.getElementsByClassName("insertBtn")[0].addEventListener("click", e => {
	e.preventDefault();
	let val = document.getElementsByClassName("value")[0].value;
  if (!Number.isNaN(val)) {
    running = true;
    tree.insert(val);
    tree.verify();
    document.getElementsByClassName("value")[0].value = "";
  }
});

document.getElementsByClassName("removeBtn")[0].addEventListener("click", e => {
	e.preventDefault();

	let value = parseInt(document.getElementsByClassName("value")[1].value);

  document.getElementsByClassName("value")[1].value = "";

  tree.delete(value);
});


function updateInfo() {
	let info = document.getElementsByClassName("tree-data")[0];
	info.innerHTML = `
    <tr>
      <th>Mínimo:</th>
      <th>${tree.getMin()}</th>
    </tr>
	<tr>	
    <tr>
      <th>Máximo:</th>
      <th>${tree.getMax()}</th>
    </tr>
	<tr>		

  `;
}