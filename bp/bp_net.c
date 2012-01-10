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

void bp_net_destory(struct BPNet** net) {
	if (!*net || !net)
		return;
	int i;
	for (i = 0; i < (*net)->layer_count; ++i) {
		bp_layer_destory(&(*net)->layers[i]);
	}
	free(*net);
	*net = NULL;
}

