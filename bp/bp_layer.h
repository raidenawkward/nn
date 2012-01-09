#ifndef _BP_LAYER_H
#define _BP_LAYER_H

#include "bp_node.h"

struct BPLayer {
	struct BPNode* first;
	int node_count;
};

/// empty layer created, returns NULL if failed
struct BPLayer* bp_layer_create();

/// init layer with given nodes, returns NULL if failed
struct BPLayer* bp_layer_init(struct BPNode* nodes, int count);

/// get indexed node from layer, returns NULL if failed
struct BPNode* bp_layer_indexed_node(struct BPLayer* layer, int index);

/// layer destory
void bp_layer_destory(struct BPLayer* layer);

/// append node to layer, returns succeed? 1 : 0
int bp_layer_append(struct BPLayer* layer, struct BPNode* node);

/// make 2 layers connected, which weights have not been tetermined
//	to init weights of input layout, level0 = NULL
int bp_layer_connect(struct BPLayer* level0, struct BPLayer* level1);

/// makes weights of each node in layer random
void bp_layer_weights_randomize(struct BPLayer* layer, int accuracy);

#endif //_BP_LAYER_H
