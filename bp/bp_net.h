#ifndef _BP_NET_H
#define _BP_NET_H

#include "bp_node.h"
#include "bp_layer.h"

struct BPNet {
	struct BPLayer *layers;
	int layer_count;
};

/// empty bp net created, returns NULL if failed
struct BPNet* bp_net_create();
/// init bp net with given layer and node num
struct BPNet* bp_net_init(int layerCount, int nodesPerLayer);
/// append layer to net
int bp_net_append_layer(struct BPNet* net, struct BPLayer* layer);
/// net destory, after doing that net == NULL
void bp_net_destory(struct BPNet** net);

#endif // _BP_NET_H
