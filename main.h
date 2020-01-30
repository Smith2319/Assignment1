#define LINE 100
typedef struct Node {
    char* name;
    int minStr;
    int maxStr;
    int str;
    char* rarity;
    struct Node* prev;
    struct Node* next;
}item;

typedef struct Node2 {
    int bagn;
    item *items;
} bags;

