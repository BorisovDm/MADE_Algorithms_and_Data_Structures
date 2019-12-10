/*
 * Задача 7. Использование самобалансирующихся деревьев (7 баллов)
 *
 * Солдаты.
 * В одной военной части решили построить в одну шеренгу по росту.
 * Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
 * а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
 * Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
 * а в конце – самые низкие. За расстановку солдат отвечал прапорщик,
 * который заметил интересную особенность – все солдаты в части разного роста.
 * Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
 * а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
 *
 * 7_2. Требуемая скорость выполнения команды - O(log n) амортизировано.
 *      Для решения задачи реализуйте сплей дерево.
 *
 * Формат входных данных.
 * Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000).
 * В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй
 * (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата,
 * стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
 *
 * Формат выходных данных.
 * На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции,
 * на которую должен встать этот солдат (все стоящие за ним двигаются назад).
 */


#include <cassert>
#include <iostream>
#include <stack>


struct TreeNode {
    int key;
    int n_left_childs = 0;
    int n_right_childs = 0;
    TreeNode* parent = nullptr;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int value) : key(value) {}
};

class SplayTree {
public:
    void Add(int value);
    int GetRootRightChildsNumber() const;
    void DeleteByOrderNumber(int k);
    ~SplayTree();

private:
    TreeNode* root = nullptr;
    TreeNode* SearchByOrderNumber(int k) const;
    TreeNode* FindMax() const;

    void Splay(const TreeNode* node);
    void RotateLeft(TreeNode* node);
    void RotateRight(TreeNode* node);
    void Transplant(TreeNode* parent, TreeNode* child);

    void DeleteRoot();
    static void DeleteSubtree(TreeNode* node);
};

int SplayTree::GetRootRightChildsNumber() const {
    return root->n_right_childs;
}

void SplayTree::Add(int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }

    TreeNode* parent = root;
    while (true) {
        if (value < parent->key) { // left subtree
            parent->n_left_childs++;
            if (parent->left == nullptr) {
                parent->left = new TreeNode(value);
                parent->left->parent = parent;
                Splay(parent->left);
                return;
            } else {
                parent = parent->left;
            }
        } else { // right subtree
            parent->n_right_childs++;
            if (parent->right == nullptr) {
                parent->right = new TreeNode(value);
                parent->right->parent = parent;
                Splay(parent->right);
                return;
            } else {
                parent = parent->right;
            }
        }
    }
}

void SplayTree::Transplant(TreeNode* localParent, TreeNode* localChild) {
    if (localParent == root) {
        root = localChild;
    } else if (localParent == localParent->parent->left) {
        localParent->parent->left = localChild;
    } else if (localParent == localParent->parent->right) {
        localParent->parent->right = localChild;
    }

    localChild->parent = localParent->parent;
    localParent->parent = localChild;
}

void SplayTree::RotateRight(TreeNode* topNode) {
    TreeNode* leftChild = topNode->left;

    // change number of childs
    topNode->n_left_childs = leftChild->n_right_childs;
    leftChild->n_right_childs += 1 + topNode->n_right_childs;

    // change parents
    if (leftChild->right) leftChild->right->parent = topNode;
    Transplant(topNode, leftChild);

    // change childs
    topNode->left = leftChild->right;
    leftChild->right = topNode;
}

void SplayTree::RotateLeft(TreeNode* topNode) {
    TreeNode* rightChild = topNode->right;

    // change number of childs
    topNode->n_right_childs = rightChild->n_left_childs;
    rightChild->n_left_childs += 1 + topNode->n_left_childs;

    // change parents
    if (rightChild->left) rightChild->left->parent = topNode;
    Transplant(topNode, rightChild);

    // change childs
    topNode->right = rightChild->left;
    rightChild->left = topNode;
}

void SplayTree::Splay(const TreeNode* pivotNode) {
    while (pivotNode != root) {
        if (pivotNode->parent == root) { // Zig
            pivotNode == root->left ? RotateRight(root) : RotateLeft(root);
            continue;
        }

        if (pivotNode == pivotNode->parent->left && pivotNode->parent == pivotNode->parent->parent->left) {
            // ZigZig - RotateRight, RotateRight
            RotateRight(pivotNode->parent->parent);
            RotateRight(pivotNode->parent);
            continue;
        }

        if (pivotNode == pivotNode->parent->right && pivotNode->parent == pivotNode->parent->parent->right) {
            // ZigZig - RotateLeft, RotateLeft
            RotateLeft(pivotNode->parent->parent);
            RotateLeft(pivotNode->parent);
            continue;
        }

        if (pivotNode == pivotNode->parent->right && pivotNode->parent == pivotNode->parent->parent->left) {
            // ZigZag - RotateLeft, RotateRight
            RotateLeft(pivotNode->parent);
            RotateRight(pivotNode->parent);
            continue;
        }

        if (pivotNode == pivotNode->parent->left && pivotNode->parent == pivotNode->parent->parent->right) {
            // ZigZag - RotateRight, RotateRight
            RotateRight(pivotNode->parent);
            RotateLeft(pivotNode->parent);
            continue;
        }

        assert(false);
    }
}

TreeNode* SplayTree::SearchByOrderNumber(int k) const {
    TreeNode* searchNode = root;
    while (true) {
        if (searchNode->n_right_childs == k) {
            return searchNode;
        }

        if (searchNode->n_right_childs > k) {
            searchNode = searchNode->right;
            continue;
        }

        if (searchNode->n_right_childs < k) {
            k -= 1 + searchNode->n_right_childs;
            searchNode = searchNode->left;
            continue;
        }

        assert(false);
    }
}

TreeNode* SplayTree::FindMax() const {
    TreeNode* searchNode = root;
    while (searchNode->right) {
        searchNode = searchNode->right;
    }
    return searchNode;
}

void SplayTree::DeleteRoot() {
    TreeNode* exRoot = root;

    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        return;
    }

    if (root->left == nullptr) {
        root = root->right;
    } else if (root->right == nullptr) {
        root = root->left;
    } else {
        TreeNode* rightSubtree = root->right;
        root = root->left;

        Splay(FindMax());

        root->right = rightSubtree;
        root->right->parent = root;
        root->n_right_childs = root->right->n_right_childs + root->right->n_left_childs + 1;
    }

    root->parent = nullptr;
    exRoot->left = nullptr;
    exRoot->right = nullptr;
    delete exRoot;
}

void SplayTree::DeleteByOrderNumber(int k) {
    assert(root != nullptr && root->n_left_childs + root->n_right_childs + 1 > k);
    Splay(SearchByOrderNumber(k));
    DeleteRoot();
}

SplayTree::~SplayTree() {
    DeleteSubtree(root);
}

void SplayTree::DeleteSubtree(TreeNode* node) {
    if (!node) return;

    std::stack<TreeNode*> delete_stack;
    delete_stack.push(node);

    while (!delete_stack.empty()) {
        TreeNode* delete_node = delete_stack.top();
        delete_stack.pop();

        if (delete_node->left) delete_stack.push(delete_node->left);
        if (delete_node->right) delete_stack.push(delete_node->right);
        delete delete_node;
    }
}

int main() {
    int n;
    std::cin >> n;

    SplayTree tree;

    for (int i = 0; i < n; i++) {
        int command, value;
        std::cin >> command >> value;
        assert(command == 1 || command == 2);

        if (command == 1) {
            tree.Add(value);
            std::cout << tree.GetRootRightChildsNumber() << std::endl;
        }

        if (command == 2) {
            tree.DeleteByOrderNumber(value);
        }
    }

    return 0;
}
