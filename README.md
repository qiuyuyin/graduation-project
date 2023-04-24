本仓库Fork自MiniOB

毕业设计为在关系数据库上实现混合存储

之前设计的部分已经完成

现在还需要完成的内容：
- ~~实现列存中表的信息，即将数据写入到文件中~~
- ~~实现列存中表的读取~~
- ~~实现列存的同步过程~~
- ~~实现列存中表的写入，由于列ID都是不变的，所以在读取中会将之前存在的内容进行合并~~
- 实现列存中的多个RowSet的Compact
- 实现列存中的列存索引

```bash
# 运行：
cd build
cmake .. -DDEBUG=ON
make
bin/miniolap -f ../etc/olapserver.ini
# 新建shell
cd build
bin/observer -f ../etc/observer.ini
# 新建shell
cd build
bin/obclient
```

在obclient中输入正常的sql语句可以对OLTP进行修改
目前仅支持insert的同步，后续会增加update和delete的同步
在更改OLTP数据库之后，可以通过在obclient输入olap:select id from tablename;来查询列存中的数据