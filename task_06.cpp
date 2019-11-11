/*
 * Задача 6. Порядок обхода (3 балла)
 *
 * Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root->Key ≤ K,
 * то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 * Рекурсия запрещена.
 *
 * 6_1. Выведите элементы в порядке pre-order (сверху вниз).
 */


#include <iostream>
#include <stack>
#include <vector>


struct TreeNode {
    int key;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int value) : key(value) {}
};

class Tree {
public:
    void Add(int value);
    std::vector<int> GetTreeTraversal() const;
    ~Tree();

private:
    TreeNode* root = nullptr;
    std::vector<int> traverse_subtree(TreeNode* node) const;
    static void delete_subtree(TreeNode* node);
};

void Tree::Add(int value) {
    if (!root) {
        root = new TreeNode(value);
        return;
    }

    TreeNode* parent = root;
    while (true) {
        if (value < parent->key) { // left subtree
            if (parent->left) {
                parent = parent->left;
            } else {
                parent->left = new TreeNode(value);
                return;
            }
        } else { // right subtree
            if (parent->right) {
                parent = parent->right;
            } else {
                parent->right = new TreeNode(value);
                return;
            }
        }
    }
}

Tree::~Tree() {
    delete_subtree(root);
}

void Tree::delete_subtree(TreeNode* node) {
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

std::vector<int> Tree::GetTreeTraversal() const {
    return traverse_subtree(root);
}

std::vector<int> Tree::traverse_subtree(TreeNode* node) const {
    std::vector<int> pre_order_traversal;
    if (!node) return pre_order_traversal;

    std::stack<TreeNode*> traversal_stack;
    traversal_stack.push(node);

    while (!traversal_stack.empty()) {
        TreeNode* next_node = traversal_stack.top();
        traversal_stack.pop();

        pre_order_traversal.push_back(next_node->key);
        if (next_node->right) traversal_stack.push(next_node->right);
        if (next_node->left) traversal_stack.push(next_node->left);
    }

    return pre_order_traversal;
}

int main() {
    int n;
    std::cin >> n;

    Tree tree;
    int input_number;

    for (int i = 0; i < n; i++) {
        std::cin >> input_number;
        tree.Add(input_number);
    }

    for (const auto& tree_key : tree.GetTreeTraversal()) {
        std::cout << tree_key << " ";
    }

    return 0;
}
