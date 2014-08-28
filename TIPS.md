nginx tips
==========

ngx_conf_log_error
------------------
There is need to build it with a --with-debug option if you want to use the NGX_LOG_DEBUG.
```c
ngx_conf_log_error(NGX_LOG_DEBUG, cf, 0, "test");
```

server status
-------------
```c
ngx_http_upstream_srv_conf_t *uscf   = ((ngx_http_upstream_srv_conf_t **)umcf->upstreams.elts)[i]; /* (*cf1) */
```
### The current state of
```c
ngx_http_upstream_rr_peers_t *peers  = uscf->peer.data;
```
### State of config
```c
ngx_http_upstream_server_t   *server = uscf->servers->elts;
```

backup server
-------------
server that you gave the backup is not stored in the `uscf->peer.data`.

weight
------
* ngx_http_upstream_rr_peer_t.current_weight  
I want to change dynamically during operation
* ngx_http_upstream_rr_peer_t.effective_weight  
?
* ngx_http_upstream_rr_peer_t.weight  
values ​​in the config

debug
-----
### No symbol table info available. Measures (Reference)[http://www.debian.or.jp/community/devel/debian-policy-ja/policy.ja.html/ch-source.html]
```bash
export DEB_BUILD_OPTIONS=noopt
debuild -us -uc
sudo dpkg -i nginx-debug_1.4.3-1~quantal_amd64.deb
sudo gdb /usr/sbin/nginx.debug /path/to/core
```
