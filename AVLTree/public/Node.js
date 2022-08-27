class Node {
	constructor(value, x, y) {
		this.left = null;
		this.right = null;
		this.parent = null;
		this.height = 0;
		this.balanceFactor = 0;
		this.value = value;
		this.x = x;
		this.y = y;
	}

	getHeight() {
		if (this.height > maxH) maxH = this.height;
		if (this.left) this.left.getHeight();
		if (this.right) this.right.getHeight();
	}

	getBalance() {
		let lh = this.height;
		let rh = this.height;
		if (this.left) {
			this.left.getHeight();
			lh = maxH;
			maxH = 0;
		}
		if (this.right) {
			this.right.getHeight();
			rh = maxH;
			maxH = 0;
		}
		return lh - rh;
	}

	rotateLL(root) {
		alert('rotateLL');
		let leftNode = this.left;
		let parent = this.parent;

		this.height++;
		leftNode.height--;
		leftNode.left.height--;

		this.left = leftNode.right;
		if (this.left) this.left.parent = this;

		leftNode.right = this;
		leftNode.parent = parent;
		this.parent = leftNode;

		if (parent) {
			if (parent.left === this) {
				parent.left = leftNode;
			} else {
				parent.right = leftNode;
			}
		} else {
			root = leftNode;
		}

		return root;
	}

	rotateRR(root) {
		alert('rotateRR');
		let rightNode = this.right;
		let parent = this.parent;

		this.height++;
		rightNode.height--;
		rightNode.right.height--;

		this.right = rightNode.left;
		if (this.right) this.right.parent = this;

		rightNode.left = this;
		rightNode.parent = parent;
		this.parent = rightNode;

		if (parent) {
			if (parent.left === this) {
				parent.left = rightNode;
			} else {
				parent.right = rightNode;
			}
		} else {
			root = rightNode;
		}

		return root;
	}

	rotateRL(root) {
		alert('rotateRL');
		let rightNode = this.right;
		let tempNode = rightNode.left;
		let parent = this.parent;

		this.height++;
		tempNode.height -= 2;

		rightNode.left = tempNode.right;
		if (rightNode.left) rightNode.left.parent = rightNode;

		this.right = tempNode.left;
		if (this.right) this.right.parent = this;

		tempNode.left = this;
		tempNode.right = rightNode;
		this.parent = rightNode.parent = tempNode;
		tempNode.parent = parent;

		if (parent)
			if (parent.left === this) parent.left = tempNode;
			else parent.right = tempNode;
		else root = tempNode;

		return root;
	}

	rotateLR(root) {
		alert('rotateLR');
		let leftNode = this.left;
		let tempNode = leftNode.right;
		let parent = this.parent;

		this.height++;
		tempNode.height -= 2;

		leftNode.right = tempNode.left;
		if (leftNode.right) leftNode.right.parent = leftNode;

		this.left = tempNode.right;
		if (this.left) this.left.parent = this;

		tempNode.right = this;
		tempNode.left = leftNode;
		this.parent = leftNode.parent = tempNode;
		tempNode.parent = parent;

		if (parent)
			if (parent.left === this) parent.left = tempNode;
			else parent.right = tempNode;
		else root = tempNode;

		return root;
	}

	// nodo minimo
	min() {
		let node = this;

		if (node) while (node.left) node = node.left;
		return node;
	}

	// maximo nodo
	max() {
		let node = this;

		if (node) while (node.right) node = node.right;
		return node;
	}	

	// sucesor
	next() {
		let node = this;
		let parent = null;

		if (node) {
			if (node.right) return node.right.min();
			else {
				parent = node.parent;
				while (parent && node === parent.right) {
					node = parent;
					parent = parent.parent;
				}
				return parent;
			}
		}
		return node;
	}

	assignCoords() {
		this.y = this.parent.y + height / 12;
		if (this === this.parent.right)
			this.x = this.parent.x + width / pow(2, this.height + 1);
		else this.x = this.parent.x - width / pow(2, this.height + 1);
	}

	preOrderTraverse() {
		if (this.height > maxpath) maxpath = this.height;

		this.draw();

		if (this.left) {
			this.left.height = this.height + 1;
			this.left.preOrderTraverse();
		}
		if (this.right) {
			this.right.height = this.height + 1;
			this.right.preOrderTraverse();
		}
	}

	inOrderTraverse() {
		if (this.left) this.left.inOrderTraverse();
		this.draw();
		if (this.right) this.right.inOrderTraverse();
	}

	postOrderTraverse() {	
		if (this.left) this.left.postOrderTraverse();
		if (this.right) this.right.postOrderTraverse();
		this.draw();
	}

	draw() {
		const radius = 40; //Radio de cada nodo
		stroke(255); // Color de linea

		// actualiza coordenadas al eliminar
		if (this.parent && this.height - 1 !== this.parent.height) {
			this.height--;
			this.assignCoords();
		}

		// actualiza coordenadas al actualizar
		if (this.parent) this.assignCoords();

		if (!this.parent) {
			this.x = width / 2; //posición general del gráfico X
			this.y = 30; //posición general del gráfico Y
		}

		// excluir raiz (no tiene papá)
		if (this.parent != null)
			line(this.parent.x , (this.parent.y) * 2 + radius , this.x, (this.y) * 2 - radius );

		stroke(255);
		strokeWeight(3);
		noFill();
		ellipse(this.x, this.y * 2, 2 * radius, 2 * radius);

		fill(255);
		textAlign(CENTER);
		textStyle(BOLD);
		strokeWeight(0);
		textSize(20);
		text(this.value, this.x, ((this.y + 4) * 2));
		strokeWeight(3);
	}
}
