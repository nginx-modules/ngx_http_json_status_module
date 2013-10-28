nginx tips
==========

ngx_conf_log_error
------------------
NGX_LOG_DEBUGを使用する場合 --with-debug オプションを付けてbuildする必要あり。  
```c
ngx_conf_log_error(NGX_LOG_DEBUG, cf, 0, "test");
```

server status
-------------
```c
ngx_http_upstream_srv_conf_t *uscf   = ((ngx_http_upstream_srv_conf_t **)umcf->upstreams.elts)[i]; /* (*cf1) */
```
### 現在の状態
```c
ngx_http_upstream_rr_peers_t *peers  = uscf->peer.data;
```
### configの状態
```c
ngx_http_upstream_server_t   *server = uscf->servers->elts;
```

backup server
-------------
backupを付けたserverは uscf->peer.data に格納されない。  

weight
------
| ngx_http_upstream_rr_peer_t.current_weight | 稼働中に動的に変化する |
| ngx_http_upstream_rr_peer_t.effective_weight | ? |
| ngx_http_upstream_rr_peer_t.weight | configの値 |
