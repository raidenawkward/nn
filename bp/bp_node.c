#include "bp_node.h"
#include <stdlib.h>

struct BPNode* bp_node_create() {
	struct BPNode *node = (struct BPNode*)malloc(sizeof(struct BPNode));
	if (!node)
		return node;

	node->input_weights = NULL;
	node->input_count = 0;
	node->threshold = 0;
	node->output = 0;
	node->next = NULL;

	return node;
}

struct BPNode* bp_node_init(float *inputWeight, int inputCount, float threshold, float output) {

	struct BPNode *node = (struct BPNode*)malloc(sizeof(struct BPNode));
	if (!node)
		return node;

	node->input_weights = (float*)malloc(sizeof(float) * inputCount);
	int i;
	for (i = 0; i < inputCount; ++i) {
		node->input_weights[i] = inputWeight[i];
	}

	node->input_count = inputCount;
	node->threshold = threshold;
	node->output = output;
	node->next = NULL;

	return node;

}

void bp_node_destory(struct BPNode* node) {
	if (!node)
		return;

	if (node->input_weights)
		free(node->input_weights);

	free(node);
	node = NULL;
}

