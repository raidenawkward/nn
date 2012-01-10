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
/// layer destory, after doing that layer == NULL
void bp_layer_destory(struct BPLayer* layer);
/// append node to layer, returns succeed? 1 : 0
int bp_layer_append(struct BPLayer*layer, struct BPNode* node);

#endif //_BP_LAYER_H
