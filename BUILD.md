build nginx
===========

build & install
---------------
```bash
curl http://nginx.org/download/nginx-1.4.3.tar.gz | tar xvzf -
cd nginx-1.4.3
git clone git@github.com:psychobilly/ngx_http_json_status_module.git
./configure --add-module=./ngx_http_json_status_module
make && sudo make install
```

deb included in the package
-----------------------
```bash
cat /etc/issue.net
Ubuntu 12.10
cat /etc/apt/sources.list.d/nginx.list
deb http://nginx.org/packages/ubuntu/ quantal nginx
deb-src http://nginx.org/packages/ubuntu/ quantal nginx
wget -O - http://nginx.org/keys/nginx_signing.key | sudo apt-key add -
sudo apt-get update
# I keep one installed once because there are dependencies
sudo apt-get install nginx

cd /path/to/work
apt-get source nginx
rm nginx_1.4.3*
cd nginx-1.4.3
git clone git@github.com:psychobilly/ngx_http_json_status_module.git
diff debian/{rules.orig,rules}
54c54,55
<               --with-ipv6
---
>               --with-ipv6 \
>     --add-module=./ngx_http_json_status_module
92c93,94
<               --with-debug
---
>               --with-debug \
>     --add-module=./ngx_http_json_status_module

diff debian/source/{format.orig,format}
1c1
< 3.0 (quilt)
---
> 3.0 (native)

sudo apt-get -y install libssl-dev libpcre3-dev zlib1g-dev
debuild -us -uc && debclean
sudo dpkg -i ../nginx_1.4.3-1~quantalubuntu2_amd64.deb
```
