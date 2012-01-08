#ifndef _BP_NODE_H
#define _BP_NODE_H

struct BPNode {
	float* input_weights;
	int	input_count;
	float threshold;
	float output;
	// may need function entry for getting real output
	//
	struct BPNode *next;
};

/// empty node created, returns NULL if failed
struct BPNode* bp_node_create();
/// node with inited values will be created, returns NULL if failed
struct BPNode* bp_node_init(float *inputWeight, int inputCount, float threshold, float output);
/// node destory, after doing that node == NULL
void bp_node_destory(struct BPNode* node);
#endif //_BP_NODE_H
