class BTree {
    constructor(degree, parent) {
      this.degree = degree;
      this.parent = parent;
      this.keys = [];
      this.childs = [];
    }
  
    renderString() {
      const lines = []
      let keys = this.keys.toString();
      lines.push(keys)
      if(this.childs.length === 0) {
        return lines
      }
  
      let links = ''
      this.childs.map((child) => {
        const childLines = child.renderString()
        links += "|" +' '.repeat(childLines[0].length + 2)
        childLines.map((line,index) => {
          if(lines[index+4])
          lines[index + 4] += "   " + line
          else lines[index+4] = line
        })
      })
  
      lines[1] = ''
      lines[2] = links;
      lines[3] = ''
  
      const maxLength = Math.max(...lines.map( l => l.length))
      for(let i = 0; i< lines.length; i++) {
        lines[i]+= ' '.repeat(maxLength - lines[i].length)
      }
  
      return lines
    }
  
    split() {
      if (this.keys.length !== this.degree * 2 - 1) {
        return;
      }
      const medianIndex = this.degree - 1;
      const leftChild = new BTree(this.degree, this);
      const rightChild = new BTree(this.degree, this);
      this.childs.forEach((child, index) => {
        if (index <= medianIndex) {
          child.parent = leftChild;
          leftChild.childs.push(child);
        } else {
          child.parent = rightChild;
          rightChild.childs.push(child);
        }
      });
  
      this.keys.forEach((key, index) => {
        if (index < medianIndex) {
          leftChild.keys.push(key);
        } else if (index > medianIndex) {
          rightChild.keys.push(key);
        }
      });
  
      const medianKey = this.keys[medianIndex];
      const parent = this.parent;
      if (!parent) {
        this.keys = [medianKey];
        this.childs = [leftChild, rightChild];
      } else {
        rightChild.parent = parent;
        leftChild.parent = parent;
        const childIndex = parent.childs.findIndex((c) => c == this);
        this.parent.childs[childIndex] = leftChild;
        this.parent.childs.splice(childIndex + 1, 0, rightChild);
        let i;
        for (i = 0; i < parent.keys.length; i++) {
          if (parent.keys[i] >= medianKey) {
            break;
          }
        }
        this.parent.keys.splice(i, 0, medianKey);
      }
      return { medianKey, leftChild, rightChild };
    }
  
    insert(value) {
      currentNode = this;
      if (this.keys.length === this.degree * 2 - 1) {
        const { medianKey, rightChild, leftChild } = this.split();
        if (value > medianKey) {
          setTimeout(() => rightChild.insert(value), delay);
        } else {
          setTimeout(() => leftChild.insert(value), delay);
        }
      } else {
        let i = 0;
        while (value > this.keys[i] && i < this.keys.length) {
          i += 1;
        }
        if (this.childs[i]) {
          setTimeout(() => this.childs[i].insert(value), delay);
        } else {
          this.keys.push(value);
          this.keys.sort(function(a, b) {
            return a - b;
          });
          running = false;
        }
      }
      updateInfo();
    }
  
    verify(min, max) {
      if (this.keys.length < this.degree - 1 || this.keys.length > this.degree * 2 - 1) {
        return false;
      }
  
      if (
        (this.childs.length > 1 && this.childs.length < this.keys.length) ||
        this.childs.length - this.keys.length > 1
      ) {
        return false;
      }
  
      if (min && this.keys[0] < min) {
        return false;
      }
  
      if (max && this.keys[this.keys.length - 1] > max) {
        return false;
      }
      let current = this.keys[0];
      for (let i = 0; i < this.keys.length; i++) {
        if (this.keys[i] < current) {
          return false;
        }
        current = this.keys[i];
      }
  
      for (let i = 0; i < this.childs.length; i++) {
        if (!this.childs[i].verify(this.keys[i - 1] || min, this.keys[i] || max)) {
          return false;
        }
      }
      return true;
    }
    
    getMax() {
      if(this.childs.length !== 0) {
        return this.childs[this.childs.length - 1].getMax()
      }
      return this.keys[this.keys.length - 1]
    }
  
    getMin() {
      if(this.childs.length !== 0) {
        return this.childs[0].getMin()
      }
      return this.keys[0]
    }
  
