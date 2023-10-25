#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node *newNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return (node);
}

struct Node *insert(struct Node *node, int data) {
    if (node == NULL) return (newNode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

struct Node *minValueNode(struct Node *node) {
    struct Node *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct Node *deleteNode(struct Node *root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void inorder(struct Node *node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d \n", node->data);
        inorder(node->right);
    }
}

void preorder(struct Node *node) {
    if (node != NULL) {
        printf("%d \n", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(struct Node *node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("%d \n", node->data);
    }
}

int search(struct Node *root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (root->data < data)
        return search(root->right, data);

    return search(root->left, data);
}

int main() {
    struct Node *root = NULL;
    int ch, data;

    root=new_node(root,20);
    root=insert(root,5);
    root=insert(root,1);
    root=insert(root,15);
    root=insert(root,9);
    root=insert(root,7);
    root=insert(root,12);
    root=insert(root,30);
    root=insert(root,25);
    root=insert(root,40);
    root=insert(root,45);
    root=insert(root,42);
    while (1) {
        printf("\n1.Insertion\n2.Deletion\n3.Search\n4.Traversals\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;

            case 2:
                printf("Enter the value to be deleted: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;

            case 3:
                printf("Enter the value to be searched: ");
                scanf("%d", &data);
                search(root, data) ? printf("Found\n") : printf("Not Found\n");
                break;

            case 4:
                printf("1.Inorder\n2.Preorder\n3.Postorder\n");
                printf("Enter your choice: ");
                scanf("%d", &ch);

                switch (ch) {
                    case 1:
                        inorder(root);
                        break;

                    case 2:
                        preorder(root);
                        break;

                    case 3:
                        postorder(root);
                        break;
                }
                break;

            case 5:
                exit(0);
        }
    }

    return 0;
}