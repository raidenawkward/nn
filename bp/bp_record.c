#include "bp_record.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>


static int bp_record_generate_dir(const char* path) {
	if (!path)
		return 0;

	DIR* dir = opendir(path);
	if (!dir) {
		if (mkdir(path,BP_RECORD_DIR_AUTHORITY) < 0)
			return 0;
	}

	closedir(dir);

	return 1;
}

static int bp_record_generate_files_path(const char* dir, char** net, char** layer, char** node) {
	if (!dir)
		return 0;
	*net = (char*)malloc(sizeof(char) * (strlen(dir) + strlen(BP_RECORD_NET) + 2));
	*layer = (char*)malloc(sizeof(char) * (strlen(dir) + strlen(BP_RECORD_LAYER) + 2));
	*node = (char*)malloc(sizeof(char) * (strlen(dir) + strlen(BP_RECORD_NODE) + 2));

	if (!*net || !*layer || !*node)
		return 0;

	sprintf(*net,"%s/%s\0",dir,BP_RECORD_NET);
	sprintf(*layer,"%s/%s\0",dir,BP_RECORD_LAYER);
	sprintf(*node,"%s/%s\0",dir,BP_RECORD_NODE);

	return 1;
}

static int bp_record_write_to_file(FILE* fp_net, FILE* fp_layer, FILE* fp_node, struct BPNet* net) {
	if (!fp_net || !fp_layer || !fp_node || !net)
		return -1;
	if (!fwrite(net,sizeof(struct BPNet),1,fp_net))
		return -1;

	int ret = 0;
	int i;
	for (i = 0; i < net->layer_count; ++i) {
		if (!fwrite(&(net->layers[i]),sizeof(struct BPLayer),1,fp_layer))
			return -1;

		struct BPNode *node = net->layers[i].first;
		while(node) {
			if (!fwrite(node,sizeof(struct BPNode),1,fp_node))
				return -1;
			node = node->next;
			++ret;
		}
	}

	return ret;
}

int bp_record_save(struct BPNet* net, const char* path) {
	if (!net || !path)
		return -1;
	if (!bp_record_generate_dir(path))
		return -1;

	char *file_net, *file_layer, *file_node;
	if (!bp_record_generate_files_path(path,&file_net,&file_layer,&file_node))
		return -1;

	FILE *fp_net, *fp_layer, *fp_node;
	fp_net = fopen(file_net,"w");
	fp_layer = fopen(file_layer,"w");
	fp_node = fopen(file_node,"w");

	if (!fp_net || !fp_layer || !fp_node)
		goto err;

	int ret = bp_record_write_to_file(fp_net,fp_layer,fp_node,net);

	free(file_net);
	free(file_layer);
	free(file_node);
	fclose(fp_net);
	fclose(fp_layer);
	fclose(fp_node);

	return ret;
err:
	free(file_net);
	free(file_layer);
	free(file_node);
	return -1;
}

static int bp_record_read_from_file(FILE* fp_net, FILE* fp_layer, FILE* fp_node, struct BPNet** net) {
	if (!fp_net || !fp_layer || !fp_node || !net)
		return -1;

	*net = (struct BPNet*)malloc(sizeof(struct BPNet));
	if (!*net)
		return -1;

	if (!fread(*net,sizeof(struct BPNet),1,fp_net))
		return -1;

	int ret = 0;
	int i;
	for (i = 0; i < (*net)->layer_count; ++i) {
		struct BPLayer* layer = (struct BPLayer*)malloc(sizeof(struct BPLayer));
		if (!layer)
			return -1;
		if (!fread(layer,sizeof(struct BPLayer),1,fp_layer))
			return -1;

		int j;
		int layer_node_count = layer->node_count;
		layer->node_count = 0;
		for (j = 0; j < layer_node_count; ++j) {
			struct BPNode *node = (struct BPNode*)malloc(sizeof(struct BPNode));
			if (!node)
				return -1;
			if (!fread(node,sizeof(struct BPNode),1,fp_node))
				return -1;
			if (!bp_layer_append(layer,node))
				return -1;
			++ret;
		}

		(*net)->layers[i] = *layer;	
		free(layer);
	}

	return ret;
}

int bp_record_load(const char* path, struct BPNet** net) {
	if (!net || !path)
		return -1;

	char *file_net, *file_layer, *file_node;
	if (!bp_record_generate_files_path(path,&file_net,&file_layer,&file_node))
		return -1;

	FILE *fp_net, *fp_layer, *fp_node;
	fp_net = fopen(file_net,"r");
	fp_layer = fopen(file_layer,"r");
	fp_node = fopen(file_node,"r");

	if (!fp_net || !fp_layer || !fp_node)
		goto err;

	int ret = bp_record_read_from_file(fp_net,fp_layer,fp_node,net);
	free(file_net);
	free(file_layer);
	free(file_node);
	fclose(fp_net);
	fclose(fp_layer);
	fclose(fp_node);

	return ret;

err:
	free(file_net);
	free(file_layer);
	free(file_node);
	return -1;
}