    delete(value) {
      running = true;
      if (!this.verify()) {
        running = false;
        return;
      }
      currentNode = this;
      if (this.keys.includes(value)) {
        const index = this.keys.findIndex((v) => v === value);
        if (this.childs.length === 0) {
          setTimeout(() => this.keys.splice(index, 1), delay);
          running = false;
          return;
        } else {
          const leftChild = this.childs[index];
          const rightChild = this.childs[index + 1];
          if (leftChild && leftChild.keys.length >= this.degree) {
            const toSwap = leftChild.getMax()
            this.keys[index] = toSwap;
            setTimeout(() => leftChild.delete(toSwap), delay);
          } else if (rightChild.keys.length >= this.degree) {
            const toSwap = rightChild.getMin()
            this.keys[index] = toSwap;
            setTimeout(() => rightChild.delete(toSwap), delay);
          } else {
            leftChild.keys.push(value);
            rightChild.keys.forEach((key) => {
              leftChild.keys.push(key);
            });
            rightChild.childs.forEach((child) => {
              child.parent = leftChild;
              leftChild.childs.push(child);
            });
            this.keys.splice(index, 1);
            this.childs.splice(index + 1, 1);
            if (this.keys.length === 0) {
              this.childs = leftChild.childs;
              this.keys = leftChild.keys;
            }
            setTimeout(() => leftChild.delete(value), delay);
          }
        }
      } else {
        let i = 0;
        if (this.childs.length === 0) {
          running = false;
          return;
        }
        while (this.keys[i] < value) i += 1;
        const selectedChild = this.childs[i];
        if (selectedChild.keys.length === this.degree - 1) {
          const thisIndex = i;
  
          const leftSibling = this.childs[thisIndex - 1];
  
          const rightSibling = this.childs[thisIndex + 1];
  
          if (leftSibling && leftSibling.keys.length >= this.degree) {
            selectedChild.keys.unshift(this.keys[thisIndex - 1]);
            this.keys[thisIndex - 1] = leftSibling.keys[leftSibling.keys.length - 1];
            leftSibling.keys.splice(leftSibling.keys.length - 1, 1);
            if (leftSibling.childs.length > 0) {
              const childToMove = leftSibling.childs[leftSibling.childs.length - 1];
              childToMove.parent = selectedChild;
              selectedChild.childs.unshift(childToMove);
              leftSibling.childs.splice(leftSibling.childs.length - 1, 1);
            }
          } else if (rightSibling && rightSibling.keys.length >= this.degree) {
            selectedChild.keys.push(this.keys[thisIndex]);
            this.keys[thisIndex] = rightSibling.keys[0];
            rightSibling.keys.splice(0, 1);
            if (rightSibling.childs.length > 0) {
              const childToMove = rightSibling.childs[0];
              childToMove.parent = selectedChild;
              selectedChild.childs.push(childToMove);
              rightSibling.childs.splice(0, 1);
            }
          } else {
            if (rightSibling) {
              selectedChild.keys.push(this.keys[thisIndex]);
              this.keys.splice(thisIndex, 1);
              rightSibling.keys.forEach((key) => {
                selectedChild.keys.push(key);
              });
              this.childs.splice(thisIndex + 1, 1);
              rightSibling.childs.forEach((child) => {
                child.parent = selectedChild;
                selectedChild.childs.push(child);
              });
            } else if (leftSibling) {
              selectedChild.keys.unshift(this.keys[thisIndex - 1]);
              this.keys.splice(thisIndex - 1, 1);
              for (let i = leftSibling.keys.length - 1; i > -1; i--) {
                selectedChild.keys.unshift(leftSibling.keys[i]);
              }
  
              this.childs.splice(thisIndex - 1, 1);
              for (let i = leftSibling.childs.length - 1; i > -1; i--) {
                leftSibling.childs[i].parent = selectedChild;
                selectedChild.childs.unshift(leftSibling.childs[i]);
              }
            }
            else {
              throw 'something went wrong'
            }
  
            if (this.keys.length === 0) {
              this.keys = selectedChild.keys;
              this.childs = selectedChild.childs;
              selectedChild.parent = null;
            }
          }
          setTimeout(() => selectedChild.delete(value), delay);
        } else {
          setTimeout(() => selectedChild.delete(value), delay);
        }
  
        if (!this.verify()) {
          return;
        }
      }
    }
  
    draw(x, y, size = 10, hsplit = 10, vsplit = 30) {
      this.keys.map((value, index) => {
        const valX = x + index * size;
        stroke(255);
        strokeWeight(1);
        if (this === currentNode) {
          strokeWeight(2)
        }
		stroke(255);
		strokeWeight(3);
		noFill();
        square(valX, y, size);
        strokeWeight(1)

        fill(255);
		textAlign(CENTER);
		textStyle(BOLD);
        text(value, valX + size / 2, y + size / 2);
      });
  
      let currentX = x + size * this.keys.length + hsplit;
      this.childs.map((child, index) => {
        stroke(255);
        line(x + size * index, y + size, currentX, y + size + vsplit);
        currentX = child.draw(currentX, y + size + vsplit, size, hsplit, vsplit);
      });
  
      return currentX;
    }
  }
  