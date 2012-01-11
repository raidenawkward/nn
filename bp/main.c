#include "stdio.h"
#include "bp_node.h"
#include "bp_layer.h"
#include "bp_net.h"

static void print_net_info(struct BPNet* net) {
	if (!net) {
		printf("empty ptr!\n");
		return;
	}

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
}

int main() {
	struct BPNet* net = bp_net_init(3,4);
	printf("net inited , count of layer : %d\n",net->layer_count);

	print_net_info(net);

	bp_record_save(net,"./record");
	sync();
	bp_net_destory(&net);

	if (bp_record_load("./record",&net) < 0) {
		printf("failded when loading\n");
		return 0;
	}

	printf("net reinited , count of layer : %d\n",net->layer_count);
	printf("after loaded\n");
	print_net_info(net);

	bp_net_destory(&net);
	return 0;
}
