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
/// net destory, after doing that net == NULL
void bp_net_destory(struct BPNet** net);

#endif // _BP_NET_H
