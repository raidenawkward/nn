#ifndef _BP_NODE_H
#define _BP_NODE_H

struct BPNode {
	float* input_weights;
	int	intput_length;
	float threshold;
	float output;
};


struct BPNode* bp_node_create();
void bp_node_destory(struct BPNode* node);

#endif //_BP_NODE_H
