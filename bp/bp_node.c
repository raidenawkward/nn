#include "bp_node.h"
#include <stdlib.h>
#include <string.h>

struct BPNode* bp_node_create() {
	struct BPNode *node = (struct BPNode*)malloc(sizeof(struct BPNode));
	if (!node)
		return node;

	memset(node->input_weights,0x00,BP_NODE_WEIGHT_MAX);
	node->input_count = 0;
	node->threshold = 0;
	node->output = 0;
	node->get_output = NULL;
	node->next = NULL;

	return node;
}

struct BPNode* bp_node_init(float *inputWeight, int inputCount, float threshold, float output) {
	if (inputCount >= BP_NODE_WEIGHT_MAX)
		return NULL;

	struct BPNode *node = (struct BPNode*)malloc(sizeof(struct BPNode));
	if (!node)
		return node;

	memset(node->input_weights,0x00,BP_NODE_WEIGHT_MAX);
	int i;
	for (i = 0; i < inputCount; ++i) {
		node->input_weights[i] = inputWeight[i];
	}

	node->input_count = inputCount;
	node->threshold = threshold;
	node->output = output;
	node->get_output = NULL;
	node->next = NULL;

	return node;

}

void bp_node_destory(struct BPNode* node) {
	if (!node)
		return;

	free(node);
}

