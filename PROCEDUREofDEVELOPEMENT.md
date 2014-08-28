Module development
==============

Template creation
--------
```bash
sudo gem install ngxmodgen
mkdir ngx_http_json_status_module
cd ngx_http_json_status_module
ngxmodgen -n json_status
tree
.
├── config
└── ngx_http_json_status_module.c

0 directories, 2 files
```

Directive settings
--------------------
[Configuration directives](http://www.nginxguts.com/2011/09/configuration-directives/)
### status;
```c
static char *ngx_http_json_status(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
...
static ngx_command_t
ngx_http_json_status_commands[] = {
  {
    ngx_string("status"),
    NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
    ngx_http_json_status,
    0,
    0,
    NULL
  },
  ngx_null_command
};
```
### status on|off; In the case of
```c
static char *ngx_http_json_status(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
...
static ngx_command_t
ngx_http_json_status_commands[] = {
  {
    ngx_string("status"),
    NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
    ngx_http_json_status,
    0,
    0,
    NULL
  },
  ngx_null_command
};
```

Add the header file
--------------------
To add a line to the config if you wanted to create a header file. 
Add the following to the config so you add a ngx_http_json_status_module.h this time.
```
NGX_ADDON_DEPS="$NGX_ADDON_DEPS $ngx_addon_dir/ngx_http_json_status_module.h"
```

ngx_command_t
-------------
ngx_command_t structure that the definition of the directive has been as follows.
```c
typedef struct ngx_command_s     ngx_command_t;

struct ngx_command_s {
    ngx_str_t             name;
    ngx_uint_t            type;
    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
    ngx_uint_t            conf;
    ngx_uint_t            offset;
    void                 *post;
};
```
set element function to be called when the directives of the name element has been set.

set element of ngx_command_t: ngx_http_json_status
-------------------------------------------
status; There function to call when it is set.  
I set the handler inside. 
### ngx_http_json_status_module.h
```c
static char *ngx_http_json_status(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
```
### ngx_http_json_status_module.c
```c
static char *
ngx_http_json_status(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
  ngx_http_core_loc_conf_t  *clcf;

  clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
  clcf->handler = ngx_http_json_status_handler;

  return NGX_CONF_OK;
}
```

handler:ngx_http_json_status_handler
------------------------------------
status; But to be executed when a request comes in to the location that has been set.
### ngx_http_json_status_module.h
```c
static ngx_int_t ngx_http_json_status_handler(ngx_http_request_t *r);
```
### ngx_http_json_status_module.c
json until it returns an empty data in
```c
static ngx_int_t
ngx_http_json_status_handler(ngx_http_request_t *r)
{
  size_t       size;
  ngx_buf_t   *b;
  ngx_int_t    rc;
  ngx_chain_t  out;

  /* GET or HEAD only */
  if (r->method != NGX_HTTP_GET && r->method != NGX_HTTP_HEAD) {
    return NGX_HTTP_NOT_ALLOWED;
  }

  /* request bodyは不要なので破棄する */
  rc = ngx_http_discard_request_body(r);
  if (rc != NGX_OK) {
    return rc;
  }

  size = sizeof("{}");

  b = ngx_create_temp_buf(r->pool, size);
  if (b == NULL) {
    return NGX_HTTP_INTERNAL_SERVER_ERROR;
  }

  out.buf = b;
  out.next = NULL;

  b->last = ngx_sprintf(b->last, "{}");

  b->memory = 1;
  b->flush = 1;
  b->last_buf = 1;
  b->last_in_chain = 1;

  ngx_str_set(&r->headers_out.content_type, "application/json; charset=utf-8");
  r->headers_out.status = NGX_HTTP_OK;
  r->headers_out.content_length_n = b->last - b->pos;
  rc = ngx_http_send_header(r);
  if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
    return rc;
  }

  return ngx_http_output_filter(r, &out);
}
```

create main configuration
------------
I want to generate a structure for setting the main module.
### ngx_http_json_status_module.h
```c
struct  ngx_http_json_status_main_conf_s {
  char            hostname[NGX_MAXHOSTNAMELEN];
  u_char          addr[16]; /* xxx.xxx.xxx.xxx\0 */
};
...
static void *ngx_http_json_status_create_main_conf(ngx_conf_t *cf);
```
### ngx_http_json_status_module.c
* Specify the function that generates a structure to create_main_conf of ngx_http_json_status_module_ctx 
* Set it to get the ip address and hostname in ngx_http_json_status_create_main_conf
* Do not use init_main_conf this time, but I had been prepared once
```c
static ngx_http_module_t ngx_http_json_status_module_ctx = {
  NULL,                              /* preconfiguration */
  NULL,                              /* postconfiguration */

  ngx_http_json_status_create_main_conf, /* create main configuration */
  ngx_http_json_status_init_main_conf,   /* init main configuration */

  NULL,                              /* create server configuration */
  NULL,                              /* merge server configuration */

  NULL,                              /* create location configuration */
  NULL                               /* merge location configuration */
};
...
static void *
ngx_http_json_status_create_main_conf(ngx_conf_t *cf)
{
  ngx_http_json_status_main_conf_t *jsmcf;
  struct hostent *host;

  jsmcf = ngx_pcalloc(cf->pool, sizeof(ngx_http_json_status_main_conf_t));
  if (jsmcf == NULL) {
    return NULL;
  }

  if (gethostname(jsmcf->hostname, NGX_MAXHOSTNAMELEN) == -1) {
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "gethostname() failed");
    return NULL;
  }
  host = gethostbyname(jsmcf->hostname);
  if (host == NULL) {
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "gethostbyname() failed");
    return NULL;
  }
  ngx_sprintf(jsmcf->addr, "%d.%d.%d.%d",
	      (BYTE)*(host->h_addr),
	      (BYTE)*(host->h_addr + 1),
	      (BYTE)*(host->h_addr + 2),
	      (BYTE)*(host->h_addr + 3));

  return jsmcf;
}
static char *
ngx_http_json_status_init_main_conf(ngx_conf_t *cf, void *conf)
{
  return NGX_CONF_OK;
}
```
