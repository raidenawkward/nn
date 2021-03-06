#ifndef _BP_NODE_H
#define _BP_NODE_H

#define BP_NODE_WEIGHT_MAX 10
#define BP_NODE_WEIGHT_INIT (0.5)
#define BP_NODE_WEIGHT_INPUT (1.0)
#define BP_NODE_WEIGHT_ACCURACY (1000)


struct BPNode {
	float input_weights[BP_NODE_WEIGHT_MAX];
	int	input_count;
	float threshold;
	float output;
	// may need function entry for getting real output
	float (*get_output) (struct BPNode);
	struct BPNode *next;
};

/// empty node created, returns NULL if failed
struct BPNode* bp_node_create();
/// node with inited values will be created, returns NULL if failed
struct BPNode* bp_node_init(float *inputWeight, int inputCount, float threshold, float output);
/// node destory
void bp_node_destory(struct BPNode* node);
#endif //_BP_NODE_H
