#include "mylibrary.h"

// функция создания узла списка
struct Node* createNode(uintptr_t data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (!newNode) { printf("Error: memory\n"); exit(1); }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;}

// функция добавления в конец списка
void append(struct Node** head, uintptr_t data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) { *head = newNode; return; }
    struct Node* temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;}

// функция проверки упорядоченности    
int sorted(struct Node* head) {
    while (head && head->next) {
        if ((int)head->data >= (int)head->next->data) return 0;
        head = head->next;}
    return 1;}

// функция получения k-го элемента
int get(struct Node* h, int k) {
    for (int i = 1; i < k; i++) {
        if (h == NULL) return -1;
        h = h->next;}
    return (h != NULL) ? (int)h->data : -1;}

// функция вставки на позицию k    
void insert(struct Node** h, int k, uintptr_t val) {
    struct Node* n = createNode(val);
    if (k == 1) { n->next = *h; *h = n; return; }
    struct Node* cur = *h;
    for (int i = 1; i < k - 1; i++) { if (cur == NULL) return; cur = cur->next; }
    n->next = cur->next;
    cur->next = n;}

// функция удаления с позиции k    
void deleteNode(struct Node** h, int k) {
    if (*h == NULL || k < 1) return;
    struct Node* tmp;
    if (k == 1) { tmp = *h; *h = (*h)->next; free(tmp); return; }
    struct Node* cur = *h;
    for (int i = 1; i < k - 1; i++) { if (cur == NULL) return; cur = cur->next; }
    if (cur->next == NULL) return;
    tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);}

// функция ввода списка с клавиатуры
struct Node* inputList(void) {
    struct Node* head = NULL, *tail = NULL;
    int x;
    printf("Vvedite chisla (bukva - stop): ");
    while (scanf("%d", &x) == 1) {
        struct Node* n = createNode((uintptr_t)x);
        if (!head) head = tail = n;
        else { tail->next = n; tail = n; }}
    while (getchar() != '\n');
    return head;}

// функция вывода списка
void print(struct Node* h) {
    while (h) { printf("%d ", (int)h->data); h = h->next; }
    printf("\n");}


// функция создания узла дерева
struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
    if (!newNode) { printf("Error: memory\n"); exit(1); }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;}

// рекурсивная вставка в бин дерево поиска
struct TreeNode* appendTree(struct TreeNode* cursor, int data) {
    if (cursor == NULL) return createTreeNode(data);
    if (data < cursor->data) cursor->left = appendTree(cursor->left, data);
    else if (data > cursor->data) cursor->right = appendTree(cursor->right, data);
    return cursor;}

void LNR(struct TreeNode* cursor) {
    if (cursor) { LNR(cursor->left); printf("%d ", cursor->data); LNR(cursor->right); }}
void RNL(struct TreeNode* cursor) {
    if (cursor) { RNL(cursor->right); printf("%d ", cursor->data); RNL(cursor->left); }}
void NLR(struct TreeNode* cursor) {
    if (cursor) { printf("%d ", cursor->data); NLR(cursor->left); NLR(cursor->right); }}

// обход в ширину    
void breadthFirstSearchByFlowchart(struct TreeNode* root) {
    if (!root) { printf("Pustoe derevo.\n"); return; }
    int cap = 10;
    struct TreeNode** q = malloc(cap * sizeof(struct TreeNode*));
    if (!q) exit(1);
    int top = 0, i = 0;
    q[i++] = root;
    while (top < i) {
        struct TreeNode* cur = q[top++];
        printf("%d ", cur->data);
        if (cur->left) {
            if (i >= cap) { cap *= 2; q = realloc(q, cap * sizeof(struct TreeNode*)); }
            q[i++] = cur->left;}
        if (cur->right) {
            if (i >= cap) { cap *= 2; q = realloc(q, cap * sizeof(struct TreeNode*)); }
            q[i++] = cur->right;}}
    free(q); printf("\n");}