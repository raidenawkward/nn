#include "stdio.h"
#include "bp_node.h"
#include "bp_layer.h"
#include "bp_net.h"

int main() {
	struct BPNet* net = bp_net_init(10,10);
	printf("net inited , count of layer : %d\n",net->layer_count);
	bp_net_destory(&net);
	return 0;
}
