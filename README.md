ngx_http_json_status_module
===========================

Specification
----
module to be returned in json format status of nginx

### Directives
```
syntax:	 status;
default: none;
context: location
```

### response
* Meaning of each element [Here](http://nginx.com/download/newrelic/newrelic_nginx_agent.tar.gz), want to see also
```json
{
    "version": "1",
    "nginx_version": "1.5.3",
    "address": "127.0.0.1",
    "timestamp": 1377263206961,
    "connections": {
        "accepted": 80399,
        "dropped": 0,
        "active": 1,
        "idle": 1
    },
    "requests": {
        "total": 80399,
        "current": 1
    },
    "upstreams":{
        "upstream_servers": [
            {
                "server": "127.0.0.1:1081",
                "state": "up",
                "weight": 1,
                "backup": false,
                "active": 0,
                "keepalive": 0,
                "requests": 470,
                "fails": 0,
                "unavail": 0,
                "downstart": 0,
                "sent": 78020,
                "received": 2350,
                "downtime": 0,
                "responses": {
                    "1xx": 0,
                    "2xx": 470,
                    "3xx": 0,
                    "4xx": 0,
                    "5xx": 0,
                    "total": 470
                },
                "health_checks": {
                    "checks": 0,
                    "fails": 0,
                    "unhealthy": 0
                }
            },
        ...
        ],
    }
}
```

Built-in
--------
```bash
./configure --add-module=./ngx_http_json_status_module
```

Setting Example
------
```
server {
  ...
  location = /status {
    status;
  }
}
```

Reference
----
* [module guide](http://www.evanmiller.org/nginx-modules-guide.html)
* [nginx plus](http://nginx.com/products/)
* [nginx plus tips](http://qiita.com/harukasan/items/5123f797a876696b343e)
* [nginx status](http://nginx.org/en/docs/http/ngx_http_status_module.html)
* [build nginx](BUILD.md)
* [開発手順](PROCEDUREofDEVELOPEMENT.md)
* [Development of modules for nginx](http://antoine.bonavita.free.fr/nginx_mod_dev_en.html)
