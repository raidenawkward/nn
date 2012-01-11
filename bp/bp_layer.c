#include "bp_layer.h"
#include <stdlib.h>
#include <time.h>

struct BPLayer* bp_layer_create() {
	struct BPLayer* layer = (struct BPLayer*)malloc(sizeof(struct BPLayer));
	if (!layer)
		return layer;
	layer->first = NULL;
	layer->node_count = 0;
	return layer;
}

struct BPLayer* bp_layer_init(struct BPNode* nodes, int count) {
	struct BPLayer* layer = (struct BPLayer*)malloc(sizeof(struct BPLayer));
	if (!layer)
		return layer;
	layer->first = nodes;
	layer->node_count = count;
	return layer;
}

struct BPNode* bp_layer_indexed_node(struct BPLayer* layer, int index) {
	if (!layer)
		return NULL;
	if (index >= layer->node_count)
		return NULL;
	struct BPNode* node = layer->first;
	int current = 0;
	while(node) {
		if (current == index)
			return node;
		node = node->next;	
		++ current;
	}
	return NULL;
}

static void bp_layer_destory_nodes(struct BPNode* node) {
	if (!node)
		return;
	if (node->next)
		bp_layer_destory_nodes(node->next);
	bp_node_destory(node);
}

void bp_layer_destory(struct BPLayer* layer) {
	if (!layer)
		return;

	bp_layer_destory_nodes(layer->first);
}

int bp_layer_append(struct BPLayer* layer, struct BPNode* node) {
	if (!layer || !node)
		return 0;

	if (layer->node_count < 0)
		return 0;

	if (layer->node_count == 0) {
		layer->first = node;
		node->next = NULL;
	} else {
		struct BPNode* last = layer->first;
		while (last->next) {
			last = last->next;
		}
		last->next = node;
		node->next = NULL;
	}
	++ layer->node_count;

	return 1;
}

int bp_layer_connect(struct BPLayer* level0, struct BPLayer* level1) {
	if (!level1)
		return 0;

	if (!level0) {
		struct BPNode *node = level1->first;
		while (node) {
			node->input_weights = (float*)malloc(sizeof(float));
			if (!node->input_weights)
				goto err;
			node->input_weights[0] = BP_NODE_WEIGHT_INPUT;
			node->input_count = 1;
			node = node->next;
		}
		return 1;
	}

	struct BPNode* node = level1->first;
	while (node) {
		node->input_weights = (float*)malloc(sizeof(float) * level0->node_count);
		if (!node->input_weights)
			goto err;
		int i;
		for (i = 0; i < level0->node_count; ++i)
			node->input_weights[i] = BP_NODE_WEIGHT_INIT;
		node->input_count = level0->node_count;

		node = node->next;
	}

	return 1;
err:
	return 0;
}

static float* bp_layer_make_random_array(int length, int accuracy) {
	float *array = (float*)malloc(sizeof(float) * length);
	if (!array)
		return array;

	int i;
	srand(time(NULL));
	for (i = 0; i < length; ++i) {
		array[i] = ((float)(rand() % accuracy)) / accuracy;
	}

	return array;
}

void bp_layer_weights_randomize(struct BPLayer* layer, int accuracy) {
	if (!layer)
		return;

	struct BPNode *node = layer->first;
	while (node) {
		if (node->input_count) {
			float *rand_array = bp_layer_make_random_array(node->input_count,accuracy);
			if (!rand_array)
				return;
			int i;
			for (i = 0; i < node->input_count; ++i)
				node->input_weights[i] = rand_array[i];
			free(rand_array);
		}
		node = node->next;
	}
}
