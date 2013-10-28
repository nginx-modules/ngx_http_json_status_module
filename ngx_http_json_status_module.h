/* -*- mode:c; coding:utf-8 -*- */

#ifndef NGX_STAT_STUB
#define NGX_STAT_STUB
#endif

#ifndef _NGX_HTTP_JSON_STATUS_MODULE_H_INCLUDED_
#define _NGX_HTTP_JSON_STATUS_MODULE_H_INCLUDED_

#define NGX_HTTP_JSON_STATUS_MODULE_VERSION "0.1"
#define SERVER_ADDRS_ZERO 0

#define ARG_PARAMETER_CALLBACK "arg_callback"
//#define CALLBACK_MAX_LEN 1024

typedef unsigned char BYTE;
typedef struct ngx_http_json_status_main_conf_s ngx_http_json_status_main_conf_t;

struct  ngx_http_json_status_main_conf_s {
  char    hostname[NGX_MAXHOSTNAMELEN];
  u_char  addr[16]; /* xxx.xxx.xxx.xxx\0 */
  size_t  contents_size;
};

static char *ngx_http_json_status(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_json_status_handler(ngx_http_request_t *r);

static void *ngx_http_json_status_create_main_conf(ngx_conf_t *cf);
static char *ngx_http_json_status_init_main_conf(ngx_conf_t *cf, void *conf);

static int ngx_strtcmp(ngx_str_t *s1, ngx_str_t *s2);
static ngx_str_t *ngx_http_get_arg_string(ngx_http_request_t *r, u_char *name);

#endif
