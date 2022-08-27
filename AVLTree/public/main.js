let previousvalue = false; 
let maxpath = 0; 
let maxH = 0;

function setup() {
	canvas = createCanvas(windowWidth, windowHeight);
	canvas.position(0, 0);
	canvas.style("z-index", "-1"); 
	background(51);

	tree = new Tree();
}

function draw() {} 

document.getElementsByClassName("insertBtn")[0].addEventListener("click", e => {
	e.preventDefault();
	let val = document.getElementsByClassName("value")[0].value;

	let node = tree.find(parseInt(val));

	if (node != null)
	{
		alert ("Nodo repetido");
	}
	else
	{
		tree.insertNode(val);
		document.getElementsByClassName("value")[0].value = "";
		
	}
});

document.getElementsByClassName("removeBtn")[0].addEventListener("click", e => {
	e.preventDefault();

	let value = parseInt(document.getElementsByClassName("value")[1].value);

	let node = tree.find(parseInt(value));

	if (node == null)
	{
		alert ("Nodo no encontrado");
	}
	else
	{
		tree.removeNode(value);
		document.getElementsByClassName("value")[1].value = "";
		
	}	
});

document.getElementsByClassName("findBtn")[0].addEventListener("click", e => {
	e.preventDefault();
	console.log()
	if (previousvalue) {
		clear();
		background(51);
		tree.preOrder();
	}

	let value = parseInt(document.getElementsByClassName("value")[2].value);
	let node = tree.find(value);

	if (node === null)
	{
		alert ("No se encontró nodo");
	}
	else		
	{
		strokeWeight(4);
		stroke("#49E845");
		noFill();
		ellipse(node.x, node.y * 2, 80, 80); //resalta nodo buscado

		document.getElementsByClassName("value")[2].value = "";
		previousvalue = true;
	}
});

function updateInfo() {
	let info = document.getElementsByClassName("tree-data")[0];
	info.innerHTML = `
    <tr>
      <th>Raíz:</th>
      <th>${tree.root.value} // ${tree.root.value}</th>
    </tr>
    <tr>
      <th>Altura Arbol:</th>
      <th>${tree.height}</th>
    </tr>
    <tr>
      <th>Número de nodos:</th>
      <th>${tree.nodes}</th>
    </tr>
	<tr>
    <tr>
      <th>Mínimo:</th>
      <th>${tree.root.min().value}</th>
    </tr>
	<tr>	
    <tr>
      <th>Máximo:</th>
      <th>${tree.root.max().value}</th>
    </tr>
	<tr>		

  `;
}
