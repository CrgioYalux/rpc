struct TNode {
	void *value;
	struct TNode *next;
	struct TNode *prev;
};

#define Node struct TNode

Node *new_node(void *value);
