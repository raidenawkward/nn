#include "bp_net.h"
#include <stdlib.h>

struct BPNet* bp_net_create() {
	struct BPNet *net = (struct BPNet*)malloc(sizeof(struct BPNet));
	if (!net)
		return net;

	net->layers = NULL;
	net->layer_count = 0;
	return net;
}

struct BPNet* bp_net_init(int layerCount, int nodesPerLayer) {
	struct BPNet* net = bp_net_create();
	if (!net)
		return net;

	net->layers = (struct BPLayer*)malloc(sizeof(struct BPLayer) * layerCount);
	if (!net->layers)
		goto err;
	net->layer_count = layerCount;

	int i;
	for (i = 0; i < layerCount; ++i) {
		struct BPLayer* layer = bp_layer_create();
		if (!layer)
			goto err;
		int j;
		for (j = 0; j < nodesPerLayer; ++j) {
			struct BPNode* node = bp_node_create();
			if (!node)
				goto err;
			if (!bp_layer_append(layer,node))
				goto err;
		}

		net->layers[i] = *layer;
		free(layer);
		if (!bp_layer_connect(i? &(net->layers[i - 1]) : NULL,&(net->layers[i])))
			goto err;
		bp_layer_weights_randomize(&(net->layers[i]),BP_NODE_WEIGHT_ACCURACY);
	}

	return net;

err:
	bp_net_destory(&net);
	return NULL;
}

int bp_net_append_layer(struct BPNet* net, struct BPLayer* layer) {
	if (!net || !layer)
		return 0;

	if (net->layer_count < 0)
		net->layer_count = 0;

	if (net->layer_count = 0) {
		net->layers = (struct BPLayer*)malloc(sizeof(struct BPLayer));
		if (!net->layers)
			return 0;
	} else {
		struct BPLayer* newLayers = (struct BPLayer*)realloc(net->layers,sizeof(struct BPLayer) * (net->layer_count + 1));
		if (!newLayers)
			return 0;
		net->layers = newLayers;
	}

	net->layers[++ net->layer_count - 1] = *layer;
	if (!bp_layer_connect(net->layer_count? &(net->layers[net->layer_count - 2]) : NULL,
		&(net->layers[net->layer_count - 1])))
		return 0;

	return 1;
}

void bp_net_destory(struct BPNet** net) {
	if (!*net || !net)
		return;

	int i;
	for (i = 0; i < (*net)->layer_count; ++i) {
		bp_layer_destory(&((*net)->layers[i]));
	}
	free((*net)->layers);
	free(*net);
	*net = NULL;
}

