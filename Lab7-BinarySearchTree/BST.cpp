#include "BST.h"

BST::BST() {
    rootNode = nullptr;
}

BST::~BST() {
    clear();
}

Node* to_node(NodeInterface* interface) {
    if (interface == nullptr) {
        return nullptr;
    }
    
    return static_cast<Node*>(interface);
}

NodeInterface* BST::parentOf(NodeInterface *node) {
    if (node == nullptr) { return nullptr; }
    return parentOf(node->getData());
}

/**
 * Attempts to find the nearest ancestor to a node.
 *
 * @return A pointer to the parent node if one is found.
 * @return \c nullptr if otherwise.
 */
NodeInterface* BST::parentOf(int data) {
    if (rootNode == nullptr) { return nullptr; }
    
    NodeInterface* currentNode = rootNode;
    
    while (currentNode != nullptr) {
        // If left child is correct,
        if ((currentNode->getLeftChild() != nullptr &&
            data == currentNode->getLeftChild()->getData()) ||
            // Or if right child is correct,
            (currentNode->getRightChild() != nullptr &&
             data == currentNode->getRightChild()->getData())) {
            // Return this node as parent.
            return currentNode;
            
        } else if (data < currentNode->getData()) {
            currentNode = currentNode->getLeftChild();
            
        } else if (data > currentNode->getData()) {
            currentNode = currentNode->getRightChild();
            
        } else if (data == currentNode->getData()) {
            return nullptr;
        }
    }
    
    return nullptr;
}

/**
 * Attempts to find a node with the given int in the BST tree.
 *
 * @return A pointer to the member node if it is found.
 * @return \c nullptr if otherwise.
 */
NodeInterface* BST::memberInTree(int data) {
    NodeInterface* before = parentOf(data);
    
    if (before == nullptr) { return nullptr; }
    
    NodeInterface* leftChild = before->getLeftChild();
    if (leftChild != nullptr && data == leftChild->getData()) {
        return leftChild;
    }
    
    NodeInterface* rightChild = before->getRightChild();
    if (rightChild != nullptr && data == rightChild->getData()) {
        return rightChild;
    }
    
    return nullptr;
}

/**
 * Returns \c true if \c data is found in the tree.
 */
bool BST::isMember(int data) {
    return memberInTree(data) != nullptr;
}

/**
 * Returns the root node for this tree
 *
 * @return The root node for this tree.
 */
NodeInterface* BST::getRootNode() const {
    return rootNode;
}

/**
 * Attempts to add the given int to the BST tree
 *
 * @return true if added
 * @return false if unsuccessful (i.e. the int is already in tree)
 */
bool BST::add(int data) {
    Node* insertion = rootNode;
    
    if (insertion == nullptr) {
        rootNode = new Node(data);
        return true;
    }
    
    while (insertion != nullptr) {
        // If we found the item, return false.
        if (data == insertion->getData()) { return false; }
        
        // If data < root, traverse left.
        if (data < insertion->getData() && insertion->getLeftChild() != nullptr) {
            insertion = to_node(insertion->getLeftChild());
            
        } else if (data < insertion->getData()) {
            // If there's no left to go, insert here!
            insertion->setLeftChild(new Node(data));
            return true;
            
        // If data > root, traverse right.
        } else if (data > insertion->getData() && insertion->getRightChild() != nullptr) {
            insertion = to_node(insertion->getRightChild());
            
        } else if (data > insertion->getData()) {
            // If there's no right to go, insert here!
            insertion->setRightChild(new Node(data));
            return true;
        }
    }
    
    return false;
}

/**
 * Attempts to remove the given int from the BST tree
 *
 * @return true if successfully removed
 * @return false if remove is unsuccessful (i.e. the int is not in the tree)
 */
bool BST::remove(int data) {
    if (rootNode == nullptr) { return false; } // Return if empty
    Node* parentNode = to_node(parentOf(data));
    Node* nodeToRemove = nullptr;
    bool isLeft = false;
    
    if (data == rootNode->getData()) {
        nodeToRemove = rootNode;
        
    } else if (parentNode == nullptr) {
        // If we're not root, and there was no parent (should only apply to root) then fail. Not found.
        return false;
        
    } else if (parentNode->getLeftChild() != nullptr &&
               data == parentNode->getLeftChild()->getData()) {
        nodeToRemove = to_node(parentNode->getLeftChild());
        isLeft = true;
        
    } else if (parentNode->getRightChild() != nullptr &&
               data == parentNode->getRightChild()->getData()) {
        nodeToRemove = to_node(parentNode->getRightChild());
    }
    
    // If it's a leaf node, just kill it.
    if (nodeToRemove->isLeaf()) {
        
        // Remove the bad reference
        if (nodeToRemove == rootNode) {
            rootNode = nullptr;
        } else if (isLeft) {
            parentNode->setLeftChild(nullptr);
        } else {
            parentNode->setRightChild(nullptr);
        }
        
    }
    // If it has one child, replace it with its child.
    else if (nodeToRemove->getLeftChild() != nullptr &&
             nodeToRemove->getRightChild() == nullptr) {
        
        // Replace with left child
        Node* leftChild = to_node(nodeToRemove->getLeftChild());
        
        if (nodeToRemove == rootNode) {
            rootNode = leftChild;
        } else if (isLeft) {
            parentNode->setLeftChild(leftChild);
        } else {
            parentNode->setRightChild(leftChild);
        }
        
    } else if (nodeToRemove->getLeftChild() == nullptr &&
               nodeToRemove->getRightChild() != nullptr) {
        
        // Replace with right child
        Node* rightChild = to_node(nodeToRemove->getRightChild());
        
        if (nodeToRemove == rootNode) {
            rootNode = rightChild;
        } else if (isLeft) {
            parentNode->setLeftChild(rightChild);
        } else {
            parentNode->setRightChild(rightChild);
        }
        
    } else {
        // Replace with largest node in its left child's right subtree.
        Node* leftChild = to_node(nodeToRemove->getLeftChild());
        Node* largest = leftChild->largestSubnode();
        Node* parentOfLargest = to_node(parentOf(largest));
        
        if (parentOfLargest != nullptr) {
            if (largest == parentOfLargest->getLeftChild()) {
                parentOfLargest->setLeftChild(largest->getLeftChild());
            } else {
                parentOfLargest->setRightChild(largest->getLeftChild());
            }
        }
        largest->setLeftChild(nodeToRemove->getLeftChild());
        largest->setRightChild(nodeToRemove->getRightChild());
        
        if (nodeToRemove == rootNode) {
            rootNode = largest;
        } else if (isLeft) {
            parentNode->setLeftChild(largest);
        } else {
            parentNode->setRightChild(largest);
        }
    }
    
    delete nodeToRemove;
    return true;
}

/**
 * Removes all nodes from the tree, resulting in an empty tree.
 */
void BST::clear() {
    if (rootNode == nullptr) { return; }
    
    stack<NodeInterface*> foundMembers;
    // Add the root node to [List]
    foundMembers.push(rootNode);
    
    // While [List] is not empty
    while (!foundMembers.empty()) {
        
        // N = next node out of [List]
        NodeInterface* current = foundMembers.top();
        foundMembers.pop();
        
        // Add N’s children to [List]
        if (current->getLeftChild() != nullptr) {
            foundMembers.push(current->getLeftChild());
        }
        if (current->getRightChild() != nullptr) {
            foundMembers.push(current->getRightChild());
        }
        
        // Evaluate N
        delete current;
    }
    
    rootNode = nullptr;
}
