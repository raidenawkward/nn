#ifndef _BP_RECORD_H
#define _BP_RECORD_H

#include "bp_net.h"
#include <sys/types.h>

#define BP_RECORD_DIR_AUTHORITY (S_IRWXU | S_IRWXG)
#define BP_RECORD_NET "record.net"
#define BP_RECORD_LAYER "record.layer"
#define BP_RECORD_NODE "record.node"

/// save net struct to dir 'path'
// returns count of saved nodes, -1 if failed
int bp_record_save(struct BPNet* net, const char* path);

/// load net struct from dir 'path'
// returns count of loaded nodes, -1 if failed
int bp_record_load(const char* path, struct BPNet** net);

#endif // _BP_RECORD_H
