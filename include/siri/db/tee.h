/*
 * tee.h - To tee the data for a SiriDB database.
 */
#ifndef SIRIDB_TEE_H_
#define SIRIDB_TEE_H_

typedef struct siridb_tee_s siridb_tee_t;

enum
{
    SIRIDB_TEE_FLAG_INIT = 1<<0,
    SIRIDB_TEE_FLAG_CONNECTED = 1<<1,
    SIRIDB_TEE_FLAG = 1<<31,
};

#include <uv.h>
#include <stdbool.h>
#include <siri/net/promise.h>

siridb_tee_t * siridb_tee_new(void);
void siridb_tee_free(siridb_tee_t * tee);
int siridb_tee_connect(siridb_tee_t * tee);
int siridb_tee_set_pipe_name(siridb_tee_t * tee, const char * pipe_name);
void siridb_tee_write(siridb_tee_t * tee, sirinet_promise_t * promise);
const char * tee_str(siridb_tee_t * tee);
static inline _Bool siridb_tee_is_configured(siridb_tee_t * tee);
static inline _Bool siridb_tee_is_connected(siridb_tee_t * tee);

struct siridb_tee_s
{
    uint32_t flags;  /* maps to sirnet_stream_t tp for cleanup */
    char * pipe_name_;
    char * err_msg_;
    uv_pipe_t pipe;
};

static inline _Bool siridb_tee_is_configured(siridb_tee_t * tee)
{
    return tee->pipe_name_ != NULL;
};

static inline _Bool siridb_tee_is_connected(siridb_tee_t * tee)
{
    return tee->flags & SIRIDB_TEE_FLAG_CONNECTED;
}

#endif /* SIRIDB_TEE_H_ */
