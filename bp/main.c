#include "stdio.h"
#include "bp_node.h"
#include "bp_layer.h"
#include "bp_net.h"

int main() {
	struct BPNet* net = bp_net_init(3,4);
	printf("net inited , count of layer : %d\n",net->layer_count);

	int i;
	for (i = 0; i < net->layer_count; ++i) {
		printf("level %d\t",i);
		struct BPNode *node = net->layers[i].first;
		int j = 0;
		while(node) {
			printf("node %d (",j);
			int k;
			for (k = 0; k < node->input_count; ++k) {
				printf("%f",node->input_weights[k]);
				if (k != node->input_count - 1)
					printf(",");
			}
			printf(")\t");
			node = node->next;
			++j;
		}
		printf("\n");
	}

	bp_net_destory(&net);
	return 0;
}
