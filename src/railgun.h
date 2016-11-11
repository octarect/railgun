#ifndef _RAILGUN_H_
#define _RAILGUN_H_

#include <stdarg.h>
#include <cuda_runtime.h>

#define SCHEDULE_INTERVAL 10000 // micro second

/* ----- type::args ----- */
typedef enum {
  RG_TYPE_INT_P,
  RG_TYPE_DOUBLE_P,
} railgun_data_type;

typedef enum {
  RG_DIR_DOWNLOAD,
  RG_DIR_READBACK,
} railgun_data_dir;

typedef struct {
  railgun_data_type type;
  railgun_data_dir dir;
  union {
    int *ip;
    float *fp;
    double *dp;
  } d;
  int n;
} railgun_data;

typedef struct {
  const char *fmt;
  int argc;
  railgun_data *argv;
} railgun_args;

typedef struct {
  railgun_args *args;
  void *f;
  dim3 blocks;
  dim3 threads;
} railgun_task;

typedef union {
  int *ip;
  float *fp;
  double *dp;
} railgun_memory;

typedef struct {
  int (*init)(void);
  int (*get_count)(void);
  railgun_args* (*wrap_args)(const char*, ...);
  int (*schedule)(void*, railgun_args*, dim3, dim3);
  int (*execute)();
} railgun_t;

/* ----- protoypes ----- */
railgun_t* get_railgun(void);

railgun_args* _wrap_args(const char* fmt, ...);
int _schedule(void* f, railgun_args* args, dim3 blocks, dim3 threads);
int _execute();

void dump_args(railgun_args* args);

#endif
