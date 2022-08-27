class Tree {
	constructor() {
		this.root = null;
		this.height = 0;
		this.nodes = 0;
	}

	compare(a, b) {
		return a > b ? 1 : a < b ? -1 : 0;
	}

	insertNode(value) {
		value = parseInt(value);
		if (isNaN(value)) return 0;

		if (this.find(value)) return 0;

		let newNode = new Node(value);
		let parent = this.root;

		if (!parent) {
			this.root = newNode;
			this.nodes++;
			this.height++;
			return this.root;
		}

		while (!newNode.parent) {
			if (this.compare(value, parent.value) === -1) {
				if (!parent.left) {
					parent.left = newNode;
					newNode.parent = parent;
				}
				newNode.height++;
				parent = parent.left;
			} else {
				if (!parent.right) {
					parent.right = newNode;
					newNode.parent = parent;
				}
				newNode.height++;
				parent = parent.right;
			}
		}

		// rebalanceo
		if (newNode.parent.parent) {
			let gParent = newNode.parent.parent;
			while (gParent) {
				let balance = gParent.getBalance();

				// Left Left 
				if (balance > 1 && value < gParent.left.value)
					this.root = gParent.rotateLL(this.root);
				// Right Right 
				else if (balance < -1 && value > gParent.right.value)
					this.root = gParent.rotateRR(this.root);
				// Left Right 
				else if (balance > 1 && value > gParent.left.value)
					this.root = gParent.rotateLR(this.root);
				// Right Left 
				else if (balance < -1 && value < gParent.right.value)
					this.root = gParent.rotateRL(this.root);

				gParent = gParent.parent;
			}
		}

		this.nodes++;
		clear();
		background(51);
		maxpath = 0; 
		this.preOrder(); 
		this.height = maxpath;
		updateInfo();
		return newNode;
	}

	removeNode(value) {
		// eliminación regular
		let node = this.find(value);
		let y = null; 
		let z = null; 

		if (node) {
			if (!node.left || !node.right) y = node;
			else y = node.next();

			if (y.left) z = y.left;
			else z = y.right;

			if (z) z.parent = y.parent;
			if (!y.parent) this.root = z;
			else if (y === y.parent.left) y.parent.left = z;
			else y.parent.right = z;

			if (y !== node) node.value = y.value;

			// rebalanceo
			while (y) {
				let balance = y.getBalance();
				// Left Left 
				if (balance > 1 && y.left.getBalance() >= 0)
					this.root = y.rotateLL(this.root);
				// Right Right 
				else if (balance < -1 && y.right.getBalance() <= 0)
					this.root = y.rotateRR(this.root);
				// Left Right 
				else if (balance > 1 && y.left.getBalance() < 0)
					this.root = y.rotateLR(this.root);
				// Right Left 
				else if (balance < -1 && y.right.getBalance() > 0)
					this.root = y.rotateRL(this.root);
				y = y.parent;
			}
		} else {
			return 0; 
		}

		this.nodes--; 
		clear();
		background(51);
		maxpath = 0; 
		this.preOrder(); 
		this.height = maxpath;
		updateInfo();
		return node;
	}

	find(nodevalue) {
		let childNode = this.root;

		while (childNode && nodevalue !== childNode.value) {
			if (this.compare(nodevalue, childNode.value) < 0) childNode = childNode.left;
			else childNode = childNode.right;
		}

		return childNode;
	}

	preOrder() {
		this.root.preOrderTraverse();
	}

	inOrder() {
		this.root.inOrderTraverse();
	}

	postOrder() {
		this.root.postOrderTraverse();
	}
}
